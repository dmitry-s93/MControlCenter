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

Operate operate;

bool isActive = false;

QTimer *realtimeUpdateTimer = new QTimer;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Disable debug tab
    ui->tabWidget->setTabVisible(3, false);
    updateData();

    connect(realtimeUpdateTimer, &QTimer::timeout, this, &MainWindow::realtimeUpdate);
    setUpdateInterval(1000);

    startRealtimeUpdate();
}

MainWindow::~MainWindow()
{
    delete ui;
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
            ui->tabWidget->setDisabled(false);
            loadConfigs();
            setUpdateInterval(1000);
            isActive= true;
        }
        updateBatteryCharge();
        updateCpuTemp();
        updateGpuTemp();
        updateFan1Speed();
        updateFan2Speed();
        updateKeyboardBrightness();
    } else {
        ui->tabWidget->setDisabled(true);
        setUpdateInterval(10000);
        isActive= false;
    }
}

void MainWindow::loadConfigs()
{
    ui->ecVersionValueLabel->setText(QString::fromStdString(operate.getEcVersion()));
    ui->ecBuildValueLabel->setText(QString::fromStdString(operate.getEcBuild()));

    updateBatteryCharge();
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
    ui->fan1ValueLabel->setText(intToQString(operate.getFan1Speed()) + " rpm");
}

void MainWindow::updateFan2Speed()
{
    ui->fan2ValueLabel->setText(intToQString(operate.getFan2Speed()) + " rpm");
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
