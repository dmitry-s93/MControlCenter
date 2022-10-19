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

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "operate.h"
#include <QTimer>
#include <QMessageBox>

Operate operate;

bool isActive = false;

QTimer *realtimeUpdateTimer = new QTimer;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Disable debug tab
    ui->tabWidget->setTabVisible(4, false);
    setTabsEnabled(false);

    if (!operate.isEcSysModuleLoaded())
        if (!operate.loadEcSysModule())
            showMessage(tr("Failed to load the ec_sys kernel module"));

    updateData();

    connect(realtimeUpdateTimer, &QTimer::timeout, this, &MainWindow::realtimeUpdate);
    setUpdateInterval(1000);

    startRealtimeUpdate();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setTabsEnabled(bool enabled)
{
    ui->infoTab->setEnabled(enabled);
    ui->modeTab->setEnabled(enabled);
    ui->batteryTab->setEnabled(enabled);
    ui->settingsTab->setEnabled(enabled);
    ui->debugTab->setEnabled(enabled);
}

void MainWindow::startRealtimeUpdate()
{
    realtimeUpdateTimer->start();
}

void MainWindow::stopRealtimeUpdate()
{
    realtimeUpdateTimer->stop();
}

void MainWindow::setUpdateInterval(int msec)
{
    realtimeUpdateTimer->setInterval(msec);
}

void MainWindow::realtimeUpdate()
{
    updateData();
}

void MainWindow::updateData()
{
    if (operate.updateEcData()) {
        if (!isActive) {
            operate.doProbe();
            setTabsEnabled(true);
            loadConfigs();
            isActive= true;
        }
        updateBatteryCharge();
        updateChargingStatus();
        updateCpuTemp();
        updateGpuTemp();
        updateFan1Speed();
        updateFan2Speed();
        updateKeyboardBrightness();
    } else {
        setTabsEnabled(false);
        isActive= false;
    }
}

void MainWindow::loadConfigs()
{
    ui->ecVersionValueLabel->setText(QString::fromStdString(operate.getEcVersion()));
    ui->ecBuildValueLabel->setText(QString::fromStdString(operate.getEcBuild()));

    updateUserMode();
    updateCoolerBoostState();

    if (operate.isBatteryThresholdSupport()) {
        updateBatteryThreshold();
    } else {
        ui->batteryTab->setEnabled(false);
    }

    if (operate.isKeyboardBacklightSupport()) {
        updateKeyboardBacklightMode();
        updateKeyboardBrightness();
    } else {
        ui->keyboardBacklightModeComboBox->setEnabled(false);
        ui->keyboardBrightnessSlider->setEnabled(false);
    }

    if (operate.isUsbPowerShareSupport()) {
        updateUsbPowerShareState();
    } else {
        ui->usbPowerShareCheckBox->setEnabled(false);
    }

    if (operate.isWebCamOffSupport()) {
        updateWebCamState();
    } else {
        ui->webCamCheckBox->setEnabled(false);
    }

    if (operate.isFnSuperSwapSupport()) {
        updateFnSuperSwapState();
    } else {
        ui->fnSuperSwapCheckBox->setEnabled(false);
    }
}

void MainWindow::showMessage(QString text)
{
    QMessageBox msgBox;
    msgBox.setText(text);
    msgBox.exec();
}

QString MainWindow::intToQString(int value)
{
    if (value < 0)
        return "-";
    return QString::number(value);
}

void MainWindow::updateBatteryCharge()
{
    ui->BatteryChargeValueLabel->setText(intToQString(operate.getBatteryCharge()) + " %");
}

void MainWindow::updateBatteryThreshold()
{
    operate.updateEcData();
    int batteryThreshold = operate.getBatteryThreshold();
    if (batteryThreshold == 0)
        ui->batteryThresholdValueLabel->setText("100 %");
    else
        ui->batteryThresholdValueLabel->setText(QString::number(batteryThreshold) + " %");

    switch (batteryThreshold)
    {
        case 0:
            ui->bestMobilityRadioButton->click();
            break;
        case 60:
            ui->bestBatteryRadioButton->click();
            break;
        case 80:
            ui->balancedBatteryRadioButton->click();
            break;
        default:
            ui->customBatteryThresholdRadioButton->click();
            break;
    }
}

void MainWindow::updateChargingStatus()
{
    QString chargingStatus;
    switch (operate.getChargingStatus())
    {
        case battery_charging:
            chargingStatus = tr("Charging");
            break;
        case battery_discharging:
            chargingStatus = tr("Discharging");
            break;
        case battery_not_charging:
            chargingStatus = tr("Not charging");
            break;
        case battery_fully_charged:
            chargingStatus = tr("Fully charged");
            break;
        case battery_fully_charged_no_power:
            chargingStatus = tr("Fully charged (Discharging)");
            break;
        default:
            chargingStatus = tr("Unknown");
            break;
    }
    ui->chargingStatusValueLabel->setText(chargingStatus);
}

void MainWindow::updateCpuTemp()
{
    ui->cpuTempValueLabel->setText(intToQString(operate.getCpuTemp()) + " °C");
}

void MainWindow::updateGpuTemp()
{
    ui->gpuTempValueLabel->setText(intToQString(operate.getGpuTemp()) + " °C");
}

void MainWindow::updateFan1Speed()
{
    ui->fan1ValueLabel->setText(intToQString(operate.getFan1Speed()) + " " + tr("rpm"));
}

void MainWindow::updateFan2Speed()
{
    ui->fan2ValueLabel->setText(intToQString(operate.getFan2Speed()) + " " + tr("rpm"));
}

void MainWindow::updateKeyboardBacklightMode()
{
    ui->keyboardBacklightModeComboBox->setCurrentIndex(operate.getKeybordBacklightMode());
}

void MainWindow::updateKeyboardBrightness()
{
    ui->keyboardBrightnessSlider->setSliderPosition(operate.getKeyboardBrightness());
}

void MainWindow::updateUsbPowerShareState()
{
    ui->usbPowerShareCheckBox->setChecked(operate.getUsbPowerShareState());
}

void MainWindow::updateWebCamState()
{
    ui->webCamCheckBox->setChecked(operate.getWebCamState());
}

void MainWindow::updateFnSuperSwapState()
{
    ui->fnSuperSwapCheckBox->setChecked(operate.getFnSuperSwapState());
}

void MainWindow::updateCoolerBoostState()
{
    ui->coolerBoostCheckBox->setChecked(operate.getCoolerBoostState());
}

void MainWindow::updateUserMode()
{
    operate.updateEcData();
    int userMode = operate.getUserMode();
    switch (userMode)
    {
        case balanced_mode:
            ui->balancedModeRadioButton->click();
            break;
        case performance_mode:
            ui->highPerformanceModeRadioButton->click();
            break;
        case silent_mode:
            ui->silentModeRadioButton->click();
            break;
        case super_battery_mode:
            ui->superBatteryModeRadioButton->click();
            break;
        default:
            ui->modeTab->setDisabled(true);
            break;
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    operate.closeHelperApp();
}

void MainWindow::on_bestMobilityRadioButton_toggled(bool checked)
{
    if (checked) {
        operate.setBatteryThreshold(0);
        updateBatteryThreshold();
    }
}

void MainWindow::on_balancedBatteryRadioButton_toggled(bool checked)
{
    if (checked) {
        operate.setBatteryThreshold(80);
        updateBatteryThreshold();
    }
}

void MainWindow::on_bestBatteryRadioButton_toggled(bool checked)
{
    if (checked) {
        operate.setBatteryThreshold(60);
        updateBatteryThreshold();
    }
}

void MainWindow::on_customBatteryThresholdRadioButton_toggled(bool checked)
{
    if (checked) {
        ui->customBatteryThresholdComboBox->setEnabled(true);
        ui->customBatteryThresholdComboBox->setCurrentText(QString::number(operate.getBatteryThreshold()));
    } else {
        ui->customBatteryThresholdComboBox->setEnabled(false);
    }
}


void MainWindow::on_customBatteryThresholdComboBox_currentTextChanged(const QString &arg1)
{
    operate.setBatteryThreshold(arg1.toInt());
    updateBatteryThreshold();
}


void MainWindow::on_ReadValueButton_clicked()
{
    QString text = ui->addressEdit->displayText();
    int value = operate.getValue(text.toInt());
    ui->ValueSpinBox->setValue(value);
}


void MainWindow::on_WriteWalueButton_clicked()
{
    QString text = ui->addressEdit->displayText();
    int address = text.toInt();
    operate.setValue(address, ui->ValueSpinBox->value());
}


void MainWindow::on_usbPowerShareCheckBox_toggled(bool checked)
{
    operate.setUsbPowerShareState(checked);
}


void MainWindow::on_webCamCheckBox_toggled(bool checked)
{
    operate.setWebCamState(checked);
}


void MainWindow::on_fnSuperSwapCheckBox_toggled(bool checked)
{
    operate.setFnSuperSwapState(checked);
}


void MainWindow::on_coolerBoostCheckBox_toggled(bool checked)
{
    operate.setCoolerBoostState(checked);
}


void MainWindow::on_keyboardBrightnessSlider_valueChanged(int value)
{
    operate.setKeybordBrightness(value);
}


void MainWindow::on_keyboardBacklightModeComboBox_currentIndexChanged(int index)
{
    operate.setKeyoardBacklightMode(index);
}

void MainWindow::on_highPerformanceModeRadioButton_toggled(bool checked)
{
    if (checked) {
        operate.setUserMode(performance_mode);
        updateUserMode();
    }
}


void MainWindow::on_balancedModeRadioButton_toggled(bool checked)
{
    if (checked) {
        operate.setUserMode(balanced_mode);
        updateUserMode();
    }
}


void MainWindow::on_silentModeRadioButton_toggled(bool checked)
{
    if (checked) {
        operate.setUserMode(silent_mode);
        updateUserMode();
    }
}


void MainWindow::on_superBatteryModeRadioButton_toggled(bool checked)
{
    if (checked) {
        operate.setUserMode(super_battery_mode);
        updateUserMode();
    }
}

