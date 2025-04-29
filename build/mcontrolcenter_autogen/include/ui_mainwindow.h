/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_3;
    QTabWidget *tabWidget;
    QWidget *overviewTab;
    QGridLayout *gridLayout_11;
    QGridLayout *gridLayout_12;
    QGridLayout *gridLayout_8;
    QLabel *gpuFanLabel;
    QLabel *cpuTempValueLabel;
    QLabel *cpuFanLabel;
    QLabel *fan1ValueLabel;
    QLabel *BatteryChargeValueLabel;
    QLabel *batteryThresholdLabel;
    QLabel *batteryThresholdValueLabel;
    QLabel *cpuTempLabel;
    QLabel *gpuTempValueLabel;
    QLabel *BatteryChargeLabel;
    QLabel *fan2ValueLabel;
    QLabel *gpuTempLabel;
    QFrame *line_6;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *chargingStatusLabel;
    QLabel *chargingStatusValueLabel;
    QCheckBox *usbPowerShareCheckBox;
    QCheckBox *fnSuperSwapCheckBox;
    QCheckBox *webCamCheckBox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_19;
    QLabel *fanModeValueLabel;
    QCheckBox *coolerBoostCheckBox;
    QSpacerItem *horizontalSpacer_5;
    QWidget *modeFormWidget;
    QFormLayout *formLayout_5;
    QRadioButton *highPerformanceModeRadioButton;
    QLabel *label_15;
    QRadioButton *balancedModeRadioButton;
    QLabel *label_16;
    QRadioButton *silentModeRadioButton;
    QLabel *label_17;
    QRadioButton *superBatteryModeRadioButton;
    QLabel *label_18;
    QFrame *line_4;
    QWidget *batteryTab;
    QGridLayout *gridLayout_13;
    QLabel *label_5;
    QFrame *line;
    QGridLayout *gridLayout_10;
    QLabel *label_4;
    QRadioButton *bestMobilityRadioButton;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_8;
    QSpinBox *customBatteryThresholdSpinBox;
    QPushButton *customBatteryApplyButton;
    QSpacerItem *horizontalSpacer_3;
    QRadioButton *customBatteryThresholdRadioButton;
    QLabel *label_6;
    QRadioButton *balancedBatteryRadioButton;
    QRadioButton *bestBatteryRadioButton;
    QSpacerItem *verticalSpacer_4;
    QWidget *fanControlTab;
    QGridLayout *gridLayout_9;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_3;
    QGridLayout *gridLayout_7;
    QCheckBox *advancedFanControlCheckBox;
    QTabWidget *fanControlTabWidget;
    QWidget *tabWidgetPage1;
    QGridLayout *_2;
    QSlider *fan1Speed4Slider;
    QLabel *fan1Speed3Label;
    QSlider *fan1Speed3Slider;
    QSlider *fan1Speed5Slider;
    QSlider *fan1Speed2Slider;
    QLabel *fan1Speed7Label;
    QLabel *fan1Speed6Label;
    QLabel *fan1Speed2Label;
    QSlider *fan1Speed7Slider;
    QLabel *fan1Speed5Label;
    QLabel *fan1Speed1Label;
    QSlider *fan1Speed1Slider;
    QLabel *fan1Speed4Label;
    QSlider *fan1Speed6Slider;
    QLabel *fan1Speed1TempLabel;
    QSpinBox *fan1Speed2TempSpinBox;
    QSpinBox *fan1Speed3TempSpinBox;
    QSpinBox *fan1Speed4TempSpinBox;
    QSpinBox *fan1Speed5TempSpinBox;
    QSpinBox *fan1Speed6TempSpinBox;
    QSpinBox *fan1Speed7TempSpinBox;
    QWidget *tabWidgetPage2;
    QGridLayout *gridLayout_4;
    QLabel *fan2Speed4Label;
    QLabel *fan2Speed1Label;
    QSlider *fan2Speed4Slider;
    QSlider *fan2Speed2Slider;
    QSlider *fan2Speed3Slider;
    QLabel *fan2Speed6Label;
    QSlider *fan2Speed6Slider;
    QLabel *fan2Speed5Label;
    QSlider *fan2Speed1Slider;
    QSlider *fan2Speed5Slider;
    QLabel *fan2Speed2Label;
    QLabel *fan2Speed3Label;
    QSlider *fan2Speed7Slider;
    QLabel *fan2Speed7Label;
    QLabel *fan2Speed1TempLabel;
    QSpinBox *fan2Speed2TempSpinBox;
    QSpinBox *fan2Speed3TempSpinBox;
    QSpinBox *fan2Speed4TempSpinBox;
    QSpinBox *fan2Speed5TempSpinBox;
    QSpinBox *fan2Speed6TempSpinBox;
    QSpinBox *fan2Speed7TempSpinBox;
    QHBoxLayout *horizontalLayout;
    QPushButton *fanSpeedResetButton;
    QPushButton *fanSpeedApplyButton;
    QWidget *keyboardTab;
    QGridLayout *gridLayout_2;
    QLabel *keyboardBacklightLabel;
    QFrame *line_2;
    QSlider *keyboardBrightnessSlider;
    QSpacerItem *verticalSpacer;
    QComboBox *keyboardBacklightModeComboBox;
    QWidget *aboutTab;
    QGridLayout *gridLayout_5;
    QLabel *label_3;
    QFrame *line_3;
    QGridLayout *gridLayout;
    QLabel *QtVersionValue;
    QLabel *bugTrackerLabel;
    QLabel *ecVersionLabel;
    QLabel *label_13;
    QLabel *label_11;
    QLabel *gitHubLabel;
    QLabel *ecVersionValueLabel;
    QLabel *versionLabel;
    QLabel *MsiEcGitHubLabel;
    QLabel *bugTrackerValueLabel;
    QLabel *versionValueLabel;
    QLabel *gitHubValueLabel;
    QLabel *ecBuildLabel;
    QLabel *label_12;
    QLabel *MsiEcStatusLabel;
    QLabel *ecBuildValueLabel;
    QSpacerItem *verticalSpacer_3;
    QWidget *debugTab;
    QGridLayout *gridLayout_14;
    QLabel *label_10;
    QFrame *line_5;
    QGridLayout *gridLayout_6;
    QPushButton *ReadValueButton;
    QPushButton *WriteValueButton;
    QLineEdit *addressEdit;
    QSpinBox *ValueSpinBox;
    QLabel *label_2;
    QLabel *label;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->setEnabled(true);
        MainWindow->resize(580, 480);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(580, 480));
        MainWindow->setMaximumSize(QSize(580, 480));
        MainWindow->setWindowTitle(QString::fromUtf8("MControlCenter"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setEnabled(true);
        gridLayout_3 = new QGridLayout(centralwidget);
        gridLayout_3->setObjectName("gridLayout_3");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        tabWidget->setMinimumSize(QSize(0, 0));
        tabWidget->setBaseSize(QSize(0, 0));
        tabWidget->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        tabWidget->setAutoFillBackground(true);
        tabWidget->setTabPosition(QTabWidget::TabPosition::North);
        tabWidget->setTabShape(QTabWidget::TabShape::Rounded);
        tabWidget->setDocumentMode(true);
        tabWidget->setTabsClosable(false);
        tabWidget->setMovable(true);
        tabWidget->setTabBarAutoHide(true);
        overviewTab = new QWidget();
        overviewTab->setObjectName("overviewTab");
        overviewTab->setMaximumSize(QSize(16777215, 16777215));
        gridLayout_11 = new QGridLayout(overviewTab);
        gridLayout_11->setObjectName("gridLayout_11");
        gridLayout_12 = new QGridLayout();
        gridLayout_12->setObjectName("gridLayout_12");
        gridLayout_8 = new QGridLayout();
        gridLayout_8->setObjectName("gridLayout_8");
        gpuFanLabel = new QLabel(overviewTab);
        gpuFanLabel->setObjectName("gpuFanLabel");

        gridLayout_8->addWidget(gpuFanLabel, 5, 1, 1, 1);

        cpuTempValueLabel = new QLabel(overviewTab);
        cpuTempValueLabel->setObjectName("cpuTempValueLabel");
        cpuTempValueLabel->setText(QString::fromUtf8("-"));
        cpuTempValueLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_8->addWidget(cpuTempValueLabel, 2, 2, 1, 1);

        cpuFanLabel = new QLabel(overviewTab);
        cpuFanLabel->setObjectName("cpuFanLabel");

        gridLayout_8->addWidget(cpuFanLabel, 4, 1, 1, 1);

        fan1ValueLabel = new QLabel(overviewTab);
        fan1ValueLabel->setObjectName("fan1ValueLabel");
        fan1ValueLabel->setText(QString::fromUtf8("-"));
        fan1ValueLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_8->addWidget(fan1ValueLabel, 4, 2, 1, 1);

        BatteryChargeValueLabel = new QLabel(overviewTab);
        BatteryChargeValueLabel->setObjectName("BatteryChargeValueLabel");
        BatteryChargeValueLabel->setText(QString::fromUtf8("-"));
        BatteryChargeValueLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_8->addWidget(BatteryChargeValueLabel, 0, 2, 1, 1);

        batteryThresholdLabel = new QLabel(overviewTab);
        batteryThresholdLabel->setObjectName("batteryThresholdLabel");

        gridLayout_8->addWidget(batteryThresholdLabel, 1, 1, 1, 1);

        batteryThresholdValueLabel = new QLabel(overviewTab);
        batteryThresholdValueLabel->setObjectName("batteryThresholdValueLabel");
        batteryThresholdValueLabel->setText(QString::fromUtf8("-"));
        batteryThresholdValueLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_8->addWidget(batteryThresholdValueLabel, 1, 2, 1, 1);

        cpuTempLabel = new QLabel(overviewTab);
        cpuTempLabel->setObjectName("cpuTempLabel");

        gridLayout_8->addWidget(cpuTempLabel, 2, 1, 1, 1);

        gpuTempValueLabel = new QLabel(overviewTab);
        gpuTempValueLabel->setObjectName("gpuTempValueLabel");
        gpuTempValueLabel->setText(QString::fromUtf8("-"));
        gpuTempValueLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_8->addWidget(gpuTempValueLabel, 3, 2, 1, 1);

        BatteryChargeLabel = new QLabel(overviewTab);
        BatteryChargeLabel->setObjectName("BatteryChargeLabel");

        gridLayout_8->addWidget(BatteryChargeLabel, 0, 1, 1, 1);

        fan2ValueLabel = new QLabel(overviewTab);
        fan2ValueLabel->setObjectName("fan2ValueLabel");
        fan2ValueLabel->setText(QString::fromUtf8("-"));
        fan2ValueLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_8->addWidget(fan2ValueLabel, 5, 2, 1, 1);

        gpuTempLabel = new QLabel(overviewTab);
        gpuTempLabel->setObjectName("gpuTempLabel");

        gridLayout_8->addWidget(gpuTempLabel, 3, 1, 1, 1);


        gridLayout_12->addLayout(gridLayout_8, 0, 1, 1, 1);

        line_6 = new QFrame(overviewTab);
        line_6->setObjectName("line_6");
        line_6->setMinimumSize(QSize(35, 0));
        line_6->setFrameShadow(QFrame::Shadow::Sunken);
        line_6->setFrameShape(QFrame::Shape::VLine);

        gridLayout_12->addWidget(line_6, 0, 3, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(58, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_12->addItem(horizontalSpacer_4, 0, 6, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_12->addItem(horizontalSpacer, 0, 4, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_12->addItem(horizontalSpacer_2, 0, 2, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(-1, 1, -1, -1);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        chargingStatusLabel = new QLabel(overviewTab);
        chargingStatusLabel->setObjectName("chargingStatusLabel");

        horizontalLayout_5->addWidget(chargingStatusLabel);

        chargingStatusValueLabel = new QLabel(overviewTab);
        chargingStatusValueLabel->setObjectName("chargingStatusValueLabel");
        chargingStatusValueLabel->setText(QString::fromUtf8("-"));
        chargingStatusValueLabel->setAlignment(Qt::AlignmentFlag::AlignJustify|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout_5->addWidget(chargingStatusValueLabel);


        verticalLayout_2->addLayout(horizontalLayout_5);

        usbPowerShareCheckBox = new QCheckBox(overviewTab);
        usbPowerShareCheckBox->setObjectName("usbPowerShareCheckBox");

        verticalLayout_2->addWidget(usbPowerShareCheckBox);

        fnSuperSwapCheckBox = new QCheckBox(overviewTab);
        fnSuperSwapCheckBox->setObjectName("fnSuperSwapCheckBox");

        verticalLayout_2->addWidget(fnSuperSwapCheckBox);

        webCamCheckBox = new QCheckBox(overviewTab);
        webCamCheckBox->setObjectName("webCamCheckBox");

        verticalLayout_2->addWidget(webCamCheckBox);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_19 = new QLabel(overviewTab);
        label_19->setObjectName("label_19");
        label_19->setEnabled(true);

        horizontalLayout_2->addWidget(label_19);

        fanModeValueLabel = new QLabel(overviewTab);
        fanModeValueLabel->setObjectName("fanModeValueLabel");
        fanModeValueLabel->setEnabled(true);
        fanModeValueLabel->setText(QString::fromUtf8("-"));
        fanModeValueLabel->setAlignment(Qt::AlignmentFlag::AlignJustify|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout_2->addWidget(fanModeValueLabel);


        verticalLayout_2->addLayout(horizontalLayout_2);

        coolerBoostCheckBox = new QCheckBox(overviewTab);
        coolerBoostCheckBox->setObjectName("coolerBoostCheckBox");
        coolerBoostCheckBox->setMinimumSize(QSize(0, 0));

        verticalLayout_2->addWidget(coolerBoostCheckBox);


        gridLayout_12->addLayout(verticalLayout_2, 0, 5, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_12->addItem(horizontalSpacer_5, 0, 0, 1, 1);


        gridLayout_11->addLayout(gridLayout_12, 0, 0, 1, 1);

        modeFormWidget = new QWidget(overviewTab);
        modeFormWidget->setObjectName("modeFormWidget");
        formLayout_5 = new QFormLayout(modeFormWidget);
        formLayout_5->setObjectName("formLayout_5");
        formLayout_5->setFieldGrowthPolicy(QFormLayout::FieldGrowthPolicy::AllNonFixedFieldsGrow);
        formLayout_5->setRowWrapPolicy(QFormLayout::RowWrapPolicy::WrapLongRows);
        formLayout_5->setLabelAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        formLayout_5->setFormAlignment(Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignTop);
        formLayout_5->setHorizontalSpacing(45);
        formLayout_5->setVerticalSpacing(10);
        formLayout_5->setContentsMargins(10, 10, 10, 10);
        highPerformanceModeRadioButton = new QRadioButton(modeFormWidget);
        highPerformanceModeRadioButton->setObjectName("highPerformanceModeRadioButton");

        formLayout_5->setWidget(0, QFormLayout::LabelRole, highPerformanceModeRadioButton);

        label_15 = new QLabel(modeFormWidget);
        label_15->setObjectName("label_15");
        label_15->setMinimumSize(QSize(26, 0));
        label_15->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_15->setWordWrap(true);

        formLayout_5->setWidget(0, QFormLayout::FieldRole, label_15);

        balancedModeRadioButton = new QRadioButton(modeFormWidget);
        balancedModeRadioButton->setObjectName("balancedModeRadioButton");

        formLayout_5->setWidget(1, QFormLayout::LabelRole, balancedModeRadioButton);

        label_16 = new QLabel(modeFormWidget);
        label_16->setObjectName("label_16");
        label_16->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_16->setWordWrap(true);

        formLayout_5->setWidget(1, QFormLayout::FieldRole, label_16);

        silentModeRadioButton = new QRadioButton(modeFormWidget);
        silentModeRadioButton->setObjectName("silentModeRadioButton");

        formLayout_5->setWidget(2, QFormLayout::LabelRole, silentModeRadioButton);

        label_17 = new QLabel(modeFormWidget);
        label_17->setObjectName("label_17");
        label_17->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_17->setWordWrap(true);

        formLayout_5->setWidget(2, QFormLayout::FieldRole, label_17);

        superBatteryModeRadioButton = new QRadioButton(modeFormWidget);
        superBatteryModeRadioButton->setObjectName("superBatteryModeRadioButton");

        formLayout_5->setWidget(3, QFormLayout::LabelRole, superBatteryModeRadioButton);

        label_18 = new QLabel(modeFormWidget);
        label_18->setObjectName("label_18");
        label_18->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_18->setWordWrap(true);

        formLayout_5->setWidget(3, QFormLayout::FieldRole, label_18);


        gridLayout_11->addWidget(modeFormWidget, 2, 0, 1, 1);

        line_4 = new QFrame(overviewTab);
        line_4->setObjectName("line_4");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(line_4->sizePolicy().hasHeightForWidth());
        line_4->setSizePolicy(sizePolicy2);
        line_4->setMinimumSize(QSize(0, 30));
        line_4->setFrameShadow(QFrame::Shadow::Sunken);
        line_4->setFrameShape(QFrame::Shape::HLine);

        gridLayout_11->addWidget(line_4, 1, 0, 1, 1);

        QIcon icon(QIcon::fromTheme(QString::fromUtf8("computer")));
        tabWidget->addTab(overviewTab, icon, QString());
        batteryTab = new QWidget();
        batteryTab->setObjectName("batteryTab");
        gridLayout_13 = new QGridLayout(batteryTab);
        gridLayout_13->setObjectName("gridLayout_13");
        label_5 = new QLabel(batteryTab);
        label_5->setObjectName("label_5");
        label_5->setScaledContents(false);
        label_5->setAlignment(Qt::AlignmentFlag::AlignJustify|Qt::AlignmentFlag::AlignVCenter);
        label_5->setWordWrap(true);
        label_5->setMargin(0);
        label_5->setTextInteractionFlags(Qt::TextInteractionFlag::NoTextInteraction);

        gridLayout_13->addWidget(label_5, 0, 0, 1, 1);

        line = new QFrame(batteryTab);
        line->setObjectName("line");
        line->setMinimumSize(QSize(0, 10));
        line->setFrameShadow(QFrame::Shadow::Sunken);
        line->setFrameShape(QFrame::Shape::HLine);

        gridLayout_13->addWidget(line, 1, 0, 1, 1);

        gridLayout_10 = new QGridLayout();
        gridLayout_10->setObjectName("gridLayout_10");
        gridLayout_10->setHorizontalSpacing(10);
        gridLayout_10->setVerticalSpacing(6);
        gridLayout_10->setContentsMargins(10, 0, 10, 0);
        label_4 = new QLabel(batteryTab);
        label_4->setObjectName("label_4");
        label_4->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_4->setWordWrap(true);

        gridLayout_10->addWidget(label_4, 0, 1, 1, 1);

        bestMobilityRadioButton = new QRadioButton(batteryTab);
        bestMobilityRadioButton->setObjectName("bestMobilityRadioButton");
        bestMobilityRadioButton->setCheckable(true);

        gridLayout_10->addWidget(bestMobilityRadioButton, 0, 0, 1, 1);

        label_7 = new QLabel(batteryTab);
        label_7->setObjectName("label_7");
        label_7->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_7->setWordWrap(true);

        gridLayout_10->addWidget(label_7, 2, 1, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_8);

        customBatteryThresholdSpinBox = new QSpinBox(batteryTab);
        customBatteryThresholdSpinBox->setObjectName("customBatteryThresholdSpinBox");
        customBatteryThresholdSpinBox->setEnabled(false);
        customBatteryThresholdSpinBox->setMinimumSize(QSize(52, 0));
        customBatteryThresholdSpinBox->setAlignment(Qt::AlignmentFlag::AlignCenter);
        customBatteryThresholdSpinBox->setMinimum(30);
        customBatteryThresholdSpinBox->setMaximum(100);

        horizontalLayout_3->addWidget(customBatteryThresholdSpinBox);

        customBatteryApplyButton = new QPushButton(batteryTab);
        customBatteryApplyButton->setObjectName("customBatteryApplyButton");
        customBatteryApplyButton->setEnabled(false);

        horizontalLayout_3->addWidget(customBatteryApplyButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        gridLayout_10->addLayout(horizontalLayout_3, 3, 1, 1, 1);

        customBatteryThresholdRadioButton = new QRadioButton(batteryTab);
        customBatteryThresholdRadioButton->setObjectName("customBatteryThresholdRadioButton");

        gridLayout_10->addWidget(customBatteryThresholdRadioButton, 3, 0, 1, 1);

        label_6 = new QLabel(batteryTab);
        label_6->setObjectName("label_6");
        label_6->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_6->setWordWrap(true);

        gridLayout_10->addWidget(label_6, 1, 1, 1, 1);

        balancedBatteryRadioButton = new QRadioButton(batteryTab);
        balancedBatteryRadioButton->setObjectName("balancedBatteryRadioButton");

        gridLayout_10->addWidget(balancedBatteryRadioButton, 1, 0, 1, 1);

        bestBatteryRadioButton = new QRadioButton(batteryTab);
        bestBatteryRadioButton->setObjectName("bestBatteryRadioButton");

        gridLayout_10->addWidget(bestBatteryRadioButton, 2, 0, 1, 1);


        gridLayout_13->addLayout(gridLayout_10, 2, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 195, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_13->addItem(verticalSpacer_4, 3, 0, 1, 1);

        QIcon icon1(QIcon::fromTheme(QString::fromUtf8("battery")));
        tabWidget->addTab(batteryTab, icon1, QString());
        fanControlTab = new QWidget();
        fanControlTab->setObjectName("fanControlTab");
        gridLayout_9 = new QGridLayout(fanControlTab);
        gridLayout_9->setObjectName("gridLayout_9");
        scrollArea = new QScrollArea(fanControlTab);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setFrameShape(QFrame::Shape::NoFrame);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName("scrollAreaWidgetContents_3");
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 556, 424));
        gridLayout_7 = new QGridLayout(scrollAreaWidgetContents_3);
        gridLayout_7->setObjectName("gridLayout_7");
        advancedFanControlCheckBox = new QCheckBox(scrollAreaWidgetContents_3);
        advancedFanControlCheckBox->setObjectName("advancedFanControlCheckBox");

        gridLayout_7->addWidget(advancedFanControlCheckBox, 0, 0, 1, 1);

        fanControlTabWidget = new QTabWidget(scrollAreaWidgetContents_3);
        fanControlTabWidget->setObjectName("fanControlTabWidget");
        fanControlTabWidget->setEnabled(false);
        fanControlTabWidget->setStyleSheet(QString::fromUtf8(""));
        fanControlTabWidget->setTabShape(QTabWidget::TabShape::Rounded);
        fanControlTabWidget->setDocumentMode(false);
        tabWidgetPage1 = new QWidget();
        tabWidgetPage1->setObjectName("tabWidgetPage1");
        _2 = new QGridLayout(tabWidgetPage1);
        _2->setObjectName("_2");
        fan1Speed4Slider = new QSlider(tabWidgetPage1);
        fan1Speed4Slider->setObjectName("fan1Speed4Slider");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(fan1Speed4Slider->sizePolicy().hasHeightForWidth());
        fan1Speed4Slider->setSizePolicy(sizePolicy3);
        fan1Speed4Slider->setMinimumSize(QSize(0, 200));
        fan1Speed4Slider->setMaximum(150);
        fan1Speed4Slider->setOrientation(Qt::Orientation::Vertical);
        fan1Speed4Slider->setTickPosition(QSlider::TickPosition::TicksBelow);
        fan1Speed4Slider->setTickInterval(100);

        _2->addWidget(fan1Speed4Slider, 2, 3, 1, 1);

        fan1Speed3Label = new QLabel(tabWidgetPage1);
        fan1Speed3Label->setObjectName("fan1Speed3Label");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(fan1Speed3Label->sizePolicy().hasHeightForWidth());
        fan1Speed3Label->setSizePolicy(sizePolicy4);
        fan1Speed3Label->setText(QString::fromUtf8("0%"));
        fan1Speed3Label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        _2->addWidget(fan1Speed3Label, 0, 2, 1, 1);

        fan1Speed3Slider = new QSlider(tabWidgetPage1);
        fan1Speed3Slider->setObjectName("fan1Speed3Slider");
        sizePolicy3.setHeightForWidth(fan1Speed3Slider->sizePolicy().hasHeightForWidth());
        fan1Speed3Slider->setSizePolicy(sizePolicy3);
        fan1Speed3Slider->setMinimumSize(QSize(0, 200));
        fan1Speed3Slider->setMaximum(150);
        fan1Speed3Slider->setOrientation(Qt::Orientation::Vertical);
        fan1Speed3Slider->setTickPosition(QSlider::TickPosition::TicksBelow);
        fan1Speed3Slider->setTickInterval(100);

        _2->addWidget(fan1Speed3Slider, 2, 2, 1, 1);

        fan1Speed5Slider = new QSlider(tabWidgetPage1);
        fan1Speed5Slider->setObjectName("fan1Speed5Slider");
        sizePolicy3.setHeightForWidth(fan1Speed5Slider->sizePolicy().hasHeightForWidth());
        fan1Speed5Slider->setSizePolicy(sizePolicy3);
        fan1Speed5Slider->setMinimumSize(QSize(0, 200));
        fan1Speed5Slider->setMaximum(150);
        fan1Speed5Slider->setOrientation(Qt::Orientation::Vertical);
        fan1Speed5Slider->setTickPosition(QSlider::TickPosition::TicksBelow);
        fan1Speed5Slider->setTickInterval(100);

        _2->addWidget(fan1Speed5Slider, 2, 4, 1, 1);

        fan1Speed2Slider = new QSlider(tabWidgetPage1);
        fan1Speed2Slider->setObjectName("fan1Speed2Slider");
        sizePolicy3.setHeightForWidth(fan1Speed2Slider->sizePolicy().hasHeightForWidth());
        fan1Speed2Slider->setSizePolicy(sizePolicy3);
        fan1Speed2Slider->setMinimumSize(QSize(0, 200));
        fan1Speed2Slider->setMaximum(150);
        fan1Speed2Slider->setOrientation(Qt::Orientation::Vertical);
        fan1Speed2Slider->setTickPosition(QSlider::TickPosition::TicksBelow);
        fan1Speed2Slider->setTickInterval(100);

        _2->addWidget(fan1Speed2Slider, 2, 1, 1, 1);

        fan1Speed7Label = new QLabel(tabWidgetPage1);
        fan1Speed7Label->setObjectName("fan1Speed7Label");
        sizePolicy4.setHeightForWidth(fan1Speed7Label->sizePolicy().hasHeightForWidth());
        fan1Speed7Label->setSizePolicy(sizePolicy4);
        fan1Speed7Label->setText(QString::fromUtf8("0%"));
        fan1Speed7Label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        _2->addWidget(fan1Speed7Label, 0, 6, 1, 1);

        fan1Speed6Label = new QLabel(tabWidgetPage1);
        fan1Speed6Label->setObjectName("fan1Speed6Label");
        sizePolicy4.setHeightForWidth(fan1Speed6Label->sizePolicy().hasHeightForWidth());
        fan1Speed6Label->setSizePolicy(sizePolicy4);
        fan1Speed6Label->setText(QString::fromUtf8("0%"));
        fan1Speed6Label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        _2->addWidget(fan1Speed6Label, 0, 5, 1, 1);

        fan1Speed2Label = new QLabel(tabWidgetPage1);
        fan1Speed2Label->setObjectName("fan1Speed2Label");
        sizePolicy4.setHeightForWidth(fan1Speed2Label->sizePolicy().hasHeightForWidth());
        fan1Speed2Label->setSizePolicy(sizePolicy4);
        fan1Speed2Label->setText(QString::fromUtf8("0%"));
        fan1Speed2Label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        _2->addWidget(fan1Speed2Label, 0, 1, 1, 1);

        fan1Speed7Slider = new QSlider(tabWidgetPage1);
        fan1Speed7Slider->setObjectName("fan1Speed7Slider");
        sizePolicy3.setHeightForWidth(fan1Speed7Slider->sizePolicy().hasHeightForWidth());
        fan1Speed7Slider->setSizePolicy(sizePolicy3);
        fan1Speed7Slider->setMinimumSize(QSize(0, 200));
        fan1Speed7Slider->setMaximum(150);
        fan1Speed7Slider->setOrientation(Qt::Orientation::Vertical);
        fan1Speed7Slider->setTickPosition(QSlider::TickPosition::TicksBelow);
        fan1Speed7Slider->setTickInterval(100);

        _2->addWidget(fan1Speed7Slider, 2, 6, 1, 1);

        fan1Speed5Label = new QLabel(tabWidgetPage1);
        fan1Speed5Label->setObjectName("fan1Speed5Label");
        sizePolicy4.setHeightForWidth(fan1Speed5Label->sizePolicy().hasHeightForWidth());
        fan1Speed5Label->setSizePolicy(sizePolicy4);
        fan1Speed5Label->setText(QString::fromUtf8("0%"));
        fan1Speed5Label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        _2->addWidget(fan1Speed5Label, 0, 4, 1, 1);

        fan1Speed1Label = new QLabel(tabWidgetPage1);
        fan1Speed1Label->setObjectName("fan1Speed1Label");
        sizePolicy4.setHeightForWidth(fan1Speed1Label->sizePolicy().hasHeightForWidth());
        fan1Speed1Label->setSizePolicy(sizePolicy4);
        fan1Speed1Label->setText(QString::fromUtf8("0%"));
        fan1Speed1Label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        _2->addWidget(fan1Speed1Label, 0, 0, 1, 1);

        fan1Speed1Slider = new QSlider(tabWidgetPage1);
        fan1Speed1Slider->setObjectName("fan1Speed1Slider");
        sizePolicy3.setHeightForWidth(fan1Speed1Slider->sizePolicy().hasHeightForWidth());
        fan1Speed1Slider->setSizePolicy(sizePolicy3);
        fan1Speed1Slider->setMinimumSize(QSize(0, 200));
        fan1Speed1Slider->setMaximum(150);
        fan1Speed1Slider->setOrientation(Qt::Orientation::Vertical);
        fan1Speed1Slider->setTickPosition(QSlider::TickPosition::TicksBelow);
        fan1Speed1Slider->setTickInterval(100);

        _2->addWidget(fan1Speed1Slider, 2, 0, 1, 1);

        fan1Speed4Label = new QLabel(tabWidgetPage1);
        fan1Speed4Label->setObjectName("fan1Speed4Label");
        sizePolicy4.setHeightForWidth(fan1Speed4Label->sizePolicy().hasHeightForWidth());
        fan1Speed4Label->setSizePolicy(sizePolicy4);
        fan1Speed4Label->setText(QString::fromUtf8("0%"));
        fan1Speed4Label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        _2->addWidget(fan1Speed4Label, 0, 3, 1, 1);

        fan1Speed6Slider = new QSlider(tabWidgetPage1);
        fan1Speed6Slider->setObjectName("fan1Speed6Slider");
        sizePolicy3.setHeightForWidth(fan1Speed6Slider->sizePolicy().hasHeightForWidth());
        fan1Speed6Slider->setSizePolicy(sizePolicy3);
        fan1Speed6Slider->setMinimumSize(QSize(0, 200));
        fan1Speed6Slider->setMaximum(150);
        fan1Speed6Slider->setOrientation(Qt::Orientation::Vertical);
        fan1Speed6Slider->setTickPosition(QSlider::TickPosition::TicksBelow);
        fan1Speed6Slider->setTickInterval(100);

        _2->addWidget(fan1Speed6Slider, 2, 5, 1, 1);

        fan1Speed1TempLabel = new QLabel(tabWidgetPage1);
        fan1Speed1TempLabel->setObjectName("fan1Speed1TempLabel");
        fan1Speed1TempLabel->setText(QString::fromUtf8("< 0 \302\260C"));
        fan1Speed1TempLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        _2->addWidget(fan1Speed1TempLabel, 3, 0, 1, 1);

        fan1Speed2TempSpinBox = new QSpinBox(tabWidgetPage1);
        fan1Speed2TempSpinBox->setObjectName("fan1Speed2TempSpinBox");
        fan1Speed2TempSpinBox->setMaximumSize(QSize(62, 16777215));
        fan1Speed2TempSpinBox->setSuffix(QString::fromUtf8(" \302\260C"));

        _2->addWidget(fan1Speed2TempSpinBox, 3, 1, 1, 1);

        fan1Speed3TempSpinBox = new QSpinBox(tabWidgetPage1);
        fan1Speed3TempSpinBox->setObjectName("fan1Speed3TempSpinBox");
        fan1Speed3TempSpinBox->setMaximumSize(QSize(62, 16777215));
        fan1Speed3TempSpinBox->setSuffix(QString::fromUtf8(" \302\260C"));

        _2->addWidget(fan1Speed3TempSpinBox, 3, 2, 1, 1);

        fan1Speed4TempSpinBox = new QSpinBox(tabWidgetPage1);
        fan1Speed4TempSpinBox->setObjectName("fan1Speed4TempSpinBox");
        fan1Speed4TempSpinBox->setMaximumSize(QSize(62, 16777215));
        fan1Speed4TempSpinBox->setSuffix(QString::fromUtf8(" \302\260C"));

        _2->addWidget(fan1Speed4TempSpinBox, 3, 3, 1, 1);

        fan1Speed5TempSpinBox = new QSpinBox(tabWidgetPage1);
        fan1Speed5TempSpinBox->setObjectName("fan1Speed5TempSpinBox");
        fan1Speed5TempSpinBox->setMaximumSize(QSize(62, 16777215));
        fan1Speed5TempSpinBox->setSuffix(QString::fromUtf8(" \302\260C"));

        _2->addWidget(fan1Speed5TempSpinBox, 3, 4, 1, 1);

        fan1Speed6TempSpinBox = new QSpinBox(tabWidgetPage1);
        fan1Speed6TempSpinBox->setObjectName("fan1Speed6TempSpinBox");
        fan1Speed6TempSpinBox->setMaximumSize(QSize(62, 16777215));
        fan1Speed6TempSpinBox->setSuffix(QString::fromUtf8(" \302\260C"));

        _2->addWidget(fan1Speed6TempSpinBox, 3, 5, 1, 1);

        fan1Speed7TempSpinBox = new QSpinBox(tabWidgetPage1);
        fan1Speed7TempSpinBox->setObjectName("fan1Speed7TempSpinBox");
        fan1Speed7TempSpinBox->setMaximumSize(QSize(62, 16777215));
        fan1Speed7TempSpinBox->setSuffix(QString::fromUtf8(" \302\260C"));

        _2->addWidget(fan1Speed7TempSpinBox, 3, 6, 1, 1);

        fanControlTabWidget->addTab(tabWidgetPage1, QString());
        tabWidgetPage2 = new QWidget();
        tabWidgetPage2->setObjectName("tabWidgetPage2");
        gridLayout_4 = new QGridLayout(tabWidgetPage2);
        gridLayout_4->setObjectName("gridLayout_4");
        fan2Speed4Label = new QLabel(tabWidgetPage2);
        fan2Speed4Label->setObjectName("fan2Speed4Label");
        sizePolicy4.setHeightForWidth(fan2Speed4Label->sizePolicy().hasHeightForWidth());
        fan2Speed4Label->setSizePolicy(sizePolicy4);
        fan2Speed4Label->setText(QString::fromUtf8("0%"));
        fan2Speed4Label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_4->addWidget(fan2Speed4Label, 0, 3, 1, 1);

        fan2Speed1Label = new QLabel(tabWidgetPage2);
        fan2Speed1Label->setObjectName("fan2Speed1Label");
        sizePolicy4.setHeightForWidth(fan2Speed1Label->sizePolicy().hasHeightForWidth());
        fan2Speed1Label->setSizePolicy(sizePolicy4);
        fan2Speed1Label->setText(QString::fromUtf8("0%"));
        fan2Speed1Label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_4->addWidget(fan2Speed1Label, 0, 0, 1, 1);

        fan2Speed4Slider = new QSlider(tabWidgetPage2);
        fan2Speed4Slider->setObjectName("fan2Speed4Slider");
        fan2Speed4Slider->setMinimumSize(QSize(0, 200));
        fan2Speed4Slider->setMaximum(150);
        fan2Speed4Slider->setOrientation(Qt::Orientation::Vertical);
        fan2Speed4Slider->setTickPosition(QSlider::TickPosition::TicksBelow);
        fan2Speed4Slider->setTickInterval(100);

        gridLayout_4->addWidget(fan2Speed4Slider, 1, 3, 1, 1);

        fan2Speed2Slider = new QSlider(tabWidgetPage2);
        fan2Speed2Slider->setObjectName("fan2Speed2Slider");
        fan2Speed2Slider->setMinimumSize(QSize(0, 200));
        fan2Speed2Slider->setMaximum(150);
        fan2Speed2Slider->setOrientation(Qt::Orientation::Vertical);
        fan2Speed2Slider->setTickPosition(QSlider::TickPosition::TicksBelow);
        fan2Speed2Slider->setTickInterval(100);

        gridLayout_4->addWidget(fan2Speed2Slider, 1, 1, 1, 1);

        fan2Speed3Slider = new QSlider(tabWidgetPage2);
        fan2Speed3Slider->setObjectName("fan2Speed3Slider");
        fan2Speed3Slider->setMinimumSize(QSize(0, 200));
        fan2Speed3Slider->setMaximum(150);
        fan2Speed3Slider->setOrientation(Qt::Orientation::Vertical);
        fan2Speed3Slider->setTickPosition(QSlider::TickPosition::TicksBelow);
        fan2Speed3Slider->setTickInterval(100);

        gridLayout_4->addWidget(fan2Speed3Slider, 1, 2, 1, 1);

        fan2Speed6Label = new QLabel(tabWidgetPage2);
        fan2Speed6Label->setObjectName("fan2Speed6Label");
        sizePolicy4.setHeightForWidth(fan2Speed6Label->sizePolicy().hasHeightForWidth());
        fan2Speed6Label->setSizePolicy(sizePolicy4);
        fan2Speed6Label->setText(QString::fromUtf8("0%"));
        fan2Speed6Label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_4->addWidget(fan2Speed6Label, 0, 5, 1, 1);

        fan2Speed6Slider = new QSlider(tabWidgetPage2);
        fan2Speed6Slider->setObjectName("fan2Speed6Slider");
        fan2Speed6Slider->setMinimumSize(QSize(0, 200));
        fan2Speed6Slider->setMaximum(150);
        fan2Speed6Slider->setOrientation(Qt::Orientation::Vertical);
        fan2Speed6Slider->setTickPosition(QSlider::TickPosition::TicksBelow);
        fan2Speed6Slider->setTickInterval(100);

        gridLayout_4->addWidget(fan2Speed6Slider, 1, 5, 1, 1);

        fan2Speed5Label = new QLabel(tabWidgetPage2);
        fan2Speed5Label->setObjectName("fan2Speed5Label");
        sizePolicy4.setHeightForWidth(fan2Speed5Label->sizePolicy().hasHeightForWidth());
        fan2Speed5Label->setSizePolicy(sizePolicy4);
        fan2Speed5Label->setText(QString::fromUtf8("0%"));
        fan2Speed5Label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_4->addWidget(fan2Speed5Label, 0, 4, 1, 1);

        fan2Speed1Slider = new QSlider(tabWidgetPage2);
        fan2Speed1Slider->setObjectName("fan2Speed1Slider");
        fan2Speed1Slider->setMinimumSize(QSize(0, 200));
        fan2Speed1Slider->setMaximum(150);
        fan2Speed1Slider->setOrientation(Qt::Orientation::Vertical);
        fan2Speed1Slider->setTickPosition(QSlider::TickPosition::TicksBelow);
        fan2Speed1Slider->setTickInterval(100);

        gridLayout_4->addWidget(fan2Speed1Slider, 1, 0, 1, 1);

        fan2Speed5Slider = new QSlider(tabWidgetPage2);
        fan2Speed5Slider->setObjectName("fan2Speed5Slider");
        fan2Speed5Slider->setMinimumSize(QSize(0, 200));
        fan2Speed5Slider->setMaximum(150);
        fan2Speed5Slider->setOrientation(Qt::Orientation::Vertical);
        fan2Speed5Slider->setTickPosition(QSlider::TickPosition::TicksBelow);
        fan2Speed5Slider->setTickInterval(100);

        gridLayout_4->addWidget(fan2Speed5Slider, 1, 4, 1, 1);

        fan2Speed2Label = new QLabel(tabWidgetPage2);
        fan2Speed2Label->setObjectName("fan2Speed2Label");
        sizePolicy4.setHeightForWidth(fan2Speed2Label->sizePolicy().hasHeightForWidth());
        fan2Speed2Label->setSizePolicy(sizePolicy4);
        fan2Speed2Label->setText(QString::fromUtf8("0%"));
        fan2Speed2Label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_4->addWidget(fan2Speed2Label, 0, 1, 1, 1);

        fan2Speed3Label = new QLabel(tabWidgetPage2);
        fan2Speed3Label->setObjectName("fan2Speed3Label");
        sizePolicy4.setHeightForWidth(fan2Speed3Label->sizePolicy().hasHeightForWidth());
        fan2Speed3Label->setSizePolicy(sizePolicy4);
        fan2Speed3Label->setText(QString::fromUtf8("0%"));
        fan2Speed3Label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_4->addWidget(fan2Speed3Label, 0, 2, 1, 1);

        fan2Speed7Slider = new QSlider(tabWidgetPage2);
        fan2Speed7Slider->setObjectName("fan2Speed7Slider");
        fan2Speed7Slider->setMinimumSize(QSize(0, 200));
        fan2Speed7Slider->setMaximum(150);
        fan2Speed7Slider->setOrientation(Qt::Orientation::Vertical);
        fan2Speed7Slider->setTickPosition(QSlider::TickPosition::TicksBelow);
        fan2Speed7Slider->setTickInterval(100);

        gridLayout_4->addWidget(fan2Speed7Slider, 1, 6, 1, 1);

        fan2Speed7Label = new QLabel(tabWidgetPage2);
        fan2Speed7Label->setObjectName("fan2Speed7Label");
        sizePolicy4.setHeightForWidth(fan2Speed7Label->sizePolicy().hasHeightForWidth());
        fan2Speed7Label->setSizePolicy(sizePolicy4);
        fan2Speed7Label->setText(QString::fromUtf8("0%"));
        fan2Speed7Label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_4->addWidget(fan2Speed7Label, 0, 6, 1, 1);

        fan2Speed1TempLabel = new QLabel(tabWidgetPage2);
        fan2Speed1TempLabel->setObjectName("fan2Speed1TempLabel");
        fan2Speed1TempLabel->setText(QString::fromUtf8("< 0 \302\260C"));
        fan2Speed1TempLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout_4->addWidget(fan2Speed1TempLabel, 2, 0, 1, 1);

        fan2Speed2TempSpinBox = new QSpinBox(tabWidgetPage2);
        fan2Speed2TempSpinBox->setObjectName("fan2Speed2TempSpinBox");
        fan2Speed2TempSpinBox->setMaximumSize(QSize(62, 16777215));
        fan2Speed2TempSpinBox->setSuffix(QString::fromUtf8(" \302\260C"));

        gridLayout_4->addWidget(fan2Speed2TempSpinBox, 2, 1, 1, 1);

        fan2Speed3TempSpinBox = new QSpinBox(tabWidgetPage2);
        fan2Speed3TempSpinBox->setObjectName("fan2Speed3TempSpinBox");
        fan2Speed3TempSpinBox->setMaximumSize(QSize(62, 16777215));
        fan2Speed3TempSpinBox->setSuffix(QString::fromUtf8(" \302\260C"));

        gridLayout_4->addWidget(fan2Speed3TempSpinBox, 2, 2, 1, 1);

        fan2Speed4TempSpinBox = new QSpinBox(tabWidgetPage2);
        fan2Speed4TempSpinBox->setObjectName("fan2Speed4TempSpinBox");
        fan2Speed4TempSpinBox->setMaximumSize(QSize(62, 16777215));
        fan2Speed4TempSpinBox->setSuffix(QString::fromUtf8(" \302\260C"));

        gridLayout_4->addWidget(fan2Speed4TempSpinBox, 2, 3, 1, 1);

        fan2Speed5TempSpinBox = new QSpinBox(tabWidgetPage2);
        fan2Speed5TempSpinBox->setObjectName("fan2Speed5TempSpinBox");
        fan2Speed5TempSpinBox->setMaximumSize(QSize(62, 16777215));
        fan2Speed5TempSpinBox->setSuffix(QString::fromUtf8(" \302\260C"));

        gridLayout_4->addWidget(fan2Speed5TempSpinBox, 2, 4, 1, 1);

        fan2Speed6TempSpinBox = new QSpinBox(tabWidgetPage2);
        fan2Speed6TempSpinBox->setObjectName("fan2Speed6TempSpinBox");
        fan2Speed6TempSpinBox->setMaximumSize(QSize(62, 16777215));
        fan2Speed6TempSpinBox->setSuffix(QString::fromUtf8(" \302\260C"));

        gridLayout_4->addWidget(fan2Speed6TempSpinBox, 2, 5, 1, 1);

        fan2Speed7TempSpinBox = new QSpinBox(tabWidgetPage2);
        fan2Speed7TempSpinBox->setObjectName("fan2Speed7TempSpinBox");
        fan2Speed7TempSpinBox->setMaximumSize(QSize(62, 16777215));
        fan2Speed7TempSpinBox->setSuffix(QString::fromUtf8(" \302\260C"));

        gridLayout_4->addWidget(fan2Speed7TempSpinBox, 2, 6, 1, 1);

        fanControlTabWidget->addTab(tabWidgetPage2, QString());

        gridLayout_7->addWidget(fanControlTabWidget, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        fanSpeedResetButton = new QPushButton(scrollAreaWidgetContents_3);
        fanSpeedResetButton->setObjectName("fanSpeedResetButton");
        fanSpeedResetButton->setEnabled(false);

        horizontalLayout->addWidget(fanSpeedResetButton);

        fanSpeedApplyButton = new QPushButton(scrollAreaWidgetContents_3);
        fanSpeedApplyButton->setObjectName("fanSpeedApplyButton");
        fanSpeedApplyButton->setEnabled(false);

        horizontalLayout->addWidget(fanSpeedApplyButton);


        gridLayout_7->addLayout(horizontalLayout, 2, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents_3);

        gridLayout_9->addWidget(scrollArea, 0, 0, 1, 1);

        tabWidget->addTab(fanControlTab, QString());
        keyboardTab = new QWidget();
        keyboardTab->setObjectName("keyboardTab");
        gridLayout_2 = new QGridLayout(keyboardTab);
        gridLayout_2->setObjectName("gridLayout_2");
        keyboardBacklightLabel = new QLabel(keyboardTab);
        keyboardBacklightLabel->setObjectName("keyboardBacklightLabel");

        gridLayout_2->addWidget(keyboardBacklightLabel, 0, 0, 1, 1);

        line_2 = new QFrame(keyboardTab);
        line_2->setObjectName("line_2");
        line_2->setMinimumSize(QSize(0, 10));
        line_2->setFrameShadow(QFrame::Shadow::Sunken);
        line_2->setFrameShape(QFrame::Shape::HLine);

        gridLayout_2->addWidget(line_2, 3, 0, 1, 2);

        keyboardBrightnessSlider = new QSlider(keyboardTab);
        keyboardBrightnessSlider->setObjectName("keyboardBrightnessSlider");
        QSizePolicy sizePolicy5(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(keyboardBrightnessSlider->sizePolicy().hasHeightForWidth());
        keyboardBrightnessSlider->setSizePolicy(sizePolicy5);
        keyboardBrightnessSlider->setMaximum(3);
        keyboardBrightnessSlider->setPageStep(1);
        keyboardBrightnessSlider->setOrientation(Qt::Orientation::Horizontal);
        keyboardBrightnessSlider->setTickPosition(QSlider::TickPosition::TicksBothSides);
        keyboardBrightnessSlider->setTickInterval(1);

        gridLayout_2->addWidget(keyboardBrightnessSlider, 2, 0, 1, 2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 4, 0, 1, 2);

        keyboardBacklightModeComboBox = new QComboBox(keyboardTab);
        keyboardBacklightModeComboBox->addItem(QString());
        keyboardBacklightModeComboBox->addItem(QString());
        keyboardBacklightModeComboBox->setObjectName("keyboardBacklightModeComboBox");

        gridLayout_2->addWidget(keyboardBacklightModeComboBox, 1, 0, 1, 2);

        QIcon icon2(QIcon::fromTheme(QString::fromUtf8("input-keyboard")));
        tabWidget->addTab(keyboardTab, icon2, QString());
        aboutTab = new QWidget();
        aboutTab->setObjectName("aboutTab");
        gridLayout_5 = new QGridLayout(aboutTab);
        gridLayout_5->setObjectName("gridLayout_5");
        label_3 = new QLabel(aboutTab);
        label_3->setObjectName("label_3");
        label_3->setAlignment(Qt::AlignmentFlag::AlignJustify|Qt::AlignmentFlag::AlignVCenter);
        label_3->setWordWrap(true);

        gridLayout_5->addWidget(label_3, 0, 0, 1, 3);

        line_3 = new QFrame(aboutTab);
        line_3->setObjectName("line_3");
        line_3->setMinimumSize(QSize(0, 10));
        line_3->setFrameShadow(QFrame::Shadow::Sunken);
        line_3->setFrameShape(QFrame::Shape::HLine);

        gridLayout_5->addWidget(line_3, 1, 0, 1, 3);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        gridLayout->setHorizontalSpacing(70);
        gridLayout->setVerticalSpacing(10);
        gridLayout->setContentsMargins(10, 10, 10, 10);
        QtVersionValue = new QLabel(aboutTab);
        QtVersionValue->setObjectName("QtVersionValue");

        gridLayout->addWidget(QtVersionValue, 1, 1, 1, 1);

        bugTrackerLabel = new QLabel(aboutTab);
        bugTrackerLabel->setObjectName("bugTrackerLabel");

        gridLayout->addWidget(bugTrackerLabel, 4, 0, 1, 1);

        ecVersionLabel = new QLabel(aboutTab);
        ecVersionLabel->setObjectName("ecVersionLabel");

        gridLayout->addWidget(ecVersionLabel, 6, 0, 1, 1);

        label_13 = new QLabel(aboutTab);
        label_13->setObjectName("label_13");

        gridLayout->addWidget(label_13, 1, 0, 1, 1);

        label_11 = new QLabel(aboutTab);
        label_11->setObjectName("label_11");

        gridLayout->addWidget(label_11, 5, 0, 1, 1);

        gitHubLabel = new QLabel(aboutTab);
        gitHubLabel->setObjectName("gitHubLabel");

        gridLayout->addWidget(gitHubLabel, 3, 0, 1, 1);

        ecVersionValueLabel = new QLabel(aboutTab);
        ecVersionValueLabel->setObjectName("ecVersionValueLabel");
        ecVersionValueLabel->setText(QString::fromUtf8("-"));

        gridLayout->addWidget(ecVersionValueLabel, 6, 1, 1, 1);

        versionLabel = new QLabel(aboutTab);
        versionLabel->setObjectName("versionLabel");

        gridLayout->addWidget(versionLabel, 0, 0, 1, 1);

        MsiEcGitHubLabel = new QLabel(aboutTab);
        MsiEcGitHubLabel->setObjectName("MsiEcGitHubLabel");
        MsiEcGitHubLabel->setText(QString::fromUtf8("<a href=\"https://github.com/BeardOverflow/msi-ec\">https://github.com/BeardOverflow/msi-ec</a>"));
        MsiEcGitHubLabel->setOpenExternalLinks(true);
        MsiEcGitHubLabel->setTextInteractionFlags(Qt::TextInteractionFlag::TextBrowserInteraction);

        gridLayout->addWidget(MsiEcGitHubLabel, 5, 1, 1, 1);

        bugTrackerValueLabel = new QLabel(aboutTab);
        bugTrackerValueLabel->setObjectName("bugTrackerValueLabel");
        bugTrackerValueLabel->setText(QString::fromUtf8("<a href=\"https://github.com/dmitry-s93/MControlCenter/issues\">https://github.com/dmitry-s93/MControlCenter/issues</a>"));
        bugTrackerValueLabel->setOpenExternalLinks(true);
        bugTrackerValueLabel->setTextInteractionFlags(Qt::TextInteractionFlag::TextBrowserInteraction);

        gridLayout->addWidget(bugTrackerValueLabel, 4, 1, 1, 1);

        versionValueLabel = new QLabel(aboutTab);
        versionValueLabel->setObjectName("versionValueLabel");
        versionValueLabel->setText(QString::fromUtf8("-"));

        gridLayout->addWidget(versionValueLabel, 0, 1, 1, 1);

        gitHubValueLabel = new QLabel(aboutTab);
        gitHubValueLabel->setObjectName("gitHubValueLabel");
        gitHubValueLabel->setText(QString::fromUtf8("<a href=\"https://github.com/dmitry-s93/MControlCenter\">https://github.com/dmitry-s93/MControlCenter</a>"));
        gitHubValueLabel->setOpenExternalLinks(true);
        gitHubValueLabel->setTextInteractionFlags(Qt::TextInteractionFlag::TextBrowserInteraction);

        gridLayout->addWidget(gitHubValueLabel, 3, 1, 1, 1);

        ecBuildLabel = new QLabel(aboutTab);
        ecBuildLabel->setObjectName("ecBuildLabel");

        gridLayout->addWidget(ecBuildLabel, 7, 0, 1, 1);

        label_12 = new QLabel(aboutTab);
        label_12->setObjectName("label_12");

        gridLayout->addWidget(label_12, 2, 0, 1, 1);

        MsiEcStatusLabel = new QLabel(aboutTab);
        MsiEcStatusLabel->setObjectName("MsiEcStatusLabel");

        gridLayout->addWidget(MsiEcStatusLabel, 2, 1, 1, 1);

        ecBuildValueLabel = new QLabel(aboutTab);
        ecBuildValueLabel->setObjectName("ecBuildValueLabel");
        ecBuildValueLabel->setText(QString::fromUtf8("-"));

        gridLayout->addWidget(ecBuildValueLabel, 7, 1, 1, 1);


        gridLayout_5->addLayout(gridLayout, 2, 1, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 105, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_5->addItem(verticalSpacer_3, 3, 1, 1, 1);

        QIcon icon3(QIcon::fromTheme(QString::fromUtf8("help-about")));
        tabWidget->addTab(aboutTab, icon3, QString());
        debugTab = new QWidget();
        debugTab->setObjectName("debugTab");
        gridLayout_14 = new QGridLayout(debugTab);
        gridLayout_14->setObjectName("gridLayout_14");
        label_10 = new QLabel(debugTab);
        label_10->setObjectName("label_10");
        label_10->setWordWrap(true);

        gridLayout_14->addWidget(label_10, 0, 0, 1, 1);

        line_5 = new QFrame(debugTab);
        line_5->setObjectName("line_5");
        line_5->setMinimumSize(QSize(0, 10));
        line_5->setBaseSize(QSize(0, 0));
        line_5->setLineWidth(1);
        line_5->setMidLineWidth(0);
        line_5->setFrameShape(QFrame::Shape::HLine);
        line_5->setFrameShadow(QFrame::Shadow::Sunken);

        gridLayout_14->addWidget(line_5, 1, 0, 1, 1);

        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName("gridLayout_6");
        gridLayout_6->setHorizontalSpacing(30);
        gridLayout_6->setVerticalSpacing(5);
        gridLayout_6->setContentsMargins(160, -1, 174, 0);
        ReadValueButton = new QPushButton(debugTab);
        ReadValueButton->setObjectName("ReadValueButton");
        ReadValueButton->setText(QString::fromUtf8("Read Value"));

        gridLayout_6->addWidget(ReadValueButton, 2, 0, 1, 1);

        WriteValueButton = new QPushButton(debugTab);
        WriteValueButton->setObjectName("WriteValueButton");
        WriteValueButton->setText(QString::fromUtf8("Write Value"));

        gridLayout_6->addWidget(WriteValueButton, 2, 1, 1, 1);

        addressEdit = new QLineEdit(debugTab);
        addressEdit->setObjectName("addressEdit");

        gridLayout_6->addWidget(addressEdit, 1, 0, 1, 1);

        ValueSpinBox = new QSpinBox(debugTab);
        ValueSpinBox->setObjectName("ValueSpinBox");
        ValueSpinBox->setMaximum(255);

        gridLayout_6->addWidget(ValueSpinBox, 1, 1, 1, 1);

        label_2 = new QLabel(debugTab);
        label_2->setObjectName("label_2");
        label_2->setText(QString::fromUtf8("Value"));

        gridLayout_6->addWidget(label_2, 0, 1, 1, 1);

        label = new QLabel(debugTab);
        label->setObjectName("label");
        label->setText(QString::fromUtf8("Address"));

        gridLayout_6->addWidget(label, 0, 0, 1, 1);


        gridLayout_14->addLayout(gridLayout_6, 2, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 239, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_14->addItem(verticalSpacer_2, 3, 0, 1, 1);

        QIcon icon4(QIcon::fromTheme(QString::fromUtf8("dialog-warning")));
        tabWidget->addTab(debugTab, icon4, QString());

        gridLayout_3->addWidget(tabWidget, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        QWidget::setTabOrder(scrollArea, fan1Speed1Slider);
        QWidget::setTabOrder(fan1Speed1Slider, fan1Speed2Slider);
        QWidget::setTabOrder(fan1Speed2Slider, fan1Speed3Slider);
        QWidget::setTabOrder(fan1Speed3Slider, fan1Speed4Slider);
        QWidget::setTabOrder(fan1Speed4Slider, fan1Speed5Slider);
        QWidget::setTabOrder(fan1Speed5Slider, fan1Speed6Slider);
        QWidget::setTabOrder(fan1Speed6Slider, fan1Speed7Slider);
        QWidget::setTabOrder(fan1Speed7Slider, customBatteryThresholdRadioButton);
        QWidget::setTabOrder(customBatteryThresholdRadioButton, customBatteryThresholdSpinBox);
        QWidget::setTabOrder(customBatteryThresholdSpinBox, fan2Speed1Slider);
        QWidget::setTabOrder(fan2Speed1Slider, fan2Speed2Slider);
        QWidget::setTabOrder(fan2Speed2Slider, fan2Speed3Slider);
        QWidget::setTabOrder(fan2Speed3Slider, fan2Speed4Slider);
        QWidget::setTabOrder(fan2Speed4Slider, fan2Speed5Slider);
        QWidget::setTabOrder(fan2Speed5Slider, fan2Speed6Slider);
        QWidget::setTabOrder(fan2Speed6Slider, fan2Speed7Slider);
        QWidget::setTabOrder(fan2Speed7Slider, fanSpeedResetButton);
        QWidget::setTabOrder(fanSpeedResetButton, fanSpeedApplyButton);
        QWidget::setTabOrder(fanSpeedApplyButton, bestMobilityRadioButton);
        QWidget::setTabOrder(bestMobilityRadioButton, bestBatteryRadioButton);
        QWidget::setTabOrder(bestBatteryRadioButton, keyboardBacklightModeComboBox);
        QWidget::setTabOrder(keyboardBacklightModeComboBox, keyboardBrightnessSlider);
        QWidget::setTabOrder(keyboardBrightnessSlider, ValueSpinBox);
        QWidget::setTabOrder(ValueSpinBox, addressEdit);
        QWidget::setTabOrder(addressEdit, ReadValueButton);
        QWidget::setTabOrder(ReadValueButton, WriteValueButton);
        QWidget::setTabOrder(WriteValueButton, balancedBatteryRadioButton);
        QWidget::setTabOrder(balancedBatteryRadioButton, customBatteryApplyButton);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);
        fanControlTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setProperty("setWindowOpacity", QVariant(QString()));
        gpuFanLabel->setText(QCoreApplication::translate("MainWindow", "GPU Fan:", nullptr));
        cpuFanLabel->setText(QCoreApplication::translate("MainWindow", "CPU Fan:", nullptr));
        batteryThresholdLabel->setText(QCoreApplication::translate("MainWindow", "Battery threshold:", nullptr));
        cpuTempLabel->setText(QCoreApplication::translate("MainWindow", "CPU temp:", nullptr));
        BatteryChargeLabel->setText(QCoreApplication::translate("MainWindow", "Battery charge:", nullptr));
        gpuTempLabel->setText(QCoreApplication::translate("MainWindow", "GPU temp:", nullptr));
        chargingStatusLabel->setText(QCoreApplication::translate("MainWindow", "Charging status:", nullptr));
        usbPowerShareCheckBox->setText(QCoreApplication::translate("MainWindow", "USB Power", nullptr));
#if QT_CONFIG(tooltip)
        fnSuperSwapCheckBox->setToolTip(QCoreApplication::translate("MainWindow", "Swap FN and Super buttons", nullptr));
#endif // QT_CONFIG(tooltip)
        fnSuperSwapCheckBox->setText(QCoreApplication::translate("MainWindow", "FN \342\207\204 Meta", nullptr));
        webCamCheckBox->setText(QCoreApplication::translate("MainWindow", "WebCam", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "Current fan Mode:", nullptr));
        coolerBoostCheckBox->setText(QCoreApplication::translate("MainWindow", "Cooler Boost", nullptr));
#if QT_CONFIG(tooltip)
        highPerformanceModeRadioButton->setToolTip(QCoreApplication::translate("MainWindow", "This mode unlocks Advanced fan mode", nullptr));
#endif // QT_CONFIG(tooltip)
        highPerformanceModeRadioButton->setText(QCoreApplication::translate("MainWindow", "High Performance", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "Maximum performance at the cost of heat and increased power consumption", nullptr));
        balancedModeRadioButton->setText(QCoreApplication::translate("MainWindow", "Balanced", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "The middle spot between fan noise and power usage", nullptr));
        silentModeRadioButton->setText(QCoreApplication::translate("MainWindow", "Silent", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "Low fan noise and moderate power usage", nullptr));
        superBatteryModeRadioButton->setText(QCoreApplication::translate("MainWindow", "Super Battery", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "Limits performance and turns off fans at lower temperatures", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(overviewTab), QCoreApplication::translate("MainWindow", "Overview", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "If you mainly use your laptop with the charger plugged most of the time, it is recommended to set the charge capacity at a lower percentage (60% or 80%) to prolong your battery lifecycle.", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Charge the battery when under 90%, stop at 100%", nullptr));
        bestMobilityRadioButton->setText(QCoreApplication::translate("MainWindow", "Best for Mobility", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Charge the battery when under 50%, stop at 60%", nullptr));
        customBatteryApplyButton->setText(QCoreApplication::translate("MainWindow", "Apply", nullptr));
        customBatteryThresholdRadioButton->setText(QCoreApplication::translate("MainWindow", "Custom", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Charge the battery when under 70%, stop at 80%", nullptr));
        balancedBatteryRadioButton->setText(QCoreApplication::translate("MainWindow", "Balanced", nullptr));
        bestBatteryRadioButton->setText(QCoreApplication::translate("MainWindow", "Best for battery", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(batteryTab), QCoreApplication::translate("MainWindow", "Battery", nullptr));
        advancedFanControlCheckBox->setText(QCoreApplication::translate("MainWindow", "Enable advanced fan control", nullptr));
        fanControlTabWidget->setTabText(fanControlTabWidget->indexOf(tabWidgetPage1), QCoreApplication::translate("MainWindow", "Fan 1 speed", nullptr));
        fanControlTabWidget->setTabText(fanControlTabWidget->indexOf(tabWidgetPage2), QCoreApplication::translate("MainWindow", "Fan 2 speed", nullptr));
        fanSpeedResetButton->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        fanSpeedApplyButton->setText(QCoreApplication::translate("MainWindow", "Apply", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(fanControlTab), QCoreApplication::translate("MainWindow", "Fan control", nullptr));
        keyboardBacklightLabel->setText(QCoreApplication::translate("MainWindow", "Keyboard Backlight", nullptr));
        keyboardBacklightModeComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Always on", nullptr));
        keyboardBacklightModeComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Auto turn off in 10 sec", nullptr));

        tabWidget->setTabText(tabWidget->indexOf(keyboardTab), QCoreApplication::translate("MainWindow", "Keyboard", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:700;\">MC</span>ontrol<span style=\" font-weight:700;\">C</span>enter (MCC) is an application that allows you to change the settings of MSI laptops running Linux.</p><p>MCC acts as a graphical interface for the <span style=\" font-weight:700;\">MSI-EC </span>driver that already exist in the Linux kernel, if your device is not supported (grey buttons/limited in-app functionality), please visit the msi-ec github page to get help.</p></body></html>", nullptr));
        QtVersionValue->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        bugTrackerLabel->setText(QCoreApplication::translate("MainWindow", "MCC Bug Tracker:", nullptr));
        ecVersionLabel->setText(QCoreApplication::translate("MainWindow", "EC Version:", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "Qt version:", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "MSI-EC GitHub:", nullptr));
        gitHubLabel->setText(QCoreApplication::translate("MainWindow", "MCC GitHub:", nullptr));
        versionLabel->setText(QCoreApplication::translate("MainWindow", "Version:", nullptr));
        ecBuildLabel->setText(QCoreApplication::translate("MainWindow", "EC Build:", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "MSI-EC Status:", nullptr));
        MsiEcStatusLabel->setText(QCoreApplication::translate("MainWindow", "Unknown", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(aboutTab), QCoreApplication::translate("MainWindow", "About", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-weight:700;\">Warning</span>: Writing the wrong values to the wrong addresses <span style=\" font-weight:700;\">WILL BRICK YOUR DEVICE!</span></p><p align=\"center\"><span style=\" font-weight:700;\">Never</span> write to EC memory without knowing how to do a proper <span style=\" font-weight:700;\">BIOS/EC</span> reset, keep in mind that a reset <span style=\" font-weight:700;\">might not</span> fix the device if the device got bricked/broken. </p></body></html>", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(debugTab), QCoreApplication::translate("MainWindow", "Debug", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
