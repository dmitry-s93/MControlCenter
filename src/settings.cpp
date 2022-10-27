/* Copyright (C) 2022  Dmitry Serov
 *
 * This file is part of MControlCenter.
 *
 * MControlCenter is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * MControlCenter is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with MControlCenter. If not, see <https://www.gnu.org/licenses/>.
 */

#include <QSettings>
#include "settings.h"

QSettings settings("MControlCenter");

QVariant Settings::getValue(const QString &key) {
    return settings.value(key);
}

void Settings::setValue(const QString &key, const QVariant &value) {
    if (settings.value(key) == value)
        return;
    settings.setValue(key, value);
    settings.sync();
}

bool Settings::isValueExist(const QString &key) {
    if (settings.contains(key))
        return true;
    return false;
}
