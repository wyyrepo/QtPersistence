/*
 * QtPersistence Test
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

#include "databaseconfigurationtest.h"
#include "testutils.h"
#include "databaseconfiguration_p.h"

#include <QtSql/QSqlDatabase>

void DatabaseConfigurationTest::TearDown()
{
    QSqlDatabase::removeDatabase("qtp-database");
}

TEST_P(DatabaseConfigurationTest, testUseDatabase)
{
    dbcTestData data = GetParam();
    DatabaseConfiguration* dbc = DatabaseConfiguration::self();
    bool configOk = dbc->configureDatabase(data.url);
    EXPECT_EQ(data.result, configOk);

    //QSqlDatabase db = QSqlDatabase::database("dbc-database", false [> open <]);
    //EXPECT_EQ(data.validity, db.isValid());

    EXPECT_EQ(data.system, dbc->databaseSystem());
    EXPECT_EQ(data.host, dbc->hostName());
    EXPECT_EQ(data.port, dbc->port());
    EXPECT_EQ(data.user, dbc->userName());
    EXPECT_EQ(data.database, dbc->databaseName());
}


dbcTestData databaseTestData[] = {
    { QUrl(), QString(), QString(), 0, QString(),
      QString(), QString(), false, false },
    { QUrl("sqlite://localhost/path/to/dbfile"), "QSQLITE",
      "localhost", 0, QString(), QString(), "/path/to/dbfile", true, true },
    { QUrl("mysql://mysql:mysql@localhost:1234/test1"), "QMYSQL", 
      "localhost", 1234, "mysql", "mysql", "test1", true, true },
    { QUrl("postgresql://pgsql:pgsql@localhost:5432"), "QPSQL",
      "localhost", 5432, "pgsql", "pgsql", QString(), true, true },
    { QUrl(), QString(), QString(), 0, QString(),
      QString(), QString(), false, false },
    };

INSTANTIATE_TEST_CASE_P(ConfigureDatabaseTest,
                        DatabaseConfigurationTest,
                        ::testing::ValuesIn(databaseTestData));


/* vim: set et sts=4 sw=4 ts=16 tw=78 : */

