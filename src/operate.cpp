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
const int tileAddress = 0xE9;

const int webCamAddress = 0x2E;
const int webCamOff = 0x08;
const int webCamOn = 0x0A;

const int fnSuperSwapAddress = 0xE8;
const int fnSuperSwapOff = 0x00;
const int fnSuperSwapOn = 0x10;

const int fan1Address = 0xC9;
const int fan2Address = 0xCB;

bool batteryThresholdSupport = false;
bool keyboardBacklightSupport = false;
bool usbPowerShareSupport = false;
bool webCamOffSupport = false;
bool fnSuperSwapSupport = false;

Operate::Operate()
{

}

void Operate::closeHelperApp()
{
    helper.quit();
}

bool Operate::updateEcData()
{
    return helper.updateData();
}

bool Operate::doProbe()
{
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

    if (helper.getValue(usbPowerShareAddress) == usbPowerShareOff || helper.getValue(usbPowerShareAddress) == usbPowerShareOn)
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

std::string Operate::getEcVersion()
{
        return helper.getValues(160, 12).toStdString();
}

std::string Operate::getEcBuild()
{
    std::string s = helper.getValues(172, 16).toStdString();
    if (s.size() < 16)
        return s;
    return s.substr(0, 2) + "/" + s.substr(2, 2) + "/" + s.substr(4, 4) + " " + s.substr(8, 8);
}

int Operate::getBatteryCharge()
{
    return helper.getValue(batteryChargeAddress);
}

int Operate::getBatteryThreshold()
{
    return helper.getValue(batteryThresholdAddress) - 128;
}

charging_state Operate::getChargingStatus()
{
    switch (helper.getValue(batteryChargingStatusAddress)) {
        case batteryCharging:
            return battery_charging;
        case batteryDischarging:
            return battery_discharging;
        case batteryNotCharging:
            return battery_not_charging;
        case batteryFullyCharged:
            return battery_fully_charged;
        case batteryFullyCharged_noPower:
            return battery_fully_charged_no_power;
        default:
            return battery_unknown;
    }
}

int Operate::getCpuTemp()
{
    return helper.getValue(cpuTempAddress);
}

int Operate::getGpuTemp()
{
    return helper.getValue(gpuTempAddress);
}

int Operate::getFan1Speed()
{
    int value = helper.getValue(fan1Address);
    if (value > 0)
        return 470000 / value;
    return value;
}

int Operate::getFan2Speed()
{
    int value = helper.getValue(fan2Address);
    if (value > 0)
        return 470000 / value;
    return value;
}

int Operate::getKeybordBacklightMode()
{
    if (helper.getValue(keyboardBacklightModeAddress) == keyboardBacklightAutoTurnOff)
        return 1;
    return 0;
}

int Operate::getKeyboardBrightness()
{
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

bool Operate::getUsbPowerShareState()
{
    if (helper.getValue(usbPowerShareAddress) == usbPowerShareOn)
        return true;
    return false;
}

bool Operate::getWebCamState()
{
    if (helper.getValue(webCamAddress) == webCamOn)
        return true;
    return false;
}

bool Operate::getFnSuperSwapState()
{
    if (helper.getValue(fnSuperSwapAddress) == fnSuperSwapOn)
        return true;
    return false;
}

bool Operate::getCoolerBoostState()
{
    if (helper.getValue(coolerBoostAddress) > 127)
        return true;
    return false;
}

void Operate::setBatteryThreshold(int value)
{
    if (value != getBatteryThreshold())
        helper.putValue(batteryThresholdAddress, value + 128);
}

void Operate::setKeyoardBacklightMode(int value)
{
    int resValue = keyboardBacklightAlwaysOn;
    if (value == 1)
        resValue = keyboardBacklightAutoTurnOff;
    helper.putValue(keyboardBacklightModeAddress, resValue);
}

void Operate::setKeybordBrightness(int value)
{
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

void Operate::setUsbPowerShareState(bool enabled)
{
    int value = enabled ? usbPowerShareOn : usbPowerShareOff;
    helper.putValue(usbPowerShareAddress, value);
}

void Operate::setWebCamState(bool enabled)
{
    int value = enabled ? webCamOn : webCamOff;
    helper.putValue(webCamAddress, value);
}

void Operate::setFnSuperSwapState(bool enabled)
{
    int value = enabled ? fnSuperSwapOn : fnSuperSwapOff;
    helper.putValue(fnSuperSwapAddress, value);
}

void Operate::setCoolerBoostState(bool enabled)
{
    int value = helper.getValue(coolerBoostAddress);
    if (enabled && (value < 128))
        helper.putValue(coolerBoostAddress, value + 128);
    if (!enabled && (value > 127))
        helper.putValue(coolerBoostAddress, value - 128);
}

int Operate::getValue(int address)
{
    helper.updateData();
    return helper.getValue(address);
}

void Operate::setValue(int address, int value)
{
    helper.putValue(address, value);
}

bool Operate::isBatteryThresholdSupport()
{
    return batteryThresholdSupport;
}

bool Operate::isKeyboardBacklightSupport()
{
    return keyboardBacklightSupport;
}

bool Operate::isUsbPowerShareSupport()
{
    return usbPowerShareSupport;
}

bool Operate::isWebCamOffSupport()
{
    return webCamOffSupport;
}

bool Operate::isFnSuperSwapSupport()
{
    return fnSuperSwapSupport;
}
