/* Copyright (C) 2022  Dmitry Serov
 *
 * This file is part of MControlCenter.
 *
 * MControlCenter is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 */

#ifndef MCONTROLCENTER_USER_MODE_POLICY_H
#define MCONTROLCENTER_USER_MODE_POLICY_H

#include <optional>

#include <QString>

enum class user_mode {
    performance_mode,
    balanced_mode,
    silent_mode,
    super_battery_mode,
    unknown_mode
};

[[nodiscard]] std::optional<user_mode> parseSavedUserMode(const QString &value);
[[nodiscard]] bool userModeMayOwnAdvanced(user_mode mode);

#endif // MCONTROLCENTER_USER_MODE_POLICY_H
