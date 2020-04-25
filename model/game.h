#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H	// добавлено A.K.

#include <QHash>
#include <QList>
#include <QPoint>

// A.K. Страж включения ставится строго сверху; для отклонения от этого правила
// нужны веские основания.
// В данном случае компилятор нагружается дополнительной работой по повторному
// включению системных include'ов <QHash>, <QList>, <QPoint>
//#define GAMEOFLIFE_H

class Game
{
public:

    virtual void clearGame() = 0;

    virtual QList<QPoint> computeNextGeneration() = 0;

    virtual int getCurrentGenerationNumber() const = 0;

    virtual int getAliveCellAmount() = 0;

    virtual QList<QPoint> getAliveCellList() = 0;

    virtual void addOrDeleteAliveCell(QPoint cell) = 0;

    virtual int getGridSize() = 0;

    virtual bool isGameOver() = 0;
};

// A.K. Зачем нужен этот класс?
// Чисто виртуальные классы, подобные данному (нет данных, одни чисто 
// виртуальные функции), используются либо когда от них наследуется более, 
// чем один потомок, либо когда требуется в середину уже готовой иерархии 
// добавить некую дополнительную функциональность/
// Соответственно, в данной задаче этот класс вообще не нужен, а вся
// функциональность реализуется в классе GameArray

#endif // GAMEOFLIFE_H
