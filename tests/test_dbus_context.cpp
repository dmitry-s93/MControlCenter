#include "../src/helper/authorization.h"
#include "../src/helper/msi-ec.h"
#include "../src/helper/service.h"

#include <QCoreApplication>
#include <QDBusAbstractAdaptor>
#include <QDBusArgument>
#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusMessage>
#include <QDBusReply>
#include <QDir>
#include <QElapsedTimer>
#include <QFile>
#include <QMap>
#include <QProcess>
#include <QTemporaryDir>
#include <QTest>
#include <QTextStream>
#include <QTimer>

namespace {
const QString testService = QStringLiteral("org.mcontrolcenter.DBusContextTest");
const QString probeInterface = QStringLiteral("org.mcontrolcenter.DBusContextProbe");
bool authorizationGranted = true;

FanCurveProfile expectedProfile() {
    return {{55, 60, 70, 78, 85, 90},
            {0, 45, 60, 70, 75, 80, 80},
            {55, 60, 70, 80, 82, 87},
            {0, 55, 65, 70, 75, 80, 80}};
}

bool writeSysfsValue(const QString &path, const QString &value) {
    QFile file(path);
    const QByteArray data = (value + QLatin1Char('\n')).toUtf8();
    return file.open(QIODevice::WriteOnly) && file.write(data) == data.size();
}

bool initializeFakeFanCurveSysfs(const QString &root) {
    QDir dir(root);
    if (!dir.mkpath(QStringLiteral("cpu")) || !dir.mkpath(QStringLiteral("gpu")))
        return false;
    const QMap<QString, QString> capability{
        {QStringLiteral("fan_curve_supported"), QStringLiteral("1")},
        {QStringLiteral("fan_curve_threshold_count"), QStringLiteral("6")},
        {QStringLiteral("fan_curve_level_count"), QStringLiteral("7")},
        {QStringLiteral("fan_curve_threshold_min"), QStringLiteral("0")},
        {QStringLiteral("fan_curve_threshold_max"), QStringLiteral("100")},
        {QStringLiteral("fan_curve_level_min"), QStringLiteral("0")},
        {QStringLiteral("fan_curve_level_max"), QStringLiteral("150")},
        {QStringLiteral("fan_mode"), QStringLiteral("silent")},
    };
    for (auto it = capability.cbegin(); it != capability.cend(); ++it) {
        if (!writeSysfsValue(dir.filePath(it.key()), it.value()))
            return false;
    }
    const FanCurveProfile profile = expectedProfile();
    const auto writePoints = [&](const QString &fan, const QString &kind,
                                 const QVector<int> &values) {
        for (int index = 0; index < values.size(); ++index) {
            if (!writeSysfsValue(dir.filePath(
                    QStringLiteral("%1/fan_curve_%2_%3").arg(fan, kind).arg(index + 1)),
                    QString::number(values[index])))
                return false;
        }
        return true;
    };
    return writePoints(QStringLiteral("cpu"), QStringLiteral("threshold"), profile.cpuThresholds) &&
           writePoints(QStringLiteral("cpu"), QStringLiteral("level"), profile.cpuLevels) &&
           writePoints(QStringLiteral("gpu"), QStringLiteral("threshold"), profile.gpuThresholds) &&
           writePoints(QStringLiteral("gpu"), QStringLiteral("level"), profile.gpuLevels);
}

// This integration target deliberately substitutes a fake authorizer. It
// grants only when the production adaptor passes the registered object's live
// D-Bus context with a unique caller name. No PolicyKit service is contacted.
bool contextHasAuthenticatedCaller(const QDBusContext &context) {
    return context.calledFromDBus() && context.connection().isConnected() &&
           context.message().service().startsWith(QLatin1Char(':'));
}

class ContextProbe final : public QDBusAbstractAdaptor {
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.mcontrolcenter.DBusContextProbe")
public:
    ContextProbe(DBusContextObject &parent, QString modePath)
        : QDBusAbstractAdaptor(&parent), context(parent), modePath(std::move(modePath)) {}

public slots:
    [[nodiscard]] bool hasLiveContext() const {
        return contextHasAuthenticatedCaller(context.callContext());
    }

    [[nodiscard]] QString caller() const {
        const QDBusContext &call = context.callContext();
        return call.calledFromDBus() ? call.message().service() : QString();
    }

    [[nodiscard]] QString modeValue() const {
        QFile file(modePath);
        return file.open(QIODevice::ReadOnly)
                   ? QString::fromUtf8(file.readAll()).trimmed()
                   : QString();
    }

    bool setAuthorizationGranted(bool granted) const {
        authorizationGranted = granted;
        return true;
    }

    bool quit() const {
        QTimer::singleShot(0, QCoreApplication::instance(), &QCoreApplication::quit);
        return true;
    }

private:
    DBusContextObject &context;
    QString modePath;
};

int runServer(QCoreApplication &app) {
    QTemporaryDir sysfs;
    if (!sysfs.isValid())
        return 70;

    if (!initializeFakeFanCurveSysfs(sysfs.path()))
        return 71;
    const QString modePath = sysfs.filePath(QStringLiteral("fan_mode"));

    DBusContextObject probeObject;
    ContextProbe probe(probeObject, modePath);
    DBusContextObject msiEcObject;
    MsiEc msiEc(msiEcObject, sysfs.path());

    QDBusConnection bus = QDBusConnection::sessionBus();
    if (!bus.isConnected() ||
        !bus.registerObject(QStringLiteral("/context"), &probeObject) ||
        !bus.registerObject(QStringLiteral("/msi_ec"), &msiEcObject) ||
        !bus.registerService(testService)) {
        return 72;
    }

    QTextStream(stdout) << "READY\n" << Qt::flush;
    return app.exec();
}
}

// Link-time test double for src/helper/msi-ec.cpp. The production
// authorization.cpp is intentionally not part of this isolated target.
bool authorizeHardwareMutation(const QDBusContext &context) {
    return authorizationGranted && contextHasAuthenticatedCaller(context);
}

class DBusContextTest final : public QObject {
    Q_OBJECT
private slots:
    void initTestCase();
    void registeredObjectOwnsCallContext();
    void invalidArgumentReturnsErrorWithoutCrashing();
    void authorizationDenialReturnsErrorWithoutWritingOrCrashing();
    void validCallPassesRegisteredContextToAuthorizer();
    void fanProfileRoundTripsAcrossPrivateBus();
    void cleanupTestCase();

private:
    QProcess server;
};

void DBusContextTest::initTestCase() {
    server.setProcessChannelMode(QProcess::MergedChannels);
    server.start(QCoreApplication::applicationFilePath(), {QStringLiteral("--context-test-server")});
    QVERIFY2(server.waitForStarted(5000), qPrintable(server.errorString()));

    QByteArray output;
    QElapsedTimer timer;
    timer.start();
    while (!output.contains("READY\n") && timer.elapsed() < 5000) {
        if (server.waitForReadyRead(250))
            output += server.readAll();
        if (server.state() == QProcess::NotRunning)
            break;
    }
    QVERIFY2(output.contains("READY\n"), output.constData());
}

void DBusContextTest::registeredObjectOwnsCallContext() {
    QDBusInterface probe(testService, QStringLiteral("/context"), probeInterface,
                         QDBusConnection::sessionBus());
    QVERIFY(probe.isValid());

    const QDBusReply<bool> live = probe.call(QStringLiteral("hasLiveContext"));
    QVERIFY2(live.isValid(), qPrintable(live.error().message()));
    QVERIFY(live.value());

    const QDBusReply<QString> caller = probe.call(QStringLiteral("caller"));
    QVERIFY2(caller.isValid(), qPrintable(caller.error().message()));
    QCOMPARE(caller.value(), QDBusConnection::sessionBus().baseService());
}

void DBusContextTest::invalidArgumentReturnsErrorWithoutCrashing() {
    QDBusInterface msiEc(testService, QStringLiteral("/msi_ec"),
                         QStringLiteral(INTERFACE_NAME_MSI_EC),
                         QDBusConnection::sessionBus());
    QVERIFY(msiEc.isValid());

    const QDBusMessage reply = msiEc.call(QStringLiteral("setFanMode"),
                                          QStringLiteral("not-a-mode"));
    QCOMPARE(reply.type(), QDBusMessage::ErrorMessage);
    QCOMPARE(reply.errorName(), QStringLiteral("org.freedesktop.DBus.Error.InvalidArgs"));
    QVERIFY(server.state() == QProcess::Running);

    QDBusInterface probe(testService, QStringLiteral("/context"), probeInterface,
                         QDBusConnection::sessionBus());
    const QDBusReply<bool> stillAlive = probe.call(QStringLiteral("hasLiveContext"));
    QVERIFY2(stillAlive.isValid(), qPrintable(stillAlive.error().message()));
    QVERIFY(stillAlive.value());
}

void DBusContextTest::authorizationDenialReturnsErrorWithoutWritingOrCrashing() {
    QDBusInterface probe(testService, QStringLiteral("/context"), probeInterface,
                         QDBusConnection::sessionBus());
    QDBusReply<bool> configured = probe.call(QStringLiteral("setAuthorizationGranted"), false);
    QVERIFY2(configured.isValid() && configured.value(), qPrintable(configured.error().message()));

    QDBusInterface msiEc(testService, QStringLiteral("/msi_ec"),
                         QStringLiteral(INTERFACE_NAME_MSI_EC),
                         QDBusConnection::sessionBus());
    const QDBusMessage denied = msiEc.call(QStringLiteral("setFanMode"), QStringLiteral("auto"));
    QCOMPARE(denied.type(), QDBusMessage::ErrorMessage);
    QCOMPARE(denied.errorName(), QStringLiteral("org.freedesktop.DBus.Error.AccessDenied"));
    QVERIFY(server.state() == QProcess::Running);

    const QDBusReply<QString> unchanged = probe.call(QStringLiteral("modeValue"));
    QVERIFY2(unchanged.isValid(), qPrintable(unchanged.error().message()));
    QCOMPARE(unchanged.value(), QStringLiteral("silent"));

    configured = probe.call(QStringLiteral("setAuthorizationGranted"), true);
    QVERIFY2(configured.isValid() && configured.value(), qPrintable(configured.error().message()));
}

void DBusContextTest::validCallPassesRegisteredContextToAuthorizer() {
    QDBusInterface msiEc(testService, QStringLiteral("/msi_ec"),
                         QStringLiteral(INTERFACE_NAME_MSI_EC),
                         QDBusConnection::sessionBus());
    const QDBusReply<bool> applied = msiEc.call(QStringLiteral("setFanMode"),
                                                QStringLiteral("auto"));
    QVERIFY2(applied.isValid(), qPrintable(applied.error().message()));
    QVERIFY(applied.value());

    QDBusInterface probe(testService, QStringLiteral("/context"), probeInterface,
                         QDBusConnection::sessionBus());
    const QDBusReply<QString> mode = probe.call(QStringLiteral("modeValue"));
    QVERIFY2(mode.isValid(), qPrintable(mode.error().message()));
    QCOMPARE(mode.value(), QStringLiteral("auto"));
}

void DBusContextTest::fanProfileRoundTripsAcrossPrivateBus() {
    const QVariantMap localProfile = fanCurveProfileToMap(expectedProfile());
    FanCurveProfile localDecoded;
    QVERIFY(fanCurveProfileFromMap(localProfile, &localDecoded));
    QCOMPARE(localDecoded, expectedProfile());

    QDBusInterface msiEc(testService, QStringLiteral("/msi_ec"),
                         QStringLiteral(INTERFACE_NAME_MSI_EC),
                         QDBusConnection::sessionBus());
    QVERIFY(msiEc.isValid());

    const QDBusReply<QVariantMap> profileReply =
        msiEc.call(QStringLiteral("getFanCurveProfile"));
    QVERIFY2(profileReply.isValid(), qPrintable(profileReply.error().message()));
    const QVariantMap wireProfile = profileReply.value();
    QVERIFY(wireProfile.value(QStringLiteral("readable")).toBool());
    QVERIFY(wireProfile.value(QStringLiteral("valid")).toBool());
    for (const QString &key : {QStringLiteral("cpu_thresholds"),
                               QStringLiteral("cpu_levels"),
                               QStringLiteral("gpu_thresholds"),
                               QStringLiteral("gpu_levels")}) {
        const QVariant value = wireProfile.value(key);
        QVERIFY(value.metaType() == QMetaType::fromType<QDBusArgument>() ||
                value.canConvert<QVariantList>());
        if (value.metaType() == QMetaType::fromType<QDBusArgument>())
            QCOMPARE(qvariant_cast<QDBusArgument>(value).currentSignature(), QStringLiteral("av"));
    }

    FanCurveProfile decoded;
    QVERIFY(fanCurveProfileFromMap(wireProfile, &decoded));
    QCOMPARE(decoded, expectedProfile());

    const QDBusReply<QVariantMap> applyReply =
        msiEc.call(QStringLiteral("applyFanCurveTransaction"), fanCurveProfileToMap(decoded));
    QVERIFY2(applyReply.isValid(), qPrintable(applyReply.error().message()));
    const FanCurveResult result = fanCurveResultFromMap(applyReply.value());
    QVERIFY2(result.success, qPrintable(result.error));
    QCOMPARE(result.effectiveMode, QStringLiteral("advanced"));
    QCOMPARE(result.rollbackStatus, QStringLiteral("not-needed"));

    const QDBusReply<QVariantMap> readbackReply =
        msiEc.call(QStringLiteral("getFanCurveProfile"));
    QVERIFY2(readbackReply.isValid(), qPrintable(readbackReply.error().message()));
    FanCurveProfile readback;
    QVERIFY(fanCurveProfileFromMap(readbackReply.value(), &readback));
    QCOMPARE(readback, expectedProfile());

    const QDBusReply<bool> restored =
        msiEc.call(QStringLiteral("setFanMode"), QStringLiteral("auto"));
    QVERIFY2(restored.isValid(), qPrintable(restored.error().message()));
    QVERIFY(restored.value());
}

void DBusContextTest::cleanupTestCase() {
    if (server.state() == QProcess::NotRunning)
        return;
    QDBusInterface probe(testService, QStringLiteral("/context"), probeInterface,
                         QDBusConnection::sessionBus());
    const QDBusReply<bool> stopped = probe.call(QStringLiteral("quit"));
    QVERIFY2(stopped.isValid() && stopped.value(), qPrintable(stopped.error().message()));
    if (!server.waitForFinished(3000)) {
        server.terminate();
        QVERIFY(server.waitForFinished(3000));
    }
    QCOMPARE(server.exitStatus(), QProcess::NormalExit);
    QCOMPARE(server.exitCode(), 0);
}

int main(int argc, char **argv) {
    QCoreApplication app(argc, argv);
    if (app.arguments().contains(QStringLiteral("--context-test-server")))
        return runServer(app);

    DBusContextTest test;
    return QTest::qExec(&test, argc, argv);
}

#include "test_dbus_context.moc"
