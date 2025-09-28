#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QStatusBar>
#include "Tardigrade.h"

class VisualSimWidget;
class ScienceSimWidget;
class KnowledgeBase;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onParametersChanged();
    void updateStatusBar();

private:
    void setupUI();
    void connectSignals();
    
    QTabWidget *tabWidget;
    VisualSimWidget *visualSimWidget;
    ScienceSimWidget *scienceSimWidget;
    KnowledgeBase *knowledgeBase;
    
    Tardigrade *tardigrade;
    QLabel *survivalLabel;
    QLabel *stateLabel;
};

#endif // MAINWINDOW_H