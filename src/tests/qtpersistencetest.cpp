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

#include "qtpersistencetest.h"
#include "testutils.h"
#include "qtpersistence.h"

#include <QtSql/QSqlDatabase>


TEST_P(QtPersistenceTest, testUseDatabase)
{
    qtpTestData data = GetParam();
    EXPECT_EQ(data.result, QtPersistence::useDatabase(data.url));
    
    QSqlDatabase db = QSqlDatabase::database("qtp-database", false /* open */);
    EXPECT_EQ(data.validity, db.isValid());

}


qtpTestData testData[] = {
    { QUrl("sqlite://localhost/path/to/dbfile"), "QSQLITE",
      "localhost", 0, QString(), QString(), "/path/to/dbfile", true, true },
    { QUrl("mysql://mysql:mysql@localhost:1234/test1"), "QMYSQL", 
      "localhost", 1234, "mysql", "mysql", "test1", true, true },
    { QUrl("postgresql://pgsql:pgsql@localhost:5432"), "QPSQL",
      "localhost", 5432, "pgsql", "pgsql", QString(), true, true },
    { QUrl(), QString(), QString(), 0, QString(),
      QString(), QString(), false, false }
    };

INSTANTIATE_TEST_CASE_P(UseDatabaseTest,
                        QtPersistenceTest,
                        ::testing::ValuesIn(testData));


/* vim: set et sts=4 sw=4 ts=16 tw=78 : */

