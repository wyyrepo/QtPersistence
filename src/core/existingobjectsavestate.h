/*
 * Existing Object Save State
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

#ifndef EXISTINGOBJECTSAVESTATE_H
#define EXISTINGOBJECTSAVESTATE_H

#include "objectsavestate.h"

class ExistingObjectSaveState : public ObjectSaveState
{
public:
    virtual ~ExistingObjectSaveState();

    virtual bool save(QPersistantObject* o);
};


#endif
/* vim: set et sts=4 sw=4 ts=16 tw=78 : */

