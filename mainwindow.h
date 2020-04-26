#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QDebug>
#include <QTimer>

#include "gamegridwidget.h"

#include <model/gamearray.h>

#include <view/populationlabel.h>

#include <lib/qcustomplot.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public  slots:
    void onStartGameButton();
    void onPauseContinueButton();
    void onNewGameButton();

    void onTimeout();

private:
    GameArray* model;

    GameGridWidget* gameGridWidget;
    QWidget* centralWidget;
    QGridLayout* gridLayout;
    QHBoxLayout* hboxLayout;
    QVBoxLayout* vboxLayout;
    QPushButton* startGameButton;
    QPushButton* pauseContinueButton;
    QPushButton* newGameButton;
    PopulationLabel* populationLabel;
    QTimer* timer;

    QCustomPlot* plot;

    QFrame* test;

    bool m_IsStopped;
    int m_Interval = 200;

};
#endif // MAINWINDOW_H
