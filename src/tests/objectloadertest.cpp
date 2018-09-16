/*
 * Object Loader Test
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

#include "objectloadertest.h"

#include <QtSql/QtSql>

#include "fakebook.h"
#include "objectloader.h"
#include "testutils.h"

void ObjectLoaderTest::SetUpTestCase()
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

void ObjectLoaderTest::SetUp()
{
    FakeBook* b = new FakeBook;
    b->setAuthor("Matt Rogers");
    b->setYearPublished(2009);

    bool objectSaved = b->save();
    delete b;
    ASSERT_TRUE(objectSaved);

    b = new FakeBook;
    b->setAuthor("Not Matt Rogers");
    b->setYearPublished(1999);

    objectSaved = b->save();
    delete b;
    ASSERT_TRUE(objectSaved);
}

void ObjectLoaderTest::TearDown()
{
    QSqlDatabase db = QSqlDatabase::database("qtp-database");
    QSqlQuery query(db);
    query.exec("DELETE FROM fake_books");
    query.finish();
}

void ObjectLoaderTest::TearDownTestCase()
{
    QSqlDatabase::removeDatabase("qtp-database");
}

TEST_F(ObjectLoaderTest, testAll)
{
    QList<FakeBook*> objectList;
    objectList = ObjectLoader::all<FakeBook>();

    ASSERT_EQ(2, objectList.count());

    FakeBook* b = objectList.at(0);
    EXPECT_EQ(QString("Matt Rogers"), b->author());
    EXPECT_EQ(2009, b->yearPublished());

    b = objectList.at(1);
    ASSERT_EQ(QString("Not Matt Rogers"), b->author());
    ASSERT_EQ(1999, b->yearPublished());

    qDeleteAll(objectList);
    objectList.clear();
}
