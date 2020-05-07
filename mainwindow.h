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
    void onModelChanged();

private:
    GameArray* m_Model;

    GameGridWidget* gameGridWidget;
    QWidget* centralWidget;
    QGridLayout* gridLayout;
    QHBoxLayout* hboxLayout;
    QVBoxLayout* vboxLayout;
    QPushButton* startGameButton;
    QPushButton* pauseContinueButton;
    QPushButton* newGameButton;
    QLabel* populationLabel;
    QTimer* timer;

    QCustomPlot* plot;

    bool m_IsStopped;
    int m_Interval;

    const char*  m_PopulationLabelPattern;

    // QObject interface
public:
    bool eventFilter(QObject *, QEvent *);
};
#endif // MAINWINDOW_H
