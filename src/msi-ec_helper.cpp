/* Copyright (C) 2022  Jérôme Lécuyer, Dmitry Serov
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

#include "msi-ec_helper.h"
#include "helper/service.h"
#include "mainwindow.h"

#include <QDBusReply>

MsiEcHelper::MsiEcHelper() {
    if (!QDBusConnection::systemBus().isConnected()) {
        fprintf(stderr, "Cannot connect to the D-Bus system bus");
        return;
    }
    iface = new QDBusInterface(SERVICE_NAME, "/msi_ec", INTERFACE_NAME_MSI_EC, QDBusConnection::systemBus());
}

bool MsiEcHelper::isMsiEcModuleLoaded() {
    return getValue<bool>("isMsiEcModuleLoaded", false);
}

//////////////// webcam ////////////////

bool MsiEcHelper::hasWebcam() const {
    return getValue<bool>("hasWebcam", false);
}

bool MsiEcHelper::getWebcam() const {
    return getValue<bool>("getWebcam", false);
}

void MsiEcHelper::setWebcam(bool enabled) const {
    setValue<bool>("setWebcam", enabled);
}

//////////////// webcam_block ////////////////

bool MsiEcHelper::hasWebcamBlock() const {
    return getValue<bool>("hasWebcamBlock", false);
}

bool MsiEcHelper::getWebcamBlock() const {
    return getValue<bool>("getWebcamBlock", false);
}

void MsiEcHelper::setWebcamBlock(bool enabled) const {
    setValue<bool>("setWebcamBlock", enabled);
}

//////////////// fn_win_swap ////////////////

bool MsiEcHelper::hasFnWinSwap() const {
    return getValue<bool>("hasFnWinSwap", false);
}

bool MsiEcHelper::getFnWinSwap() const {
    return getValue<bool>("getFnWinSwap", false);
}

void MsiEcHelper::setFnWinSwap(bool swap) const {
    setValue<bool>("setFnWinSwap", swap);
}

//////////////// cooler_boost ////////////////

bool MsiEcHelper::hasCoolerBoost() const {
    return getValue<bool>("hasCoolerBoost", false);
}

bool MsiEcHelper::getCoolerBoost() const {
    return getValue<bool>("getCoolerBoost", false);
}

void MsiEcHelper::setCoolerBoost(bool enable) const {
    setValue<bool>("setCoolerBoost", enable);
}

//////////////// shift_mode ////////////////
bool MsiEcHelper::hasShiftMode() const {
    return getValue<bool>("hasShiftMode", false);
}

QList<shift_mode> MsiEcHelper::getAvailableShiftModes() const {
    QList<QString> modesStr = getValue<QString>("getAvailableShiftModes", "").split("\n");
    QList<shift_mode> shiftModes;
    for (QString mode : modesStr) {
        if(mode == "eco")
            shiftModes.append(shift_mode::eco_mode);
        else if (mode == "comfort")
            shiftModes.append(shift_mode::comfort_mode);
        else if (mode == "sport")
            shiftModes.append(shift_mode::sport_mode);
        else if (mode == "turbo")
            shiftModes.append(shift_mode::turbo_mode);
    }
    return shiftModes;
}

shift_mode MsiEcHelper::getShiftMode() const {
    QString mode = getValue<QString>("getShiftMode", "");
    if(mode == "eco")
        return shift_mode::eco_mode;
    else if (mode == "comfort")
        return shift_mode::comfort_mode;
    else if (mode == "sport")
        return shift_mode::sport_mode;
    else if (mode == "turbo")
        return shift_mode::turbo_mode;
    else
        return shift_mode::unknown_mode;
}

void MsiEcHelper::setShiftMode(shift_mode mode) const {
    QString modeStr;
    switch(mode) {
        case shift_mode::eco_mode:
            modeStr = "eco";
            break;
        case shift_mode::comfort_mode:
            modeStr = "comfort";
            break;
        case shift_mode::sport_mode:
            modeStr = "sport";
            break;
        case shift_mode::turbo_mode:
            modeStr = "turbo";
            break;
        case shift_mode::unknown_mode:
            return;
        }
    setValue<QString>("setShiftMode", modeStr);
}

//////////////// super_battery ////////////////

bool MsiEcHelper::hasSuperBattery() const {
    return getValue<bool>("hasSuperBattery", false);
}

bool MsiEcHelper::getSuperBattery() const {
    return getValue<bool>("getSuperBattery", false);
}

void MsiEcHelper::setSuperBattery(bool enable) const {
    setValue<bool>("setSuperBattery", enable);
}

//////////////// fan_mode ////////////////

bool MsiEcHelper::hasFanMode() const {
    return getValue<bool>("hasFanMode", false);
}

QList<fan_mode> MsiEcHelper::getAvailableFanModes() const {
    QList<QString> modesStr = getValue<QString>("getAvailableFanModes", "").split("\n");
    QList<fan_mode> fanModes;
    for (QString mode : modesStr) {
        if(mode == "auto")
            fanModes.append(fan_mode::auto_fan_mode);
        else if (mode == "silent")
            fanModes.append(fan_mode::silent_fan_mode);
        else if (mode == "basic")
            fanModes.append(fan_mode::basic_fan_mode);
        else if (mode == "advanced")
            fanModes.append(fan_mode::advanced_fan_mode);
    }
    return fanModes;
}

fan_mode MsiEcHelper::getFanMode() const {
    QString mode = getValue<QString>("getFanMode", "");
    if (mode == "auto")
        return fan_mode::auto_fan_mode;
    else if (mode == "silent")
        return fan_mode::silent_fan_mode;
    else if (mode == "basic")
        return fan_mode::basic_fan_mode;
    else if (mode == "advanced")
        return fan_mode::advanced_fan_mode;
    else
        return fan_mode::unknown_fan_mode;
}

void MsiEcHelper::setFanMode(fan_mode mode) const {
    QString modeStr;
    switch (mode) {
        case fan_mode::auto_fan_mode:
            modeStr = "auto";
            break;
        case fan_mode::silent_fan_mode:
            modeStr = "silent";
            break;
        case fan_mode::basic_fan_mode:
            modeStr = "basic";
            break;
        case fan_mode::advanced_fan_mode:
            modeStr = "advanced";
            break;
        default:
            return;
    }
    setValue<QString>("setFanMode", modeStr);
}

//////////////// fw_version ////////////////

QString MsiEcHelper::getFWVersion() const {
    return getValue<QString>("getFWVersion", "");
}

//////////////// fw_release_date ////////////////

QString MsiEcHelper::getFWReleaseDate() const {
    return getValue<QString>("getFWReleaseDate", "");
}

//////////////// CPU ////////////////

// cpu/realtime_temperature 0-100 (celsius scale)
bool MsiEcHelper::hasCPURealtimeTemperature() const {
    return getValue<bool>("hasCPURealtimeTemperature", false);
}

int MsiEcHelper::getCPURealtimeTemperature() const {
    return getValue<int>("getCPURealtimeTemperature", -1);
}

// cpu/realtime_fan_speed 0-100 (percent)
bool MsiEcHelper::hasCPURealtimeFanSpeed() const {
    return getValue<bool>("hasCPURealtimeFanSpeed", false);
}

int MsiEcHelper::getCPURealtimeFanSpeed() const {
    return getValue<int>("getCPURealtimeFanSpeed", -1);
}

// cpu/basic_fan_speed 0-100 (percent)
bool MsiEcHelper::hasCPUBasicFanSpeed() const {
    return getValue<bool>("hasCPUBasicFanSpeed", false);
}

int MsiEcHelper::getCPUBasicFanSpeed() const {
    return getValue<int>("getCPUBasicFanSpeed", -1);
}

void MsiEcHelper::setCPUBasicFanSpeed(int value) const {
    setValue<int>("setCPUBasicFanSpeed", value);
}

//////////////// GPU ////////////////

// gpu/realtime_temperature 0-100 (celsius scale)
bool MsiEcHelper::hasGPURealtimeTemperature() const {
    return getValue<bool>("hasGPURealtimeTemperature", false);
}

std::optional<int> MsiEcHelper::getGPURealtimeTemperature() const {
    return getOptionalValue<int>("getGPURealtimeTemperature");
}

// gpu/realtime_fan_speed 0-100 (percent)
bool MsiEcHelper::hasGPURealtimeFanSpeed() const {
    return getValue<bool>("hasGPURealtimeFanSpeed", false);
}

std::optional<int> MsiEcHelper::getGPURealtimeFanSpeed() const {
    return getOptionalValue<int>("getGPURealtimeFanSpeed");
}

//////////////// Charge control ////////////////

// BAT1/charge_control_start_threshold 0-100 (percent)
bool MsiEcHelper::hasBatteryStartThreshold() const {
    return getValue<bool>("hasBatteryStartThreshold", false);
}

int MsiEcHelper::getBatteryStartThreshold() const {
    return getValue<int>("getBatteryStartThreshold", -1);
}

void MsiEcHelper::setBatteryStartThreshold(int value) const {
    return setValue<int>("setBatteryStartThreshold", value);
}

// BAT1/charge_control_end_threshold 0-100 (percent)
bool MsiEcHelper::hasBatteryEndThreshold() const {
    return getValue<bool>("hasBatteryEndThreshold", false);
}

int MsiEcHelper::getBatteryEndThreshold() const {
    return getValue<int>("getBatteryEndThreshold", -1);
}

void MsiEcHelper::setBatteryEndThreshold(int value) const {
    return setValue<int>("setBatteryEndThreshold", value);
}

// BAT1/capacity 0-100 (percent)
bool MsiEcHelper::hasBatteryCapacity() const {
    return getValue<bool>("hasBatteryCapacity", false);
}

int MsiEcHelper::getBatteryCapacity() const {
    return getValue<int>("getBatteryCapacity", -1);
}

// BAT1/status
bool MsiEcHelper::hasBatteryStatus() const {
    return getValue<bool>("hasBatteryStatus", false);
}

QString MsiEcHelper::getBatteryStatus() const {
    return getValue<QString>("getBatteryStatus", "");
}

//////////////// Keyboard Backlight ////////////////

// kbd_backlight/brightness 0-3
bool MsiEcHelper::hasKeyboardBacklightBrightness() const {
    return getValue<bool>("hasKeyboardBacklightBrightness", false);
}

int MsiEcHelper::getKeyboardBacklightBrightness() const {
    return getValue<int>("getKeyboardBacklightBrightness", -1);
}

void MsiEcHelper::setKeyboardBacklightBrightness(int value) const {
    return setValue<int>("setKeyboardBacklightBrightness", value);
}

////////////////////////////////

void MsiEcHelper::printError(QDBusError const &error) const {
    if (error.isValid())
        fprintf(stderr, "Call failed: %s\n", qPrintable(error.message()));
}

template <typename T>
inline std::optional<T> MsiEcHelper::getOptionalValue(QString method) const {
    if (QDBusReply<T> reply = iface->call(method); reply.isValid())
        return reply.value();
    printError(iface->lastError());
    return std::nullopt;
}

template <typename T>
inline T MsiEcHelper::getValue(QString method, T defaultValue) const {
    return getOptionalValue<T>(method).value_or(defaultValue);
}

template <typename T>
void MsiEcHelper::setValue(QString method, T value) const {
    iface->call(method, value);
    printError(iface->lastError());
}
