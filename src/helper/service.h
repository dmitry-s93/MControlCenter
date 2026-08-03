/* Copyright (C) 2022  Dmitry Serov
 *
 * This file is part of MControlCenter.
 *
 * MControlCenter is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * MControlCenter is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with MControlCenter. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef MCONTROL_CENTER_SERVICE_H
#define MCONTROL_CENTER_SERVICE_H

#include <QObject>
#include <QtDBus/QDBusContext>
#include <QtDBus/QDBusError>

#define SERVICE_NAME "mcontrolcenter.helper"
#define INTERFACE_NAME "dmitry_s93.MControlCenter"
#define INTERFACE_NAME_MSI_EC "BeardOverflow.msi_ec"

// Qt attaches QDBusContext to the QObject registered with registerObject(),
// not to a QDBusAbstractAdaptor attached to that object. Adaptors must use
// this registered owner's context for caller identity and error replies.
class DBusContextObject final : public QObject, protected QDBusContext {
    Q_OBJECT
public:
    explicit DBusContextObject(QObject *parent = nullptr) : QObject(parent) {}

    [[nodiscard]] const QDBusContext &callContext() const noexcept { return *this; }

    bool sendCallError(QDBusError::ErrorType type, const QString &message) const {
        if (!calledFromDBus())
            return false;
        sendErrorReply(type, message);
        return true;
    }
};

#endif // MCONTROL_CENTER_SERVICE_H
