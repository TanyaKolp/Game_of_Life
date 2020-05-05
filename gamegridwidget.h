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
	A.K. Архитектура неудачная - надо сделать GameArray потомком QObject,
	создать сигнал changed, а в слоте данного класса, который будет этот
	самый changed обрабатывать, вызывать update(), а не возбуждать сигнал
	needRepaint().
*/

class GameGridWidget : public QFrame
{
    Q_OBJECT
public:
    explicit GameGridWidget(QWidget *parent = 0);
    GameGridWidget(GameArray* modelValue);

signals:
    void populationChanged(int size);	// A.K. этот сигнал в данном классе не вызывается
    void needRepaint();

public slots:

    // QWidget interface
protected:
    void paintEvent(QPaintEvent*);

private:
    GameArray* m_Model;
    int m_GridSize;

    void drawCell(QPainter& painter, int step, QPoint pos);

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent* e) ;
};

#endif // GAMEGRID_H
