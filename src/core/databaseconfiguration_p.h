/*
 * Database Configuration for Qt Persistance
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

#ifndef DATABASECONFIGURATION_P_H
#define DATABASECONFIGURATION_P_H

#include <QtCore/QString>
#include <QtCore/QUrl>

class DatabaseConfiguration
{
public:
    virtual ~DatabaseConfiguration();

    static DatabaseConfiguration* self();

    bool configureDatabase(const QUrl& url);

    QString databaseSystem() const;
    QString hostName() const;
    QString userName() const;
    QString databaseName() const;
    int port() const;

private:
    DatabaseConfiguration();
    static DatabaseConfiguration* s_instance;

    QString m_databaseSystem;
    QString m_hostName;
    QString m_userName;
    QString m_databaseName;
    int m_port;

};



#endif
/* vim: set et sts=4 sw=4 ts=16 tw=78 : */

