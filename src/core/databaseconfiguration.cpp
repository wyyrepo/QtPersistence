/*
 * Database Configuration
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

#include "databaseconfiguration_p.h"

#include <QtSql/QtSql>

DatabaseConfiguration* DatabaseConfiguration::s_instance = 0;

DatabaseConfiguration::DatabaseConfiguration()
    : m_port(0)
{
}

DatabaseConfiguration::~DatabaseConfiguration()
{

}


DatabaseConfiguration* DatabaseConfiguration::self()
{
    if (!s_instance) {
        s_instance = new DatabaseConfiguration;
    }

    return s_instance;
}

bool DatabaseConfiguration::configureDatabase(const QUrl& url)
{
    if (!url.isValid()) {
        m_port = 0;
        m_userName = QString();
        m_databaseSystem = QString();
        m_databaseName = QString();
        m_hostName = QString();
        QSqlDatabase::removeDatabase("qtp-database");
        return false;
    }

    m_hostName = url.host();
    if (url.port() > 0) {
        m_port = url.port();
    }
    m_userName = url.userName();
    QString password = url.password();
    m_databaseName = url.path();

    QString scheme = url.scheme();
    if (scheme == "mysql") {
        m_databaseSystem = "QMYSQL";
        m_databaseName = m_databaseName.remove(0,1);
    }

    if (scheme == "postgresql") {
        m_databaseSystem = "QPSQL";
        m_databaseName = m_databaseName.remove(0,1);
    }

    if (scheme == "sqlite") {
        m_databaseSystem = "QSQLITE";
    }

    QSqlDatabase db = QSqlDatabase::addDatabase(m_databaseSystem, "qtp-database");
    db.setPassword(password);
    db.setUserName(m_userName);
    db.setHostName(m_hostName);
    db.setPort(m_port);
    db.setDatabaseName(m_databaseName);

    return true;
}

QString DatabaseConfiguration::databaseSystem() const
{
    return m_databaseSystem;
}

QString DatabaseConfiguration::hostName() const
{
    return m_hostName;
}

QString DatabaseConfiguration::userName() const
{
    return m_userName;
}

QString DatabaseConfiguration::databaseName() const
{
    return m_databaseName;
}

int DatabaseConfiguration::port() const
{
    return m_port;
}
