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
#include "readwrite.h"
#include <QCoreApplication>
#include <QDBusConnection>
#include <QDBusError>
#include <QProcess>
#include <QTimer>

ReadWrite rw;

void Helper::quit()
{
    QTimer::singleShot(0, QCoreApplication::instance(), &QCoreApplication::quit);
}

QByteArray Helper::getData()
{
    return rw.readFromFile();
}

void Helper::putValue(const int &address, const int &value)
{
    rw.writeToFile(address, value);
}

void Helper::loadEcSysModule()
{
    QProcess *process = new QProcess();
    process->start("sh", QStringList() << "-c" << "lsmod | grep ec_sys");
    process->waitForFinished(1000);
    if (process->readAllStandardOutput() == "") {
        fprintf(stderr, "%s\n", qPrintable("ec_sys module is not loaded. Trying to load"));
        process->start("sh", QStringList() << "-c" << "modprobe ec_sys write_support=1 2>&1");
        process->waitForFinished(1000);
        QByteArray output = process->readAllStandardOutput();
        if (output != "")
            fprintf(stderr, "%s", qPrintable(output));
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QObject obj;
    Helper *helper = new Helper(&obj);
    QObject::connect(&a, &QCoreApplication::aboutToQuit, helper, &Helper::aboutToQuit);
    helper->setProperty("value", "initial value");
    QDBusConnection::systemBus().registerObject("/", &obj);

    if (!QDBusConnection::systemBus().registerService(SERVICE_NAME)) {
        fprintf(stderr, "%s\n", qPrintable(QDBusConnection::systemBus().lastError().message()));
        exit(1);
    }

    return a.exec();
}
