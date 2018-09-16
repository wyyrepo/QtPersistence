/*
 * Fake Book class - used for testing
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

#ifndef FAKEBOOK_H
#define FAKEBOOK_H

#include "qpersistantobject.h"

class FakeBook : public QPersistantObject
{
Q_OBJECT
Q_PROPERTY(QString author READ author WRITE setAuthor)
Q_PROPERTY(int yearPublished READ yearPublished WRITE setYearPublished)
public:
    Q_INVOKABLE FakeBook(QObject* parent = 0) : QPersistantObject(parent) {}
    virtual ~FakeBook() {}

    void setAuthor(const QString& a) { m_author = a; }
    QString author() const { return m_author; }

    void setYearPublished(int year) { m_yearPublished = year; }
    int yearPublished() const { return m_yearPublished; }

private:
    QString m_author;
    int m_yearPublished;
};

#endif
/* vim: set et sts=4 sw=4 ts=16 tw=78 : */

