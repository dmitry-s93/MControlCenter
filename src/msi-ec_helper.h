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

#ifndef MSI_EC_HELPER_H
#define MSI_EC_HELPER_H

#include "operate.h"
#include <QtCore/QObject>
#include <QtDBus/QDBusInterface>

class MsiEcHelper : public QObject {
    Q_OBJECT
public:
    MsiEcHelper();

    [[nodiscard]] bool isMsiEcModuleLoaded();

    // webcam on/off
    [[nodiscard]] bool hasWebcam() const;
    [[nodiscard]] bool getWebcam() const;
    Q_NOREPLY void setWebcam(bool enable) const;

    // webcam_block on/off
    [[nodiscard]] bool hasWebcamBlock() const;
    [[nodiscard]] bool getWebcamBlock() const;
    Q_NOREPLY void setWebcamBlock(bool enable) const;

    // fn_win_swap swap/no swap
    [[nodiscard]] bool hasFnWinSwap() const;
    [[nodiscard]] bool getFnWinSwap() const;
    Q_NOREPLY void setFnWinSwap(bool swap) const;

    // cooler_boost
    [[nodiscard]] bool hasCoolerBoost() const;
    [[nodiscard]] bool getCoolerBoost() const;
    Q_NOREPLY void setCoolerBoost(bool enable) const;

    // shift_mode & available_shift_modes
    [[nodiscard]] bool hasShiftMode() const;
    [[nodiscard]] QList<shift_mode> getAvailableShiftModes() const;
    [[nodiscard]] shift_mode getShiftMode() const;
    Q_NOREPLY void setShiftMode(shift_mode mode) const;

    // super_battery
    [[nodiscard]] bool hasSuperBattery() const;
    [[nodiscard]] bool getSuperBattery() const;
    Q_NOREPLY void setSuperBattery(bool enable) const;

    // fan_mode & available_fan_modes
    [[nodiscard]] bool hasFanMode() const;
    [[nodiscard]] QList<fan_mode> getAvailableFanModes() const;
    [[nodiscard]] fan_mode getFanMode() const;
    Q_NOREPLY void setFanMode(fan_mode mode) const;

    // fw_version
    [[nodiscard]] QString getFWVersion() const;
    // fw_release_date
    [[nodiscard]] QString getFWReleaseDate() const;

    // cpu/realtime_temperature 0-100 (celsius scale)
    [[nodiscard]] bool hasCPURealtimeTemperature() const;
    [[nodiscard]] int getCPURealtimeTemperature() const;
    // cpu/realtime_fan_speed 0-100 (percent)
    [[nodiscard]] bool hasCPURealtimeFanSpeed() const;
    [[nodiscard]] int getCPURealtimeFanSpeed() const;
    // cpu/basic_fan_speed 0-100 (percent)
    [[nodiscard]] bool hasCPUBasicFanSpeed() const;
    [[nodiscard]] int getCPUBasicFanSpeed() const;
    Q_NOREPLY void setCPUBasicFanSpeed(int value) const;

    // gpu/realtime_temperature 0-100 (celsius scale)
    [[nodiscard]] bool hasGPURealtimeTemperature() const;
    [[nodiscard]] std::optional<int> getGPURealtimeTemperature() const;
    // gpu/realtime_fan_speed 0-100 (percent)
    [[nodiscard]] bool hasGPURealtimeFanSpeed() const;
    [[nodiscard]] std::optional<int> getGPURealtimeFanSpeed() const;

    // BAT1/charge_control_start_threshold 0-100 (percent)
    [[nodiscard]] bool hasBatteryStartThreshold() const;
    [[nodiscard]] int getBatteryStartThreshold() const;
    Q_NOREPLY void setBatteryStartThreshold(int value) const;

    // BAT1/charge_control_end_threshold 0-100 (percent)
    [[nodiscard]] bool hasBatteryEndThreshold() const;
    [[nodiscard]] int getBatteryEndThreshold() const;
    Q_NOREPLY void setBatteryEndThreshold(int value) const;

    // BAT1/capacity 0-100 (percent)
    [[nodiscard]] bool hasBatteryCapacity() const;
    [[nodiscard]] int getBatteryCapacity() const;

    // BAT1/status
    [[nodiscard]] bool hasBatteryStatus() const;
    [[nodiscard]] QString getBatteryStatus() const;

    // kbd_backlight/brightness 0-3
    [[nodiscard]] bool hasKeyboardBacklightBrightness() const;
    [[nodiscard]] int getKeyboardBacklightBrightness() const;
    Q_NOREPLY void setKeyboardBacklightBrightness(int value) const;

private:
    QDBusInterface *iface;
    void printError(QDBusError const &error) const;

    template <typename T>
    [[nodiscard]] std::optional<T> getOptionalValue(QString method) const;
    template <typename T>
    [[nodiscard]] T getValue(QString method, T defaultValue) const;
    template <typename T>
    Q_NOREPLY void setValue(QString method, T value) const;
};

#endif // MSI_EC_HELPER_H
