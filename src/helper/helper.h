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

#include "service.h"

#include <QtCore/QObject>
#include <QtDBus/QDBusAbstractAdaptor>
#include <QtDBus/QDBusVariant>

typedef unsigned char BYTE;

class Helper: public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", INTERFACE_NAME)
public:
    Helper(QObject *obj) : QDBusAbstractAdaptor(obj) {}
signals:
    void aboutToQuit();
public slots:
    Q_NOREPLY void quit();
    QByteArray getData();
    Q_NOREPLY void putValue(const int &address, const int &value);
    bool isEcSysModuleLoaded();
    bool loadEcSysModule();
private:    
};

#endif // HELPER_H
