/*
 * QtPersistenceObject Implementation Test
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

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "mockobjectsavestate.h"
#include "qpersistantobjectimpltest.h"
#include "qpersistantobject_p.h"
#include "qpersistantobject.h"

using ::testing::Return;
using ::testing::_;

TEST(QtPersistantObjectImplTest, testSuccessfulSave)
{
    MockObjectSaveState* moss = new MockObjectSaveState;
    MockObjectSaveState* nextOss = new MockObjectSaveState;
    QPersistantObject qpo;
    EXPECT_CALL(*moss, save(&qpo))
        .Times(1)
        .WillOnce(Return(true));
    EXPECT_CALL(*nextOss, save(&qpo))
        .WillRepeatedly(Return(true));

    QPersistantObjectPrivate qpop;
    qpop.setObjectSaveState(moss);

    bool saveSuccessful = qpop.save(&qpo);
    EXPECT_TRUE(saveSuccessful);
    qpop.setObjectSaveState(nextOss);
    saveSuccessful = qpop.save(&qpo);
    EXPECT_TRUE(saveSuccessful);
}



/* vim: set et sts=4 sw=4 ts=16 tw=78 : */
