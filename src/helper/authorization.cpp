#include "authorization.h"

#include <QDBusConnection>
#include <QDBusMessage>
#include <QProcess>

namespace {
bool runPolicyKitCheck(const QStringList &arguments, int timeoutMs) {
    QProcess check;
    check.start(QStringLiteral("/usr/bin/pkcheck"), arguments);
    if (!check.waitForFinished(timeoutMs)) {
        check.kill();
        check.waitForFinished(100);
        return false;
    }
    return check.exitStatus() == QProcess::NormalExit && check.exitCode() == 0;
}
}

QStringList policyKitArgumentsForBusName(const QString &sender, bool allowInteraction) {
    QStringList args{QStringLiteral("--action-id"),
                     QStringLiteral("org.mcontrolcenter.fan-control"),
                     QStringLiteral("--system-bus-name"), sender};
    if (allowInteraction)
        args.append(QStringLiteral("--allow-user-interaction"));
    return args;
}

bool preauthorizeHardwareMutation() {
    const QDBusConnection bus = QDBusConnection::systemBus();
    const QString sender = bus.baseService();
    if (!bus.isConnected() || sender.isEmpty())
        return false;
    return runPolicyKitCheck(policyKitArgumentsForBusName(sender, true),
                             FAN_AUTHORIZATION_TIMEOUT_MS);
}

bool authorizeHardwareMutation(const QDBusContext &context) {
    // Direct C++ calls have no authenticated caller. They must not silently
    // become a root write; transaction tests use a fake backend directly.
    if (!context.calledFromDBus())
        return false;

    // Qt exposes the authenticated incoming unique bus name as service() on
    // the QDBusContext message (QDBusMessage has no sender() accessor).
    const QString sender = context.message().service();
    if (!context.connection().isConnected() || sender.isEmpty())
        return false;

    // The helper check is deliberately noninteractive and short. The client
    // must have completed any user interaction before invoking this method.
    return runPolicyKitCheck(policyKitArgumentsForBusName(sender, false),
                             FAN_HELPER_AUTHORIZATION_TIMEOUT_MS);
}
