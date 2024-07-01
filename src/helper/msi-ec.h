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

#ifndef MSI_EC_H
#define MSI_EC_H

#include "service.h"

#include <QtCore/QObject>
#include <QtDBus/QDBusAbstractAdaptor>
#include <QtDBus/QDBusVariant>

/**
 * Interface for [msi-ec by BeardOverflow](https://github.com/BeardOverflow/msi-ec/)
 */
class MsiEc : public QDBusAbstractAdaptor {
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", INTERFACE_NAME_MSI_EC)
public:
    explicit MsiEc(QObject *parent) : QDBusAbstractAdaptor(parent) {}

private:
    QString readFile(QString path) const;
    bool readFileOnOff(QString path) const;
    void writeFile(QString path, QString value) const;
    void writeFileOnOff(QString path, bool on) const;

public slots:
    [[nodiscard]] bool isMsiEcModuleLoaded() const;

    // webcam on/off
    [[nodiscard]] bool hasWebcam() const;
    [[nodiscard]] bool getWebcam() const;
    Q_NOREPLY void setWebcam(bool enable) const;

    // webcam_block on/off
    [[nodiscard]] bool hasWebcamBlock() const;
    [[nodiscard]] bool getWebcamBlock() const;
    Q_NOREPLY void setWebcamBlock(bool enable) const;

    // fn_key left/right
    [[nodiscard]] bool hasFnKey() const;
    [[nodiscard]] QString getFnKey() const;
    Q_NOREPLY void setFnKey(QString side) const;
    // win_key left/right
    [[nodiscard]] bool hasWinKey() const;
    [[nodiscard]] QString getWinKey() const;
    Q_NOREPLY void setWinKey(QString side) const;
    // fn_win_swap swap/no swap
    [[nodiscard]] bool hasFnWinSwap() const;
    [[nodiscard]] bool getFnWinSwap() const;
    Q_NOREPLY void setFnWinSwap(bool swap) const;

    // battery_mode
    [[nodiscard]] bool hasBatteryMode() const;
    [[nodiscard]] QString getBatteryMode() const;
    Q_NOREPLY void setBatteryMode(QString mode) const;

    // cooler_boost
    [[nodiscard]] bool hasCoolerBoost() const;
    [[nodiscard]] bool getCoolerBoost() const;
    Q_NOREPLY void setCoolerBoost(bool enable) const;

    // shift_mode & available_shift_modes
    [[nodiscard]] bool hasShiftMode() const;
    [[nodiscard]] QString getAvailableShiftModes() const;
    [[nodiscard]] QString getShiftMode() const;
    Q_NOREPLY void setShiftMode(QString mode) const;

    // super_battery
    [[nodiscard]] bool hasSuperBattery() const;
    [[nodiscard]] bool getSuperBattery() const;
    Q_NOREPLY void setSuperBattery(bool enable) const;

    // fan_mode & available_fan_modes
    [[nodiscard]] bool hasFanMode() const;
    [[nodiscard]] QString getAvailableFanModes() const;
    [[nodiscard]] QString getFanMode() const;
    Q_NOREPLY void setFanMode(QString mode) const;

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
    [[nodiscard]] int getGPURealtimeTemperature() const;
    // gpu/realtime_fan_speed 0-100 (percent)
    [[nodiscard]] bool hasGPURealtimeFanSpeed() const;
    [[nodiscard]] int getGPURealtimeFanSpeed() const;

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
};

#endif // MSI_EC_H
