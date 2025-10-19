#ifndef CHARTSWIDGET_H
#define CHARTSWIDGET_H

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QVBoxLayout>
#include <QLabel>
#include "Tardigrade.h"

QT_CHARTS_USE_NAMESPACE

class ChartsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChartsWidget(Tardigrade *tardigrade, QWidget *parent = nullptr);

public slots:
    void updateCharts();

private:
    void setupUI();
    void createSurvivalFactorsChart();
    
    Tardigrade *tardigrade;
    
    QChart *factorsChart;
    QChartView *factorsChartView;
    QBarSeries *factorsSeries;
    QBarSet *factorsSet;
    
    QLabel *chartTitle;
};

#endif // CHARTSWIDGET_H