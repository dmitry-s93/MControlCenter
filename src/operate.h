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

#ifndef OPERATE_H
#define OPERATE_H


#include <string>

enum charging_state
{
    battery_charging,
    battery_discharging,
    battery_not_charging,
    battery_fully_charged,
    battery_fully_charged_no_power,
    battery_unknown
};

class Operate
{
public:
    Operate();
    void closeHelperApp();
    bool updateEcData();
    bool doProbe();
    std::string getEcVersion();
    std::string getEcBuild();
    int getBatteryCharge();
    int getBatteryThreshold();
    charging_state getChargingStatus();
    int getCpuTemp();
    int getGpuTemp();
    int getFan1Speed();
    int getFan2Speed();

    int getKeybordBacklightMode();
    int getKeyboardBrightness();
    bool getUsbPowerShareState();
    bool getWebCamState();
    bool getFnSuperSwapState();
    bool getCoolerBoostState();

    void setBatteryThreshold(int value);
    void setKeyoardBacklightMode(int value);
    void setKeybordBrightness(int value);
    void setUsbPowerShareState(bool enabled);
    void setWebCamState(bool enabled);
    void setFnSuperSwapState(bool enabled);
    void setCoolerBoostState(bool enabled);

    int getValue(int address);
    void setValue(int address, int value);

    bool isBatteryThresholdSupport();
    bool isKeyboardBacklightSupport();
    bool isUsbPowerShareSupport();
    bool isWebCamOffSupport();
    bool isFnSuperSwapSupport();
};

#endif // OPERATE_H
