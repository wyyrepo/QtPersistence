/*
 * Existing Object Save State Test
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

#include "existingobjectsavestatetest.h"

#include <QtSql/QtSql>

#include "fakebook.h"
#include "testutils.h"
#include "newobjectsavestate.h"
#include "existingobjectsavestate.h"

FakeBook* ExistingObjectSaveStateTest::fake_book = NULL;

void ExistingObjectSaveStateTest::SetUpTestCase()
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

    fake_book = new FakeBook;
    NewObjectSaveState noss;
    noss.save(fake_book);
    q.exec("SELECT id FROM fake_books");
    q.first();
    fake_book->setId(q.value(0).toInt());
    q.finish();
}

void ExistingObjectSaveStateTest::TearDownTestCase()
{
    delete fake_book;
}

TEST_F(ExistingObjectSaveStateTest, testSave)
{
    QSqlDatabase db = QSqlDatabase::database("qtp-database");

    fake_book->setAuthor("Not Matt Rogers");
    fake_book->setYearPublished(1999);

    ExistingObjectSaveState eoss;
    bool saveSuccessful = eoss.save(fake_book);
    EXPECT_TRUE(saveSuccessful);

    QSqlQuery query(db);
    query.prepare("SELECT author, year_published FROM fake_books WHERE id = ?");
    query.addBindValue(fake_book->id());
    bool fetchSuccess = query.exec();
    ASSERT_TRUE(fetchSuccess) << "Unable to check values from DB";

    query.first();
    QString author = query.value(0).toString();
    int year = query.value(1).toInt();
    EXPECT_EQ(fake_book->author(), author);
    EXPECT_EQ(fake_book->yearPublished(), year);
    query.finish();

}

TEST_F(ExistingObjectSaveStateTest, testNonSave)
{
    QSqlDatabase db = QSqlDatabase::database("qtp-database");
    db.close();

    ExistingObjectSaveState eoss;
    bool saveSuccessful = eoss.save(fake_book);
    EXPECT_FALSE(saveSuccessful);

    db.close();
    QSqlDatabase::removeDatabase("qtp-database");
    saveSuccessful = eoss.save(fake_book);
    EXPECT_FALSE(saveSuccessful);

}

/* vim: set et sts=4 sw=4 ts=16 tw=78 : */

