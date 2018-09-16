/*
 * QPersistantObject - the core of QtPersistence
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

#include "qpersistantobject.h"
#include "objectsavestate.h"
#include "qpersistantobject_p.h"
#include "newobjectsavestate.h"
#include "existingobjectsavestate.h"

QPersistantObjectPrivate::QPersistantObjectPrivate()
    : id(0), oss(0)
{
}

QPersistantObjectPrivate::~QPersistantObjectPrivate()
{
    delete oss;
}


void QPersistantObjectPrivate::setObjectSaveState(ObjectSaveState* newOss)
{
    delete oss;
    oss = newOss;
}

bool QPersistantObjectPrivate::isSaved() const
{
    return id > 0;
}

bool QPersistantObjectPrivate::save(QPersistantObject* qpo)
{
    Q_ASSERT(oss);
    bool saveSuccessful = oss->save(qpo);
    return saveSuccessful;
}


/* begin public class implementation */

QPersistantObject::QPersistantObject(QObject* parent)
    : QObject(parent), d(new QPersistantObjectPrivate())
{

}

QPersistantObject::~QPersistantObject()
{
    delete d;
}

int QPersistantObject::id() const
{
    return d->id;
}

void QPersistantObject::setId(int id)
{
    d->id = id;
}

bool QPersistantObject::isSaved() const
{
    return d->isSaved();
}

bool QPersistantObject::save()
{
    if (!isSaved())
    {
        NewObjectSaveState* noss = new NewObjectSaveState;
        d->setObjectSaveState(noss);
    }

    bool saveOk = d->save(this);
    if (saveOk)
    {
        ExistingObjectSaveState* eoss = new ExistingObjectSaveState;
        d->setObjectSaveState(eoss);
    }

    return saveOk;
}

/* vim: set et sts=4 sw=4 ts=16 tw=78 : */
