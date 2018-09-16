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

#ifndef INFLECTION_H
#define INFLECTION_H

#include <QtCore/QString>
#include <QtCore/QHash>


class Utils
{
public:
    /**
     * Convert to snake case
     */
    static QString snakeCase(const QString& name);

    /**
     * Take an underscored name and make it into a camelized name
     *
     * @example
     * classify("i_am_sam") returns "IAmSam"
     * classify("comment") returns "Comment"
     */
    static QString classify(const QString& name);

    /**
     * Convert a string to UpperCamelCase
     *
     */
    static QString camelize(const QString& name);

    /**
     * Capitalize a string
     *
     * @return the capitalized version of the string
     */
    static QString capitalize(const QString& name);

    /**
     * Convert a string into a table name
     *
     * @return a version of the string useful as a database table name
     */
    static QString tableize(const QString& s);

#include "inflection_p.h"
};

#endif
/* vim: set et sts=4 sw=4 ts=16 tw=78 : */
