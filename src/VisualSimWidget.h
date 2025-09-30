#ifndef VISUALSIMWIDGET_H
#define VISUALSIMWIDGET_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "Tardigrade.h"

class VisualSimWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VisualSimWidget(Tardigrade *tardigrade, QWidget *parent = nullptr);
    
public slots:
    void updateVisualization();

private slots:
    void onEnvironmentChanged(int index);
    void animateTimer();

private:
    void setupUI();
    void setupScene();
    void updateBackground();
    void updateTardigradeSprite();
    void startAnimation();
    void stopAnimation();
    
    Tardigrade *tardigrade;
    
    QGraphicsView *graphicsView;
    QGraphicsScene *scene;
    QGraphicsItem *backgroundItem;
    QGraphicsItem *tardigradeItem;
    
    QComboBox *environmentCombo;
    QLabel *environmentLabel;
    QLabel *statusLabel;
    
    QTimer *animationTimer;
    
    enum Environment {
        WATER = 0,
        ICE,
        RADIATION,
        SPACE
    };
    
    Environment currentEnvironment;
    int animationFrame;
    bool animationDirection;
};

#endif // VISUALSIMWIDGET_H