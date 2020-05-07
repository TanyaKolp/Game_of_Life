#include "gamegridwidget.h"


#include <iostream>

#include <QLine>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

#include <QSizePolicy>

using namespace std;

GameGridWidget::GameGridWidget(QWidget *parent) :
    m_GridSize(32),
    m_AliveCells(new QList<QPoint>)
{
    setFixedSize(320, 320);
    setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
}

void GameGridWidget::drawCell(QPainter& painter, int step, QPoint pos)
{
    int pointerRadius = step*3/8;
    painter.setBrush(QBrush(Qt::black, Qt::SolidPattern));
    painter.drawEllipse(QPoint(pos.x()*step + step/2, pos.y()*step + step/2), pointerRadius, pointerRadius);
}

void GameGridWidget::paintEvent(QPaintEvent* e)
{
    QFrame::paintEvent(e);

    QPainter painter(this);
    int step = this->height()/m_GridSize;

    //draw grid
    for (int i = 1; i <= m_GridSize; i++) {
        painter.drawLine(0, step*i, this->width(), step*i);
        painter.drawLine(step*i, 0, step*i, this->height());
    }

    //draw alive cell
    for (int i = 0; i < m_AliveCells->size(); i++) {
        drawCell(painter, step, (*m_AliveCells)[i]);
    }
}

int GameGridWidget::gridSize() const
{
    return m_GridSize;
}

void GameGridWidget::setAliveCells(QList<QPoint> *AliveCells)
{
    delete m_AliveCells;
    m_AliveCells = AliveCells;
}

void GameGridWidget::setGridSize(int GridSize)
{
    m_GridSize = GridSize;
}

