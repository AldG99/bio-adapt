#include "ChartsWidget.h"
#include <cmath>

ChartsWidget::ChartsWidget(Tardigrade *tardigrade, QWidget *parent)
    : QWidget(parent), tardigrade(tardigrade)
{
    setupUI();
    createSurvivalFactorsChart();
    updateCharts();
}

void ChartsWidget::setupUI()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    
    chartTitle = new QLabel(">>> [FACTORES_DE_SUPERVIVENCIA] <<<", this);
    chartTitle->setAlignment(Qt::AlignCenter);
    chartTitle->setStyleSheet(
        "QLabel { "
        "font-size: 16px; "
        "font-weight: bold; "
        "color: #00ff41; "
        "font-family: 'Courier New', monospace; "
        "background-color: #000000; "
        "border: 1px solid #00ff00; "
        "padding: 5px; "
        "}"
    );
    
    // Create chart with terminal theme
    factorsChart = new QChart();
    factorsChart->setTitle(">>> IMPACTO_CONDICIONES_AMBIENTALES <<<");
    factorsChart->setTitleFont(QFont("Courier New", 12, QFont::Bold));
    factorsChart->setTitleBrush(QBrush(QColor(0, 255, 65)));
    factorsChart->setAnimationOptions(QChart::SeriesAnimations);
    factorsChart->setBackgroundBrush(QBrush(QColor(0, 0, 0)));
    factorsChart->setPlotAreaBackgroundBrush(QBrush(QColor(0, 0, 0)));
    factorsChart->setPlotAreaBackgroundVisible(true);
    
    factorsChartView = new QChartView(factorsChart, this);
    factorsChartView->setRenderHint(QPainter::Antialiasing);
    factorsChartView->setMinimumHeight(300);
    factorsChartView->setStyleSheet(
        "QChartView { "
        "background-color: #000000; "
        "border: 2px solid #00ff00; "
        "}"
    );
    
    layout->addWidget(chartTitle);
    layout->addWidget(factorsChartView);
}

void ChartsWidget::createSurvivalFactorsChart()
{
    // Create bar set with terminal styling
    factorsSet = new QBarSet("[FACTOR_SUPERVIVENCIA]");
    factorsSet->setColor(QColor(0, 255, 65));
    factorsSet->setBorderColor(QColor(0, 255, 0));
    
    // Create series
    factorsSeries = new QBarSeries();
    factorsSeries->append(factorsSet);
    
    // Add series to chart
    factorsChart->addSeries(factorsSeries);
    
    // Create axes with terminal styling
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append({"TEMP", "RAD", "PRES", "HID"});
    axisX->setLabelsColor(QColor(0, 255, 0));
    axisX->setLabelsFont(QFont("Courier New", 10, QFont::Bold));
    axisX->setGridLineColor(QColor(0, 100, 0));
    factorsChart->addAxis(axisX, Qt::AlignBottom);
    factorsSeries->attachAxis(axisX);
    
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 1);
    axisY->setLabelFormat("%.2f");
    axisY->setTitleText(">>> FACTOR <<<");
    axisY->setLabelsColor(QColor(0, 255, 0));
    axisY->setLabelsFont(QFont("Courier New", 10, QFont::Bold));
    axisY->setTitleFont(QFont("Courier New", 10, QFont::Bold));
    axisY->setTitleBrush(QBrush(QColor(0, 255, 65)));
    axisY->setGridLineColor(QColor(0, 100, 0));
    factorsChart->addAxis(axisY, Qt::AlignLeft);
    factorsSeries->attachAxis(axisY);
    
    // Configure legend with terminal styling
    factorsChart->legend()->setVisible(true);
    factorsChart->legend()->setAlignment(Qt::AlignBottom);
    factorsChart->legend()->setLabelColor(QColor(0, 255, 0));
    factorsChart->legend()->setFont(QFont("Courier New", 10, QFont::Bold));
    factorsChart->legend()->setBackgroundVisible(true);
    factorsChart->legend()->setBrush(QBrush(QColor(0, 0, 0)));
    factorsChart->legend()->setPen(QPen(QColor(0, 255, 0)));
}

void ChartsWidget::updateCharts()
{
    if (!factorsSet) return;
    
    // Calculate individual survival factors using the same logic as Tardigrade class
    double tempFactor = 1.0;  // Default optimal
    double temp = tardigrade->getTemperatura();
    
    if (temp >= -20.0 && temp <= 40.0) {
        tempFactor = 1.0;
    } else if (temp >= -273.0 && temp <= 150.0) {
        double distance = std::min(std::abs(temp + 20.0), std::abs(temp - 40.0));
        tempFactor = std::max(0.1, 1.0 - distance / 200.0);
    } else {
        tempFactor = 0.0;
    }
    
    double radFactor = 1.0;
    double rad = tardigrade->getRadiacion();
    if (rad <= 100.0) {
        radFactor = 1.0;
    } else if (rad <= 5000.0) {
        radFactor = 1.0 - (rad - 100.0) / 4900.0;
    } else {
        radFactor = 0.0;
    }
    
    double presFactor = 1.0;
    double pres = tardigrade->getPresion();
    if (pres >= 0.5 && pres <= 2.0) {
        presFactor = 1.0;
    } else if (pres >= 0.0 && pres <= 600.0) {
        if (pres < 0.5) {
            presFactor = 0.3 + 0.7 * (pres / 0.5);
        } else {
            presFactor = 1.0 - (pres - 2.0) / 598.0 * 0.7;
        }
    } else {
        presFactor = 0.0;
    }
    
    double hidFactor = 1.0;
    double hid = tardigrade->getHidratacion();
    if (hid >= 60.0) {
        hidFactor = 1.0;
    } else if (hid >= 10.0) {
        hidFactor = 0.5 + 0.5 * (hid - 10.0) / 50.0;
    } else {
        hidFactor = 0.3;
    }
    
    // Update chart data
    factorsSet->remove(0, factorsSet->count());
    factorsSet->append({tempFactor, radFactor, presFactor, hidFactor});
    
    // Update bar colors with terminal theme
    factorsSet->setBorderColor(QColor(0, 255, 0));
    factorsSet->setBrush(QColor(0, 255, 65, 200));
}