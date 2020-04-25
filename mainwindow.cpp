#include "gamegridwidget.h"
#include "mainwindow.h"
#include "testframe.h"

#include <model/gamearray.h>

#include <view/populationlabel.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    isStopped = false;
    model = new GameArray(32);
    centralWidget = new QWidget();
    setCentralWidget(centralWidget);

    timer = new QTimer();

    gridLayout = new QGridLayout();
    centralWidget->setLayout(gridLayout);

    hboxLayout = new QHBoxLayout();
    gridLayout->addLayout(hboxLayout, 0, 0);

    gameGridWidget = new GameGridWidget(model);
    hboxLayout->addWidget(gameGridWidget);

    vboxLayout = new QVBoxLayout();
    hboxLayout->addLayout(vboxLayout);

    startGameButton = new QPushButton();
    startGameButton->setText(tr("Start Game"));
    vboxLayout->addWidget(startGameButton);

    pauseContinueButton = new QPushButton();
    pauseContinueButton->setText(tr("Pause"));
    pauseContinueButton->setDisabled(true);
    vboxLayout->addWidget(pauseContinueButton);

    newGameButton = new QPushButton();
    newGameButton->setText(tr("New Game"));
    vboxLayout->addWidget(newGameButton);

    populationLabel = new PopulationLabel();
    populationLabel->setModel(model);
    vboxLayout->addWidget(populationLabel);

    plot = new QCustomPlot();
    gridLayout->addWidget(plot);
    // create graph and assign data to it:
    plot->addGraph();
    //    plot->graph(0)->setData(x, y);
    // give the axes some labels:
    plot->xAxis->setLabel("#Generation");
    plot->yAxis->setLabel("Population");
    // set axes ranges, so we see all data:
    plot->xAxis->setRange(0, 10);
    plot->yAxis->setRange(0, model->getGridSize()*model->getGridSize());
    plot->adjustSize();
    plot->replot();


    connect(startGameButton, SIGNAL(clicked()), this, SLOT(onStartGameButton()));
    connect(pauseContinueButton, SIGNAL(clicked()), this, SLOT(onPauseContinueButton()));
    connect(newGameButton, SIGNAL(clicked()), this, SLOT(onNewGameButton()));

    connect(gameGridWidget, SIGNAL(needRepaint()), this, SLOT(update()));
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::onStartGameButton()
{
    //view
    pauseContinueButton->setDisabled(false);

    newGameButton->setDisabled(true);
    startGameButton->setDisabled(true);
    gameGridWidget->setDisabled(true);

    plot->graph(0)->addData(0, model->getAliveCellAmount());
    plot->graph(0)->rescaleAxes();
    //timer
    timer->start(interval);
}

void MainWindow::onPauseContinueButton()
{
    if (isStopped){
        pauseContinueButton->setText("Pause");
        newGameButton->setDisabled(true);

        isStopped = false;
        timer->start(interval);
    } else {
        pauseContinueButton->setText("Continue");
        newGameButton->setDisabled(false);

        isStopped = true;
        timer->stop();
    }
}

void MainWindow::onNewGameButton()
{
    model->clearGame();
    plot->graph(0)->data()->clear();
    plot->replot();
    gameGridWidget->setEnabled(true);

    pauseContinueButton->setDisabled(true);
    pauseContinueButton->setText(tr("Pause"));
    isStopped = false;

    startGameButton->setDisabled(false);
    update();
}

void MainWindow::onTimeout()
{
    model->computeNextGeneration();
    plot->xAxis->setRange(0, model->getCurrentGenerationNumber());
    plot->graph(0)->rescaleAxes();
    plot->graph(0)->addData(model->getCurrentGenerationNumber(), model->getAliveCellAmount());
    plot->replot();
    if (model->isGameOver()){
        timer->stop();
        newGameButton->setDisabled(false);
    }
    update();
}



