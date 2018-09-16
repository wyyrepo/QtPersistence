/*
 * QtPersistence class test
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
#ifndef QTPERSISTENCETEST_H
#define QTPERSISTENCETEST_H

#include <gtest/gtest.h>

#include "qtpersistence.h"
#include <QtCore/QUrl>

struct qtpTestData
{
    QUrl url;
    QString system;
    QString host;
    int port;
    QString user;
    QString pass;
    QString database;
    bool result;
    bool validity;
};

class QtPersistenceTest :
    public ::testing::TestWithParam<qtpTestData> {};


#endif
/* vim: set et sts=4 sw=4 ts=16 tw=78 : */

