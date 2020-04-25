#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gamegridwidget.h"

#include <QFrame>
#include <QGridLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QDebug>
#include <QTimer>

#include <model/game.h>

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
    Game* model;

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

    bool isStopped;
    int interval = 200;

};
#endif // MAINWINDOW_H
