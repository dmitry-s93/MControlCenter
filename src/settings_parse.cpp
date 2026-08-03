/* Copyright (C) 2022  Dmitry Serov
 *
 * This file is part of MControlCenter.
 *
 * MControlCenter is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 */

#include "settings.h"

#include <QStringList>

QVector<int> Settings::parseValueVector(const QString &encoded, bool *ok) {
    QVector<int> value;
    if (ok)
        *ok = false;
    if (encoded.isEmpty())
        return value;
    const QStringList entries = encoded.split(QLatin1Char('|'), Qt::KeepEmptyParts);
    value.reserve(entries.size());
    for (const QString &entry : entries) {
        bool converted = false;
        const int parsed = entry.toInt(&converted);
        if (!converted)
            return {};
        value.append(parsed);
    }
    if (ok)
        *ok = true;
    return value;
}
