/*
 * Copyright (C) 2014 Stuart Howarth <showarth@marxoft.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU Lesser General Public License,
 * version 3, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <QApplication>
#include <QStringList>
#include <QFileDialog>
#include <QDeclarativeEngine>
#include <QDeclarativeComponent>
#include <qdeclarative.h>
#include <QDebug>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setOrganizationName("QtComponentsHildon");
    app.setApplicationName(QObject::tr("Viewer"));
    
    QStringList args = app.arguments();
    QString qmlFile;
    
    if (args.size() > 1) {
        qmlFile = args.last();
    }
    
    if (qmlFile.isEmpty()) {
        qmlFile = QFileDialog::getOpenFileName(0, QObject::tr("Open QML file"), "/home/user/", QObject::tr("QML files (*.qml)"));
    }
    
    if (qmlFile.isEmpty()) {
        qWarning() << "No QML file specified. Exiting...";
        return 0;
    }

    QDeclarativeEngine engine;
    QDeclarativeComponent component(&engine, QUrl::fromLocalFile(qmlFile));
    component.create();

    if (component.isError()) {
        foreach (QDeclarativeError error, component.errors()) {
            qWarning() << error.toString();
        }

        return 0;
    }

    return app.exec();
}
