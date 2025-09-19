#include "ScienceSimWidget.h"
#include <QProgressBar>

ScienceSimWidget::ScienceSimWidget(Tardigrade *tardigrade, QWidget *parent)
    : QWidget(parent), tardigrade(tardigrade)
{
    setupUI();
    updateAllDisplays();
}

void ScienceSimWidget::setupUI()
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    
    // Left side - Parameter controls
    QVBoxLayout *leftLayout = new QVBoxLayout();
    setupParameterControls();
    
    // Parameter controls group with terminal styling
    QGroupBox *paramGroup = new QGroupBox("[PARAMETROS_AMBIENTALES]", this);
    paramGroup->setStyleSheet(
        "QGroupBox { "
        "color: #00ff00; "
        "border: 2px solid #00ff00; "
        "font-family: 'Courier New', monospace; "
        "font-weight: bold; "
        "margin: 5px; "
        "padding-top: 15px; "
        "background-color: #000000; "
        "}"
        "QGroupBox::title { "
        "subcontrol-origin: margin; "
        "left: 10px; "
        "padding: 0 5px 0 5px; "
        "color: #00ff41; "
        "}"
    );
    QGridLayout *paramLayout = new QGridLayout(paramGroup);
    
    // Temperature with terminal labels
    QLabel *tempLabel = new QLabel(">>> TEMPERATURA_(C):");
    tempLabel->setStyleSheet("color: #00ff00; font-family: 'Courier New', monospace; font-weight: bold;");
    paramLayout->addWidget(tempLabel, 0, 0);
    paramLayout->addWidget(temperaturaSlider, 0, 1);
    paramLayout->addWidget(temperaturaSpinBox, 0, 2);
    paramLayout->addWidget(temperaturaLabel, 0, 3);
    
    // Radiation
    QLabel *radLabel = new QLabel(">>> RADIACION_(GY):");
    radLabel->setStyleSheet("color: #00ff00; font-family: 'Courier New', monospace; font-weight: bold;");
    paramLayout->addWidget(radLabel, 1, 0);
    paramLayout->addWidget(radiacionSlider, 1, 1);
    paramLayout->addWidget(radiacionSpinBox, 1, 2);
    paramLayout->addWidget(radiacionLabel, 1, 3);
    
    // Pressure
    QLabel *presLabel = new QLabel(">>> PRESION_(ATM):");
    presLabel->setStyleSheet("color: #00ff00; font-family: 'Courier New', monospace; font-weight: bold;");
    paramLayout->addWidget(presLabel, 2, 0);
    paramLayout->addWidget(presionSlider, 2, 1);
    paramLayout->addWidget(presionSpinBox, 2, 2);
    paramLayout->addWidget(presionLabel, 2, 3);
    
    // Hydration
    QLabel *hidLabel = new QLabel(">>> HIDRATACION_(%):");
    hidLabel->setStyleSheet("color: #00ff00; font-family: 'Courier New', monospace; font-weight: bold;");
    paramLayout->addWidget(hidLabel, 3, 0);
    paramLayout->addWidget(hidratacionSlider, 3, 1);
    paramLayout->addWidget(hidratacionSpinBox, 3, 2);
    paramLayout->addWidget(hidratacionLabel, 3, 3);
    
    leftLayout->addWidget(paramGroup);
    
    // Preset buttons with terminal styling
    setupPresets();
    QGroupBox *presetGroup = new QGroupBox("[AMBIENTES_PREDEFINIDOS]", this);
    presetGroup->setStyleSheet(
        "QGroupBox { "
        "color: #00ff00; "
        "border: 2px solid #00ff00; "
        "font-family: 'Courier New', monospace; "
        "font-weight: bold; "
        "margin: 5px; "
        "padding-top: 15px; "
        "background-color: #000000; "
        "}"
        "QGroupBox::title { "
        "subcontrol-origin: margin; "
        "left: 10px; "
        "padding: 0 5px 0 5px; "
        "color: #00ff41; "
        "}"
    );
    QGridLayout *presetLayout = new QGridLayout(presetGroup);
    
    presetLayout->addWidget(waterBtn, 0, 0);
    presetLayout->addWidget(iceBtn, 0, 1);
    presetLayout->addWidget(radiationBtn, 1, 0);
    presetLayout->addWidget(spaceBtn, 1, 1);
    presetLayout->addWidget(resetBtn, 2, 0, 1, 2);
    
    leftLayout->addWidget(presetGroup);
    
    // Survival display with terminal styling
    QGroupBox *survivalGroup = new QGroupBox("[ESTADO_DE_SUPERVIVENCIA]", this);
    survivalGroup->setStyleSheet(
        "QGroupBox { "
        "color: #00ff00; "
        "border: 2px solid #00ff00; "
        "font-family: 'Courier New', monospace; "
        "font-weight: bold; "
        "margin: 5px; "
        "padding-top: 15px; "
        "background-color: #000000; "
        "}"
        "QGroupBox::title { "
        "subcontrol-origin: margin; "
        "left: 10px; "
        "padding: 0 5px 0 5px; "
        "color: #00ff41; "
        "}"
    );
    QVBoxLayout *survivalLayout = new QVBoxLayout(survivalGroup);
    
    survivalValueLabel = new QLabel("[100%]");
    survivalValueLabel->setAlignment(Qt::AlignCenter);
    survivalValueLabel->setStyleSheet("QLabel { font-size: 24px; font-weight: bold; color: #00ff41; font-family: 'Courier New', monospace; }");
    
    survivalBarLabel = new QLabel();
    survivalBarLabel->setMinimumHeight(30);
    survivalBarLabel->setStyleSheet("QLabel { background-color: #00ff41; border: 2px solid #00ff00; }");
    
    stateLabel = new QLabel("[ESTADO: ACTIVO]");
    stateLabel->setAlignment(Qt::AlignCenter);
    stateLabel->setStyleSheet("QLabel { font-size: 16px; font-weight: bold; color: #00ff00; font-family: 'Courier New', monospace; }");
    
    survivalLayout->addWidget(survivalValueLabel);
    survivalLayout->addWidget(survivalBarLabel);
    survivalLayout->addWidget(stateLabel);
    
    leftLayout->addWidget(survivalGroup);
    leftLayout->addStretch();
    
    // Right side - Charts
    chartsWidget = new ChartsWidget(tardigrade, this);
    
    mainLayout->addLayout(leftLayout, 1);
    mainLayout->addWidget(chartsWidget, 2);
}

void ScienceSimWidget::setupParameterControls()
{
    // Temperature controls with terminal styling
    temperaturaSlider = new QSlider(Qt::Horizontal);
    temperaturaSlider->setRange(-200, 150);
    temperaturaSlider->setValue(20);
    temperaturaSlider->setStyleSheet(
        "QSlider::groove:horizontal { "
        "border: 1px solid #00ff00; "
        "height: 6px; "
        "background: #000000; "
        "}"
        "QSlider::handle:horizontal { "
        "background: #00ff41; "
        "border: 2px solid #00ff00; "
        "width: 18px; "
        "margin: -6px 0; "
        "border-radius: 9px; "
        "}"
    );
    
    temperaturaSpinBox = new QDoubleSpinBox();
    temperaturaSpinBox->setRange(-200.0, 150.0);
    temperaturaSpinBox->setValue(20.0);
    temperaturaSpinBox->setSuffix(" C");
    temperaturaSpinBox->setStyleSheet(
        "QDoubleSpinBox { "
        "background-color: #001100; "
        "color: #00ff00; "
        "border: 1px solid #00ff00; "
        "font-family: 'Courier New', monospace; "
        "font-weight: bold; "
        "}"
    );
    
    temperaturaLabel = new QLabel("[OPTIMA]");
    temperaturaLabel->setStyleSheet("color: #00ff41; font-family: 'Courier New', monospace; font-weight: bold;");
    
    // Radiation controls with terminal styling
    radiacionSlider = new QSlider(Qt::Horizontal);
    radiacionSlider->setRange(0, 10000);
    radiacionSlider->setValue(0);
    radiacionSlider->setStyleSheet(
        "QSlider::groove:horizontal { "
        "border: 1px solid #00ff00; "
        "height: 6px; "
        "background: #000000; "
        "}"
        "QSlider::handle:horizontal { "
        "background: #00ff41; "
        "border: 2px solid #00ff00; "
        "width: 18px; "
        "margin: -6px 0; "
        "border-radius: 9px; "
        "}"
    );
    
    radiacionSpinBox = new QSpinBox();
    radiacionSpinBox->setRange(0, 10000);
    radiacionSpinBox->setValue(0);
    radiacionSpinBox->setSuffix(" Gy");
    radiacionSpinBox->setStyleSheet(
        "QSpinBox { "
        "background-color: #001100; "
        "color: #00ff00; "
        "border: 1px solid #00ff00; "
        "font-family: 'Courier New', monospace; "
        "font-weight: bold; "
        "}"
    );
    
    radiacionLabel = new QLabel("[SEGURA]");
    radiacionLabel->setStyleSheet("color: #00ff41; font-family: 'Courier New', monospace; font-weight: bold;");
    
    // Pressure controls (0-1,000 atm)
    presionSlider = new QSlider(Qt::Horizontal);
    presionSlider->setRange(0, 1000);
    presionSlider->setValue(100);  // 1.0 atm * 100 for integer slider
    
    presionSpinBox = new QDoubleSpinBox();
    presionSpinBox->setRange(0.0, 1000.0);
    presionSpinBox->setValue(1.0);
    presionSpinBox->setDecimals(1);
    presionSpinBox->setSuffix(" atm");
    
    presionLabel = new QLabel("Normal");
    
    // Hydration controls (0-100%)
    hidratacionSlider = new QSlider(Qt::Horizontal);
    hidratacionSlider->setRange(0, 100);
    hidratacionSlider->setValue(80);
    
    hidratacionSpinBox = new QSpinBox();
    hidratacionSpinBox->setRange(0, 100);
    hidratacionSpinBox->setValue(80);
    hidratacionSpinBox->setSuffix(" %");
    
    hidratacionLabel = new QLabel("Alta");
    
    // Connect signals
    connect(temperaturaSlider, &QSlider::valueChanged, this, &ScienceSimWidget::onTemperaturaChanged);
    connect(temperaturaSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &ScienceSimWidget::onTemperaturaChanged);
    
    connect(radiacionSlider, &QSlider::valueChanged, this, &ScienceSimWidget::onRadiacionChanged);
    connect(radiacionSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &ScienceSimWidget::onRadiacionChanged);
    
    connect(presionSlider, &QSlider::valueChanged, this, &ScienceSimWidget::onPresionChanged);
    connect(presionSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &ScienceSimWidget::onPresionChanged);
    
    connect(hidratacionSlider, &QSlider::valueChanged, this, &ScienceSimWidget::onHidratacionChanged);
    connect(hidratacionSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &ScienceSimWidget::onHidratacionChanged);
}

void ScienceSimWidget::setupPresets()
{
    waterBtn = new QPushButton("[AGUA]");
    iceBtn = new QPushButton("[CONGELACION]");
    radiationBtn = new QPushButton("[RADIACION]");
    spaceBtn = new QPushButton("[ESPACIO]");
    resetBtn = new QPushButton("[RESTABLECER]");
    
    connect(waterBtn, &QPushButton::clicked, this, &ScienceSimWidget::presetWater);
    connect(iceBtn, &QPushButton::clicked, this, &ScienceSimWidget::presetIce);
    connect(radiationBtn, &QPushButton::clicked, this, &ScienceSimWidget::presetRadiation);
    connect(spaceBtn, &QPushButton::clicked, this, &ScienceSimWidget::presetSpace);
    connect(resetBtn, &QPushButton::clicked, this, &ScienceSimWidget::resetToDefaults);
    
    // Style buttons with terminal theme
    QString buttonStyle = 
        "QPushButton { "
        "background-color: #001100; "
        "color: #00ff00; "
        "border: 2px solid #00ff00; "
        "padding: 8px; "
        "font-weight: bold; "
        "font-family: 'Courier New', monospace; "
        "} "
        "QPushButton:hover { "
        "background-color: #003300; "
        "color: #00ff41; "
        "} "
        "QPushButton:pressed { "
        "background-color: #005500; "
        "}";
    waterBtn->setStyleSheet(buttonStyle);
    iceBtn->setStyleSheet(buttonStyle);
    radiationBtn->setStyleSheet(buttonStyle);
    spaceBtn->setStyleSheet(buttonStyle);
    resetBtn->setStyleSheet(buttonStyle);
}

void ScienceSimWidget::onTemperaturaChanged()
{
    double temp = temperaturaSpinBox->value();
    temperaturaSlider->setValue(static_cast<int>(temp));
    tardigrade->setTemperatura(temp);
    
    // Update label with terminal styling
    if (temp >= -20 && temp <= 40) {
        temperaturaLabel->setText("[OPTIMA]");
        temperaturaLabel->setStyleSheet("color: #00ff41; font-family: 'Courier New', monospace; font-weight: bold;");
    } else if (temp >= -273 && temp <= 150) {
        temperaturaLabel->setText("[EXTREMA]");
        temperaturaLabel->setStyleSheet("color: #ffff00; font-family: 'Courier New', monospace; font-weight: bold;");
    } else {
        temperaturaLabel->setText("[LETAL]");
        temperaturaLabel->setStyleSheet("color: #ff4444; font-family: 'Courier New', monospace; font-weight: bold;");
    }
    
    updateSurvivalDisplay();
    chartsWidget->updateCharts();
    emit parametersChanged();
}

void ScienceSimWidget::onRadiacionChanged()
{
    int rad = radiacionSpinBox->value();
    radiacionSlider->setValue(rad);
    tardigrade->setRadiacion(rad);
    
    // Update label
    if (rad <= 100) {
        radiacionLabel->setText("Segura");
        radiacionLabel->setStyleSheet("color: #27ae60;");
    } else if (rad <= 5000) {
        radiacionLabel->setText("Peligrosa");
        radiacionLabel->setStyleSheet("color: #f39c12;");
    } else {
        radiacionLabel->setText("Letal");
        radiacionLabel->setStyleSheet("color: #e74c3c;");
    }
    
    updateSurvivalDisplay();
    chartsWidget->updateCharts();
    emit parametersChanged();
}

void ScienceSimWidget::onPresionChanged()
{
    double pres = presionSpinBox->value();
    presionSlider->setValue(static_cast<int>(pres * 100));
    tardigrade->setPresion(pres);
    
    // Update label
    if (pres >= 0.5 && pres <= 2.0) {
        presionLabel->setText("Normal");
        presionLabel->setStyleSheet("color: #27ae60;");
    } else if (pres >= 0.0 && pres <= 600.0) {
        presionLabel->setText("Extrema");
        presionLabel->setStyleSheet("color: #f39c12;");
    } else {
        presionLabel->setText("Letal");
        presionLabel->setStyleSheet("color: #e74c3c;");
    }
    
    updateSurvivalDisplay();
    chartsWidget->updateCharts();
    emit parametersChanged();
}

void ScienceSimWidget::onHidratacionChanged()
{
    int hid = hidratacionSpinBox->value();
    hidratacionSlider->setValue(hid);
    tardigrade->setHidratacion(hid);
    
    // Update label
    if (hid >= 60) {
        hidratacionLabel->setText("Alta");
        hidratacionLabel->setStyleSheet("color: #27ae60;");
    } else if (hid >= 10) {
        hidratacionLabel->setText("Baja");
        hidratacionLabel->setStyleSheet("color: #f39c12;");
    } else {
        hidratacionLabel->setText("Crítica");
        hidratacionLabel->setStyleSheet("color: #e74c3c;");
    }
    
    updateSurvivalDisplay();
    chartsWidget->updateCharts();
    emit parametersChanged();
}

void ScienceSimWidget::updateAllDisplays()
{
    temperaturaSpinBox->setValue(tardigrade->getTemperatura());
    radiacionSpinBox->setValue(static_cast<int>(tardigrade->getRadiacion()));
    presionSpinBox->setValue(tardigrade->getPresion());
    hidratacionSpinBox->setValue(static_cast<int>(tardigrade->getHidratacion()));
    
    onTemperaturaChanged();
    onRadiacionChanged();
    onPresionChanged();
    onHidratacionChanged();
}

void ScienceSimWidget::updateSurvivalDisplay()
{
    int survival = tardigrade->calcularSupervivencia();
    
    survivalValueLabel->setText(QString("[%1%]").arg(survival));
    stateLabel->setText(QString("[ESTADO: %1]").arg(QString::fromStdString(tardigrade->estadoVisual()).toUpper()));
    
    // Update colors with terminal theme
    QString color;
    if (survival >= 70) {
        color = "#00ff41";
    } else if (survival >= 30) {
        color = "#ffff00";
    } else {
        color = "#ff4444";
    }
    
    survivalValueLabel->setStyleSheet(QString("QLabel { font-size: 24px; font-weight: bold; color: %1; font-family: 'Courier New', monospace; }").arg(color));
    stateLabel->setStyleSheet(QString("QLabel { font-size: 16px; font-weight: bold; color: %1; font-family: 'Courier New', monospace; }").arg(color));
    
    // Update survival bar with terminal gradient
    QString barStyle = QString("QLabel { background: qlineargradient(x1:0, y1:0, x2:%1, y2:0, stop:0 %2, stop:1 #000000); border: 2px solid %2; }")
                      .arg(survival / 100.0).arg(color);
    survivalBarLabel->setStyleSheet(barStyle);
}

void ScienceSimWidget::resetToDefaults()
{
    temperaturaSpinBox->setValue(20.0);
    radiacionSpinBox->setValue(0);
    presionSpinBox->setValue(1.0);
    hidratacionSpinBox->setValue(80);
}

void ScienceSimWidget::presetWater()
{
    temperaturaSpinBox->setValue(20.0);
    radiacionSpinBox->setValue(0);
    presionSpinBox->setValue(1.0);
    hidratacionSpinBox->setValue(90);
}

void ScienceSimWidget::presetIce()
{
    temperaturaSpinBox->setValue(-20.0);
    radiacionSpinBox->setValue(0);
    presionSpinBox->setValue(1.0);
    hidratacionSpinBox->setValue(10);
}

void ScienceSimWidget::presetRadiation()
{
    temperaturaSpinBox->setValue(40.0);
    radiacionSpinBox->setValue(1000);
    presionSpinBox->setValue(1.0);
    hidratacionSpinBox->setValue(50);
}

void ScienceSimWidget::presetSpace()
{
    temperaturaSpinBox->setValue(-270.0);
    radiacionSpinBox->setValue(5000);
    presionSpinBox->setValue(0.0);
    hidratacionSpinBox->setValue(5);
}