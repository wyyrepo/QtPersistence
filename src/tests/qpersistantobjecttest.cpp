/*
 * QPersistantObject Test
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

#include "qpersistantobjecttest.h"

#include "fakebook.h"
#include <QtSql/QtSql>

void QPersistantObjectTest::SetUpTestCase()
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

void QPersistantObjectTest::TearDownTestCase()
{
    QSqlDatabase::removeDatabase("qtp-database");
}

void QPersistantObjectTest::TearDown()
{
    QSqlDatabase db = QSqlDatabase::database("qtp-database");
    db.exec("DELETE FROM fake_books");
}


TEST_F(QPersistantObjectTest, testIsSaved)
{
    FakeBook* b = new FakeBook;
    b->setYearPublished(2010);
    b->setAuthor("Matt Rogers");

    ASSERT_TRUE(b->save());
    EXPECT_TRUE(b->isSaved());
    EXPECT_GT(b->id(), 0);

    int currentId = b->id();

    EXPECT_TRUE(b->save());
    EXPECT_EQ(currentId, b->id());

    delete b;
}


/* vim: set et sts=4 sw=4 ts=16 tw=78 : */
