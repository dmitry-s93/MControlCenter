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
#include "cli.h"
#include "options.h"

#include <QApplication>
#include <QTranslator>
#include <QLocalSocket>
#include <QLocalServer>


int main(int argc, char *argv[]) {

    Options options;
    options.process_args(argc, argv);

    const QString serverName = "MControlCenter";
    QLocalSocket* socket = new QLocalSocket();
    socket->connectToServer(serverName);

    if(options.cli){
        fprintf(stderr, "Executing CLI commands...\n");
        CLI cli;
        if(options.cooler_boost.has_value()){
            cli.setCoolerBoost(options.cooler_boost.value());
        }

        if (socket->isOpen()) {
            socket->write("update");
            socket->flush();
            socket->close();
        }
        socket->deleteLater();
        return 0;
    }

    if (socket->isOpen()) {
        fprintf(stderr, "Another instance of the application is already running\n");
        socket->write("show");
        socket->flush();
        socket->close();
        socket->deleteLater();
        return 0;
    }
    socket->deleteLater();

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

    QLocalServer server;
    QObject::connect(&server, &QLocalServer::newConnection, [&w, &server]() {
        QLocalSocket* socket = server.nextPendingConnection();
        if(socket->waitForConnected() && socket->waitForReadyRead()){
            QByteArray data = socket->readAll();
            if(std::strcmp(data.data(), "show") == 0){
                w.show();
            }
            else if(std::strcmp(data.data(), "update") == 0){
                w.externalUpdate();
            }
        }
    });
    bool serverListening = server.listen(serverName);
    if (!serverListening && (server.serverError() == QAbstractSocket::AddressInUseError)) {
        QLocalServer::removeServer(serverName);
        server.listen(serverName);
    }

    return QApplication::exec();
}
