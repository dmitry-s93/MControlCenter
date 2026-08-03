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
#include "settings.h"
#include <QTimer>
#include <QMessageBox>
#include <QSignalBlocker>
#include <QDBusConnection>

Operate operate;
PowerMonitor powerMonitor;

bool isActive = false;
bool isUpdateDataError = false;

QTimer *realtimeUpdateTimer = new QTimer;

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->advancedFanControlCheckBox, &QCheckBox::toggled, this, &MainWindow::setFanModeAdvanced);

    connect(ui->fan1Speed1Slider, &QSlider::valueChanged, this, [this]() {
        ui->fan1Speed1Label->setText(QString(tr("fan level %1")).arg(ui->fan1Speed1Slider->value()));
        checkFanSettingsChanged();
    });
    connect(ui->fan1Speed2Slider, &QSlider::valueChanged, this, [this]() {
        ui->fan1Speed2Label->setText(QString(tr("fan level %1")).arg(ui->fan1Speed2Slider->value()));
        checkFanSettingsChanged();
    });
    connect(ui->fan1Speed3Slider, &QSlider::valueChanged, this, [this]() {
        ui->fan1Speed3Label->setText(QString(tr("fan level %1")).arg(ui->fan1Speed3Slider->value()));
        checkFanSettingsChanged();
    });
    connect(ui->fan1Speed4Slider, &QSlider::valueChanged, this, [this]() {
        ui->fan1Speed4Label->setText(QString(tr("fan level %1")).arg(ui->fan1Speed4Slider->value()));
        checkFanSettingsChanged();
    });
    connect(ui->fan1Speed5Slider, &QSlider::valueChanged, this, [this]() {
        ui->fan1Speed5Label->setText(QString(tr("fan level %1")).arg(ui->fan1Speed5Slider->value()));
        checkFanSettingsChanged();
    });
    connect(ui->fan1Speed6Slider, &QSlider::valueChanged, this, [this]() {
        ui->fan1Speed6Label->setText(QString(tr("fan level %1")).arg(ui->fan1Speed6Slider->value()));
        checkFanSettingsChanged();
    });
    connect(ui->fan1Speed7Slider, &QSlider::valueChanged, this, [this]() {
        ui->fan1Speed7Label->setText(QString(tr("fan level %1")).arg(ui->fan1Speed7Slider->value()));
        checkFanSettingsChanged();
    });

    connect(ui->fan1Speed2TempSpinBox, &QSpinBox::textChanged, this, [this]() {
        ui->fan1Speed1TempLabel->setText(QString("< %1 °C").arg(ui->fan1Speed2TempSpinBox->value()));
        checkFanSettingsChanged();
    });
    connect(ui->fan1Speed3TempSpinBox, &QSpinBox::textChanged, this, [this]() {
        checkFanSettingsChanged();
    });
    connect(ui->fan1Speed4TempSpinBox, &QSpinBox::textChanged, this, [this]() {
        checkFanSettingsChanged();
    });
    connect(ui->fan1Speed5TempSpinBox, &QSpinBox::textChanged, this, [this]() {
        checkFanSettingsChanged();
    });
    connect(ui->fan1Speed6TempSpinBox, &QSpinBox::textChanged, this, [this]() {
        checkFanSettingsChanged();
    });
    connect(ui->fan1Speed7TempSpinBox, &QSpinBox::textChanged, this, [this]() {
        checkFanSettingsChanged();
    });

    connect(ui->fan2Speed1Slider, &QSlider::valueChanged, this, [this]() {
        ui->fan2Speed1Label->setText(QString(tr("fan level %1")).arg(ui->fan2Speed1Slider->value()));
        checkFanSettingsChanged();
    });
    connect(ui->fan2Speed2Slider, &QSlider::valueChanged, this, [this]() {
        ui->fan2Speed2Label->setText(QString(tr("fan level %1")).arg(ui->fan2Speed2Slider->value()));
        checkFanSettingsChanged();
    });
    connect(ui->fan2Speed3Slider, &QSlider::valueChanged, this, [this]() {
        ui->fan2Speed3Label->setText(QString(tr("fan level %1")).arg(ui->fan2Speed3Slider->value()));
        checkFanSettingsChanged();
    });
    connect(ui->fan2Speed4Slider, &QSlider::valueChanged, this, [this]() {
        ui->fan2Speed4Label->setText(QString(tr("fan level %1")).arg(ui->fan2Speed4Slider->value()));
        checkFanSettingsChanged();
    });
    connect(ui->fan2Speed5Slider, &QSlider::valueChanged, this, [this]() {
        ui->fan2Speed5Label->setText(QString(tr("fan level %1")).arg(ui->fan2Speed5Slider->value()));
        checkFanSettingsChanged();
    });
    connect(ui->fan2Speed6Slider, &QSlider::valueChanged, this, [this]() {
        ui->fan2Speed6Label->setText(QString(tr("fan level %1")).arg(ui->fan2Speed6Slider->value()));
        checkFanSettingsChanged();
    });
    connect(ui->fan2Speed7Slider, &QSlider::valueChanged, this, [this]() {
        ui->fan2Speed7Label->setText(QString(tr("fan level %1")).arg(ui->fan2Speed7Slider->value()));
        checkFanSettingsChanged();
    });

    connect(ui->fan2Speed2TempSpinBox, &QSpinBox::textChanged, this, [this]() {
        ui->fan2Speed1TempLabel->setText(QString("< %1 °C").arg(ui->fan2Speed2TempSpinBox->value()));
        checkFanSettingsChanged();
    });
    connect(ui->fan2Speed3TempSpinBox, &QSpinBox::textChanged, this, [this]() {
        checkFanSettingsChanged();
    });
    connect(ui->fan2Speed4TempSpinBox, &QSpinBox::textChanged, this, [this]() {
        checkFanSettingsChanged();
    });
    connect(ui->fan2Speed5TempSpinBox, &QSpinBox::textChanged, this, [this]() {
        checkFanSettingsChanged();
    });
    connect(ui->fan2Speed6TempSpinBox, &QSpinBox::textChanged, this, [this]() {
        checkFanSettingsChanged();
    });
    connect(ui->fan2Speed7TempSpinBox, &QSpinBox::textChanged, this, [this]() {
        checkFanSettingsChanged();
    });

    connect(ui->fanSpeedResetButton, &QPushButton::clicked, this, &MainWindow::updateFanSpeedSettings);
    connect(ui->fanSpeedApplyButton, &QPushButton::clicked, this, &MainWindow::setFanSpeedSettings);
    connect(&powerMonitor, &PowerMonitor::currentChargerState, this, &MainWindow::on_ChargerStateChange);
    connect(&powerMonitor, &PowerMonitor::currentPowerProfile, this, &MainWindow::on_PowerProfileChange);

    connect(qApp, &QGuiApplication::saveStateRequest, this, &MainWindow::saveStateRequest);

    MainWindow::setWindowIcon(QIcon(":/images/AppIcon"));
    Settings s;
    if (s.isValueExist("MainWindow/Width") && s.isValueExist("MainWindow/Height"))
        MainWindow::resize(s.getValue("MainWindow/Width").toInt(), s.getValue("MainWindow/Height").toInt());

    createTrayIcon();

    ui->tabWidget->tabBar()->setExpanding(true);
    // Disable debug tab
    ui->tabWidget->setTabVisible(5, false);
    setTabsEnabled(false);

    if (!operate.isMsiEcLoaded()) {
        QMessageBox::critical(nullptr, this->windowTitle(), tr("The msi-ec module is not loaded/installed.\n"
                                                               "Check the <About> page for more info."));
    }

    // ec_sys/acpi_ec is optional read-only RPM diagnostics. Never autoload it
    // when typed msi_ec is already active; msi_ec-only systems stay usable.
    if (!operate.isMsiEcLoaded() && !operate.isEcSysModuleLoaded() && !operate.loadEcSysModule())
        QMessageBox::critical(nullptr, this->windowTitle(), tr("The optional ec_sys module couldn't be detected; raw RPM diagnostics are unavailable."));



    if(operate.updateEcData())
        updateData();

    connect(realtimeUpdateTimer, &QTimer::timeout, this, &MainWindow::realtimeUpdate);
    setUpdateInterval(1000);

    // logind emits this signal across suspend/resume; timer-gap heuristics can
    // miss short sleeps and do not identify firmware changes.
    QDBusConnection::systemBus().connect(QStringLiteral("org.freedesktop.login1"),
                                         QStringLiteral("/org/freedesktop/login1"),
                                         QStringLiteral("org.freedesktop.login1.Manager"),
                                         QStringLiteral("PrepareForSleep"), this,
                                         SLOT(onPrepareForSleep(bool)));

    ui->QtVersionValue->setText(QT_VERSION_STR);
    ui->versionValueLabel->setText(MControlCenter_VERSION);
    ui->autoAcDcProfilesGroupBox->setChecked(s.getValue("Settings/autoAcDcProfilesState").toBool());
    ui->userModeOnBatteryComboBox->setCurrentIndex(s.getValue("Settings/UserModeOnBattery").toInt());
    ui->userModeOnChargerComboBox->setCurrentIndex(s.getValue("Settings/UserModeOnCharger").toInt());
    ui->autoPPDCheckBox->setChecked(s.getValue("Settings/autoPPDstate").toBool());
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setUpdateDataError(bool error) {
    isUpdateDataError = error;
}

void MainWindow::setTabsEnabled(bool enabled) {
    ui->overviewTab->setEnabled(enabled);
    ui->modeFormWidget->setEnabled(enabled);
    ui->batteryTab->setEnabled(enabled);
    ui->fanControlTab->setEnabled(enabled);
    ui->keyboardTab->setEnabled(enabled);
    ui->debugTab->setEnabled(enabled);

    if (modeTrayMenu)
        modeTrayMenu->setEnabled(enabled);
    if (batteryTrayMenu)
        batteryTrayMenu->setEnabled(enabled);
}

void MainWindow::startRealtimeUpdate() const {
    realtimeUpdateTimer->start();
}

void MainWindow::stopRealtimeUpdate() const {
    realtimeUpdateTimer->stop();
}

void MainWindow::setUpdateInterval(int msec) const {
    realtimeUpdateTimer->setInterval(msec);
}

void MainWindow::realtimeUpdate() {
    // Do not issue raw EC reads when ec_sys/acpi_ec is absent.
    if (operate.isEcSysModuleLoaded())
        operate.updateEcDataAsync();
    updateData();
}

void MainWindow::updateData() {
    if (operate.isMsiEcLoaded() || (!isUpdateDataError && operate.isEcSysModuleLoaded())) {
        if (!isActive) {
            operate.doProbe();
            setTabsEnabled(true);
            loadConfigs();
            isActive = true;
        }
        updateBatteryCharge();
        updateChargingStatus();
        updateCpuTemp();
        updateGpuTemp();
        updateFanMode();
        updateFan1Speed();
        updateFan2Speed();
        updateKeyboardBrightness();
        updateWebCamState();

        if (operate.isMsiEcLoaded()) {
            ui->MsiEcStatusLabel->setText(tr("Loaded"));
        } else {
            ui->MsiEcStatusLabel->setText(tr("Fallback: Only ec_sys is loaded"));
        }
    } else {
        setTabsEnabled(false);
        ui->MsiEcStatusLabel->setText(tr("Failed to load both msi-ec/ec_sys"));
        isActive = false;
    }
}

void MainWindow::loadConfigs() {
    ui->ecVersionValueLabel->setText(QString::fromStdString(operate.getEcVersion()));
    ui->ecBuildValueLabel->setText(QString::fromStdString(operate.getEcBuild()));

    const auto restoreResult = operate.loadSettings();
    updateUserMode();
    if (operate.isCoolerBoostSupport())
        updateCoolerBoostState();
    else {
        ui->coolerBoostCheckBox->setEnabled(false);
        if (coolerBoostAction)
            coolerBoostAction->setEnabled(false);
    }

    if (operate.isBatteryThresholdSupport()) {
        updateBatteryThreshold();
    } else {
        ui->batteryTab->setEnabled(false);
        if (batteryTrayMenu)
            batteryTrayMenu->setEnabled(false);
    }

    updateFanSpeedSettings();
    if (restoreResult.has_value() && !restoreResult->success)
        ui->fanCurveStatusLabel->setText(tr("Failed to restore fan preference: %1").arg(restoreResult->error));

    if (operate.isKeyboardBacklightModeSupport()) {
        updateKeyboardBacklightMode();
    } else {
        ui->keyboardBacklightModeComboBox->setEnabled(false);
    }

    if (operate.isKeyboardBacklightSupport()) {
        updateKeyboardBrightness();
    } else {
        ui->keyboardBrightnessSlider->setEnabled(false);
        ui->tabWidget->removeTab(3);
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

    if (operate.isFnSuperSwapSupport())
        updateFnSuperSwapState();
    else
        ui->fnSuperSwapCheckBox->setEnabled(false);
}

QString MainWindow::intToQString(int value) const {
    if (value < 0)
        return "-";
    return QString::number(value);
}

void MainWindow::updateBatteryCharge() {
    ui->BatteryChargeValueLabel->setText(intToQString(operate.getBatteryCharge()) + " %");
}

void MainWindow::updateBatteryThreshold() {
    if (operate.updateEcData()) {
        int batteryThreshold = operate.getBatteryThreshold();
        if (batteryThreshold == 0)
            ui->batteryThresholdValueLabel->setText("100 %");
        else
            ui->batteryThresholdValueLabel->setText(QString::number(batteryThreshold) + " %");

        {
            const QSignalBlocker bestMobilityBlocker(ui->bestMobilityRadioButton);
            const QSignalBlocker bestBatteryBlocker(ui->bestBatteryRadioButton);
            const QSignalBlocker balancedBatteryBlocker(ui->balancedBatteryRadioButton);
            const QSignalBlocker customBlocker(ui->customBatteryThresholdRadioButton);
            switch (batteryThreshold) {
                case 0:
                case 100:
                    ui->bestMobilityRadioButton->setChecked(true);
                    batteryThreshold = 100;
                    break;
                case 60:
                    ui->bestBatteryRadioButton->setChecked(true);
                    break;
                case 80:
                    ui->balancedBatteryRadioButton->setChecked(true);
                    break;
                default:
                    ui->customBatteryThresholdRadioButton->setChecked(true);
                    ui->customBatteryApplyButton->setEnabled(
                            batteryThreshold != ui->customBatteryThresholdSpinBox->value());
                    break;
            }
            ui->customBatteryThresholdSpinBox->setValue(batteryThreshold);
        }
    }
}

void MainWindow::updateChargingStatus() {
    QString chargingStatus;
    switch (operate.getChargingStatus()) {
        case charging_state::battery_charging:
            chargingStatus = tr("Charging");
            break;
        case charging_state::battery_discharging:
            chargingStatus = tr("Discharging");
            break;
        case charging_state::battery_not_charging:
            chargingStatus = tr("Not charging");
            break;
        case charging_state::battery_fully_charged:
            chargingStatus = tr("Fully charged");
            break;
        default:
            chargingStatus = tr("Unknown");
            break;
    }
    ui->chargingStatusValueLabel->setText(chargingStatus);
}

void MainWindow::updateCpuTemp() {
    ui->cpuTempValueLabel->setText(intToQString(operate.getCpuTemp()) + " °C");
}

void MainWindow::updateGpuTemp() {
    std::optional<int> temp = operate.getGpuTemp();
    if (temp.has_value()) {
        ui->gpuTempValueLabel->setVisible(true);
        ui->gpuTempLabel->setVisible(true);
        if (temp.value() != 0)
            ui->gpuTempValueLabel->setText(intToQString(temp.value()) + " °C");
        else
            ui->gpuTempValueLabel->setText(tr("OFF"));
    } else {
        ui->gpuTempValueLabel->setVisible(false);
        ui->gpuTempLabel->setVisible(false);
    }
}

void MainWindow::updateFan1Speed() {
    const std::optional<int> speed = operate.getFan1Speed();
    if (!speed.has_value())
        ui->fan1ValueLabel->setText(tr("Unavailable"));
    else if (speed.value() != 0)
        ui->fan1ValueLabel->setText(intToQString(speed.value()) + " " + tr("rpm"));
    else
        ui->fan1ValueLabel->setText(tr("OFF"));
}

void MainWindow::updateFan2Speed() {
    std::optional<int> speed = operate.getFan2Speed();
    if (speed.has_value()) {
        ui->fan2ValueLabel->setVisible(true);
        ui->gpuFanLabel->setVisible(true);
        if (speed.value() != 0)
            ui->fan2ValueLabel->setText(intToQString(speed.value()) + " " + tr("rpm"));
        else
            ui->fan2ValueLabel->setText(tr("OFF"));
    } else {
        ui->fan2ValueLabel->setVisible(false);
        ui->gpuFanLabel->setVisible(false);
        ui->fanControlTabWidget->setTabEnabled(1, false);
    }
}

void MainWindow::updateKeyboardBacklightMode() {
    ui->keyboardBacklightModeComboBox->setCurrentIndex(operate.getKeyboardBacklightMode());
}

void MainWindow::updateKeyboardBrightness() const {
    ui->keyboardBrightnessSlider->setSliderPosition(operate.getKeyboardBrightness());
}

void MainWindow::updateUsbPowerShareState() {
    ui->usbPowerShareCheckBox->setChecked(operate.getUsbPowerShareState());
}

void MainWindow::updateWebCamState() const {
    ui->webCamCheckBox->setChecked(operate.getWebCamState());
}

void MainWindow::updateFnSuperSwapState() {
    ui->fnSuperSwapCheckBox->setChecked(operate.getFnSuperSwapState());
}

void MainWindow::updateCoolerBoostState() const {
    ui->coolerBoostCheckBox->setChecked(operate.getCoolerBoostState());
    coolerBoostAction->setChecked(operate.getCoolerBoostState());
}

void MainWindow::updateUserMode() {
    if (operate.updateEcData()) {
        const QSignalBlocker balancedBlocker(ui->balancedModeRadioButton);
        const QSignalBlocker performanceBlocker(ui->highPerformanceModeRadioButton);
        const QSignalBlocker silentBlocker(ui->silentModeRadioButton);
        const QSignalBlocker superBatteryBlocker(ui->superBatteryModeRadioButton);
        switch (operate.getUserMode()) {
            case user_mode::balanced_mode:
                ui->balancedModeRadioButton->setChecked(true);
                balancedMode->setChecked(true);
                break;
            case user_mode::performance_mode:
                ui->highPerformanceModeRadioButton->setChecked(true);
                highPerformanceMode->setChecked(true);
                break;
            case user_mode::silent_mode:
                ui->silentModeRadioButton->setChecked(true);
                silentMode->setChecked(true);
                break;
            case user_mode::super_battery_mode:
                ui->superBatteryModeRadioButton->setChecked(true);
                superBatteryMode->setChecked(true);
                break;
            case user_mode::unknown_mode:
                //fall to default, happens on some models after booting
            default:
                if (!operate.isMsiEcLoaded()){
                    ui->modeFormWidget->setDisabled(true);
                    if (modeTrayMenu)
                        modeTrayMenu->setDisabled(true);
                } else {
                    ui->superBatteryModeRadioButton->setChecked(false);
                    ui->silentModeRadioButton->setChecked(false);
                    ui->balancedModeRadioButton->setChecked(false);
                    ui->highPerformanceModeRadioButton->setChecked(false);
                }
                break;
        }
    }
}

void MainWindow::updateFanMode() {
    QString fanMode;
    switch (operate.getFanMode()) {
        case fan_mode::auto_fan_mode:
            fanMode = tr("Auto");
            break;
        case fan_mode::silent_fan_mode:
            fanMode = tr("Silent");
            break;
        case fan_mode::basic_fan_mode:
            fanMode = tr("Basic");
            break;
        case fan_mode::advanced_fan_mode:
            fanMode = tr("Advanced");
            break;
        default:
            fanMode = tr("Unknown");
            break;
    }
    ui->fanModeValueLabel->setText(fanMode);
}

void MainWindow::updateFanSpeedSettings() {
    const FanCurveCapability capability = operate.getFanCurveCapability();
    const bool curveSupported = capability.complete();
    ui->advancedFanControlCheckBox->setEnabled(curveSupported);
    ui->advancedFanControlCheckBox->setToolTip(
        curveSupported ? tr("Uses the complete msi-ec fan curve ABI")
                       : tr("Fan curves are unavailable: the driver does not expose the complete verified ABI"));
    // Editing is allowed in Auto as well: a malformed existing curve must be
    // repairable before Advanced is activated by the transaction.
    ui->fanControlTabWidget->setEnabled(curveSupported);
    if (!curveSupported) {
        ui->fanCurveStatusLabel->setText(
            tr("Unsupported: complete msi-ec fan curve ABI is unavailable"));
        ui->fanSpeedApplyButton->setEnabled(false);
        ui->fanSpeedResetButton->setEnabled(false);
        return;
    }
    for (QSlider *slider : {ui->fan1Speed1Slider, ui->fan1Speed2Slider, ui->fan1Speed3Slider,
                            ui->fan1Speed4Slider, ui->fan1Speed5Slider, ui->fan1Speed6Slider,
                            ui->fan1Speed7Slider, ui->fan2Speed1Slider, ui->fan2Speed2Slider,
                            ui->fan2Speed3Slider, ui->fan2Speed4Slider, ui->fan2Speed5Slider,
                            ui->fan2Speed6Slider, ui->fan2Speed7Slider})
        slider->setRange(capability.levelMin, capability.levelMax);
    for (QSpinBox *spin : {ui->fan1Speed2TempSpinBox, ui->fan1Speed3TempSpinBox,
                           ui->fan1Speed4TempSpinBox, ui->fan1Speed5TempSpinBox,
                           ui->fan1Speed6TempSpinBox, ui->fan1Speed7TempSpinBox,
                           ui->fan2Speed2TempSpinBox, ui->fan2Speed3TempSpinBox,
                           ui->fan2Speed4TempSpinBox, ui->fan2Speed5TempSpinBox,
                           ui->fan2Speed6TempSpinBox, ui->fan2Speed7TempSpinBox})
        spin->setRange(capability.thresholdMin, capability.thresholdMax);

    const QSignalBlocker advancedBlocker(ui->advancedFanControlCheckBox);
    const QSignalBlocker fan1Slider1Blocker(ui->fan1Speed1Slider);
    const QSignalBlocker fan1Slider2Blocker(ui->fan1Speed2Slider);
    const QSignalBlocker fan1Slider3Blocker(ui->fan1Speed3Slider);
    const QSignalBlocker fan1Slider4Blocker(ui->fan1Speed4Slider);
    const QSignalBlocker fan1Slider5Blocker(ui->fan1Speed5Slider);
    const QSignalBlocker fan1Slider6Blocker(ui->fan1Speed6Slider);
    const QSignalBlocker fan1Slider7Blocker(ui->fan1Speed7Slider);
    const QSignalBlocker fan2Slider1Blocker(ui->fan2Speed1Slider);
    const QSignalBlocker fan2Slider2Blocker(ui->fan2Speed2Slider);
    const QSignalBlocker fan2Slider3Blocker(ui->fan2Speed3Slider);
    const QSignalBlocker fan2Slider4Blocker(ui->fan2Speed4Slider);
    const QSignalBlocker fan2Slider5Blocker(ui->fan2Speed5Slider);
    const QSignalBlocker fan2Slider6Blocker(ui->fan2Speed6Slider);
    const QSignalBlocker fan2Slider7Blocker(ui->fan2Speed7Slider);
    const QSignalBlocker fan1Temp2Blocker(ui->fan1Speed2TempSpinBox);
    const QSignalBlocker fan1Temp3Blocker(ui->fan1Speed3TempSpinBox);
    const QSignalBlocker fan1Temp4Blocker(ui->fan1Speed4TempSpinBox);
    const QSignalBlocker fan1Temp5Blocker(ui->fan1Speed5TempSpinBox);
    const QSignalBlocker fan1Temp6Blocker(ui->fan1Speed6TempSpinBox);
    const QSignalBlocker fan1Temp7Blocker(ui->fan1Speed7TempSpinBox);
    const QSignalBlocker fan2Temp2Blocker(ui->fan2Speed2TempSpinBox);
    const QSignalBlocker fan2Temp3Blocker(ui->fan2Speed3TempSpinBox);
    const QSignalBlocker fan2Temp4Blocker(ui->fan2Speed4TempSpinBox);
    const QSignalBlocker fan2Temp5Blocker(ui->fan2Speed5TempSpinBox);
    const QSignalBlocker fan2Temp6Blocker(ui->fan2Speed6TempSpinBox);
    const QSignalBlocker fan2Temp7Blocker(ui->fan2Speed7TempSpinBox);
    ui->advancedFanControlCheckBox->setChecked(operate.getFanMode() == fan_mode::advanced_fan_mode);

    const auto currentProfile = operate.getFanCurveProfile();
    if (!currentProfile.has_value()) {
        ui->fanCurveStatusLabel->setText(tr("Failed: driver fan curve readback is unavailable"));
        ui->fanSpeedApplyButton->setEnabled(false);
        ui->fanSpeedResetButton->setEnabled(false);
        return;
    }
    const bool currentCurveValid = validateFanCurve(capability, *currentProfile).isEmpty();
    const QVector<int> fan1SpeedSettings = currentProfile->cpuLevels;
    const QVector<int> fan1TempSettings = currentProfile->cpuThresholds;
    const QVector<int> fan2SpeedSettings = currentProfile->gpuLevels;
    const QVector<int> fan2TempSettings = currentProfile->gpuThresholds;
    if (fan1SpeedSettings.size() != 7 || fan2SpeedSettings.size() != 7 ||
        fan1TempSettings.size() != 6 || fan2TempSettings.size() != 6) {
        ui->fanCurveStatusLabel->setText(tr("Failed: driver fan curve readback is unavailable"));
        ui->fanSpeedApplyButton->setEnabled(false);
        ui->fanSpeedResetButton->setEnabled(false);
        return;
    }

    ui->fan1Speed1Slider->setValue(fan1SpeedSettings[0]);
    ui->fan1Speed2Slider->setValue(fan1SpeedSettings[1]);
    ui->fan1Speed3Slider->setValue(fan1SpeedSettings[2]);
    ui->fan1Speed4Slider->setValue(fan1SpeedSettings[3]);
    ui->fan1Speed5Slider->setValue(fan1SpeedSettings[4]);
    ui->fan1Speed6Slider->setValue(fan1SpeedSettings[5]);
    ui->fan1Speed7Slider->setValue(fan1SpeedSettings[6]);

    ui->fan1Speed1TempLabel->setText(QString("< %1 °C").arg(fan1TempSettings[0]));
    ui->fan1Speed2TempSpinBox->setValue(fan1TempSettings[0]);
    ui->fan1Speed3TempSpinBox->setValue(fan1TempSettings[1]);
    ui->fan1Speed4TempSpinBox->setValue(fan1TempSettings[2]);
    ui->fan1Speed5TempSpinBox->setValue(fan1TempSettings[3]);
    ui->fan1Speed6TempSpinBox->setValue(fan1TempSettings[4]);
    ui->fan1Speed7TempSpinBox->setValue(fan1TempSettings[5]);

    ui->fan2Speed1Slider->setValue(fan2SpeedSettings[0]);
    ui->fan2Speed2Slider->setValue(fan2SpeedSettings[1]);
    ui->fan2Speed3Slider->setValue(fan2SpeedSettings[2]);
    ui->fan2Speed4Slider->setValue(fan2SpeedSettings[3]);
    ui->fan2Speed5Slider->setValue(fan2SpeedSettings[4]);
    ui->fan2Speed6Slider->setValue(fan2SpeedSettings[5]);
    ui->fan2Speed7Slider->setValue(fan2SpeedSettings[6]);

    ui->fan2Speed1TempLabel->setText(QString("< %1 °C").arg(fan2TempSettings[0]));
    ui->fan2Speed2TempSpinBox->setValue(fan2TempSettings[0]);
    ui->fan2Speed3TempSpinBox->setValue(fan2TempSettings[1]);
    ui->fan2Speed4TempSpinBox->setValue(fan2TempSettings[2]);
    ui->fan2Speed5TempSpinBox->setValue(fan2TempSettings[3]);
    ui->fan2Speed6TempSpinBox->setValue(fan2TempSettings[4]);
    ui->fan2Speed7TempSpinBox->setValue(fan2TempSettings[5]);

    checkFanSettingsChanged();
    if (!currentCurveValid) {
        ui->fanCurveStatusLabel->setText(
            tr("Warning: current driver curve has an invalid range or ordering; repair it before applying"));
        ui->fanSpeedApplyButton->setEnabled(true);
    }
}

void MainWindow::setBestMobility() {
    operate.setBatteryThreshold(100);
    updateBatteryThreshold();
}

void MainWindow::setBalancedBattery() {
    operate.setBatteryThreshold(80);
    updateBatteryThreshold();
}

void MainWindow::setBestBattery() {
    operate.setBatteryThreshold(60);
    updateBatteryThreshold();
}

namespace {
void showModeResult(const std::optional<FanCurveResult> &result, QLabel *statusLabel,
                    const QString &actualMode) {
    if (!result.has_value()) {
        statusLabel->setText(QObject::tr("Mode applied: %1").arg(actualMode));
    } else if (result->success) {
        statusLabel->setText(result->effectiveMode == QStringLiteral("advanced")
                                 ? QObject::tr("Applied (advanced)")
                                 : QObject::tr("Mode applied: %1").arg(result->effectiveMode));
    } else {
        statusLabel->setText(QObject::tr("Failed to reconcile fan preference: %1").arg(result->error));
    }
}
}

void MainWindow::setHighPerformanceMode() {
    const bool modeOk = operate.setUserMode(user_mode::performance_mode);
    updateUserMode();
    updateFanMode();
    if (!modeOk) {
        ui->fanCurveStatusLabel->setText(tr("Failed to verify Performance mode; pending fan edits preserved"));
        return;
    }
    const auto result = operate.reconcileFanCurvePreference();
    updateFanMode();
    showModeResult(result, ui->fanCurveStatusLabel, ui->fanModeValueLabel->text());
    if (!result.has_value() || result->success)
        updateFanSpeedSettings();
}

void MainWindow::setBalancedMode() {
    const bool modeOk = operate.setUserMode(user_mode::balanced_mode);
    updateUserMode();
    updateFanMode();
    if (!modeOk) {
        ui->fanCurveStatusLabel->setText(tr("Failed to verify Balanced mode; pending fan edits preserved"));
        return;
    }
    const auto result = operate.reconcileFanCurvePreference();
    updateFanMode();
    showModeResult(result, ui->fanCurveStatusLabel, ui->fanModeValueLabel->text());
    if (!result.has_value() || result->success)
        updateFanSpeedSettings();
}

void MainWindow::setSilentMode() {
    const bool modeOk = operate.setUserMode(user_mode::silent_mode);
    updateUserMode();
    updateFanMode();
    if (!modeOk) {
        ui->fanCurveStatusLabel->setText(tr("Failed to verify Silent mode; pending fan edits preserved"));
        return;
    }
    const auto result = operate.reconcileFanCurvePreference();
    updateFanMode();
    showModeResult(result, ui->fanCurveStatusLabel, ui->fanModeValueLabel->text());
    if (!result.has_value() || result->success)
        updateFanSpeedSettings();
}

void MainWindow::setSuperBatteryMode() {
    const bool modeOk = operate.setUserMode(user_mode::super_battery_mode);
    updateUserMode();
    updateFanMode();
    if (!modeOk) {
        ui->fanCurveStatusLabel->setText(tr("Failed to verify Super Battery mode; pending fan edits preserved"));
        return;
    }
    const auto result = operate.reconcileFanCurvePreference();
    updateFanMode();
    showModeResult(result, ui->fanCurveStatusLabel, ui->fanModeValueLabel->text());
    if (!result.has_value() || result->success)
        updateFanSpeedSettings();
}

void MainWindow::setCoolerBoostState(bool enabled) const {
    operate.setCoolerBoostState(enabled);
    if (operate.updateEcData())
        updateCoolerBoostState();
}

QVector<int> MainWindow::getFan1SpeedValues() const {
    QVector<int> fan1SpeedSettings;

    fan1SpeedSettings.push_back(ui->fan1Speed1Slider->value());
    fan1SpeedSettings.push_back(ui->fan1Speed2Slider->value());
    fan1SpeedSettings.push_back(ui->fan1Speed3Slider->value());
    fan1SpeedSettings.push_back(ui->fan1Speed4Slider->value());
    fan1SpeedSettings.push_back(ui->fan1Speed5Slider->value());
    fan1SpeedSettings.push_back(ui->fan1Speed6Slider->value());
    fan1SpeedSettings.push_back(ui->fan1Speed7Slider->value());

    return fan1SpeedSettings;
}

QVector<int> MainWindow::getFan2SpeedValues() const {
    QVector<int> fan2SpeedSettings;

    fan2SpeedSettings.push_back(ui->fan2Speed1Slider->value());
    fan2SpeedSettings.push_back(ui->fan2Speed2Slider->value());
    fan2SpeedSettings.push_back(ui->fan2Speed3Slider->value());
    fan2SpeedSettings.push_back(ui->fan2Speed4Slider->value());
    fan2SpeedSettings.push_back(ui->fan2Speed5Slider->value());
    fan2SpeedSettings.push_back(ui->fan2Speed6Slider->value());
    fan2SpeedSettings.push_back(ui->fan2Speed7Slider->value());

    return fan2SpeedSettings;
}

QVector<int> MainWindow::getFan1TempValues() const {
    QVector<int> fan1TempSettings;

    fan1TempSettings.push_back(ui->fan1Speed2TempSpinBox->value());
    fan1TempSettings.push_back(ui->fan1Speed3TempSpinBox->value());
    fan1TempSettings.push_back(ui->fan1Speed4TempSpinBox->value());
    fan1TempSettings.push_back(ui->fan1Speed5TempSpinBox->value());
    fan1TempSettings.push_back(ui->fan1Speed6TempSpinBox->value());
    fan1TempSettings.push_back(ui->fan1Speed7TempSpinBox->value());

    return fan1TempSettings;
}

QVector<int> MainWindow::getFan2TempValues() const {
    QVector<int> fan2TempSettings;

    fan2TempSettings.push_back(ui->fan2Speed2TempSpinBox->value());
    fan2TempSettings.push_back(ui->fan2Speed3TempSpinBox->value());
    fan2TempSettings.push_back(ui->fan2Speed4TempSpinBox->value());
    fan2TempSettings.push_back(ui->fan2Speed5TempSpinBox->value());
    fan2TempSettings.push_back(ui->fan2Speed6TempSpinBox->value());
    fan2TempSettings.push_back(ui->fan2Speed7TempSpinBox->value());

    return fan2TempSettings;
}

void MainWindow::setFanSpeedSettings() {
    const FanCurveCapability capability = operate.getFanCurveCapability();
    if (!capability.complete()) {
        ui->fanCurveStatusLabel->setText(tr("Unsupported: complete msi-ec fan curve ABI is unavailable"));
        return;
    }
    ui->fanCurveStatusLabel->setText(tr("Applying…"));
    qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
    FanCurveProfile profile;
    profile.cpuLevels = getFan1SpeedValues();
    profile.cpuThresholds = getFan1TempValues();
    profile.gpuLevels = getFan2SpeedValues();
    profile.gpuThresholds = getFan2TempValues();
    const FanCurveResult result = operate.applyFanCurve(profile);
    if (result.success) {
        ui->fanCurveStatusLabel->setText(tr("Applied (advanced)"));
        updateFanSpeedSettings();
    } else {
        // Keep the editor's pending values intact on failure while reconciling
        // only actual mode/status.
        {
            const QSignalBlocker blocker(ui->advancedFanControlCheckBox);
            ui->advancedFanControlCheckBox->setChecked(result.effectiveMode == QStringLiteral("advanced"));
        }
        updateFanMode();
        ui->fanCurveStatusLabel->setText(
            tr("Failed: %1 (rollback: %2)").arg(result.error, result.rollbackStatus));
        checkFanSettingsChanged();
    }
}

void MainWindow::setFanModeAdvanced(bool enabled) {
    if (!operate.getFanCurveCapability().complete()) {
        ui->fanCurveStatusLabel->setText(tr("Unsupported: complete msi-ec fan curve ABI is unavailable"));
        return;
    }
    if (enabled) {
        ui->fanCurveStatusLabel->setText(tr("Applying…"));
        qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
    }
    if (!enabled) {
        if (!operate.setFanModeAdvanced(false)) {
            {
                const QSignalBlocker blocker(ui->advancedFanControlCheckBox);
                ui->advancedFanControlCheckBox->setChecked(
                    operate.getFanMode() == fan_mode::advanced_fan_mode);
            }
            ui->fanCurveStatusLabel->setText(tr("Failed: could not verify Auto mode; pending fan edits preserved"));
            updateFanMode();
            checkFanSettingsChanged();
            return;
        }
    }
    ui->fanControlTabWidget->setEnabled(operate.getFanCurveCapability().complete());
    ui->fanSpeedResetButton->setEnabled(enabled);
    ui->fanSpeedApplyButton->setEnabled(enabled);
    if (enabled) {
        const FanCurveResult result = operate.applyFanCurve(
            FanCurveProfile{getFan1TempValues(), getFan1SpeedValues(),
                             getFan2TempValues(), getFan2SpeedValues()});
        if (result.success) {
            ui->fanCurveStatusLabel->setText(tr("Applied (advanced)"));
            updateFanSpeedSettings();
        } else {
            const QSignalBlocker blocker(ui->advancedFanControlCheckBox);
            ui->advancedFanControlCheckBox->setChecked(result.effectiveMode == QStringLiteral("advanced"));
            ui->fanCurveStatusLabel->setText(
                tr("Failed: %1 (rollback: %2); pending fan edits preserved")
                    .arg(result.error, result.rollbackStatus));
            checkFanSettingsChanged();
        }
    } else {
        ui->fanCurveStatusLabel->setText(tr("Auto"));
    }
}

void MainWindow::checkFanSettingsChanged() const {
    const FanCurveCapability capability = operate.getFanCurveCapability();
    if (!capability.complete()) {
        ui->fanSpeedApplyButton->setEnabled(false);
        ui->fanSpeedResetButton->setEnabled(false);
        return;
    }
    const auto currentProfile = operate.getFanCurveProfile();
    const bool currentCurveInvalid = !currentProfile.has_value() ||
                                     !validateFanCurve(capability, *currentProfile).isEmpty();
    bool fanSettingChanged = currentCurveInvalid ||
                             (getFan1SpeedValues() != currentProfile->cpuLevels ||
                              getFan2SpeedValues() != currentProfile->gpuLevels ||
                              getFan1TempValues() != currentProfile->cpuThresholds ||
                              getFan2TempValues() != currentProfile->gpuThresholds);
    ui->fanSpeedApplyButton->setEnabled(fanSettingChanged);
    ui->fanSpeedResetButton->setEnabled(fanSettingChanged);
}

void MainWindow::showEvent(QShowEvent *event) {
    startRealtimeUpdate();
    activateWindow();
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if (trayIcon && trayIcon->isVisible()) {
        stopRealtimeUpdate();
        MainWindow::hide();
        event->ignore();
        return;
    }
    quitApp();
}

void MainWindow::quitApp() const {
    Settings::setValue("MainWindow/Width", MainWindow::width());
    Settings::setValue("MainWindow/Height", MainWindow::height());
    (void) QCoreApplication::quit();
}

void MainWindow::onPrepareForSleep(bool sleeping) {
    if (sleeping)
        return;
    const auto result = operate.handleWakeEvent();
    if (result.has_value() && !result->success) {
        ui->fanCurveStatusLabel->setText(
            tr("Failed to reconcile after resume: %1; pending fan edits preserved").arg(result->error));
        updateUserMode();
        updateFanMode();
    } else if (result.has_value() && result->success) {
        updateUserMode();
        updateFanMode();
        updateFanSpeedSettings();
    }
}

void MainWindow::setModeFromSelection(PowerProfile profile) {
    switch (profile) {
    case PowerProfile::Performance:
        setHighPerformanceMode();
        break;
    case PowerProfile::Balanced:
        setBalancedMode();
        break;
    case PowerProfile::Silent:
        setSilentMode();
        break;
    case PowerProfile::PowerSaver:
        setSuperBatteryMode();
        break;
    case PowerProfile::Unknown:
    default:;
    }
}

void MainWindow::on_ChargerStateChange(bool isCharging) {
    if (ui->autoAcDcProfilesGroupBox->isChecked()) {
        Settings s;
        int SelectedModeOnBattery = s.getValue("Settings/UserModeOnBattery").toInt();
        int SelectedModeOnCharger = s.getValue("Settings/UserModeOnCharger").toInt();

        PowerProfile batteryProfile = static_cast<PowerProfile>(SelectedModeOnBattery);
        PowerProfile chargerProfile = static_cast<PowerProfile>(SelectedModeOnCharger);

        if (isCharging) {
            setModeFromSelection(chargerProfile);
        } else {
            setModeFromSelection(batteryProfile);
        }
    } else {
        ui->autoPPDCheckBox->setEnabled(1);
    }
}

void MainWindow::on_PowerProfileChange(const PowerProfile profile) {
    if (ui->autoPPDCheckBox->isChecked()) {
        switch (profile) {
        case PowerProfile::Performance:
            setHighPerformanceMode();
            break;
        case PowerProfile::Balanced:
            setBalancedMode();
            break;
        case PowerProfile::PowerSaver:
            setSuperBatteryMode();
            break;
        case PowerProfile::Unknown:
            default:;
        }
    }
}

void MainWindow::on_bestMobilityRadioButton_toggled(bool checked) {
    if (checked)
        setBestMobility();
}

void MainWindow::on_balancedBatteryRadioButton_toggled(bool checked) {
    if (checked)
        setBalancedBattery();
}

void MainWindow::on_bestBatteryRadioButton_toggled(bool checked) {
    if (checked)
        setBestBattery();
}

void MainWindow::on_customBatteryThresholdRadioButton_toggled(bool checked) {
    if (checked) {
        ui->customBatteryThresholdSpinBox->setEnabled(true);
    } else {
        ui->customBatteryThresholdSpinBox->setEnabled(false);
        ui->customBatteryApplyButton->setEnabled(false);
    }
}

void MainWindow::on_customBatteryThresholdSpinBox_valueChanged(int arg1) {
    ui->customBatteryApplyButton->setEnabled(
            ui->customBatteryThresholdRadioButton->isChecked() && operate.getBatteryThreshold() != arg1);
}

void MainWindow::on_customBatteryApplyButton_clicked() {
    operate.setBatteryThreshold(ui->customBatteryThresholdSpinBox->value());
    updateBatteryThreshold();
}

void MainWindow::on_ReadValueButton_clicked() {
    QString text = ui->addressEdit->displayText();
    int value = operate.getValue(text.toInt());
    ui->ValueSpinBox->setValue(value);
}

void MainWindow::on_usbPowerShareCheckBox_clicked(bool checked) const {
    operate.setUsbPowerShareState(checked);
}

void MainWindow::on_webCamCheckBox_clicked(bool checked) const {
    operate.setWebCamState(checked);
    if (operate.updateEcData()) {
        updateWebCamState();
    }
}

void MainWindow::on_fnSuperSwapCheckBox_clicked(bool checked) const {
    if (operate.setFnSuperSwapState(checked))
        return;
    const QSignalBlocker blocker(ui->fnSuperSwapCheckBox);
    ui->fnSuperSwapCheckBox->setChecked(operate.getFnSuperSwapState());
    ui->fanCurveStatusLabel->setText(tr("Failed to verify Fn/Super swap; setting was not persisted"));
}

void MainWindow::on_coolerBoostCheckBox_clicked(bool checked) const {
    if (operate.getCoolerBoostState() != checked)
        setCoolerBoostState(checked);
}

void MainWindow::on_keyboardBrightnessSlider_valueChanged(int value) const {
    operate.setKeyboardBrightness(value);
    if (operate.updateEcData()) {
        updateKeyboardBrightness();
    }
}

void MainWindow::on_keyboardBacklightModeComboBox_currentIndexChanged(int index) const {
    operate.setKeyboardBacklightMode(index);
}

void MainWindow::on_userModeOnBatteryComboBox_currentIndexChanged(int index) const {
    Settings::setValue("Settings/UserModeOnBattery", index);
    powerMonitor.queryChargerState();
}

void MainWindow::on_userModeOnChargerComboBox_currentIndexChanged(int index) const {
    Settings::setValue("Settings/UserModeOnCharger", index);
    powerMonitor.queryChargerState();
}

void MainWindow::on_autoAcDcProfilesGroupBox_toggled(bool checked) {
    if(checked) {
        if (!powerMonitor.connectToUpower()) {
            QMessageBox::critical(nullptr, this->windowTitle(), tr("Couldn't connect to UPower to get charger status.\n"
                                                                   "Make sure that UPower is installed and running then restart the system."));
            ui->autoAcDcProfilesGroupBox->setChecked(0);
            ui->autoAcDcProfilesGroupBox->setEnabled(0);
            return;
        }

        powerMonitor.disconnectFromPowerProfiles();
        ui->autoPPDCheckBox->setChecked(0);
        ui->autoPPDCheckBox->setEnabled(0);
        powerMonitor.queryChargerState();
    } else {
        ui->autoPPDCheckBox->setEnabled(1);
        powerMonitor.disconnectFromUpower();
    }

    Settings::setValue("Settings/autoAcDcProfilesState", checked);
}

void MainWindow::on_autoPPDCheckBox_toggled(bool checked) {
    if (checked) {

        if (!powerMonitor.connectToPowerProfiles()) {
            QMessageBox::critical(nullptr, this->windowTitle(), tr("Couldn't connect to Power Profiles Daemon.\n"
                                                                   "Make sure that either Power Profiles Daemon or TuneD is installed and restart the system."));
            ui->autoPPDCheckBox->setChecked(0);
            return;
        }

        powerMonitor.disconnectFromUpower();
        ui->highPerformanceModeRadioButton->setEnabled(0);
        ui->balancedModeRadioButton->setEnabled(0);
        ui->silentModeRadioButton->setEnabled(0);
        ui->superBatteryModeRadioButton->setEnabled(0);
        ui->autoAcDcProfilesGroupBox->setChecked(0);
        ui->autoAcDcProfilesGroupBox->setEnabled(0);
        powerMonitor.queryPowerProfile();
    } else {
        ui->highPerformanceModeRadioButton->setEnabled(1);
        ui->balancedModeRadioButton->setEnabled(1);
        ui->silentModeRadioButton->setEnabled(1);
        ui->superBatteryModeRadioButton->setEnabled(1);
        ui->autoAcDcProfilesGroupBox->setEnabled(1);
    }
    Settings::setValue("Settings/autoPPDstate", checked);
}

void MainWindow::on_highPerformanceModeRadioButton_toggled(bool checked) {
    if (checked)
        setHighPerformanceMode();
}

void MainWindow::on_balancedModeRadioButton_toggled(bool checked) {
    if (checked)
        setBalancedMode();
}

void MainWindow::on_silentModeRadioButton_toggled(bool checked) {
    if (checked)
        setSilentMode();
}

void MainWindow::on_superBatteryModeRadioButton_toggled(bool checked) {
    if (checked)
        setSuperBatteryMode();
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason) {
    switch (reason) {
        case QSystemTrayIcon::Trigger:
        case QSystemTrayIcon::DoubleClick:
            if (!MainWindow::isHidden()) {
                MainWindow::close();
            } else {
                MainWindow::showNormal();
            }
            break;
        case QSystemTrayIcon::MiddleClick:
            break;
        default:;
    }
}

void MainWindow::createTrayIcon() {
    createActions();

    modeTrayMenu = new QMenu(tr("Mode"));
    modeTrayActions = new QActionGroup(this);
    modeTrayActions->setExclusive(true);


    modeTrayActions->addAction(highPerformanceMode);
    modeTrayActions->addAction(balancedMode);
    modeTrayActions->addAction(silentMode);
    modeTrayActions->addAction(superBatteryMode);

    modeTrayMenu->addAction(highPerformanceMode);
    modeTrayMenu->addAction(balancedMode);
    modeTrayMenu->addAction(silentMode);
    modeTrayMenu->addAction(superBatteryMode);

    fanTrayMenu = new QMenu(tr("Cooling"));
    fanTrayMenu->addAction(coolerBoostAction);

    batteryTrayMenu = new QMenu(tr("Charge limit"));
    batteryTrayMenu->addAction(bestMobilityAction);
    batteryTrayMenu->addAction(balancedBatteryAction);
    batteryTrayMenu->addAction(bestBatteryAction);

    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addMenu(modeTrayMenu);
    trayIconMenu->addMenu(fanTrayMenu);
    trayIconMenu->addMenu(batteryTrayMenu);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
    auto icon = QIcon(":/images/AppIcon");
    trayIcon->setIcon(icon);
    trayIcon->setToolTip("MControlCenter");

    trayIcon->show();

    connect(trayIcon, &QSystemTrayIcon::activated, this, &MainWindow::iconActivated);
}

void MainWindow::createActions() {
    restoreAction = new QAction(tr("Show"), this);
    connect(restoreAction, &QAction::triggered, this, &MainWindow::showNormal);

    highPerformanceMode = new QAction(ui->highPerformanceModeRadioButton->text(), this);
    highPerformanceMode->setCheckable(true);

    balancedMode = new QAction(ui->balancedModeRadioButton->text(), this);
    balancedMode->setCheckable(true);

    silentMode = new QAction(ui->silentModeRadioButton->text(), this);
    silentMode->setCheckable(true);

    superBatteryMode = new QAction(ui->superBatteryModeRadioButton->text(), this);
    superBatteryMode->setCheckable(true);

    connect(highPerformanceMode, &QAction::triggered, this, &MainWindow::setHighPerformanceMode);
    connect(balancedMode, &QAction::triggered, this, &MainWindow::setBalancedMode);
    connect(silentMode, &QAction::triggered, this, &MainWindow::setSilentMode);
    connect(superBatteryMode, &QAction::triggered, this, &MainWindow::setSuperBatteryMode);

    coolerBoostAction = new QAction(tr("Cooler Boost"), this);
    coolerBoostAction->setCheckable(true);

    connect(coolerBoostAction, &QAction::triggered, this, &MainWindow::setCoolerBoostState);

    bestMobilityAction = new QAction(ui->bestMobilityRadioButton->text() + " (100%)", this);
    balancedBatteryAction = new QAction(ui->balancedBatteryRadioButton->text() + " (80%)", this);
    bestBatteryAction = new QAction(ui->bestBatteryRadioButton->text() + " (60%)", this);

    connect(bestMobilityAction, &QAction::triggered, this, &MainWindow::setBestMobility);
    connect(balancedBatteryAction, &QAction::triggered, this, &MainWindow::setBalancedBattery);
    connect(bestBatteryAction, &QAction::triggered, this, &MainWindow::setBestBattery);

    quitAction = new QAction(tr("Quit"), this);
    connect(quitAction, &QAction::triggered, this, &MainWindow::quitApp);
}

void MainWindow::saveStateRequest(QSessionManager &sessionManager) {
    sessionManager.setRestartHint(QSessionManager::RestartNever);
}
