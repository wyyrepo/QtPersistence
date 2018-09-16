/*
 * NewObjectSaveState Test
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


#include "newobjectsavestatetest.h"

#include <QtSql/QtSql>
#include <QtCore/QDebug>

#include "newobjectsavestate.h"

#include "fakebook.h"
#include "testutils.h"


void NewObjectSaveStateTest::SetUpTestCase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "qtp-database");
    db.setDatabaseName(":memory:");
    db.open();
    QSqlQuery q(db);
    q.exec ("CREATE TABLE fake_books ("
            " id INTEGER PRIMARY KEY AUTOINCREMENT,"
            " author TEXT,"
            " year_published INTEGER "
            ");");
    q.finish();
}

void NewObjectSaveStateTest::TearDownTestCase()
{
    QSqlDatabase::removeDatabase("qtp-database");
}



TEST_F(NewObjectSaveStateTest, testSave)
{
    QSqlDatabase db = QSqlDatabase::database("qtp-database");
    FakeBook* b = new FakeBook;
    b->setAuthor("Matt Rogers");
    b->setYearPublished(2010);

    NewObjectSaveState noss;
    bool saveSuccessful = noss.save(b);
    EXPECT_TRUE(saveSuccessful);

    QSqlQuery query(db);
    bool fetchSuccess = query.exec("SELECT author, year_published FROM fake_books");
    ASSERT_TRUE(fetchSuccess) << "Unable to check values from DB";

    query.first();
    QString author = query.value(0).toString();
    int year = query.value(1).toInt();
    EXPECT_EQ(b->author(), author);
    EXPECT_EQ(b->yearPublished(), year);
    query.finish();
    delete b;
}

TEST_F(NewObjectSaveStateTest, testNonSave)
{
    QSqlDatabase db = QSqlDatabase::database("qtp-database");
    db.close();

    FakeBook* b = new FakeBook;
    b->setAuthor("Matt Rogers");
    b->setYearPublished(2010);

    NewObjectSaveState noss;
    bool saveSuccessful = noss.save(b);
    EXPECT_FALSE(saveSuccessful);

    db.close();
    QSqlDatabase::removeDatabase("qtp-database");
    saveSuccessful = noss.save(b);
    EXPECT_FALSE(saveSuccessful);

    delete b;
}

/* vim: set et sts=4 sw=4 ts=16 tw=78 : */
