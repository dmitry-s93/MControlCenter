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

#include "helper/service.h"
#include "helper.h"

#include <QCoreApplication>
#include <QDBusReply>

#include <stdio.h>

Helper::Helper()
{
    if (!QDBusConnection::systemBus().isConnected()) {
        fprintf(stderr, "Cannot connect to the D-Bus system bus");
        return;
    }
    iface = new QDBusInterface(SERVICE_NAME, "/", "org.MControlCenter", QDBusConnection::systemBus());
}

bool Helper::updateData()
{
    QDBusReply<bool> reply = iface->call("updateData");
    if (reply.isValid())
        return reply.value();
    printError(iface->lastError());
    return false;
}

int Helper::getValue(int address)
{
    QDBusReply<int> reply = iface->call("getValue", address);
    if (reply.isValid())
        return reply.value();
    printError(iface->lastError());
    return -1;
}

QByteArray Helper::getValues(int startAddress, int size)
{
    QDBusReply<QByteArray> reply = iface->call("getValues", startAddress, size);
    if (reply.isValid())
        return reply.value();
    printError(iface->lastError());
    return QByteArray();
}

void Helper::putValue(int address, int value)
{
    iface->call("putValue", address, value);
    printError(iface->lastError());
}

bool Helper::empty()
{
    QDBusReply<bool> reply = iface->call("empty");
    if (reply.isValid())
        return reply.value();
    printError(iface->lastError());
    return true;
}

void Helper::printError(QDBusError error)
{
    if (error.isValid())
        fprintf(stderr, "Call failed: %s\n", qPrintable(error.message()));
}
