/*
 * New Object Save State
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

#include "newobjectsavestate.h"

#include <QtSql/QtSql>

#include "introspection.h"
#include "qpersistantobject.h"
#include "inflection.h"

NewObjectSaveState::~NewObjectSaveState()
{

}

bool NewObjectSaveState::save(QPersistantObject* o)
{
    QSqlDatabase db = QSqlDatabase::database("qtp-database");
    if (!db.isOpen()) {
        return false;
    }

    QString tableName = tableNameForObject(o);
    QList<QString> pList = propertyListForObject(o);
    QVariantHash propertyValues = propertyValuesForObject(o);

    QString queryString = QString("INSERT INTO %1 ").arg(tableName);
    queryString += "(";
    Q_FOREACH(const QString& property, pList) {
        queryString += Utils::snakeCase(property);
        queryString += ", ";
    }

    queryString.chop(2);

    queryString += ") VALUES (";
    for (int i = 0; i < pList.count(); i++) {
        queryString += "?, ";
        if (i == pList.count() - 1) {
            queryString.chop(2);
        }
    }
    queryString += ");";

    QSqlQuery query(db);
    query.prepare(queryString);

    Q_FOREACH(const QString& property, pList) {
        query.addBindValue(propertyValues.value(property));
    }

    bool querySuccessful = query.exec();
    if (!querySuccessful) {
        qWarning() << "Query unsuccessful! Object not saved\n"
                   << query.lastQuery() << "\n"
                   << query.lastError().text();
    }
    else
    {
        o->setId(query.lastInsertId().toInt());
        query.finish();
    }


    return querySuccessful;
}
