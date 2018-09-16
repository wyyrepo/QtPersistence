/*
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

#include "inflectiontest.h"
#include "testutils.h"
#include "inflection.h"

TEST_P(SnakeCaseTest, testSnakeCase)
{
    StringPair testData = GetParam();
    EXPECT_EQ(Utils::snakeCase(testData.first), testData.second);
}

INSTANTIATE_TEST_CASE_P(testSnakeCase,
                        SnakeCaseTest,
                        ::testing::Values(qMakePair(QString("Post"), QString("post")),
                                          qMakePair(QString("FooBar"), QString("foo_bar")),
                                          qMakePair(QString("RootURLData"), QString("root_url_data")),
                                          qMakePair(QString("RootUrlData"), QString("root_url_data")),
                                          qMakePair(QString("BLING"), QString("bling"))));


TEST_P(ClassifyTest, testClassify)
{
    StringPair testData = GetParam();
    EXPECT_EQ(Utils::classify(testData.first), testData.second);
}

INSTANTIATE_TEST_CASE_P(testClassify,
                        ClassifyTest,
                        ::testing::Values(qMakePair(QString("eggs_and_ham"), QString("EggAndHam")),
                                          qMakePair(QString("post"), QString("Post")),
                                          qMakePair(QString("blind_mice"), QString("BlindMouse")),
                                          qMakePair(QString("book_authors"), QString("BookAuthor"))));



TEST_P(CapitalizeTest, testCapitalize)
{
    StringPair testData = GetParam();
    EXPECT_EQ(Utils::capitalize(testData.first), testData.second);
}

INSTANTIATE_TEST_CASE_P(testCapitalize,
                        CapitalizeTest,
                        ::testing::Values(qMakePair(QString("TEST"),QString("Test")),
                                          qMakePair(QString("Compile"),QString("Compile")),
                                          qMakePair(QString("hElL0"), QString("Hell0")),
                                          qMakePair(QString(), QString()),
                                          qMakePair(QString("goodbye"), QString("Goodbye"))));


TEST_P(CamelizeTest, testCamelize)
{
    StringPair testData = GetParam();
    EXPECT_EQ(Utils::camelize(testData.first), testData.second);
}

INSTANTIATE_TEST_CASE_P(testCamelize,
                        CamelizeTest,
                        ::testing::Values(qMakePair(QString("post"),QString("Post")),
                                          qMakePair(QString("active_record"), QString("ActiveRecord")),
                                          qMakePair(QString("book_club"), QString("BookClub")),
                                          qMakePair(QString("book/author"), QString("Book::Author")),
                                          qMakePair(QString("path/to/nowhere"), QString("Path::To::Nowhere"))));

TEST_P(TableizeTest, testTableize)
{
    StringPair testData = GetParam();
    EXPECT_EQ(Utils::tableize(testData.first), testData.second);
}

INSTANTIATE_TEST_CASE_P(testTableize,
                        TableizeTest,
                        ::testing::Values(qMakePair(QString("Post"),QString("posts")),
                                          qMakePair(QString("ActiveRecord"), QString("active_records")),
                                          qMakePair(QString("FancyCategory"), QString("fancy_categories"))));


/* vim: set et sts=4 sw=4 ts=16 tw=78 : */
