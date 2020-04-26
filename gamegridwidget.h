#ifndef GAMEGRID_H
#define GAMEGRID_H

#include <QFrame>
#include <QWidget>
#include <QVector>
#include <QPoint>
#include <QSet>
#include <QList>

#include <model/gamearray.h>

class GameGridWidget : public QFrame
{
    Q_OBJECT
public:
    explicit GameGridWidget(QWidget *parent = 0);
    GameGridWidget(GameArray* modelValue);

signals:
    void populationChanged(int size);
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
