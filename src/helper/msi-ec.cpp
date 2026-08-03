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

#include "msi-ec.h"
#include "authorization.h"
#include <QFile>
#include <utility>

// Available entries: https://github.com/BeardOverflow/msi-ec?tab=readme-ov-file#usage
const QString msi_ec_path = "/sys/devices/platform/msi-ec";
const QString msi_ec_webcam = msi_ec_path + "/webcam";
const QString msi_ec_webcam_block = msi_ec_path + "/webcam_block";
const QString msi_ec_fn_key = msi_ec_path + "/fn_key";
const QString msi_ec_win_key = msi_ec_path + "/win_key";
const QString msi_ec_cooler_boost = msi_ec_path + "/cooler_boost";
const QString msi_ec_available_shift_modes = msi_ec_path + "/available_shift_modes";
const QString msi_ec_shift_mode = msi_ec_path + "/shift_mode";
const QString msi_ec_super_battery = msi_ec_path + "/super_battery";
const QString msi_ec_available_fan_modes = msi_ec_path + "/available_fan_modes";
const QString msi_ec_fan_mode = msi_ec_path + "/fan_mode";
const QString msi_ec_fw_version = msi_ec_path + "/fw_version";
const QString msi_ec_fw_release_date = msi_ec_path + "/fw_release_date";
const QString msi_ec_cpu_realtime_temperature = msi_ec_path + "/cpu/realtime_temperature";
const QString msi_ec_cpu_realtime_fan_speed = msi_ec_path + "/cpu/realtime_fan_speed";
const QString msi_ec_cpu_basic_fan_speed = msi_ec_path + "/cpu/basic_fan_speed";
const QString msi_ec_gpu_realtime_temperature = msi_ec_path + "/gpu/realtime_temperature";
const QString msi_ec_gpu_realtime_fan_speed = msi_ec_path + "/gpu/realtime_fan_speed";
const QString msi_ec_bat1 = "/sys/class/power_supply/BAT1";
const QString msi_ec_bat1_start_threshold = msi_ec_bat1 + "/charge_control_start_threshold";
const QString msi_ec_bat1_end_threshold = msi_ec_bat1 + "/charge_control_end_threshold";
const QString msi_ec_bat1_capacity = msi_ec_bat1 + "/capacity";
const QString msi_ec_bat1_status = msi_ec_bat1 + "/status";
// /sys/class/leds/platform::<led_name>/brightness
const QString msi_ec_kbd_backlight_brightness = "/sys/class/leds/msiacpi::kbd_backlight/brightness";

MsiEc::MsiEc(DBusContextObject &parent, QString sysfsRoot)
    : QDBusAbstractAdaptor(&parent), context(parent),
      fanCurveBackend(sysfsRoot.isEmpty() ? QStringLiteral("/sys/devices/platform/msi-ec") : std::move(sysfsRoot)) {}

QString MsiEc::readFile(QString path) const {
    if (QFile file(path); file.exists() && file.open(QIODevice::ReadOnly)) {
        // Remove only the last '\n'
        return file.readAll().chopped(1);
    }
    return "";
}

bool MsiEc::readFileOnOff(QString path) const {
    return readFile(path) == "on";
}

bool MsiEc::writeFile(QString path, QString value) const {
    if (!authorizeHardwareMutation(context.callContext()))
        return false;
    if (QFile file(path); file.exists() && file.open(QIODevice::WriteOnly))
        return file.write(value.toUtf8()) == value.toUtf8().size();
    return false;
}

void MsiEc::writeFileOnOff(QString path, bool on) const {
    writeFile(path, on ? "on" : "off");
}

bool MsiEc::isMsiEcModuleLoaded() const {
    if (QFile::exists(msi_ec_fw_version)) {
        return true;
    }
    fprintf(stderr, "%s\n", qPrintable("The msi_ec kernel module is not loaded"));
    return false;
}

//////////////// webcam ////////////////

bool MsiEc::hasWebcam() const {
    return QFile::exists(msi_ec_webcam);
}
bool MsiEc::getWebcam() const {
    return readFileOnOff(msi_ec_webcam);
}
void MsiEc::setWebcam(bool enable) const {
    writeFileOnOff(msi_ec_webcam, enable);
}

//////////////// webcam_block ////////////////

bool MsiEc::hasWebcamBlock() const {
    return QFile::exists(msi_ec_webcam_block);
}
bool MsiEc::getWebcamBlock() const {
    return readFileOnOff(msi_ec_webcam_block);
}
void MsiEc::setWebcamBlock(bool enable) const {
    writeFileOnOff(msi_ec_webcam_block, enable);
}

//////////////// fn_key ////////////////

bool MsiEc::hasFnKey() const {
    return QFile::exists(msi_ec_fn_key);
}
QString MsiEc::getFnKey() const {
    return readFile(msi_ec_fn_key);
}
bool MsiEc::setFnKey(QString side) const {
    if (side != QStringLiteral("left") && side != QStringLiteral("right")) {
        context.sendCallError(QDBusError::InvalidArgs, QStringLiteral("invalid Fn key side"));
        return false;
    }
    return writeFile(msi_ec_fn_key, side);
}

//////////////// win_key ////////////////

bool MsiEc::hasWinKey() const {
    return QFile::exists(msi_ec_win_key);
}
QString MsiEc::getWinKey() const {
    return readFile(msi_ec_win_key);
}
void MsiEc::setWinKey(QString side) const {
    writeFile(msi_ec_win_key, side);
}

//////////////// fn_win_swap ////////////////

bool MsiEc::hasFnWinSwap() const {
    return hasFnKey();
}
bool MsiEc::getFnWinSwap() const {
    // here we only want to know if the keys are swapped or not
    // we don't care if it is left or right
    // swap may be inverted on some devices
    // it would be better to get the value directly
    // (e.g. with a file fn_win_swap)
    return getFnKey() == "left";
}
bool MsiEc::setFnWinSwap(bool swap) const {
    if (!setFnKey(swap ? QStringLiteral("left") : QStringLiteral("right")))
        return false;
    return getFnWinSwap() == swap;
}

//////////////// cooler_boost ////////////////

bool MsiEc::hasCoolerBoost() const {
    return QFile::exists(msi_ec_cooler_boost);
}
bool MsiEc::getCoolerBoost() const {
    return readFileOnOff(msi_ec_cooler_boost);
}
void MsiEc::setCoolerBoost(bool enable) const {
    writeFileOnOff(msi_ec_cooler_boost, enable);
}

//////////////// shift_mode ////////////////

bool MsiEc::hasShiftMode() const {
    return QFile::exists(msi_ec_shift_mode);
}
QString MsiEc::getAvailableShiftModes() const {
    return readFile(msi_ec_available_shift_modes);
}
QString MsiEc::getShiftMode() const {
    return readFile(msi_ec_shift_mode);
}
bool MsiEc::setShiftMode(QString mode) const {
    if (mode != QStringLiteral("eco") && mode != QStringLiteral("comfort") &&
        mode != QStringLiteral("sport") && mode != QStringLiteral("turbo")) {
        context.sendCallError(QDBusError::InvalidArgs, QStringLiteral("invalid shift mode"));
        return false;
    }
    if (!writeFile(msi_ec_shift_mode, mode))
        return false;
    return getShiftMode() == mode;
}

//////////////// super_battery ////////////////

bool MsiEc::hasSuperBattery() const {
    return QFile::exists(msi_ec_super_battery);
}
bool MsiEc::getSuperBattery() const {
    return readFileOnOff(msi_ec_super_battery);
}
bool MsiEc::setSuperBattery(bool enable) const {
    if (!writeFile(msi_ec_super_battery, enable ? QStringLiteral("on") : QStringLiteral("off")))
        return false;
    return getSuperBattery() == enable;
}

//////////////// fan_mode ////////////////

bool MsiEc::hasFanMode() const {
    return QFile::exists(msi_ec_fan_mode);
}
QString MsiEc::getAvailableFanModes() const {
    return readFile(msi_ec_available_fan_modes);
}
QString MsiEc::getFanMode() const {
    return readFile(msi_ec_fan_mode);
}
bool MsiEc::setFanMode(QString mode) const {
    // Reject malformed requests before any PolicyKit invocation. An invalid
    // D-Bus call must not trigger authentication UI or consume the helper's
    // authorization timeout.
    if (mode != QStringLiteral("auto") && mode != QStringLiteral("silent") &&
        mode != QStringLiteral("basic") && mode != QStringLiteral("advanced")) {
        context.sendCallError(QDBusError::InvalidArgs, QStringLiteral("invalid fan mode"));
        return false;
    }
    if (!authorizeHardwareMutation(context.callContext())) {
        context.sendCallError(QDBusError::AccessDenied,
                              QStringLiteral("PolicyKit authorization required"));
        return false;
    }
    QString error;
    if (!writeFanModeVerified(fanCurveBackend, mode, &error))
        return false;
    return true;
}

//////////////// fan curve ////////////////

QVariantMap MsiEc::getFanCurveCapability() const {
    return fanCurveCapabilityToMap(fanCurveBackend.capability());
}

QVariantMap MsiEc::getFanCurveProfile() const {
    FanCurveProfile profile;
    QString error;
    const FanCurveCapability capability = fanCurveBackend.capability();
    if (!capability.complete() || !fanCurveBackend.readProfile(&profile, &error))
        return {{QStringLiteral("readable"), false}, {QStringLiteral("error"), error}};
    // Readability is distinct from strict validity. A complete device profile
    // remains available for repair even when values are out of range or badly
    // ordered; Apply performs the strict validation.
    QVariantMap result = fanCurveProfileToMap(profile);
    result.insert(QStringLiteral("readable"), true);
    result.insert(QStringLiteral("valid"), validateFanCurve(capability, profile).isEmpty());
    if (const QString validationError = validateFanCurve(capability, profile); !validationError.isEmpty())
        result.insert(QStringLiteral("error"), validationError);
    return result;
}

QVariantMap MsiEc::applyFanCurveTransaction(const QVariantMap &profileMap) const {
    if (!authorizeHardwareMutation(context.callContext())) {
        FanCurveResult denied;
        denied.error = QStringLiteral("PolicyKit authorization required");
        denied.rollbackStatus = QStringLiteral("not-attempted");
        denied.effectiveMode = fanCurveBackend.readMode();
        return fanCurveResultToMap(denied);
    }
    FanCurveProfile profile;
    FanCurveResult result;
    if (!fanCurveProfileFromMap(profileMap, &profile)) {
        result.error = QStringLiteral("malformed fan curve profile");
        result.effectiveMode = fanCurveBackend.readMode();
        result.rollbackStatus = QStringLiteral("not-attempted");
        return fanCurveResultToMap(result);
    }
    FanCurveTransaction transaction(fanCurveBackend);
    return fanCurveResultToMap(transaction.apply(profile));
}

//////////////// fw_version ////////////////

QString MsiEc::getFWVersion() const {
    return readFile(msi_ec_fw_version);
}

//////////////// fw_release_date ////////////////

QString MsiEc::getFWReleaseDate() const {
    return readFile(msi_ec_fw_release_date);
}

//////////////// CPU ////////////////

// cpu/realtime_temperature 0-100 (celsius scale)
bool MsiEc::hasCPURealtimeTemperature() const {
    return QFile::exists(msi_ec_cpu_realtime_temperature);
}
int MsiEc::getCPURealtimeTemperature() const {
    return readFile(msi_ec_cpu_realtime_temperature).toInt();
}

// cpu/realtime_fan_speed: driver-reported fan level (not RPM)
bool MsiEc::hasCPURealtimeFanSpeed() const {
    return QFile::exists(msi_ec_cpu_realtime_fan_speed);
}
int MsiEc::getCPURealtimeFanSpeed() const {
    return readFile(msi_ec_cpu_realtime_fan_speed).toInt();
}

// cpu/basic_fan_speed 0-100 (percent)
bool MsiEc::hasCPUBasicFanSpeed() const {
    return QFile::exists(msi_ec_cpu_basic_fan_speed);
}
int MsiEc::getCPUBasicFanSpeed() const {
    return readFile(msi_ec_cpu_basic_fan_speed).toInt();
}
void MsiEc::setCPUBasicFanSpeed(int value) const {
    writeFile(msi_ec_cpu_basic_fan_speed, QString::number(value));
}

//////////////// GPU ////////////////

// gpu/realtime_temperature 0-100 (celsius scale)
bool MsiEc::hasGPURealtimeTemperature() const {
    return QFile::exists(msi_ec_gpu_realtime_temperature);
}
int MsiEc::getGPURealtimeTemperature() const {
    return readFile(msi_ec_gpu_realtime_temperature).toInt();
}

// gpu/realtime_fan_speed: driver-reported fan level (not RPM)
bool MsiEc::hasGPURealtimeFanSpeed() const {
    return QFile::exists(msi_ec_gpu_realtime_fan_speed);
}
int MsiEc::getGPURealtimeFanSpeed() const {
    return readFile(msi_ec_gpu_realtime_fan_speed).toInt();
}

//////////////// Charge control ////////////////

// BAT1/charge_control_start_threshold 0-100 (percent)
bool MsiEc::hasBatteryStartThreshold() const {
    return QFile::exists(msi_ec_bat1_start_threshold);
}
int MsiEc::getBatteryStartThreshold() const {
    return readFile(msi_ec_bat1_start_threshold).toInt();
}
void MsiEc::setBatteryStartThreshold(int value) const {
    writeFile(msi_ec_bat1_start_threshold, QString::number(value));
}

// BAT1/charge_control_end_threshold 0-100 (percent)
bool MsiEc::hasBatteryEndThreshold() const {
    return QFile::exists(msi_ec_bat1_end_threshold);
}
int MsiEc::getBatteryEndThreshold() const {
    return readFile(msi_ec_bat1_end_threshold).toInt();
}
void MsiEc::setBatteryEndThreshold(int value) const {
    writeFile(msi_ec_bat1_end_threshold, QString::number(value));
}

// BAT1/capacity 0-100 (percent)
bool MsiEc::hasBatteryCapacity() const {
    return QFile::exists(msi_ec_bat1_capacity);
}

int MsiEc::getBatteryCapacity() const {
    return readFile(msi_ec_bat1_capacity).toInt();
}

// BAT1/status 0-100 (percent)
bool MsiEc::hasBatteryStatus() const {
    return QFile::exists(msi_ec_bat1_status);
}

QString MsiEc::getBatteryStatus() const {
    return readFile(msi_ec_bat1_status);
}

//////////////// Keyboard Backlight ////////////////

// kbd_backlight/brightness 0-3
bool MsiEc::hasKeyboardBacklightBrightness() const {
    return QFile::exists(msi_ec_kbd_backlight_brightness);
}
int MsiEc::getKeyboardBacklightBrightness() const {
    return readFile(msi_ec_kbd_backlight_brightness).toInt();
}
void MsiEc::setKeyboardBacklightBrightness(int value) const {
    writeFile(msi_ec_kbd_backlight_brightness, QString::number(value));
}
