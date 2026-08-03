/* Copyright (C) 2022  Dmitry Serov
 *
 * This file is part of MControlCenter.
 *
 * MControlCenter is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 */

#include "user_mode_policy.h"

std::optional<user_mode> parseSavedUserMode(const QString &value) {
    if (value == QStringLiteral("balanced_mode"))
        return user_mode::balanced_mode;
    if (value == QStringLiteral("performance_mode"))
        return user_mode::performance_mode;
    if (value == QStringLiteral("silent_mode"))
        return user_mode::silent_mode;
    if (value == QStringLiteral("super_battery_mode"))
        return user_mode::super_battery_mode;
    return std::nullopt;
}

bool userModeMayOwnAdvanced(user_mode mode) {
    return mode == user_mode::balanced_mode || mode == user_mode::performance_mode;
}
