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

#include "service.h"
#include "helper.h"
#include "readwrite.h"
#include <QCoreApplication>
#include <QDBusConnection>
#include <QDBusError>
#include <QProcess>
#include <QTimer>

std::vector<BYTE> ecData;

ReadWrite rw;

bool firstRun = true;

void Helper::quit()
{
    QTimer::singleShot(0, QCoreApplication::instance(), &QCoreApplication::quit);
}

bool Helper::updateData()
{
    if (firstRun) {
        firstRun = false;
        loadEcSysModule();
    }
    ecData = rw.readFileWithPos(0, 256);
    if (!ecData.empty())
        return true;
    return false;
}

bool Helper::empty()
{
    return ecData.empty();
}

QByteArray Helper::getValues(const int &address, const int &size)
{
    QByteArray out;
    for (BYTE c: rw.readFileWithPos(address, size)) {
        out.append(c);
    }
    return out;
}

int Helper::getValue(const int &address)
{
    if (ecData.size() < address + 1)
        return -1;
    return ecData[address];
}

void Helper::putValue(const int &address, const int &value)
{
    rw.writeToFile(address, value);
    updateData();
}

void Helper::loadEcSysModule()
{
    QProcess *myProcess = new QProcess();
    myProcess->start("sh", QStringList() << "-c" << "lsmod | grep ec_sys");
    myProcess->waitForFinished(1000);
    if (myProcess->readAllStandardOutput() == "") {
        fprintf(stderr, "%s\n", qPrintable("ec_sys module is not loaded. Trying to load"));
        myProcess->start("modprobe", QStringList() << "ec_sys write_support=1");
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
