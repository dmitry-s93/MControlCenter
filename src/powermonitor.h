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

#ifndef POWERMONITOR_H
#define POWERMONITOR_H

#include <QObject>

enum class PowerProfile {
    Performance,
    Balanced,
    Silent,
    PowerSaver,
    Unknown
};

class PowerMonitor : public QObject {
    Q_OBJECT
public:
    PowerMonitor();

    bool connectToUpower();
    bool connectToPowerProfiles();
    void disconnectFromUpower();
    void disconnectFromPowerProfiles();
    void queryChargerState();
    void queryPowerProfile();

    Q_ENUM(PowerProfile)

private:
    bool parseChargerState(uint state) const;
    PowerProfile parsePowerProfile(const QString &profile);

    bool isUPowerConnected = false;
    bool isPowerProfileConnected = false;

signals:
    void currentChargerState(bool isOnline);
    void currentPowerProfile(const PowerProfile profile);

private slots:
    void onChargerStateChanged(const QString &interface,
                               const QVariantMap &changedProps,
                               const QStringList &invalidatedProps);

    void onPowerProfileChanged(const QString &interface,
                               const QVariantMap &changed,
                               const QStringList &invalidatedProps);
};

#endif // POWERMONITOR_H
