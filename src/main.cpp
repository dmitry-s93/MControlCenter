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
#include <QApplication>
#include <QTranslator>
#include <QDBusConnectionInterface>

int main(int argc, char *argv[]) {
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
