#ifndef SCIENCESIMWIDGET_H
#define SCIENCESIMWIDGET_H

#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include "Tardigrade.h"
#include "ChartsWidget.h"

class ScienceSimWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ScienceSimWidget(Tardigrade *tardigrade, QWidget *parent = nullptr);

signals:
    void parametersChanged();

private slots:
    void onTemperaturaChanged();
    void onRadiacionChanged();
    void onPresionChanged();
    void onHidratacionChanged();
    void resetToDefaults();
    void presetWater();
    void presetIce();
    void presetRadiation();
    void presetSpace();

private:
    void setupUI();
    void setupParameterControls();
    void setupPresets();
    void updateAllDisplays();
    void updateSurvivalDisplay();
    
    Tardigrade *tardigrade;
    
    // Temperature controls
    QSlider *temperaturaSlider;
    QDoubleSpinBox *temperaturaSpinBox;
    QLabel *temperaturaLabel;
    
    // Radiation controls
    QSlider *radiacionSlider;
    QSpinBox *radiacionSpinBox;
    QLabel *radiacionLabel;
    
    // Pressure controls
    QSlider *presionSlider;
    QDoubleSpinBox *presionSpinBox;
    QLabel *presionLabel;
    
    // Hydration controls
    QSlider *hidratacionSlider;
    QSpinBox *hidratacionSpinBox;
    QLabel *hidratacionLabel;
    
    // Survival display
    QLabel *survivalValueLabel;
    QLabel *survivalBarLabel;
    QLabel *stateLabel;
    
    // Charts
    ChartsWidget *chartsWidget;
    
    // Preset buttons
    QPushButton *waterBtn;
    QPushButton *iceBtn;
    QPushButton *radiationBtn;
    QPushButton *spaceBtn;
    QPushButton *resetBtn;
};

#endif // SCIENCESIMWIDGET_H