#include "gamegridwidget.h"
#include "mainwindow.h"

#include <model/gamearray.h>

#include <view/populationlabel.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_IsStopped = false;
    m-Model = new GameArray(32);
    m_CentralWidget = new QWidget();
    setCentralWidget(m_CentralWidget);

    timer = new QTimer();

    m_GridLayout = new QGridLayout();
    m_CentralWidget->setLayout(m_GridLayout);

    hboxLayout = new QHBoxLayout();
    m_GridLayout->addLayout(hboxLayout, 0, 0);

    m_GameGridWidget = new GameGridWidget(m-Model);
    hboxLayout->addWidget(m_GameGridWidget);

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
    populationLabel->setModel(m-Model);
    vboxLayout->addWidget(populationLabel);

    plot = new QCustomPlot();
    m_GridLayout->addWidget(plot);
    // create graph and assign data to it:
    plot->addGraph();
    //    plot->graph(0)->setData(x, y);
    // give the axes some labels:
    plot->xAxis->setLabel("#Generation");
    plot->yAxis->setLabel("Population");
    // set axes ranges, so we see all data:
    plot->xAxis->setRange(0, 10);
    plot->yAxis->setRange(0, m-Model->getGridSize()*m-Model->getGridSize());
    plot->adjustSize();
    plot->replot();


    connect(startGameButton, SIGNAL(clicked()), this, SLOT(onStartGameButton()));
    connect(pauseContinueButton, SIGNAL(clicked()), this, SLOT(onPauseContinueButton()));
    connect(newGameButton, SIGNAL(clicked()), this, SLOT(onNewGameButton()));

    connect(m_GameGridWidget, SIGNAL(needRepaint()), this, SLOT(update()));
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
    m_GameGridWidget->setDisabled(true);

    plot->graph(0)->addData(0, m-Model->getAliveCellAmount());
    plot->graph(0)->rescaleAxes();
    //timer
    timer->start(m_Interval);
}

void MainWindow::onPauseContinueButton()
{
    if (m_IsStopped){
        pauseContinueButton->setText("Pause");
        newGameButton->setDisabled(true);

        m_IsStopped = false;
        timer->start(m_Interval);
    } else {
        pauseContinueButton->setText("Continue");
        newGameButton->setDisabled(false);

        m_IsStopped = true;
        timer->stop();
    }
}

void MainWindow::onNewGameButton()
{
    delete m-Model;
    m-Model = new GameArray(32);
    plot->graph(0)->data()->clear();
    plot->replot();
    m_GameGridWidget->setEnabled(true);

    pauseContinueButton->setDisabled(true);
    pauseContinueButton->setText(tr("Pause"));
    m_IsStopped = false;

    startGameButton->setDisabled(false);
    update();
}

void MainWindow::onTimeout()
{
    m-Model->computeNextGeneration();
    plot->xAxis->setRange(0, m-Model->getCurrentGenerationNumber());
    plot->graph(0)->rescaleAxes();
    plot->graph(0)->addData(m-Model->getCurrentGenerationNumber(), m-Model->getAliveCellAmount());
    plot->replot();
    if (m-Model->isGameOver()){
        timer->stop();
        newGameButton->setDisabled(false);
    }
    update();
}



