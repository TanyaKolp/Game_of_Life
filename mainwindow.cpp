#include <QString>
#include "gamegridwidget.h"
#include "mainwindow.h"

#include <model/gamearray.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_IsStopped(false),
      m_Interval(200),
      m_PopulationLabelPattern("Population: %1\n# Generation: %2")
{
    m_Model = new GameArray(32);
    centralWidget = new QWidget();
    setCentralWidget(centralWidget);

    timer = new QTimer();

    gridLayout = new QGridLayout();
    centralWidget->setLayout(gridLayout);

    hboxLayout = new QHBoxLayout();
    gridLayout->addLayout(hboxLayout, 0, 0);

    gameGridWidget = new GameGridWidget();
    gameGridWidget->installEventFilter(this);
    gameGridWidget->setGridSize(m_Model->getGridSize());
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

    populationLabel = new QLabel();
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
    plot->yAxis->setRange(0, m_Model->getGridSize()*m_Model->getGridSize());
    plot->adjustSize();
    plot->replot();


    connect(startGameButton, SIGNAL(clicked()), this, SLOT(onStartGameButton()));
    connect(pauseContinueButton, SIGNAL(clicked()), this, SLOT(onPauseContinueButton()));
    connect(newGameButton, SIGNAL(clicked()), this, SLOT(onNewGameButton()));

    connect(m_Model, SIGNAL(modelChanged()), this, SLOT(onModelChanged())),
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

    plot->graph(0)->addData(0, m_Model->getAliveCellAmount());
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
    m_Model->cleanGame();

    plot->graph(0)->data()->clear();
    gameGridWidget->setEnabled(true);

    pauseContinueButton->setDisabled(true);
    pauseContinueButton->setText(tr("Pause"));
    m_IsStopped = false;

    startGameButton->setDisabled(false);
    onModelChanged();
}

void MainWindow::onTimeout()
{
    m_Model->computeNextGeneration();

    if (m_Model->isGameOver()){
        timer->stop();
        newGameButton->setDisabled(false);
    }
}

void MainWindow::onModelChanged()
{
    populationLabel->setText(QString(m_PopulationLabelPattern)
                             .arg(m_Model->getAliveCellAmount())
                                  .arg(m_Model->getCurrentGenerationNumber())
                             );

    plot->xAxis->setRange(0, m_Model->getCurrentGenerationNumber());
    plot->graph(0)->rescaleAxes();
    plot->graph(0)->addData(m_Model->getCurrentGenerationNumber(),
                            m_Model->getAliveCellAmount());
    plot->replot();

    gameGridWidget->setAliveCells(m_Model->getAliveCellList());

    update();
}

bool MainWindow::eventFilter(QObject * target, QEvent * event)
{
    if (event->type() == QEvent::MouseButtonPress){
        if (target == gameGridWidget){
          QMouseEvent* eMouse =  static_cast<QMouseEvent *>(event);
          GameGridWidget* tWid = static_cast<GameGridWidget *>(target);

          if (tWid->isEnabled()){
            const QPoint pos = eMouse->pos();
            int step = tWid->height()/tWid->gridSize();
            m_Model->addOrDeleteAliveCell(QPoint(pos.x()/step, pos.y()/step));
          }
          return true;
        }
    }
    return QMainWindow::eventFilter(target, event);
}



