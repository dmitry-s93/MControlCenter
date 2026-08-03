#ifndef MCONTROL_CENTER_AUTHORIZATION_H
#define MCONTROL_CENTER_AUTHORIZATION_H

#include <QtDBus/QDBusContext>
#include <QStringList>

// Interactive authorization is performed by the unprivileged client. The
// helper only performs a short, noninteractive independent check.
constexpr int FAN_AUTHORIZATION_TIMEOUT_MS = 60000;
constexpr int FAN_HELPER_AUTHORIZATION_TIMEOUT_MS = 3000;
constexpr int FAN_DBUS_TIMEOUT_MS = 10000;

[[nodiscard]] QStringList policyKitArgumentsForBusName(const QString &sender,
                                                        bool allowInteraction);

// Client-side preauthorization. The process is intentionally local to the UI;
// no helper event-loop call can display an authentication dialog.
[[nodiscard]] bool preauthorizeHardwareMutation();

// All mutating helper calls are root hardware operations. The caller's unique
// system-bus name is checked by PolicyKit; direct C++ calls are denied.
[[nodiscard]] bool authorizeHardwareMutation(const QDBusContext &context);

#endif // MCONTROL_CENTER_AUTHORIZATION_H
