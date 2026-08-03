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

#include "operate.h"
#include "helper.h"
#include "msi-ec_helper.h"
#include "settings.h"

Helper helper;
MsiEcHelper msiEcHelper;

const int cpuTempAddress = 0x68;
const int gpuTempAddress = 0x80;
const int batteryChargeAddress = 0x42;
int batteryThresholdAddress;
const int batteryThresholdAddress_0xEF = 0xEF;
const int batteryThresholdAddress_0xD7 = 0xD7;

const int keyboardBacklightModeAddress = 0x2C;
const int keyboardBacklightAlwaysOn = 0x00;
const int keyboardBacklightAutoTurnOff = 0x08;

int keyboardBacklightAddress;
const int keyboardBacklightAddress_0xD3 = 0xD3;
const int keyboardBacklightAddress_0xF3 = 0xF3;
const int keyboardBacklight0ff = 0x80;
const int keyboardBacklightLow = 0x81;
const int keyboardBacklightMid = 0x82;
const int keyboardBacklightHigh = 0x83;

const int usbPowerShareAddress = 0xBF;
const int usbPowerShareOff = 0x08;
const int usbPowerShareOn = 0x28;

const int coolerBoostAddress = 0x98;

const int fnSuperSwapAddress = 0xE8;

int fan1Address;
const int fan1Address_0xC9 = 0xC9;
const int fan1Address_0xCD = 0xCD;
const int fan2Address = 0xCB;

const int fan1SpeedSettingStartAddress = 0x72;
const int fan2SpeedSettingStartAddress = 0x8A;
const int fanSpeedSettingsCount = 7;
const int fan1TempSettingStartAddress = 0x6A;
const int fan2TempSettingStartAddress = 0x82;
const int fanTempSettingsCount = fanSpeedSettingsCount - 1;

int fanModeAddress;
const int fanModeAddress_0xD4 = 0xD4;
const int fanModeAddress_0xF4 = 0xF4;
const int fanModeAuto = 0x0D;
const int fanModeSilent = 0x1D;
const int fanModeBasic = 0x4D;
const int fanModeAdvanced = 0x8D;

const QString settingsGroup = "Settings/";
const QString fanCurveSettingsGroup = "Settings/FanCurve/";

namespace {
QString fanModeString(fan_mode mode) {
    switch (mode) {
    case fan_mode::auto_fan_mode: return QStringLiteral("auto");
    case fan_mode::silent_fan_mode: return QStringLiteral("silent");
    case fan_mode::basic_fan_mode: return QStringLiteral("basic");
    case fan_mode::advanced_fan_mode: return QStringLiteral("advanced");
    default: return QStringLiteral("unknown");
    }
}
}

Operate::Operate() = default;

bool Operate::isEcSysModuleLoaded() const {
    return helper.isEcSysModuleLoaded();
}

bool Operate::isMsiEcLoaded() const {
    return msiEcHelper.isMsiEcModuleLoaded();
}

bool Operate::loadEcSysModule() const {
    return helper.loadEcSysModule();
}

bool Operate::updateEcData() const {
    if (helper.isEcSysModuleLoaded())
        return helper.updateData() || msiEcHelper.isMsiEcModuleLoaded();
    // Typed msi_ec controls remain fully usable without raw EC diagnostics.
    return msiEcHelper.isMsiEcModuleLoaded();
}

void Operate::updateEcDataAsync() const {
    if (helper.isEcSysModuleLoaded())
        helper.updateDataAsync();
}

bool Operate::doProbe() const {
    fan1Address = detectFan1Address();
    batteryThresholdAddress = detectBatteryThresholdAddress();
    fanModeAddress = detectFanModeAddress();
    keyboardBacklightAddress = detectKeyboardBacklightAddress();

    return true;
}

std::string Operate::getEcVersion() const {
    if (msiEcHelper.isMsiEcModuleLoaded())
        return msiEcHelper.getFWVersion().toStdString();
    return helper.getValues(160, 12).toStdString();
}

std::string Operate::getEcBuild() const {
    if (msiEcHelper.isMsiEcModuleLoaded())
        return msiEcHelper.getFWReleaseDate().toStdString();
    std::string s = helper.getValues(172, 16).toStdString();
    if (s.size() < 16)
        return s;
    return s.substr(0, 2) + "/" + s.substr(2, 2) + "/" + s.substr(4, 4) + " " + s.substr(8, 8);
}

int Operate::getBatteryCharge() const {
    if (msiEcHelper.hasBatteryCapacity())
        return msiEcHelper.getBatteryCapacity();
    return helper.getValue(batteryChargeAddress) - 1;
}

int Operate::getBatteryThreshold() const {
    if (msiEcHelper.hasBatteryEndThreshold())
        return msiEcHelper.getBatteryEndThreshold();
    return helper.getValue(batteryThresholdAddress) - 128;
}

charging_state Operate::getChargingStatus() const {
    if (msiEcHelper.hasBatteryStatus()) {
        QString status = msiEcHelper.getBatteryStatus();
        if (status == "Charging")
            return charging_state::battery_charging;
        else if (status == "Discharging")
            return charging_state::battery_discharging;
        else if (status == "Not charging")
            return charging_state::battery_not_charging;
        else if (status == "Full")
            return charging_state::battery_fully_charged;
        // Fully charged no power doesn't exist in the kernel documentation
        else
            return charging_state::battery_unknown;
    }
    return charging_state::battery_unknown;
}

int Operate::getCpuTemp() const {
    if (msiEcHelper.hasCPURealtimeTemperature())
        return msiEcHelper.getCPURealtimeTemperature();
    return helper.getValue(cpuTempAddress);
}

std::optional<int> Operate::getGpuTemp() const {
    if (msiEcHelper.isMsiEcModuleLoaded())
        if (!msiEcHelper.hasGPURealtimeTemperature())
            return std::nullopt;
        else
            return msiEcHelper.getGPURealtimeTemperature();
    else
        return helper.getValue(gpuTempAddress);
}

std::optional<int> Operate::getFan1Speed() const {
    // msi-ec realtime_fan_speed is a level-like byte, not RPM. The RPM UI is
    // populated only by the optional read-only EC tachometer diagnostics.
    if (!helper.isEcSysModuleLoaded())
        return std::nullopt;
    const auto value0 = helper.getOptionalValue(fan1Address);
    const auto value1 = helper.getOptionalValue(fan1Address - 1);
    if (!value0.has_value() || !value1.has_value())
        return std::nullopt;
    const int value = (value1.value() << 8) | value0.value();
    return value > 0 ? std::optional<int>(480000 / value) : std::optional<int>(value);
}

std::optional<int> Operate::getFan2Speed() const {
    // msi-ec realtime_fan_speed is not RPM; use only optional raw EC
    // tachometer diagnostics when ec_sys/acpi_ec is actually available.
    if (!helper.isEcSysModuleLoaded())
        return std::nullopt;
    // Read 2 bytes (big-endian)
    auto value0 = helper.getOptionalValue(fan2Address);
    auto value1 = helper.getOptionalValue(fan2Address - 1);
    if (!value0.has_value() || !value1.has_value())
        return std::nullopt;
    int value = (value1.value() << 8) | value0.value();
    if (value > 0)
        return 480000 / value;
    return value;
}

QVector<int> Operate::getFan1SpeedSettings() const {
    if (const auto profile = getFanCurveProfile(); profile.has_value())
        return profile->cpuLevels;
    return {};
}

QVector<int> Operate::getFan2SpeedSettings() const {
    if (const auto profile = getFanCurveProfile(); profile.has_value())
        return profile->gpuLevels;
    return {};
}

QVector<int> Operate::getFan1TempSettings() const {
    if (const auto profile = getFanCurveProfile(); profile.has_value())
        return profile->cpuThresholds;
    return {};
}

QVector<int> Operate::getFan2TempSettings() const {
    if (const auto profile = getFanCurveProfile(); profile.has_value())
        return profile->gpuThresholds;
    return {};
}

int Operate::getKeyboardBacklightMode() const {
    if (helper.getValue(keyboardBacklightModeAddress) == keyboardBacklightAutoTurnOff)
        return 1;
    return 0;
}

int Operate::getKeyboardBrightness() const {
    if (msiEcHelper.hasKeyboardBacklightBrightness())
        return msiEcHelper.getKeyboardBacklightBrightness();
    int value = helper.getValue(keyboardBacklightAddress);
    switch (value) {
        case keyboardBacklight0ff:
            return 0;
        case keyboardBacklightLow:
            return 1;
        case keyboardBacklightMid:
            return 2;
        case keyboardBacklightHigh:
            return 3;
        default:
            return 0;
    }
}

bool Operate::getUsbPowerShareState() const {
    if (helper.getValue(usbPowerShareAddress) == usbPowerShareOn)
        return true;
    return false;
}

bool Operate::getWebCamState() const {
    if (msiEcHelper.hasWebcam())
        return msiEcHelper.getWebcam();
    return false;
}

bool Operate::getFnSuperSwapState() const {
    if (msiEcHelper.hasFnWinSwap())
        return msiEcHelper.getFnWinSwap();
    if (helper.getValue(fnSuperSwapAddress) / 16 % 2 != 0)
        return true;
    return false;
}

bool Operate::getCoolerBoostState() const {
    if (msiEcHelper.hasCoolerBoost())
        return msiEcHelper.getCoolerBoost();
    if (helper.getValue(coolerBoostAddress) > 127)
        return true;
    return false;
}

user_mode Operate::getUserMode() const {
    if (msiEcHelper.hasShiftMode()) {
        shift_mode shiftMode = msiEcHelper.getShiftMode();
        switch(shiftMode) {
            case shift_mode::eco_mode:
                return user_mode::super_battery_mode;
            case shift_mode::comfort_mode: {
                fan_mode fanMode = getFanMode();
                if (fanMode == fan_mode::silent_fan_mode)
                    return user_mode::silent_mode;
                else
                    return user_mode::balanced_mode;
            }
            case shift_mode::sport_mode: // ?
                return user_mode::balanced_mode;
            case shift_mode::turbo_mode:
                return user_mode::performance_mode;
            default:
                return user_mode::unknown_mode;
        }
    }
    return user_mode::unknown_mode;
}

fan_mode Operate::getFanMode() const {
    if (msiEcHelper.hasFanMode())
        return msiEcHelper.getFanMode();
    switch (helper.getValue(fanModeAddress)) {
        case fanModeAuto:
            return fan_mode::auto_fan_mode;
        case fanModeSilent:
            return fan_mode::silent_fan_mode;
        case fanModeBasic:
            return fan_mode::basic_fan_mode;
        case fanModeAdvanced:
            return fan_mode::advanced_fan_mode;
        default:
            return fan_mode::unknown_fan_mode;
    }
}

FanCurveCapability Operate::getFanCurveCapability() const {
    if (!msiEcHelper.isMsiEcModuleLoaded())
        return {};
    return msiEcHelper.getFanCurveCapability();
}

std::optional<FanCurveProfile> Operate::getFanCurveProfile() const {
    if (!getFanCurveCapability().complete())
        return std::nullopt;
    return msiEcHelper.getFanCurveProfile();
}

FanCurveResult Operate::applyFanCurve(const FanCurveProfile &profile) const {
    FanCurveResult result;
    const FanCurveCapability capability = getFanCurveCapability();
    if (const QString error = validateFanCurve(capability, profile); !error.isEmpty()) {
        result.error = error;
        result.effectiveMode = fanModeString(getFanMode());
        result.rollbackStatus = QStringLiteral("not-attempted");
        return result;
    }
    result = msiEcHelper.applyFanCurveTransaction(profile);
    if (result.success) {
        Settings::setValue(fanCurveSettingsGroup + QStringLiteral("Verified"), true);
        Settings::setValue(fanCurveSettingsGroup + QStringLiteral("FirmwareVersion"),
                           QString::fromStdString(getEcVersion()));
        Settings::setValue(fanCurveSettingsGroup + QStringLiteral("FirmwareDate"),
                           QString::fromStdString(getEcBuild()));
        Settings::setValue(fanCurveSettingsGroup + QStringLiteral("CpuThresholds"), profile.cpuThresholds);
        Settings::setValue(fanCurveSettingsGroup + QStringLiteral("CpuLevels"), profile.cpuLevels);
        Settings::setValue(fanCurveSettingsGroup + QStringLiteral("GpuThresholds"), profile.gpuThresholds);
        Settings::setValue(fanCurveSettingsGroup + QStringLiteral("GpuLevels"), profile.gpuLevels);
        Settings::setValue(fanCurveSettingsGroup + QStringLiteral("Advanced"), true);
    }
    return result;
}

QString Operate::savedFanCurveKey(const QString &suffix) const {
    return fanCurveSettingsGroup + suffix;
}

bool Operate::readVerifiedSavedFanCurve(FanCurveProfile *profile) const {
    Settings settings;
    if (!profile || !settings.getValue(savedFanCurveKey(QStringLiteral("Verified"))).toBool())
        return false;
    const QString savedVersion = settings.getValue(savedFanCurveKey(QStringLiteral("FirmwareVersion"))).toString();
    const QString savedDate = settings.getValue(savedFanCurveKey(QStringLiteral("FirmwareDate"))).toString();
    if (!fanCurveFirmwareMatches(savedVersion, savedDate,
                                 QString::fromStdString(getEcVersion()),
                                 QString::fromStdString(getEcBuild())))
        return false;
    auto readVector = [&](const QString &key, QVector<int> *values) {
        bool ok = false;
        *values = settings.getValueVector(key, &ok);
        return ok;
    };
    return readVector(savedFanCurveKey(QStringLiteral("CpuThresholds")), &profile->cpuThresholds) &&
           readVector(savedFanCurveKey(QStringLiteral("CpuLevels")), &profile->cpuLevels) &&
           readVector(savedFanCurveKey(QStringLiteral("GpuThresholds")), &profile->gpuThresholds) &&
           readVector(savedFanCurveKey(QStringLiteral("GpuLevels")), &profile->gpuLevels) &&
           validateFanCurve(getFanCurveCapability(), *profile).isEmpty();
}

bool Operate::hasVerifiedSavedFanCurve() const {
    FanCurveProfile profile;
    return readVerifiedSavedFanCurve(&profile);
}

void Operate::setBatteryThreshold(int value) const {
    if (msiEcHelper.hasBatteryEndThreshold())
        return msiEcHelper.setBatteryEndThreshold(value);
}

void Operate::setKeyboardBacklightMode(int value) const {
    Q_UNUSED(value); // raw EC writes are intentionally unavailable
}

void Operate::setKeyboardBrightness(int value) const {
    if (msiEcHelper.hasKeyboardBacklightBrightness())
        return msiEcHelper.setKeyboardBacklightBrightness(value);
    Q_UNUSED(value); // unsupported without a typed msi-ec sysfs node
}

void Operate::setUsbPowerShareState(bool enabled) const {
    Q_UNUSED(enabled); // arbitrary raw EC writes are unavailable
}

void Operate::setWebCamState(bool enabled) const {
    if (msiEcHelper.hasWebcam())
        return msiEcHelper.setWebcam(enabled);
}

bool Operate::setFnSuperSwapState(bool enabled) const {
    if (!msiEcHelper.hasFnWinSwap())
        return false;
    const bool verified = msiEcHelper.setFnWinSwap(enabled);
    if (verified)
        Settings::setValue(settingsGroup + QStringLiteral("FnSuperSwap"), enabled);
    return verified;
}

void Operate::setCoolerBoostState(bool enabled) const {
    if (msiEcHelper.hasCoolerBoost())
        return msiEcHelper.setCoolerBoost(enabled);
    Q_UNUSED(enabled); // unsupported without a typed msi-ec sysfs node
}

bool Operate::setUserMode(user_mode userMode) const {
    shift_mode shiftMode = shift_mode::comfort_mode;
    fan_mode fanMode = fan_mode::auto_fan_mode;
    bool superBattery = false;
    QString userModeStr;

    switch (userMode) {
        case user_mode::balanced_mode:
            userModeStr = "balanced_mode";
            break;
        case user_mode::performance_mode:
            shiftMode = shift_mode::turbo_mode; // sport on some devices?
            userModeStr = "performance_mode";
            break;
        case user_mode::silent_mode:
            fanMode = fan_mode::silent_fan_mode;
            userModeStr = "silent_mode";
            break;
        case user_mode::super_battery_mode:
            shiftMode = shift_mode::eco_mode;
            superBattery = true;
            userModeStr = "super_battery_mode";
            break;
        default:
            return false;
    }

    bool verified = true;
    if (msiEcHelper.hasShiftMode())
        verified = msiEcHelper.setShiftMode(shiftMode) && verified;
    if (msiEcHelper.hasFanMode())
        verified = msiEcHelper.setFanMode(fanMode) && verified;
    if (msiEcHelper.hasSuperBattery())
        verified = msiEcHelper.setSuperBattery(superBattery) && verified;

    Settings::setValue(settingsGroup + QStringLiteral("FanModeSetError"), !verified);
    if (!verified)
        return false;

    Settings::setValue(settingsGroup + QStringLiteral("UserMode"), userModeStr);
    // Silent and Super Battery must not inherit a stale Advanced preference.
    if (userMode == user_mode::silent_mode || userMode == user_mode::super_battery_mode)
        Settings::setValue(fanCurveSettingsGroup + QStringLiteral("Advanced"), false);
    return true;
}

std::optional<FanCurveResult> Operate::reconcileFanCurvePreference() const {
    Settings settings;
    if (!settings.getValue(savedFanCurveKey(QStringLiteral("Advanced"))).toBool())
        return std::nullopt;
    FanCurveProfile profile;
    if (!readVerifiedSavedFanCurve(&profile)) {
        FanCurveResult result;
        result.error = QStringLiteral("saved fan curve is unavailable or firmware-bound validation failed");
        result.effectiveMode = QStringLiteral("unknown");
        result.rollbackStatus = QStringLiteral("not-attempted");
        return result;
    }
    return applyFanCurve(profile);
}

void Operate::setFan1SpeedSettings(QVector<int> value) const {
    Q_UNUSED(value); // use applyFanCurve for one transactional operation
}

void Operate::setFan2SpeedSettings(QVector<int> value) const {
    Q_UNUSED(value);
}

void Operate::setFan1TempSettings(QVector<int> value) const {
    Q_UNUSED(value);
}

void Operate::setFan2TempSettings(QVector<int> value) const {
    Q_UNUSED(value);
}

void Operate::setFanMode(int value) const {
    Q_UNUSED(value); // raw EC fan mode writes are intentionally unavailable
}

bool Operate::setFanModeAdvanced(bool enabled) const {
    if (!msiEcHelper.hasFanMode())
        return false;
    if (!enabled) {
        if (!msiEcHelper.setFanMode(fan_mode::auto_fan_mode) ||
            getFanMode() != fan_mode::auto_fan_mode)
            return false;
        Settings::setValue(fanCurveSettingsGroup + QStringLiteral("Advanced"), false);
        return true;
    }
    FanCurveProfile profile;
    if (const auto current = getFanCurveProfile(); current.has_value())
        profile = *current;
    else if (!readVerifiedSavedFanCurve(&profile))
        return false;
    return applyFanCurve(profile).success;
}

int Operate::getValue(int address) const {
    helper.updateData();
    return helper.getValue(address);
}

bool Operate::isBatteryThresholdSupport() const {
    return msiEcHelper.hasBatteryEndThreshold();
}

bool Operate::isKeyboardBacklightModeSupport() const {
    // The old raw EC fallback is intentionally unavailable.
    return false;
}

bool Operate::isKeyboardBacklightSupport() const {
    if (msiEcHelper.hasKeyboardBacklightBrightness())
        return true;
    return false;
}

bool Operate::isUsbPowerShareSupport() const {
    // No typed msi-ec node exists in this ABI; do not expose a control that
    // would silently attempt a removed raw EC write.
    return false;
}

bool Operate::isWebCamOffSupport() const {
    // This checkbox controls the typed webcam state node used by the setter.
    return msiEcHelper.hasWebcam();
}

bool Operate::isFnSuperSwapSupport() const {
    return msiEcHelper.hasFnWinSwap();
}

bool Operate::isCoolerBoostSupport() const {
    return msiEcHelper.hasCoolerBoost();
}

namespace {
FanCurveResult preferenceFailure(const QString &error,
                                 const QString &effectiveMode = QStringLiteral("unknown")) {
    FanCurveResult result;
    result.error = error;
    result.effectiveMode = effectiveMode;
    result.rollbackStatus = QStringLiteral("not-attempted");
    return result;
}
}

std::optional<FanCurveResult> Operate::loadSettings() const {
    Settings s;
    std::optional<user_mode> savedMode;
    const QString savedModeKey = settingsGroup + QStringLiteral("UserMode");

    // Apply a validated saved mode first, even when firmware currently reports
    // Unknown. A readback-verified setter is the source of truth. An absent
    // mode does not prevent independent settings from being restored.
    if (s.isValueExist(savedModeKey)) {
        savedMode = parseSavedUserMode(s.getValue(savedModeKey).toString());
        if (!savedMode.has_value())
            return preferenceFailure(QStringLiteral("saved user mode is invalid"));
        if (!setUserMode(*savedMode))
            return preferenceFailure(QStringLiteral("saved user mode could not be verified"));
    }

    if (s.isValueExist(settingsGroup + QStringLiteral("FnSuperSwap")) &&
        !setFnSuperSwapState(s.getValue(settingsGroup + QStringLiteral("FnSuperSwap")).toBool()))
        return preferenceFailure(QStringLiteral("saved Fn/Super swap state could not be verified"));
    if (isUsbPowerShareSupport() && s.isValueExist(settingsGroup + QStringLiteral("UsbPowerShare")))
        setUsbPowerShareState(s.getValue(settingsGroup + QStringLiteral("UsbPowerShare")).toBool());

    const bool advancedRequested = s.getValue(savedFanCurveKey(QStringLiteral("Advanced"))).toBool();
    // Silent/Super Battery clear Advanced in setUserMode. Balanced/Performance
    // may restore a complete, firmware-bound verified profile.
    if (!advancedRequested || !savedMode.has_value() || !userModeMayOwnAdvanced(*savedMode))
        return std::nullopt;
    return reconcileFanCurvePreference();
}

std::optional<FanCurveResult> Operate::handleWakeEvent() const {
    Settings s;
    const QString savedModeKey = settingsGroup + QStringLiteral("UserMode");
    if (!s.isValueExist(savedModeKey))
        return std::nullopt;
    const auto savedMode = parseSavedUserMode(s.getValue(savedModeKey).toString());
    if (!savedMode.has_value())
        return preferenceFailure(QStringLiteral("resume saved user mode is invalid"));

    // The base mode owns resume. Restore and verify it before inspecting or
    // applying any optional curve so Silent/Super Battery cannot be overridden.
    if (!setUserMode(*savedMode))
        return preferenceFailure(QStringLiteral("resume user mode could not be verified"));

    const bool advancedRequested =
        s.getValue(savedFanCurveKey(QStringLiteral("Advanced"))).toBool();
    if (!advancedRequested || !userModeMayOwnAdvanced(*savedMode))
        return std::nullopt;

    FanCurveProfile profile;
    if (!readVerifiedSavedFanCurve(&profile)) {
        return preferenceFailure(
            QStringLiteral("saved fan curve is unavailable or firmware-bound validation failed"),
            fanModeString(getFanMode()));
    }
    return applyFanCurve(profile);
}

int Operate::detectFan1Address() const {
    int value_0xC9 = helper.getValue(fan1Address_0xC9);
    if (int value_0xCD = helper.getValue(fan1Address_0xCD); value_0xCD > 0)
        return fan1Address_0xCD;
    if (value_0xC9 > 0 && value_0xC9 < 50)
        return fan1Address_0xCD;
    return fan1Address_0xC9;
}

int Operate::detectBatteryThresholdAddress() const {
    if (128 <= helper.getValue(batteryThresholdAddress_0xEF) && helper.getValue(batteryThresholdAddress_0xEF) <= 228)
        return batteryThresholdAddress_0xEF;
    if (128 <= helper.getValue(batteryThresholdAddress_0xD7) && helper.getValue(batteryThresholdAddress_0xD7) <= 228)
        return batteryThresholdAddress_0xD7;
    return 0;
}

int Operate::detectFanModeAddress() const {
    if (int fanModeValue = helper.getValue(fanModeAddress_0xD4);
            fanModeValue == fanModeAuto ||
            fanModeValue == fanModeSilent ||
            fanModeValue == fanModeBasic ||
            fanModeValue == fanModeAdvanced)
        return fanModeAddress_0xD4;
    return fanModeAddress_0xF4;
}

int Operate::detectKeyboardBacklightAddress() const {
    int value_0xD3 = helper.getValue(keyboardBacklightAddress_0xD3);
    if (value_0xD3 == keyboardBacklight0ff ||
        value_0xD3 == keyboardBacklightLow ||
        value_0xD3 == keyboardBacklightMid ||
        value_0xD3 == keyboardBacklightHigh) {
        return keyboardBacklightAddress_0xD3;
    }
    
    int value_0xF3 = helper.getValue(keyboardBacklightAddress_0xF3);
    if (value_0xF3 == keyboardBacklight0ff ||
        value_0xF3 == keyboardBacklightLow ||
        value_0xF3 == keyboardBacklightMid ||
        value_0xF3 == keyboardBacklightHigh) {
        return keyboardBacklightAddress_0xF3;
    }

    return -1;
}
