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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QSystemTrayIcon>
#include <QtWidgets>
#include <QDBusPendingCallWatcher>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateData();
    static void setUpdateDataError(bool error);

private:
    Ui::MainWindow *ui;

    void setTabsEnabled(bool enabled);
    void startRealtimeUpdate() const;
    void stopRealtimeUpdate() const;
    void setUpdateInterval(int msec) const;
    void realtimeUpdate();
    void loadConfigs();

    [[nodiscard]] QString intToQString(int value) const;
    void updateBatteryCharge();
    void updateBatteryThreshold();
    void updateChargingStatus();
    void updateCpuTemp();
    void updateGpuTemp();
    void updateFan1Speed();
    void updateFan2Speed();
    void updateKeyboardBacklightMode();
    void updateKeyboardBrightness();
    void updateUsbPowerShareState();
    void updateWebCamState() const;
    void updateFnSuperSwapState();
    void updateCoolerBoostState() const;
    void updateUserMode();
    void updateFanMode();
    void updateFanSpeedSettings();

    void setBestMobility();
    void setBalancedBattery();
    void setBestBattery();

    void setHighPerformanceMode();
    void setBalancedMode();
    void setSilentMode();
    void setSuperBatteryMode();

    void setCoolerBoostState(bool enabled) const;

    QVector<int> getFan1SpeedValues() const;
    QVector<int> getFan2SpeedValues() const;
    QVector<int> getFan1TempValues() const;
    QVector<int> getFan2TempValues() const;
    void setFanSpeedSettings();
    void setFanModeAdvanced(bool enabled) const;
    void checkFanSettingsChanged() const;

    void showEvent(QShowEvent *event);
    void closeEvent(QCloseEvent *event);
    void quitApp() const;

    void createTrayIcon();
    void createActions();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void saveStateRequest(QSessionManager &sessionManager);

    QSystemTrayIcon *trayIcon = nullptr;;
    QMenu *trayIconMenu = nullptr;
    QMenu *modeTrayMenu = nullptr;
    QMenu *fanTrayMenu = nullptr;
    QMenu *batteryTrayMenu = nullptr;

    QAction *coolerBoostAction = nullptr;

    QAction *highPerformanceMode = nullptr;
    QAction *balancedMode = nullptr;
    QAction *silentMode = nullptr;
    QAction *superBatteryMode = nullptr;

    QAction *bestMobilityAction = nullptr;
    QAction *balancedBatteryAction = nullptr;
    QAction *bestBatteryAction = nullptr;

    QAction *restoreAction = nullptr;
    QAction *quitAction = nullptr;

private slots:
    void on_bestMobilityRadioButton_toggled(bool checked);
    void on_balancedBatteryRadioButton_toggled(bool checked);
    void on_bestBatteryRadioButton_toggled(bool checked);
    void on_customBatteryThresholdRadioButton_toggled(bool checked);
    void on_customBatteryThresholdSpinBox_valueChanged(int arg1);
    void on_customBatteryApplyButton_clicked();
    void on_ReadValueButton_clicked();

    void on_WriteValueButton_clicked() const;

    void on_usbPowerShareCheckBox_toggled(bool checked) const;
    void on_webCamCheckBox_toggled(bool checked) const;

    void on_fnSuperSwapCheckBox_toggled(bool checked) const;

    void on_coolerBoostCheckBox_toggled(bool checked) const;

    void on_keyboardBrightnessSlider_valueChanged(int value) const;

    void on_keyboardBacklightModeComboBox_currentIndexChanged(int index) const;

    void on_highPerformanceModeRadioButton_toggled(bool checked);
    void on_balancedModeRadioButton_toggled(bool checked);
    void on_silentModeRadioButton_toggled(bool checked);
    void on_superBatteryModeRadioButton_toggled(bool checked);
};
#endif // MAINWINDOW_H
