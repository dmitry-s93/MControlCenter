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

Helper helper;

const int cpuTempAddress = 0x68;
const int gpuTempAddress = 0x80;
const int batteryChargeAddress = 0x42;
int batteryThresholdAddress;

const int batteryChargingStatusAddress = 0x31;
const int batteryNotCharging = 0x01;
const int batteryCharging = 0x03;
const int batteryDischarging = 0x05;
const int batteryFullyCharged = 0x09;
const int batteryFullyCharged_noPower = 0x0D;

const int keyboardBacklightModeAddress = 0x2C;
const int keyboardBacklightAlwaysOn = 0x00;
const int keyboardBacklightAutoTurnOff = 0x08;

const int keyboardBacklightAddress = 0xD3;
const int keyboardBacklight0ff = 0x80;
const int keyboardBacklightLow = 0x81;
const int keyboardBacklightMid = 0x82;
const int keyboardBacklightHigh = 0x83;

const int usbPowerShareAddress = 0xBF;
const int usbPowerShareOff = 0x08;
const int usbPowerShareOn = 0x28;

const int coolerBoostAddress = 0x98;

const int webCamAddress = 0x2E;
const int webCamOff = 0x08;
const int webCamOn = 0x0A;

const int fnSuperSwapAddress = 0xE8;
const int fnSuperSwapOff = 0x00;
const int fnSuperSwapOn = 0x10;

const int fan1Address = 0xC9;
const int fan2Address = 0xCB;

// Modes
const int shiftModeAddress = 0xD2;
const int shiftMode0 = 0xC0;
const int shiftMode1 = 0xC1;
const int shiftMode2 = 0xC2;

const int fanModeAddress = 0xD4;
const int fanModeAuto = 0x0D;
const int fanModeSilent = 0x1D;
const int fanModeAdvanced = 0x4D;

const int superBatteryModeAddress = 0xEB;
const int superBatteryModeOff = 0x00;
const int superBatteryModeOn = 0x0F;

bool batteryThresholdSupport = false;
bool keyboardBacklightSupport = false;
bool usbPowerShareSupport = false;
bool webCamOffSupport = false;
bool fnSuperSwapSupport = false;

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

bool Operate::doProbe() const {
    int thresholdAddr0 = 0xEF;
    int thresholdAddr1 = 0xD7;
    // Check for charging threshold support
    if (128 <= helper.getValue(thresholdAddr0) && helper.getValue(thresholdAddr0) <= 228) {
        batteryThresholdAddress = thresholdAddr0;
        batteryThresholdSupport = true;
    } else {
        if (128 <= helper.getValue(thresholdAddr1) && helper.getValue(thresholdAddr1) <= 228) {
            batteryThresholdAddress = thresholdAddr1;
            batteryThresholdSupport = true;
        }
    }

    if (helper.getValue(usbPowerShareAddress) == usbPowerShareOff ||
        helper.getValue(usbPowerShareAddress) == usbPowerShareOn)
        usbPowerShareSupport = true;

    if (helper.getValue(webCamAddress) == webCamOff || helper.getValue(webCamAddress) == webCamOn)
        webCamOffSupport = true;

    if (helper.getValue(fnSuperSwapAddress) == fnSuperSwapOff || helper.getValue(fnSuperSwapAddress) == fnSuperSwapOn)
        fnSuperSwapSupport = true;

    if (
            helper.getValue(keyboardBacklightAddress) == keyboardBacklight0ff ||
            helper.getValue(keyboardBacklightAddress) == keyboardBacklightLow ||
            helper.getValue(keyboardBacklightAddress) == keyboardBacklightMid ||
            helper.getValue(keyboardBacklightAddress) == keyboardBacklightHigh)
        keyboardBacklightSupport = true;

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
    return helper.getValue(batteryChargeAddress);
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
    int value = helper.getValue(fan1Address);
    if (value > 0)
        return 470000 / value;
    return value;
}

int Operate::getFan2Speed() const {
    int value = helper.getValue(fan2Address);
    if (value > 0)
        return 470000 / value;
    return value;
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
    if (helper.getValue(webCamAddress) == webCamOn)
        return true;
    return false;
}

bool Operate::getFnSuperSwapState() const {
    if (helper.getValue(fnSuperSwapAddress) == fnSuperSwapOn)
        return true;
    return false;
}

bool Operate::getCoolerBoostState() const {
    if (helper.getValue(coolerBoostAddress) > 127)
        return true;
    return false;
}

user_mode Operate::getUserMode() const {
    int shiftMode = helper.getValue(shiftModeAddress);
    int fanMode = helper.getValue(fanModeAddress);
    int superBattery = helper.getValue(superBatteryModeAddress);

    if (shiftMode == shiftMode0)
        return user_mode::performance_mode;

    if (shiftMode == shiftMode1 && fanMode == fanModeAuto)
        return user_mode::balanced_mode;

    if (shiftMode == shiftMode1 && fanMode == fanModeSilent)
        return user_mode::silent_mode;

    if (shiftMode == shiftMode2 && superBattery == superBatteryModeOn)
        return user_mode::super_battery_mode;

    return user_mode::unknown_mode;
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
}

void Operate::setWebCamState(bool enabled) const {
    int value = enabled ? webCamOn : webCamOff;
    helper.putValue(webCamAddress, value);
}

void Operate::setFnSuperSwapState(bool enabled) const {
    int value = enabled ? fnSuperSwapOn : fnSuperSwapOff;
    helper.putValue(fnSuperSwapAddress, value);
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
            helper.putValue(fanModeAddress, fanModeAuto);
            helper.putValue(superBatteryModeAddress, superBatteryModeOff);
            break;
        case user_mode::performance_mode:
            helper.putValue(shiftModeAddress, shiftMode0);
            helper.putValue(fanModeAddress, fanModeAuto);
            helper.putValue(superBatteryModeAddress, superBatteryModeOff);
            break;
        case user_mode::silent_mode:
            helper.putValue(shiftModeAddress, shiftMode1);
            helper.putValue(fanModeAddress, fanModeSilent);
            helper.putValue(superBatteryModeAddress, superBatteryModeOff);
            break;
        case user_mode::super_battery_mode:
            helper.putValue(shiftModeAddress, shiftMode2);
            helper.putValue(fanModeAddress, fanModeAuto);
            helper.putValue(superBatteryModeAddress, superBatteryModeOn);
            break;
        default:
            break;
    }
}

int Operate::getValue(int address) const {
    helper.updateData();
    return helper.getValue(address);
}

void Operate::setValue(int address, int value) const {
    helper.putValue(address, value);
}

bool Operate::isBatteryThresholdSupport() const {
    return batteryThresholdSupport;
}

bool Operate::isKeyboardBacklightSupport() const {
    return keyboardBacklightSupport;
}

bool Operate::isUsbPowerShareSupport() const {
    return usbPowerShareSupport;
}

bool Operate::isWebCamOffSupport() const {
    return webCamOffSupport;
}

bool Operate::isFnSuperSwapSupport() const {
    return fnSuperSwapSupport;
}
