#include "../src/fan_curve.h"
#include "../src/helper/fan-curve.h"
#include "../src/helper/authorization.h"
#include "../src/settings.h"
#include "../src/user_mode_policy.h"

#include <QtTest/QtTest>
#include <QDir>
#include <QFile>
#include <QStringList>
#include <QTemporaryDir>

class FakeBackend final : public FanCurveBackend {
public:
    FanCurveCapability cap{true, 6, 7, 0, 100, 0, 150, {}};
    FanCurveProfile profile{{10, 20, 30, 40, 50, 60}, {0, 20, 40, 60, 80, 100, 120},
                            {10, 20, 30, 40, 50, 60}, {0, 20, 40, 60, 80, 100, 120}};
    QString mode = QStringLiteral("advanced");
    int pointWrites = 0;
    int failPointWrite = -1;
    bool failPointAlways = false;
    bool failAdvanced = false;
    bool ignoreModeWrites = false;

    [[nodiscard]] FanCurveCapability capability() const override { return cap; }
    [[nodiscard]] bool readProfile(FanCurveProfile *result, QString *) const override {
        if (!result)
            return false;
        *result = profile;
        return true;
    }
    [[nodiscard]] QString readMode() const override { return mode; }
    bool writeMode(const QString &newMode, QString *error) override {
        if (newMode == QStringLiteral("advanced") && failAdvanced) {
            if (error)
                *error = QStringLiteral("injected activation failure");
            return false;
        }
        if (newMode != QStringLiteral("auto") && newMode != QStringLiteral("silent") &&
            newMode != QStringLiteral("basic") && newMode != QStringLiteral("advanced"))
            return false;
        if (!ignoreModeWrites)
            mode = newMode;
        return true;
    }
    bool writePoint(const QString &fan, const QString &kind, int index,
                    int value, QString *error) override {
        ++pointWrites;
        if (failPointWrite > 0 && pointWrites >= failPointWrite &&
            (failPointAlways || pointWrites == failPointWrite)) {
            if (error)
                *error = QStringLiteral("injected point failure");
            return false;
        }
        QVector<int> *values = nullptr;
        if (fan == QStringLiteral("cpu") && kind == QStringLiteral("threshold"))
            values = &profile.cpuThresholds;
        else if (fan == QStringLiteral("cpu") && kind == QStringLiteral("level"))
            values = &profile.cpuLevels;
        else if (fan == QStringLiteral("gpu") && kind == QStringLiteral("threshold"))
            values = &profile.gpuThresholds;
        else if (fan == QStringLiteral("gpu") && kind == QStringLiteral("level"))
            values = &profile.gpuLevels;
        if (!values || index < 1 || index > values->size())
            return false;
        (*values)[index - 1] = value;
        return true;
    }
};

static FanCurveProfile requestedProfile() {
    return {{15, 25, 35, 45, 55, 65}, {10, 20, 20, 40, 80, 100, 140},
            {15, 25, 35, 45, 55, 65}, {10, 20, 20, 40, 80, 100, 140}};
}

class FanCurveTest : public QObject {
    Q_OBJECT
private slots:
    void validatorBoundaries();
    void ignoredFanModeWriteReadbackMismatch();
    void readableMalformedDeviceCurveIsRepairable();
    void sysfsMalformedBaselineIsReadable();
    void capabilityAbsence();
    void successfulTransaction();
    void midWriteRollback();
    void rollbackFailureForcesAuto();
    void silentRollback();
    void activationFailureSafety();
    void malformedAdvancedRollbackStaysAuto();
    void firmwareMismatch();
    void malformedSettings();
    void savedUserModeParsing();
    void advancedModeOwnershipPolicy();
    void policyKitAuthorizationContract();
    void authorizationDeniesNonDbusCalls();
    void telemetryUnitContract();
};

void FanCurveTest::ignoredFanModeWriteReadbackMismatch() {
    FakeBackend backend;
    backend.ignoreModeWrites = true;
    QString error;
    QVERIFY(!writeFanModeVerified(backend, QStringLiteral("auto"), &error));
    QVERIFY(error.contains(QStringLiteral("readback")));
}

void FanCurveTest::validatorBoundaries() {
    FakeBackend backend;
    QVERIFY(validateFanCurve(backend.cap, requestedProfile()).isEmpty());
    FanCurveProfile invalid = requestedProfile();
    invalid.cpuThresholds[0] = -1;
    QVERIFY(!validateFanCurve(backend.cap, invalid).isEmpty());
    invalid = requestedProfile();
    invalid.cpuThresholds[1] = invalid.cpuThresholds[0];
    QVERIFY(!validateFanCurve(backend.cap, invalid).isEmpty());
    invalid = requestedProfile();
    invalid.cpuLevels[2] = invalid.cpuLevels[1] - 1;
    QVERIFY(!validateFanCurve(backend.cap, invalid).isEmpty());
}

void FanCurveTest::readableMalformedDeviceCurveIsRepairable() {
    FakeBackend backend;
    FanCurveProfile device = requestedProfile();
    device.cpuThresholds = {55, 65, 0, 0, 0, 0};
    device.cpuLevels[6] = 200;
    QVERIFY(!fanCurveProfileWithinRanges(backend.cap, device).isEmpty());
    QVERIFY(!validateFanCurve(backend.cap, device).isEmpty());
}

void FanCurveTest::sysfsMalformedBaselineIsReadable() {
    QTemporaryDir root;
    QVERIFY(root.isValid());
    const auto write = [](const QString &path, const QString &value) {
        QFile file(path);
        QVERIFY2(file.open(QIODevice::WriteOnly), qPrintable(path));
        QVERIFY(file.write(value.toUtf8()) == value.toUtf8().size());
    };
    write(root.filePath("fan_curve_supported"), "1\n");
    write(root.filePath("fan_curve_threshold_count"), "6\n");
    write(root.filePath("fan_curve_level_count"), "7\n");
    write(root.filePath("fan_curve_threshold_min"), "0\n");
    write(root.filePath("fan_curve_threshold_max"), "100\n");
    write(root.filePath("fan_curve_level_min"), "0\n");
    write(root.filePath("fan_curve_level_max"), "150\n");
    write(root.filePath("fan_mode"), "auto\n");
    QDir().mkpath(root.filePath("cpu"));
    QDir().mkpath(root.filePath("gpu"));
    const QVector<int> thresholds = {55, 65, 0, 0, 0, 0};
    const QVector<int> levels = {0, 20, 40, 60, 80, 100, 200};
    for (const QString &fan : {QStringLiteral("cpu"), QStringLiteral("gpu")}) {
        for (int i = 0; i < thresholds.size(); ++i)
            write(root.filePath(fan + QStringLiteral("/fan_curve_threshold_") + QString::number(i + 1)),
                  QString::number(thresholds[i]) + QLatin1Char('\n'));
        for (int i = 0; i < levels.size(); ++i)
            write(root.filePath(fan + QStringLiteral("/fan_curve_level_") + QString::number(i + 1)),
                  QString::number(levels[i]) + QLatin1Char('\n'));
    }
    SysfsFanCurveBackend backend(root.path());
    QVERIFY(backend.capability().complete());
    FanCurveProfile profile;
    QString error;
    QVERIFY(backend.readProfile(&profile, &error));
    QVERIFY(!fanCurveProfileWithinRanges(backend.capability(), profile).isEmpty());
    QVERIFY(!validateFanCurve(backend.capability(), profile).isEmpty());
    QVERIFY(QFile::remove(root.filePath("gpu/fan_curve_level_7")));
    QVERIFY(!backend.capability().complete());
}

void FanCurveTest::capabilityAbsence() {
    FakeBackend backend;
    backend.cap.supported = false;
    FanCurveTransaction transaction(backend);
    const FanCurveResult result = transaction.apply(requestedProfile());
    QVERIFY(!result.success);
    QCOMPARE(backend.pointWrites, 0);
}

void FanCurveTest::successfulTransaction() {
    FakeBackend backend;
    backend.mode = QStringLiteral("silent");
    FanCurveTransaction transaction(backend);
    const FanCurveResult result = transaction.apply(requestedProfile());
    QVERIFY(result.success);
    QCOMPARE(result.effectiveMode, QStringLiteral("advanced"));
    QCOMPARE(backend.mode, QStringLiteral("advanced"));
    QCOMPARE(backend.profile, requestedProfile());
}

void FanCurveTest::midWriteRollback() {
    FakeBackend backend;
    backend.mode = QStringLiteral("auto");
    backend.failPointWrite = 4;
    FanCurveTransaction transaction(backend);
    const FanCurveProfile snapshot = backend.profile;
    const FanCurveResult result = transaction.apply(requestedProfile());
    QVERIFY(!result.success);
    QCOMPARE(result.rollbackStatus, QStringLiteral("succeeded"));
    QCOMPARE(result.effectiveMode, QStringLiteral("auto"));
    QCOMPARE(backend.profile, snapshot);
}

void FanCurveTest::rollbackFailureForcesAuto() {
    FakeBackend backend;
    backend.mode = QStringLiteral("silent");
    backend.failPointWrite = 1;
    backend.failPointAlways = true;
    FanCurveTransaction transaction(backend);
    const FanCurveResult result = transaction.apply(requestedProfile());
    QVERIFY(!result.success);
    QCOMPARE(result.rollbackStatus, QStringLiteral("failed_auto"));
    QCOMPARE(result.effectiveMode, QStringLiteral("auto"));
    QCOMPARE(backend.mode, QStringLiteral("auto"));
}

void FanCurveTest::silentRollback() {
    FakeBackend backend;
    backend.mode = QStringLiteral("silent");
    backend.failPointWrite = 5;
    FanCurveTransaction transaction(backend);
    const FanCurveResult result = transaction.apply(requestedProfile());
    QVERIFY(!result.success);
    QCOMPARE(result.rollbackStatus, QStringLiteral("succeeded"));
    QCOMPARE(result.effectiveMode, QStringLiteral("silent"));
    QCOMPARE(backend.mode, QStringLiteral("silent"));
}

void FanCurveTest::malformedAdvancedRollbackStaysAuto() {
    FakeBackend backend;
    backend.mode = QStringLiteral("advanced");
    backend.profile.cpuThresholds = {55, 65, 0, 0, 0, 0};
    backend.failPointWrite = 4;
    FanCurveTransaction transaction(backend);
    const FanCurveResult result = transaction.apply(requestedProfile());
    QVERIFY(!result.success);
    QCOMPARE(result.rollbackStatus, QStringLiteral("succeeded"));
    QCOMPARE(result.effectiveMode, QStringLiteral("auto"));
    QCOMPARE(backend.mode, QStringLiteral("auto"));
}

void FanCurveTest::activationFailureSafety() {
    FakeBackend backend;
    backend.mode = QStringLiteral("silent");
    backend.failAdvanced = true;
    FanCurveTransaction transaction(backend);
    const FanCurveResult result = transaction.apply(requestedProfile());
    QVERIFY(!result.success);
    QCOMPARE(result.rollbackStatus, QStringLiteral("succeeded"));
    QCOMPARE(result.effectiveMode, QStringLiteral("silent"));
    QCOMPARE(backend.mode, QStringLiteral("silent"));
}

void FanCurveTest::firmwareMismatch() {
    QVERIFY(fanCurveFirmwareMatches(QStringLiteral("15CKEMS1.108"), QStringLiteral("2026-01-01"),
                                     QStringLiteral("15CKEMS1.108"), QStringLiteral("2026-01-01")));
    QVERIFY(!fanCurveFirmwareMatches(QStringLiteral("15CKEMS1.108"), QStringLiteral("2026-01-01"),
                                     QStringLiteral("15CKEMS1.109"), QStringLiteral("2026-01-01")));
    QVERIFY(!fanCurveFirmwareMatches({}, {}, QStringLiteral("15CKEMS1.108"), QStringLiteral("2026-01-01")));
}

void FanCurveTest::telemetryUnitContract() {
    QFile source(QStringLiteral(FAN_SOURCE_DIR "/src/mainwindow.cpp"));
    QVERIFY(source.open(QIODevice::ReadOnly));
    const QString text = QString::fromUtf8(source.readAll());
    QVERIFY2(!text.contains(QStringLiteral("getCPURealtimeFanSpeed")),
             "driver fan-level telemetry must not be displayed as RPM");
    QVERIFY2(!text.contains(QStringLiteral("getGPURealtimeFanSpeed")),
             "driver fan-level telemetry must not be displayed as RPM");
}

void FanCurveTest::policyKitAuthorizationContract() {
    const QStringList interactiveArgs = policyKitArgumentsForBusName(QStringLiteral(":1.42"), true);
    QCOMPARE(interactiveArgs, QStringList({QStringLiteral("--action-id"),
                                            QStringLiteral("org.mcontrolcenter.fan-control"),
                                            QStringLiteral("--system-bus-name"), QStringLiteral(":1.42"),
                                            QStringLiteral("--allow-user-interaction")}));
    const QStringList helperArgs = policyKitArgumentsForBusName(QStringLiteral(":1.42"), false);
    QCOMPARE(helperArgs, QStringList({QStringLiteral("--action-id"),
                                      QStringLiteral("org.mcontrolcenter.fan-control"),
                                      QStringLiteral("--system-bus-name"), QStringLiteral(":1.42")}));
    QVERIFY(!helperArgs.contains(QStringLiteral("--allow-user-interaction")));
    QCOMPARE(FAN_AUTHORIZATION_TIMEOUT_MS, 60000);
    QCOMPARE(FAN_HELPER_AUTHORIZATION_TIMEOUT_MS, 3000);
    QVERIFY(FAN_DBUS_TIMEOUT_MS > FAN_HELPER_AUTHORIZATION_TIMEOUT_MS);
}

void FanCurveTest::authorizationDeniesNonDbusCalls() {
    QDBusContext context;
    QVERIFY(!context.calledFromDBus());
    QVERIFY(!authorizeHardwareMutation(context));
}

void FanCurveTest::malformedSettings() {
    bool ok = true;
    QVERIFY(Settings::parseValueVector(QStringLiteral("10|bad|30"), &ok).isEmpty());
    QVERIFY(!ok);
    ok = false;
    QCOMPARE(Settings::parseValueVector(QStringLiteral("10|20|30"), &ok), QVector<int>({10, 20, 30}));
    QVERIFY(ok);
}

void FanCurveTest::savedUserModeParsing() {
    const auto verifyMode = [](const QString &value, user_mode expected) {
        const auto parsed = parseSavedUserMode(value);
        QVERIFY(parsed.has_value());
        QCOMPARE(static_cast<int>(*parsed), static_cast<int>(expected));
    };
    verifyMode(QStringLiteral("balanced_mode"), user_mode::balanced_mode);
    verifyMode(QStringLiteral("performance_mode"), user_mode::performance_mode);
    verifyMode(QStringLiteral("silent_mode"), user_mode::silent_mode);
    verifyMode(QStringLiteral("super_battery_mode"), user_mode::super_battery_mode);

    for (const QString &invalid : {QString(), QStringLiteral("unknown_mode"),
                                   QStringLiteral("advanced"), QStringLiteral(" balanced_mode"),
                                   QStringLiteral("Balanced_mode")})
        QVERIFY(!parseSavedUserMode(invalid).has_value());
}

void FanCurveTest::advancedModeOwnershipPolicy() {
    QVERIFY(userModeMayOwnAdvanced(user_mode::balanced_mode));
    QVERIFY(userModeMayOwnAdvanced(user_mode::performance_mode));
    QVERIFY(!userModeMayOwnAdvanced(user_mode::silent_mode));
    QVERIFY(!userModeMayOwnAdvanced(user_mode::super_battery_mode));
    QVERIFY(!userModeMayOwnAdvanced(user_mode::unknown_mode));
}

QTEST_MAIN(FanCurveTest)
#include "test_fan_curve.moc"
