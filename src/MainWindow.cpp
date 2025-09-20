#include "MainWindow.h"
#include "VisualSimWidget.h"
#include "ScienceSimWidget.h"
#include "KnowledgeBase.h"
#include <QApplication>
#include <QMenuBar>
#include <QAction>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), tardigrade(new Tardigrade()), tabWidget(nullptr),
      visualSimWidget(nullptr), scienceSimWidget(nullptr), knowledgeBase(nullptr)
{
    setWindowTitle("🐻‍❄️ Simulador de Tardígrados - Proyecto Educativo");
    setMinimumSize(1000, 700);
    
    setupUI();
    connectSignals();
    updateStatusBar();
}

MainWindow::~MainWindow()
{
    delete tardigrade;
}

void MainWindow::setupUI()
{
    // Create central tab widget
    tabWidget = new QTabWidget(this);
    setCentralWidget(tabWidget);
    
    // Create widgets for each tab
    visualSimWidget = new VisualSimWidget(tardigrade, this);
    scienceSimWidget = new ScienceSimWidget(tardigrade, this);
    knowledgeBase = new KnowledgeBase(this);
    
    // Add tabs with terminal style names
    tabWidget->addTab(visualSimWidget, "[VISUAL_SIM]");
    tabWidget->addTab(scienceSimWidget, "[SCIENCE_SIM]");
    tabWidget->addTab(knowledgeBase, "[KNOWLEDGE_DB]");
    
    // Create status bar with terminal style
    statusBar()->setStyleSheet(
        "QStatusBar { "
        "background-color: #000000; "
        "color: #00ff00; "
        "border-top: 1px solid #00ff00; "
        "font-family: 'Courier New', 'Monaco', 'Consolas', monospace; "
        "font-weight: bold; "
        "}"
    );
    
    survivalLabel = new QLabel("[SUPERVIVENCIA: 100%]");
    stateLabel = new QLabel("[ESTADO: ACTIVO]");
    survivalLabel->setStyleSheet("color: #00ff00; font-family: 'Courier New', monospace;");
    stateLabel->setStyleSheet("color: #00ff00; font-family: 'Courier New', monospace;");
    
    statusBar()->addWidget(survivalLabel);
    statusBar()->addPermanentWidget(stateLabel);
    
    // Create menu bar with terminal style
    QMenuBar *menuBar = this->menuBar();
    menuBar->setStyleSheet(
        "QMenuBar { "
        "background-color: #000000; "
        "color: #00ff00; "
        "border-bottom: 1px solid #00ff00; "
        "font-family: 'Courier New', monospace; "
        "}"
        "QMenuBar::item { "
        "background-color: transparent; "
        "padding: 4px 8px; "
        "}"
        "QMenuBar::item:selected { "
        "background-color: #003300; "
        "color: #00ff41; "
        "}"
        "QMenu { "
        "background-color: #000000; "
        "color: #00ff00; "
        "border: 1px solid #00ff00; "
        "font-family: 'Courier New', monospace; "
        "}"
        "QMenu::item:selected { "
        "background-color: #003300; "
        "}"
    );
    
    QMenu *helpMenu = menuBar->addMenu("&[AYUDA]");
    QAction *aboutAction = helpMenu->addAction("&[ACERCA_DE]");
    
    connect(aboutAction, &QAction::triggered, [this]() {
        QMessageBox msgBox;
        msgBox.setWindowTitle(">>> SISTEMA TARDIGRADE_SIM v1.0 <<<");
        msgBox.setStyleSheet(
            "QMessageBox { "
            "background-color: #000000; "
            "color: #00ff00; "
            "font-family: 'Courier New', monospace; "
            "}"
            "QMessageBox QLabel { "
            "color: #00ff00; "
            "font-family: 'Courier New', monospace; "
            "}"
            "QPushButton { "
            "background-color: #001100; "
            "color: #00ff00; "
            "border: 1px solid #00ff00; "
            "padding: 4px 8px; "
            "font-family: 'Courier New', monospace; "
            "}"
            "QPushButton:hover { "
            "background-color: #003300; "
            "}"
        );
        msgBox.setText(
            ">>> TARDIGRADE SURVIVAL SIMULATOR <<<\n\n"
            "[SISTEMA EDUCATIVO INTERACTIVO]\n"
            "[SIMULACION BIOLOGICA AVANZADA]\n\n"
            "VERSION: 1.0.0\n"
            "LENGUAJE: C++/Qt5\n"
            "PROTOCOLO: BIO-ADAPT\n\n"
            ">>> SISTEMA OPERATIVO >>>"
        );
        msgBox.exec();
    });
    
    // Set retro terminal style
    setStyleSheet(
        "QMainWindow { "
        "background-color: #000000; "
        "color: #00ff00; "
        "font-family: 'Courier New', 'Monaco', 'Consolas', monospace; "
        "}"
        "QTabWidget::pane { "
        "border: 2px solid #00ff00; "
        "background-color: #000000; "
        "color: #00ff00; "
        "}"
        "QTabBar::tab { "
        "background-color: #001100; "
        "color: #00ff00; "
        "border: 1px solid #00ff00; "
        "padding: 8px 16px; "
        "margin: 1px; "
        "font-family: 'Courier New', 'Monaco', 'Consolas', monospace; "
        "font-weight: bold; "
        "}"
        "QTabBar::tab:selected { "
        "background-color: #003300; "
        "color: #00ff41; "
        "border: 2px solid #00ff41; "
        "}"
        "QTabBar::tab:hover { "
        "background-color: #002200; "
        "color: #00ff88; "
        "}"
    );
}

void MainWindow::connectSignals()
{
    // Connect science simulation changes to update visual simulation
    connect(scienceSimWidget, &ScienceSimWidget::parametersChanged,
            this, &MainWindow::onParametersChanged);
}

void MainWindow::onParametersChanged()
{
    // Update visual simulation when parameters change
    visualSimWidget->updateVisualization();
    updateStatusBar();
}

void MainWindow::updateStatusBar()
{
    int survival = tardigrade->calcularSupervivencia();
    QString survivalText = QString("[SUPERVIVENCIA: %1%]").arg(survival);
    QString stateText = QString("[ESTADO: %1]").arg(QString::fromStdString(tardigrade->estadoVisual()).toUpper());
    
    survivalLabel->setText(survivalText);
    stateLabel->setText(stateText);
    
    // Update status bar colors based on survival - terminal style
    QString color;
    if (survival >= 70) {
        color = "#00ff41";  // Bright green
    } else if (survival >= 30) {
        color = "#ffff00";  // Bright yellow
    } else {
        color = "#ff4444";  // Bright red
    }
    
    survivalLabel->setStyleSheet(QString("QLabel { color: %1; font-weight: bold; font-family: 'Courier New', monospace; }").arg(color));
    stateLabel->setStyleSheet(QString("QLabel { color: %1; font-weight: bold; font-family: 'Courier New', monospace; }").arg(color));
}