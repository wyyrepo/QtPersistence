/*
 * English Nouns Number Inflection
 * Based on code used in the Datamapper project
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

/* This file is private API and is used for the convenience of the
 * QtPersistence project. It is subject to change at any time. You use it
 * at your own risk!
 */

#ifndef INFLECTION_P_H
#define INFLECTION_P_H

#include <QtCore/QString>

class InflectionExceptions
{
    public:
        InflectionExceptions();
        void clear();

        QString singular(const QString& word);
        QString plural(const QString& word);

    private:
        void word(const QString& singular,
                  const QString& plural = QString());
        void singularWord(const QString&, const QString&);
        void pluralWord(const QString&, const QString&);

        void rule(const QString&, const QString&, bool = false);
        void singularRule(const QString&, const QString&);
        void pluralRule(const QString&, const QString&);

        QRegExp singularizationRules() const;
        QRegExp pluralizationRules() const;

    private:
        typedef QHash<QString, QString> StringHash;
        StringHash m_singularOf;
        StringHash m_pluralOf;

        StringHash m_singularizationRules;
        StringHash m_pluralizationRules;
};

#endif

/* vim: set et sts=4 sw=4 ts=16 tw=78 : */

