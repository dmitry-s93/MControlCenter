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

#include "mainwindow.h"
#include "operate.h"
#include <QApplication>
#include <QTranslator>
#include <QDBusConnectionInterface>
#include <iostream>

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "--test") == 0) {
        QCoreApplication a(argc, argv);
        Operate op;
        op.doProbe();
        op.updateEcData(); // Synchronous update
        
        std::cout << "--- MControlCenter Test Stats ---" << std::endl;
        std::cout << "msi-ec loaded: " << op.isMsiEcLoaded() << std::endl;
        std::cout << "ec_sys loaded: " << op.isEcSysModuleLoaded() << std::endl;
        std::cout << "CPU Temp: " << op.getCpuTemp() << " C" << std::endl;
        auto gpuTemp = op.getGpuTemp();
        std::cout << "GPU Temp: " << (gpuTemp.has_value() ? gpuTemp.value() : -1) << " C" << std::endl;
        std::cout << "Fan 1 Speed: " << op.getFan1Speed() << " RPM" << std::endl;
        auto fan2 = op.getFan2Speed();
        std::cout << "Fan 2 Speed: " << (fan2.has_value() ? fan2.value() : -1) << " RPM" << std::endl;
        std::cout << "Battery Charge: " << op.getBatteryCharge() << "%" << std::endl;
        std::cout << "Webcam active: " << op.getWebCamState() << std::endl;
        return 0;
    }

    const QString serviceName = "io.github.dmitry_s93.MControlCenter";

    if (QDBusConnection::sessionBus().interface()->isServiceRegistered(serviceName)) {
        fprintf(stderr, "Another instance of the application is already running\n");
        return 0;
    }

    if (!QDBusConnection::sessionBus().registerService(serviceName)) {
        fprintf(stderr, "Failed to register D-Bus service\n");
        return 1;
    }

    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale: uiLanguages) {
        const QString baseName = "lang_" + QLocale(locale).name();
        if (translator.load(":/translations/" + baseName)) {
            QApplication::installTranslator(&translator);
            break;
        }
    }

    MainWindow w;

    return QApplication::exec();
}
