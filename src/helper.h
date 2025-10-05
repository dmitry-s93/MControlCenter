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

#ifndef HELPER_H
#define HELPER_H

#include <QtCore/QObject>
#include <QtDBus/QDBusInterface>

using BYTE = unsigned char;

class Helper : public QObject {
Q_OBJECT
public:
    Helper();

    bool isEcSysModuleLoaded();
    bool loadEcSysModule();
    bool updateData();
    void updateDataAsync();
    std::optional<int> getOptionalValue(int address) const;
    int getValue(int address) const;
    QByteArray getValues(int startAddress, int size) const;
    void putValue(int address, int value);
    void quit();
    QDBusInterface *iface;
private:
    void printError(QDBusError const & error) const;
private slots:
    void callFinishedSlot(QDBusPendingCallWatcher *call);
};

#endif // HELPER_H
