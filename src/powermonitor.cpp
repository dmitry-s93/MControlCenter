/* Copyright (C) 2026 Dmitry Serov
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

#include "powermonitor.h"
#include <QDBusInterface>
#include <qdbusconnectioninterface.h>

PowerMonitor::PowerMonitor() = default;

bool PowerMonitor::connectToUpower() {
    if(isUPowerConnected) {
        return true;
    }

    auto bus = QDBusConnection::systemBus();

    if (!bus.interface()->isServiceRegistered("org.freedesktop.UPower")) {
        return false;
    }

    bool ok = bus.connect(
        "org.freedesktop.UPower",
        "/org/freedesktop/UPower/devices/DisplayDevice",
        "org.freedesktop.DBus.Properties",
        "PropertiesChanged",
        this,
        SLOT(onChargerStateChanged(QString,QVariantMap,QStringList))
        );
    isUPowerConnected = ok;
    return ok;
}

void PowerMonitor::disconnectFromUpower() {
    if(isUPowerConnected) {
        QDBusConnection::systemBus().disconnect(
            "org.freedesktop.UPower",
            "/org/freedesktop/UPower/devices/DisplayDevice",
            "org.freedesktop.DBus.Properties",
            "PropertiesChanged",
            this,
            SLOT(onChargerStateChanged(QString,QVariantMap,QStringList))
            );
        isUPowerConnected = false;
    }
}

void PowerMonitor::queryChargerState() {
    if (isUPowerConnected) {
        QDBusInterface iface(
            "org.freedesktop.UPower",
            "/org/freedesktop/UPower/devices/DisplayDevice",
            "org.freedesktop.DBus.Properties",
            QDBusConnection::systemBus()
            );

        QDBusReply<QVariant> reply =
            iface.call("Get", "org.freedesktop.UPower.Device", "State");

        if (!reply.isValid()) {
            return;
        }

        uint state = reply.value().toUInt();
        bool connected = parseChargerState(state);

        emit currentChargerState(connected);
    }
}

void PowerMonitor::onChargerStateChanged(
    const QString &interface,
    const QVariantMap &changedProps,
    const QStringList &invalidatedProps) {
    Q_UNUSED(invalidatedProps);

    if (interface != "org.freedesktop.UPower.Device")
        return;

    if (!changedProps.contains("State"))
        return;

    uint state = changedProps.value("State").toUInt();
    bool connected = parseChargerState(state);

    emit currentChargerState(connected);
}

bool PowerMonitor::parseChargerState(uint state) const {
    switch (state) {
        case 1: // Charging
        case 4: // Fully charged
        case 5: // Pending charge
            return true;

        case 2: // Discharging
        case 3: // Empty
        case 6: // Pending discharge
        default:
            return false;
    }
}

bool PowerMonitor::connectToPowerProfiles() {
    if (isPowerProfileConnected) {
        return true;
    }

    auto bus = QDBusConnection::systemBus();

    if (!bus.interface()->isServiceRegistered("net.hadess.PowerProfiles")) {
        return false;
    }

    bool ok = bus.connect(
        "net.hadess.PowerProfiles",
        "/org/freedesktop/UPower/PowerProfiles",
        "org.freedesktop.DBus.Properties",
        "PropertiesChanged",
        this,
        SLOT(onPowerProfileChanged(QString,QVariantMap,QStringList))
        );

    isPowerProfileConnected = ok;
    return ok;
}

void PowerMonitor::disconnectFromPowerProfiles() {
    if (isPowerProfileConnected) {
        QDBusConnection::systemBus().disconnect(
            "net.hadess.PowerProfiles",
            "/org/freedesktop/UPower/PowerProfiles",
            "org.freedesktop.DBus.Properties",
            "PropertiesChanged",
            this,
            SLOT(onPowerProfileChanged(QString,QVariantMap,QStringList))
            );
        isPowerProfileConnected = false;
    }
}

void PowerMonitor::queryPowerProfile() {
    if (isPowerProfileConnected) {
        QDBusInterface iface(
            "net.hadess.PowerProfiles",
            "/org/freedesktop/UPower/PowerProfiles",
            "org.freedesktop.DBus.Properties",
            QDBusConnection::systemBus()
            );

        QDBusReply<QVariant> reply =
            iface.call("Get", "org.freedesktop.UPower.PowerProfiles", "ActiveProfile");

        if (!reply.isValid()) {
            return;
        }

        const QString ProfileName = reply.value().toString();

        PowerProfile profile = parsePowerProfile(ProfileName);

        emit currentPowerProfile(profile);
    }
}

void PowerMonitor::onPowerProfileChanged(
    const QString &interface,
    const QVariantMap &changed,
    const QStringList &invalidatedProps) {
    Q_UNUSED(invalidatedProps);

    if (interface != "org.freedesktop.UPower.PowerProfiles")
        return;

    if (!changed.contains("ActiveProfile"))
        return;

    const QString ProfileName = changed.value("ActiveProfile").toString();

    PowerProfile profile = parsePowerProfile(ProfileName);

    emit currentPowerProfile(profile);
}

PowerProfile PowerMonitor::parsePowerProfile(const QString &profile) {
    if (profile == "performance")
        return PowerProfile::Performance;
    if (profile == "balanced")
        return PowerProfile::Balanced;
    if (profile == "power-saver")
        return PowerProfile::PowerSaver;
    return PowerProfile::Unknown;
}
