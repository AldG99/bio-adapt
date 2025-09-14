#include "VisualSimWidget.h"
#include <QGraphicsEllipseItem>
#include <QBrush>
#include <QPen>
#include <QGroupBox>

VisualSimWidget::VisualSimWidget(Tardigrade *tardigrade, QWidget *parent)
    : QWidget(parent), tardigrade(tardigrade), currentEnvironment(WATER),
      animationFrame(0), animationDirection(true)
{
    setupUI();
    setupScene();
    
    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &VisualSimWidget::animateTimer);
    animationTimer->start(100);  // 100ms animation frame
}

void VisualSimWidget::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Environment selection with terminal styling
    QGroupBox *environmentGroup = new QGroupBox("[AMBIENTE_DE_SIMULACION]", this);
    environmentGroup->setStyleSheet(
        "QGroupBox { "
        "color: #00ff00; "
        "border: 1px solid #00ff00; "
        "font-family: 'Courier New', monospace; "
        "font-weight: bold; "
        "margin: 5px; "
        "padding-top: 10px; "
        "background-color: #000000; "
        "}"
        "QGroupBox::title { "
        "subcontrol-origin: margin; "
        "left: 10px; "
        "padding: 0 5px 0 5px; "
        "color: #00ff41; "
        "}"
    );
    QHBoxLayout *envLayout = new QHBoxLayout(environmentGroup);
    
    environmentLabel = new QLabel(">>> AMBIENTE_ACTUAL:");
    environmentLabel->setStyleSheet("color: #00ff00; font-family: 'Courier New', monospace; font-weight: bold;");
    environmentCombo = new QComboBox();
    environmentCombo->addItems({"[AGUA]", "[CONGELACION]", "[RADIACION]", "[VACIO_ESPACIAL]"});
    environmentCombo->setStyleSheet(
        "QComboBox { "
        "background-color: #001100; "
        "color: #00ff00; "
        "border: 1px solid #00ff00; "
        "padding: 4px; "
        "font-family: 'Courier New', monospace; "
        "font-weight: bold; "
        "}"
        "QComboBox::drop-down { "
        "border: none; "
        "color: #00ff00; "
        "background-color: #003300; "
        "}"
        "QComboBox::down-arrow { "
        "color: #00ff00; "
        "}"
        "QComboBox QAbstractItemView { "
        "background-color: #000000; "
        "color: #00ff00; "
        "border: 1px solid #00ff00; "
        "font-family: 'Courier New', monospace; "
        "selection-background-color: #003300; "
        "}"
    );
    
    envLayout->addWidget(environmentLabel);
    envLayout->addWidget(environmentCombo);
    envLayout->addStretch();
    
    // Graphics view with terminal styling
    graphicsView = new QGraphicsView(this);
    graphicsView->setMinimumSize(600, 400);
    graphicsView->setStyleSheet(
        "QGraphicsView { "
        "border: 2px solid #00ff00; "
        "background-color: #000000; "
        "}"
    );
    
    // Status label with terminal styling
    statusLabel = new QLabel(">>> ESTADO_TARDIGRADO: [ACTIVO] <<<", this);
    statusLabel->setStyleSheet(
        "QLabel { "
        "font-size: 14px; "
        "font-weight: bold; "
        "padding: 10px; "
        "color: #00ff00; "
        "font-family: 'Courier New', monospace; "
        "background-color: #000000; "
        "border: 1px solid #00ff00; "
        "}"
    );
    statusLabel->setAlignment(Qt::AlignCenter);
    
    mainLayout->addWidget(environmentGroup);
    mainLayout->addWidget(graphicsView);
    mainLayout->addWidget(statusLabel);
    
    connect(environmentCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &VisualSimWidget::onEnvironmentChanged);
}

void VisualSimWidget::setupScene()
{
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 600, 400);
    graphicsView->setScene(scene);
    
    // Create background with solid color (since we don't have image resources yet)
    updateBackground();
    
    // Create tardigrade representation as a simple ellipse for now
    updateTardigradeSprite();
}

void VisualSimWidget::updateBackground()
{
    // Remove existing background
    if (backgroundItem) {
        scene->removeItem(backgroundItem);
        delete backgroundItem;
    }
    
    // Create terminal-style background based on environment
    QBrush backgroundBrush;
    switch (currentEnvironment) {
        case WATER:
            backgroundBrush = QBrush(QColor(0, 50, 100));     // Dark blue terminal
            break;
        case ICE:
            backgroundBrush = QBrush(QColor(0, 80, 120));     // Cyan terminal
            break;
        case RADIATION:
            backgroundBrush = QBrush(QColor(100, 50, 0));     // Orange terminal
            break;
        case SPACE:
            backgroundBrush = QBrush(QColor(0, 0, 0));        // Pure black for space
            break;
    }
    
    QGraphicsRectItem *background = scene->addRect(0, 0, 600, 400, QPen(Qt::NoPen), backgroundBrush);
    backgroundItem = background;
}

void VisualSimWidget::updateTardigradeSprite()
{
    // Remove existing tardigrade
    if (tardigradeItem) {
        scene->removeItem(tardigradeItem);
        delete tardigradeItem;
    }
    
    // Create terminal-style tardigrade representation based on current state
    TardigradeState state = tardigrade->getEstado();
    QBrush tardiBrush;
    QPen tardiBorder;
    QSizeF size;
    
    switch (state) {
        case TardigradeState::ACTIVE:
            tardiBrush = QBrush(QColor(0, 255, 65));   // Bright terminal green
            tardiBorder = QPen(QColor(0, 255, 0), 2);  // Green border
            size = QSizeF(40, 20);
            break;
        case TardigradeState::TUN:
            tardiBrush = QBrush(QColor(255, 255, 0));  // Bright yellow
            tardiBorder = QPen(QColor(255, 200, 0), 2); // Yellow border
            size = QSizeF(25, 25);  // More compact in tun state
            break;
        case TardigradeState::REVIVING:
            tardiBrush = QBrush(QColor(255, 165, 0));  // Orange
            tardiBorder = QPen(QColor(255, 100, 0), 2); // Orange border
            size = QSizeF(35, 18);
            break;
        case TardigradeState::DEAD:
            tardiBrush = QBrush(QColor(255, 68, 68));  // Bright red
            tardiBorder = QPen(QColor(200, 0, 0), 2);  // Red border
            size = QSizeF(30, 15);
            break;
    }
    
    // Create ellipse to represent tardigrade with terminal styling
    QGraphicsEllipseItem *tardigradeEllipse = scene->addEllipse(
        300 - size.width()/2, 200 - size.height()/2, size.width(), size.height(),
        tardiBorder, tardiBrush);
    
    tardigradeItem = tardigradeEllipse;
}

void VisualSimWidget::onEnvironmentChanged(int index)
{
    currentEnvironment = static_cast<Environment>(index);
    updateBackground();
    
    // Update tardigrade parameters based on environment
    switch (currentEnvironment) {
        case WATER:
            tardigrade->setTemperatura(20.0);
            tardigrade->setRadiacion(0.0);
            tardigrade->setPresion(1.0);
            tardigrade->setHidratacion(90.0);
            break;
        case ICE:
            tardigrade->setTemperatura(-20.0);
            tardigrade->setRadiacion(0.0);
            tardigrade->setPresion(1.0);
            tardigrade->setHidratacion(10.0);
            break;
        case RADIATION:
            tardigrade->setTemperatura(40.0);
            tardigrade->setRadiacion(1000.0);
            tardigrade->setPresion(1.0);
            tardigrade->setHidratacion(50.0);
            break;
        case SPACE:
            tardigrade->setTemperatura(-270.0);
            tardigrade->setRadiacion(5000.0);
            tardigrade->setPresion(0.0);
            tardigrade->setHidratacion(5.0);
            break;
    }
    
    updateVisualization();
}

void VisualSimWidget::updateVisualization()
{
    updateTardigradeSprite();
    
    // Update status label with terminal style
    int survival = tardigrade->calcularSupervivencia();
    QString statusText = QString(">>> ESTADO_TARDIGRADO: [%1] SUPERVIVENCIA: [%2%] <<<")
                        .arg(QString::fromStdString(tardigrade->estadoVisual()).toUpper())
                        .arg(survival);
    statusLabel->setText(statusText);
    
    // Update status label color - terminal style
    QString color;
    if (survival >= 70) {
        color = "#00ff41";  // Bright green
    } else if (survival >= 30) {
        color = "#ffff00";  // Bright yellow
    } else {
        color = "#ff4444";  // Bright red
    }
    
    statusLabel->setStyleSheet(QString(
        "QLabel { "
        "font-size: 14px; "
        "font-weight: bold; "
        "padding: 10px; "
        "color: %1; "
        "font-family: 'Courier New', monospace; "
        "background-color: #000000; "
        "border: 1px solid %1; "
        "}"
    ).arg(color));
}

void VisualSimWidget::animateTimer()
{
    if (!tardigradeItem) return;
    
    TardigradeState state = tardigrade->getEstado();
    
    // Only animate if tardigrade is active
    if (state == TardigradeState::ACTIVE) {
        // Simple floating animation
        if (animationDirection) {
            animationFrame++;
            if (animationFrame >= 10) animationDirection = false;
        } else {
            animationFrame--;
            if (animationFrame <= -10) animationDirection = true;
        }
        
        tardigradeItem->setPos(tardigradeItem->pos().x(), tardigradeItem->pos().y() + (animationDirection ? 0.5 : -0.5));
    }
}