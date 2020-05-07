#ifndef GAMEGRID_H
#define GAMEGRID_H

#include <QFrame>
#include <QWidget>
#include <QVector>
#include <QPoint>
#include <QSet>
#include <QList>

#include <model/gamearray.h>

/*
    A.K. Архитектура неудачная - надо сделать GameArray потомком QObject,  +
	создать сигнал changed, а в слоте данного класса, который будет этот
	самый changed обрабатывать, вызывать update(), а не возбуждать сигнал
	needRepaint().
*/

class GameGridWidget : public QFrame
{
    Q_OBJECT
public:
    explicit GameGridWidget(QWidget *parent = 0);

    void setGridSize(int GridSize);

    void setAliveCells(QList<QPoint> *AliveCells);

    int gridSize() const;

signals:

public slots:

    // QWidget interface
protected:
    void paintEvent(QPaintEvent*);

private:
    int m_GridSize; // default = 32
    QList<QPoint>* m_AliveCells;

    void drawCell(QPainter& painter, int step, QPoint pos);

};

#endif // GAMEGRID_H
