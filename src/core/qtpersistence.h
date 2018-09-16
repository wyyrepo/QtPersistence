/*
 * QtPersistence
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

#ifndef QTPERSISTENCE_H
#define QTPERSISTENCE_H

#include <QtCore/QString>
#include <QtCore/QList>

class QPersistantObject;

class QUrl;

namespace QtPersistence
{
    /**
     * Set up a specific database to use for the persistence layer
     *
     * Urls should be of the form:
     * \code
     * databaseSystem://user:pass@host.name/databaseName
     * \endcode
     *
     * For SQLite, to use an in-memory database, use ":memory:" as the
     * database name.
     */
    bool useDatabase(const QUrl& databaseUrl);

    template<typename T>
    static QList<QPersistantObject*> all()
    {
        return QList<QPersistantObject*>();
    }

};

#endif
/* vim: set et sts=4 sw=4 ts=16 tw=78 : */

