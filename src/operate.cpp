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
#include "settings.h"

Helper helper;

const int cpuTempAddress = 0x68;
const int gpuTempAddress = 0x80;
const int batteryChargeAddress = 0x42;
int batteryThresholdAddress;
const int batteryThresholdAddress_0xEF = 0xEF;
const int batteryThresholdAddress_0xD7 = 0xD7;

const int batteryChargingStatusAddress = 0x31;
const int batteryNotCharging = 0x01;
const int batteryCharging = 0x03;
const int batteryDischarging = 0x05;
const int batteryFullyCharged = 0x09;
const int batteryFullyCharged_noPower = 0x0D;

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

const int webCamAddress = 0x2E;

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


// Modes
const int shiftModeAddress = 0xD2;
const int shiftMode0 = 0xC0;
const int shiftMode1 = 0xC1;
const int shiftMode2 = 0xC2;

int fanModeAddress;
const int fanModeAddress_0xD4 = 0xD4;
const int fanModeAddress_0xF4 = 0xF4;
const int fanModeAuto = 0x0D;
const int fanModeSilent = 0x1D;
const int fanModeBasic = 0x4D;
const int fanModeAdvanced = 0x8D;

const int superBatteryModeAddress = 0xEB;

const QString settingsGroup = "Settings/";

Operate::Operate() = default;

void Operate::closeHelperApp() const {
    helper.quit();
}

bool Operate::isEcSysModuleLoaded() const {
    return helper.isEcSysModuleLoaded();
}

bool Operate::loadEcSysModule() const {
    return helper.loadEcSysModule();
}

bool Operate::updateEcData() const {
    return helper.updateData();
}

void Operate::updateEcDataAsync() const {
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
    return helper.getValues(160, 12).toStdString();
}

std::string Operate::getEcBuild() const {
    std::string s = helper.getValues(172, 16).toStdString();
    if (s.size() < 16)
        return s;
    return s.substr(0, 2) + "/" + s.substr(2, 2) + "/" + s.substr(4, 4) + " " + s.substr(8, 8);
}

int Operate::getBatteryCharge() const {
    return helper.getValue(batteryChargeAddress) - 1;
}

int Operate::getBatteryThreshold() const {
    return helper.getValue(batteryThresholdAddress) - 128;
}

charging_state Operate::getChargingStatus() const {
    switch (helper.getValue(batteryChargingStatusAddress)) {
        case batteryCharging:
            return charging_state::battery_charging;
        case batteryDischarging:
            return charging_state::battery_discharging;
        case batteryNotCharging:
            return charging_state::battery_not_charging;
        case batteryFullyCharged:
            return charging_state::battery_fully_charged;
        case batteryFullyCharged_noPower:
            return charging_state::battery_fully_charged_no_power;
        default:
            return charging_state::battery_unknown;
    }
}

int Operate::getCpuTemp() const {
    return helper.getValue(cpuTempAddress);
}

int Operate::getGpuTemp() const {
    return helper.getValue(gpuTempAddress);
}

int Operate::getFan1Speed() const {
    // Read 2 bytes (big-endian)
    int value0 = helper.getValue(fan1Address);
    int value1 = helper.getValue(fan1Address - 1);
    int value = (value1 << 8) | value0;
    if (value > 0)
        return 470000 / value;
    return value;
}

int Operate::getFan2Speed() const {
    // Read 2 bytes (big-endian)
    int value0 = helper.getValue(fan2Address);
    int value1 = helper.getValue(fan2Address - 1);
    int value = (value1 << 8) | value0;
    if (value > 0)
        return 470000 / value;
    return value;
}

QVector<int> Operate::getFan1SpeedSettings() const {
    QVector<int> a;
    for (int i = 0; i < fanSpeedSettingsCount; i++) {
        a.push_back(helper.getValue(fan1SpeedSettingStartAddress + i));
    }
    return a;
}

QVector<int> Operate::getFan2SpeedSettings() const {
    QVector<int> a;
    for (int i = 0; i < fanSpeedSettingsCount; i++) {
        a.push_back(helper.getValue(fan2SpeedSettingStartAddress + i));
    }
    return a;
}

QVector<int> Operate::getFan1TempSettings() const {
    QVector<int> a;
    for (int i = 0; i < fanTempSettingsCount; i++) {
        a.push_back(helper.getValue(fan1TempSettingStartAddress + i));
    }
    return a;
}

QVector<int> Operate::getFan2TempSettings() const {
    QVector<int> a;
    for (int i = 0; i < fanTempSettingsCount; i++) {
        a.push_back(helper.getValue(fan2TempSettingStartAddress + i));
    }
    return a;
}

int Operate::getKeyboardBacklightMode() const {
    if (helper.getValue(keyboardBacklightModeAddress) == keyboardBacklightAutoTurnOff)
        return 1;
    return 0;
}

int Operate::getKeyboardBrightness() const {
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
    if (helper.getValue(webCamAddress) / 2 % 2 != 0)
        return true;
    return false;
}

bool Operate::getFnSuperSwapState() const {
    if (helper.getValue(fnSuperSwapAddress) / 16 % 2 != 0)
        return true;
    return false;
}

bool Operate::getCoolerBoostState() const {
    if (helper.getValue(coolerBoostAddress) > 127)
        return true;
    return false;
}

user_mode Operate::getUserMode() const {
    switch (helper.getValue(shiftModeAddress)) {
        case shiftMode0:
            return user_mode::performance_mode;
        case shiftMode1:
            if (helper.getValue(fanModeAddress) == fanModeSilent)
                return user_mode::silent_mode;
            return user_mode::balanced_mode;
        case shiftMode2:
            return user_mode::super_battery_mode;
        default:
            return user_mode::unknown_mode;
    }
}

fan_mode Operate::getFanMode() const {
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

void Operate::setBatteryThreshold(int value) const {
    if (value != getBatteryThreshold())
        helper.putValue(batteryThresholdAddress, value + 128);
}

void Operate::setKeyboardBacklightMode(int value) const {
    int resValue = keyboardBacklightAlwaysOn;
    if (value == 1)
        resValue = keyboardBacklightAutoTurnOff;
    helper.putValue(keyboardBacklightModeAddress, resValue);
}

void Operate::setKeyboardBrightness(int value) const {
    int resValue;
    switch (value) {
        case 0:
            resValue = keyboardBacklight0ff;
            break;
        case 1:
            resValue = keyboardBacklightLow;
            break;
        case 2:
            resValue = keyboardBacklightMid;
            break;
        case 3:
            resValue = keyboardBacklightHigh;
            break;
        default:
            resValue = keyboardBacklight0ff;
    }
    helper.putValue(keyboardBacklightAddress, resValue);
}

void Operate::setUsbPowerShareState(bool enabled) const {
    int value = enabled ? usbPowerShareOn : usbPowerShareOff;
    helper.putValue(usbPowerShareAddress, value);
    Settings::setValue(settingsGroup + "UsbPowerShare", enabled);
}

void Operate::setWebCamState(bool enabled) const {
    if (getWebCamState() == enabled)
        return;
    int value = helper.getValue(webCamAddress) + (enabled ? 2 : -2);
    helper.putValue(webCamAddress, value);
}

void Operate::setFnSuperSwapState(bool enabled) const {
    if (getFnSuperSwapState() == enabled)
        return;
    int value = helper.getValue(fnSuperSwapAddress) + (enabled ? 16 : -16);
    helper.putValue(fnSuperSwapAddress, value);
    Settings::setValue(settingsGroup + "FnSuperSwap", enabled);
}

void Operate::setCoolerBoostState(bool enabled) const {
    int value = helper.getValue(coolerBoostAddress);
    if (enabled && (value < 128))
        helper.putValue(coolerBoostAddress, value + 128);
    if (!enabled && (value > 127))
        helper.putValue(coolerBoostAddress, value - 128);
}

void Operate::setUserMode(user_mode userMode) const {
    switch (userMode) {
        case user_mode::balanced_mode:
            helper.putValue(shiftModeAddress, shiftMode1);
            setFanMode(fanModeAuto);
            putSuperBatteryModeValue(false);
            Settings::setValue(settingsGroup + "UserMode", "balanced_mode");
            break;
        case user_mode::performance_mode:
            helper.putValue(shiftModeAddress, shiftMode0);
            setFanMode(fanModeAuto);
            putSuperBatteryModeValue(false);
            Settings::setValue(settingsGroup + "UserMode", "performance_mode");
            break;
        case user_mode::silent_mode:
            helper.putValue(shiftModeAddress, shiftMode1);
            setFanMode(fanModeSilent);
            putSuperBatteryModeValue(false);
            Settings::setValue(settingsGroup + "UserMode", "silent_mode");
            break;
        case user_mode::super_battery_mode:
            helper.putValue(shiftModeAddress, shiftMode2);
            setFanMode(fanModeAuto);
            putSuperBatteryModeValue(true);
            Settings::setValue(settingsGroup + "UserMode", "super_battery_mode");
            break;
        default:
            break;
    }
}

void Operate::setFan1SpeedSettings(QVector<int> value) const {
    if (value.size() != fanSpeedSettingsCount)
        return;
    for (int i = 0; i < value.size(); i++) {
        helper.putValue(fan1SpeedSettingStartAddress + i, value[i]);
    }
    Settings::setValue(settingsGroup + QString("fan1SpeedSettings"), value);
}

void Operate::setFan2SpeedSettings(QVector<int> value) const {
    if (value.size() != fanSpeedSettingsCount)
        return;
    for (int i = 0; i < value.size(); i++) {
        helper.putValue(fan2SpeedSettingStartAddress + i, value[i]);
    }
    Settings::setValue(settingsGroup + QString("fan2SpeedSettings"), value);
}

void Operate::setFan1TempSettings(QVector<int> value) const {
    if (value.size() != fanTempSettingsCount)
        return;
    for (int i = 0; i < value.size(); i++) {
        helper.putValue(fan1TempSettingStartAddress + i, value[i]);
    }
    Settings::setValue(settingsGroup + QString("fan1TempSettings"), value);
}

void Operate::setFan2TempSettings(QVector<int> value) const {
    if (value.size() != fanTempSettingsCount)
        return;
    for (int i = 0; i < value.size(); i++) {
        helper.putValue(fan2TempSettingStartAddress + i, value[i]);
    }
    Settings::setValue(settingsGroup + QString("fan2TempSettings"), value);
}

void Operate::setFanMode(int value) const {
    if (helper.getValue(fanModeAddress) == fanModeAdvanced)
        return;
    helper.putValue(fanModeAddress, value);
}

void Operate::setFanModeAdvanced(bool enabled) const {
    if (enabled)
        helper.putValue(fanModeAddress, fanModeAdvanced);
    else
        helper.putValue(fanModeAddress, fanModeAuto);
    Settings::setValue(settingsGroup + "fanModeAdvanced", enabled);
}

int Operate::getValue(int address) const {
    helper.updateData();
    return helper.getValue(address);
}

void Operate::setValue(int address, int value) const {
    helper.putValue(address, value);
}

bool Operate::isBatteryThresholdSupport() const {
    return batteryThresholdAddress != 0;
}

bool Operate::isKeyboardBacklightModeSupport() const {
    // Backlight mode is not available for all keyboard with backlight
    
    // Keep the same behaviour for devices with brightness at 0xD3
    if (keyboardBacklightAddress == keyboardBacklightAddress_0xD3)
        return true;
    
    // By security, we concider that devices with brightness at 0xF3 don't have backlight mode
    return false;
}

bool Operate::isKeyboardBacklightSupport() const {
    return keyboardBacklightAddress != -1;
}

bool Operate::isUsbPowerShareSupport() const {
    return (helper.getValue(usbPowerShareAddress) == usbPowerShareOff ||
            helper.getValue(usbPowerShareAddress) == usbPowerShareOn);
}

bool Operate::isWebCamOffSupport() const {
    return helper.getValue(webCamAddress) > 0;
}

void Operate::loadSettings() const {
    Settings s;

    if (getUserMode() != user_mode::unknown_mode && s.isValueExist(settingsGroup + "UserMode")) {
        QString value = s.getValue(settingsGroup + "UserMode").toString();
        if (value == "balanced_mode")
            setUserMode(user_mode::balanced_mode);
        else if (value == "performance_mode")
            setUserMode(user_mode::performance_mode);
        else if (value == "silent_mode")
            setUserMode(user_mode::silent_mode);
        else if (value == "super_battery_mode")
            setUserMode(user_mode::super_battery_mode);
    }

    if (s.isValueExist(settingsGroup + "FnSuperSwap"))
        setFnSuperSwapState(s.getValue(settingsGroup + "FnSuperSwap").toBool());
    if (isUsbPowerShareSupport() && s.isValueExist(settingsGroup + "UsbPowerShare"))
        setUsbPowerShareState(s.getValue(settingsGroup + "UsbPowerShare").toBool());

    if (s.isValueExist(settingsGroup + "fan1SpeedSettings"))
        setFan1SpeedSettings(s.getValueVector(settingsGroup + "fan1SpeedSettings"));
    if (s.isValueExist(settingsGroup + "fan2SpeedSettings"))
        setFan2SpeedSettings(s.getValueVector(settingsGroup + "fan2SpeedSettings"));
    if (s.isValueExist(settingsGroup + "fan1TempSettings"))
        setFan1TempSettings(s.getValueVector(settingsGroup + "fan1TempSettings"));
    if (s.isValueExist(settingsGroup + "fan2TempSettings"))
        setFan2TempSettings(s.getValueVector(settingsGroup + "fan2TempSettings"));
    if (s.isValueExist(settingsGroup + "fanModeAdvanced"))
        setFanModeAdvanced(s.getValue(settingsGroup + "fanModeAdvanced").toBool());
}

void Operate::putSuperBatteryModeValue(bool enabled) const {
    if ((helper.getValue(superBatteryModeAddress) / 15 % 2 != 0) == enabled)
        return;
    int currValue = helper.getValue(superBatteryModeAddress);
    helper.putValue(superBatteryModeAddress, currValue + (enabled ? 15 : -15));
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
