/*
 * Object Loader
 *
 * Copyright 2009 Matt Rogers <mattr@kde.org>
 *
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 3 as published by the Free Software Foundation.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software; see the file COPYING.LGPL. If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef OBJECTLOADER_H
#define OBJECTLOADER_H

#include <QtSql/QtSql>

#include "introspection.h"
#include "inflection.h"


class ObjectLoader
{
public:
    ObjectLoader() {}
    ~ObjectLoader() {}

    template <typename T>
    static QList<T*> all();
};

template <typename T>
QList<T*> ObjectLoader::all()
{
    const QMetaObject o  = T::staticMetaObject;
    QString queryString = "SELECT ";

    QStringList propertyList;
    for (int i = 0; i < o.propertyCount(); ++i) {
        QMetaProperty property = o.property(i);
        QString propertyName = QString::fromLatin1(property.name());
        if (propertyName == "objectName") {
            continue;
        }
        propertyList.append(propertyName);
        queryString += Utils::snakeCase(propertyName);
        queryString += ", ";
    }

    queryString.chop(2);
    queryString += " FROM ";
    queryString += Utils::tableize(QString(o.className()));

    QSqlDatabase db = QSqlDatabase::database("qtp-database");
    QSqlQuery q(db);

    QList<T*> objectList;

    q.exec(queryString);
    while (q.next())
    {
        QSqlRecord record = q.record();
        T* object = new T;
        Q_FOREACH(const QString& prop, propertyList) {
            object->setProperty(prop.toLatin1().constData(),
                                record.value(Utils::snakeCase(prop)));
        }

        objectList.append(object);
    }


    return objectList;
}

#endif
/* vim: set et sts=4 sw=4 ts=16 tw=78 : */

