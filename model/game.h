#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H	// ��������� A.K.

#include <QHash>
#include <QList>
#include <QPoint>

// A.K. ����� ��������� �������� ������ ������; ��� ���������� �� ����� �������
// ����� ������ ���������.
// � ������ ������ ���������� ����������� �������������� ������� �� ����������
// ��������� ��������� include'�� <QHash>, <QList>, <QPoint>
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

// A.K. ����� ����� ���� �����?
// ����� ����������� ������, �������� ������� (��� ������, ���� ����� 
// ����������� �������), ������������ ���� ����� �� ��� ����������� �����, 
// ��� ���� �������, ���� ����� ��������� � �������� ��� ������� �������� 
// �������� ����� �������������� ����������������/
// ��������������, � ������ ������ ���� ����� ������ �� �����, � ���
// ���������������� ����������� � ������ GameArray

#endif // GAMEOFLIFE_H
