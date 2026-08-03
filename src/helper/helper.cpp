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

#include "helper.h"
#include "msi-ec.h"
#include "readwrite.h"
#include "authorization.h"
#include <QCoreApplication>
#include <QDBusConnection>
#include <QDBusError>
#include <QProcess>

ReadWrite rw;

QByteArray Helper::getData() const {
    return rw.readFromFile();
}

bool Helper::isEcSysModuleLoaded() const {
    if (rw.isEcSys()) {
        return true;
    }
    if (rw.isAcpiEc()) {
        fprintf(stderr, "%s\n", qPrintable("The acpi_ec kernel module is loaded"));
        return true;
    }
    fprintf(stderr, "%s\n", qPrintable("The ec_sys kernel module is not loaded"));
    return false;
}

bool Helper::loadEcSysModule() const {
    if (!authorizeHardwareMutation(context.callContext())) {
        context.sendCallError(QDBusError::AccessDenied,
                              QStringLiteral("PolicyKit authorization required"));
        return false;
    }
    fprintf(stderr, "%s\n", qPrintable("Trying to load the ec_sys kernel module"));
    auto *process = new QProcess();
    // Raw EC writes are intentionally unavailable. Load ec_sys read-only so
    // diagnostics can continue without enabling any debugfs write support.
    process->start("/usr/sbin/modprobe", QStringList() << "ec_sys");
    process->waitForFinished(1000);
    if (QByteArray output = process->readAllStandardOutput(); output != "")
        fprintf(stderr, "%s", qPrintable(output));
    if (isEcSysModuleLoaded())
        return true;
    return false;
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    DBusContextObject obj;
    auto *helper = new Helper(obj);
    helper->setProperty("value", "initial value");
    QDBusConnection::systemBus().registerObject("/", &obj);

    DBusContextObject objMsiEc;
    auto *helperMsiEc = new MsiEc(objMsiEc);
    QDBusConnection::systemBus().registerObject("/msi_ec", &objMsiEc);

    if (!QDBusConnection::systemBus().registerService(SERVICE_NAME)) {
        fprintf(stderr, "%s\n", qPrintable(QDBusConnection::systemBus().lastError().message()));
        exit(1);
    }

    return QCoreApplication::exec();
}
