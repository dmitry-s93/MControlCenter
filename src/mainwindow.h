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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    void startRealtimeUpdate();
    void stopRealtimeUpdate();
    void setUpdateInterval(int msec);
    void realtimeUpdate();
    void updateData();
    void loadConfigs();

    QString intToQString(int value);

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
    void updateWebCamState();
    void updateFnSuperSwapState();
    void updateCoolerBoostState();
    void updateUserMode();

    void closeEvent(QCloseEvent *event);

private slots:
    void on_bestMobilityRadioButton_toggled(bool checked);
    void on_balancedBatteryRadioButton_toggled(bool checked);
    void on_bestBatteryRadioButton_toggled(bool checked);
    void on_customBatteryThresholdRadioButton_toggled(bool checked);
    void on_customBatteryThresholdComboBox_currentTextChanged(const QString &arg1);
    void on_ReadValueButton_clicked();

    void on_WriteWalueButton_clicked();

    void on_usbPowerShareCheckBox_toggled(bool checked);
    void on_webCamCheckBox_toggled(bool checked);

    void on_fnSuperSwapCheckBox_toggled(bool checked);

    void on_coolerBoostCheckBox_toggled(bool checked);

    void on_keyboardBrightnessSlider_valueChanged(int value);

    void on_keyboardBacklightModeComboBox_currentIndexChanged(int index);
    void on_highPerformanceModeRadioButton_toggled(bool checked);
    void on_balancedModeRadioButton_toggled(bool checked);
    void on_silentModeRadioButton_toggled(bool checked);
    void on_superBatteryModeRadioButton_toggled(bool checked);
};
#endif // MAINWINDOW_H
