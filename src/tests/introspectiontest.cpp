/*
 * Object Introspection Tests
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

#include <gtest/gtest.h>

#include "testutils.h"
#include "introspection.h"
#include "introspectiontest.h"


TEST(IntrospectionTest, testTableNameIntrospection)
{
    Book b;
    Life l;
    QString tableName = tableNameForObject(&b);
    QString tableName2 = tableNameForObject(&l);
    EXPECT_EQ(tableName, QString("books"));
    EXPECT_EQ(tableName2, QString("lives"));
}

TEST(IntrospectionTest, testPropertyNameIntrospection)
{
    Book b;
    QList<QString> propList = propertyListForObject(&b);
    qSort(propList);

    ASSERT_FALSE(propList.isEmpty());
    EXPECT_EQ(2, propList.size());
    EXPECT_EQ(QString("author"), propList.at(0));
    EXPECT_EQ(QString("yearPublished"), propList.at(1));
}

TEST(IntrospectionTest, testPropertyValueGathering)
{
    Book b;
    QString author = QLatin1String("Matt Rogers");
    int year = 2009;
    b.setAuthor(author);
    b.setYearPublished(year);

    QVariantHash propertyValues = propertyValuesForObject(&b);

    ASSERT_FALSE(propertyValues.isEmpty());
    EXPECT_EQ(3, propertyValues.count());
    EXPECT_TRUE(propertyValues.contains(QString("author")));
    EXPECT_TRUE(propertyValues.contains(QString("yearPublished")));
    EXPECT_TRUE(propertyValues.contains(QString("id")));
    EXPECT_EQ(author, propertyValues.value("author").toString());
    EXPECT_EQ(year, propertyValues.value("yearPublished").toInt());

}

/* vim: set et sts=4 sw=4 ts=16 tw=78 : */
