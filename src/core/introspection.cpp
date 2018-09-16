/*
 * Object Introspection
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

#include "introspection.h"

#include <QtCore/QObject>
#include <QtCore/QMetaObject>
#include <QtCore/QMetaProperty>

#include "inflection.h"

QString tableNameForObject(QObject* o)
{
    const QMetaObject* meta = o->metaObject();
    QString tableName = meta->className();
    tableName = Utils::tableize(tableName);
    return tableName;
}

QList<QString> propertyListForObject(QObject* o)
{
    QList<QString> list;

    const QMetaObject* meta = o->metaObject();
    for (int i = meta->propertyOffset(); i < meta->propertyCount(); ++i) {
        list << QString::fromLatin1(meta->property(i).name());
    }

    return list;
}

QVariantHash  propertyValuesForObject(QObject* o)
{
    QVariantHash hash;

    const QMetaObject* meta = o->metaObject();
    for (int i = 0; i < meta->propertyCount(); ++i) {
        QMetaProperty property = meta->property(i);
        QString propertyName = QString::fromLatin1(property.name());
        if (propertyName == "objectName") {
            continue;
        }

        hash.insert(propertyName, property.read(o));
    }
    return hash;
}

/* vim: set et sts=4 sw=4 ts=16 tw=78 : */

