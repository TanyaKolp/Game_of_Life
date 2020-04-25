#include "gamegridwidget.h"

#include <QLine>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

#include <QSizePolicy>

using namespace std;

GameGridWidget::GameGridWidget(QWidget *parent)
{

}

GameGridWidget::GameGridWidget(Game *modelValue)
{
    model = modelValue;
    setFixedSize(320, 320);
    setFrameStyle(QFrame::StyledPanel | QFrame::Plain);

    gridSize = model->getGridSize();
}

void GameGridWidget::drawCell(QPainter& painter, int step, QPoint pos)
{
    int pointerRadius = step*3/8;
    painter.setBrush(QBrush(Qt::black, Qt::SolidPattern));
    painter.drawEllipse(QPoint(pos.x()*step + step/2, pos.y()*step + step/2), pointerRadius, pointerRadius);
}

void GameGridWidget::mousePressEvent(QMouseEvent* event)
{
    const QPoint pos = event->pos();
    int step = this->height()/gridSize;

    QPoint point(pos.x()/step, pos.y()/step);
    model->addOrDeleteAliveCell(point);
    emit needRepaint();
}



void GameGridWidget::paintEvent(QPaintEvent* e)
{
    QFrame::paintEvent(e);

    QPainter painter(this);
    int step = this->height()/gridSize;

    //draw grid
    for (int i = 1; i <= gridSize; i++) {
        painter.drawLine(0, step*i, this->width(), step*i);
        painter.drawLine(step*i, 0, step*i, this->height());
    }

    //draw alive cell
    QList<QPoint> aliveCellList = model->getAliveCellList();
    for (int i = 0; i < aliveCellList.size(); i++) {
        drawCell(painter, step, aliveCellList[i]);
    }
}
