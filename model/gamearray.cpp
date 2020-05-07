#include "gamearray.h"

using namespace std;

// A.K. �������������������� ���������� - ���
// ��� ���������� - ����� ������, �� ������� ������������� �� ���������, ������
// ���� ����������������, ���� ���������� ����� � �� �������.
// ���� ����� ���������� �� ����������������, �� � ��� � release-������ ����� �����.
GameArray::GameArray(int sizeValue) :
	baseGameArray(new TArrayData(sizeValue, TBoolVector(sizeValue, 0))),
	nextGameArray(0),
    m_Size(sizeValue),
	m_CellAmount(0),
	m_GenerationNumber(0),
	m_GameOver(false)
{
}

GameArray::~GameArray()
{
	// A.K. ���������� ������ ���-���� ��������� �� �������������
	delete baseGameArray;
	delete nextGameArray;	
}

void GameArray::computeNextGeneration()
{
    QList<QPoint> nextGen;
    nextGameArray = new TArrayData(m_Size, TBoolVector(m_Size, 0));
    for (int x = 0;  x < m_Size; x++)
        for (int y = 0;  y < m_Size; y++)
            if (willSurvive(x, y))
			{
                (*nextGameArray)[x][y] = true;
                nextGen.push_back(QPoint(x,y));
            }

    checkGameOverConditions();
    changeGeneration();
    m_CellAmount = nextGen.size();
    m_GenerationNumber++;
    emit modelChanged();
}

void GameArray::cleanGame()
{
    delete baseGameArray;
    delete nextGameArray;

    m_CellAmount = 0;
    nextGameArray = 0;
    m_GenerationNumber = 0;
    m_GameOver = false;
    baseGameArray = new TArrayData(m_Size, TBoolVector(m_Size, 0));
}

QList<QPoint>* GameArray::getAliveCellList() const
{
    // A.K. � ���� ���� ���� ����� ����������       +
	// � ����� �������, ������ ������� ���������� �������� �����
	// � ������ ������� - ����������, ������� ��.
	// ������ ������������, ��� ������� ���������� ����� ������� ������ ���,
    // ��� ��� ����� ����� ���������������, � ������ ������� ������ �����  +
	// �����������.
	
    QList<QPoint>* p = new QList<QPoint>;
    for (int x = 0;  x < m_Size;  x++)
        for (int y = 0;  y < m_Size;  y++)
        {
/*
			bool cell = (*baseGameArray)[x][y];
            if (cell)
                p.push_back(QPoint(x,y));
*/
			// A.K. ����� ��� - ������� � ������ ������ �����������
			if ((*baseGameArray)[x][y])
                p->push_back(QPoint(x,y));
        }
	
// +   m_CellAmount = p->size();	// A.K. ������� ���� ����� �� �����, �� ������ ���� � computeNextGeneration
    return p;

}

void GameArray::addOrDeleteAliveCell(const QPoint& cell)
{

	if ((*baseGameArray)[cell.x()][cell.y()])
	{
        (*baseGameArray)[cell.x()][cell.y()] = false;
        m_CellAmount--;
    } 
	else 
	{
        (*baseGameArray)[cell.x()][cell.y()] = true;
        m_CellAmount++;
    }

	
    // A.K. ����� �������� ���; ��������� � ������� - �� �� �����       +
	// ���� � ��������� ����� ���� ��� - �������� ������� ��������
//	(*baseGameArray)[cell.x()][cell.y()] = !(*baseGameArray)[cell.x()][cell.y()];

    //TK. ��, ���� ������� ��������. �� ����� ���� ��� ������ ��������������� ������.

    emit modelChanged();
}

void GameArray::changeGeneration()
{
    delete baseGameArray;
    baseGameArray = nextGameArray;
	
	// A.K. ���� ��� �� �������, ����� �������� ��� ����������� ������ � �����������
	// ���� �� ����� ������� ������ � �����������, ����� ������.
	nextGameArray = 0;	
}

bool GameArray::willSurvive(int x, int y)
{
	int neighbourCount = countNeighbours(x, y);
/*
    bool cell = (*baseGameArray)[x][y];
	
    if (neighborsCount == 3)
        return true;
    else if (cell == true && neighborsCount == 2)
        return true;
    return false;
*/	
    // A.K. ������ ����� ���� ����� �������� ����� ����������   +
	return 
		neighbourCount == 3 || 
		((*baseGameArray)[x][y] && neighbourCount == 2);
}

int GameArray::countNeighbours(int x, int y)
{
    int count = 0;
	
	// A.K. ����� ��� �� �������������, ��� ���� ��������, �� ������� ����� 
	// ����� for ����������� �� ������ �������� ������. �������, ���� 
	// �c����� ����� �������� �� ���������� � ���� ������ �����, �� �����
	// ��������� ������� ���� ��� � ������� ��� � ��������� ����������
    // (int xLast - x + 1, yLast = y + 1)

    //+��. ����
    int xLast = x + 1;
    int yLast = y + 1;
    for (int nx = x - 1;  nx <= xLast;  nx++)
        for (int ny = y - 1;  ny <= yLast;  ny++)
		{
            if (nx == x && ny == y)
                continue;
			// A.K. ��� ��� ���������
			// ����� ����� ��������, ����� ��������������, ����� ��� ��������

                    /* TK. ��� ������� ������ ����������� � �������?
                     * ��������, ������ �� ����������, ��������� ������ (���������, �����������) � ��
                    */
			// ���� � ���, ��� (n + s) % s == n % s, ����� ���?

                /*TK. -5 % 10 = -5
                       5 % 10 =  5
                 � ��� ����� ������������� ����� ��� �������, ������� ��������� size
                    (-5 + 10) % 10 = 5
                     (5 + 10) % 10 = 5

                  ���� ����� ���� ������ ����� ������ , ��� ��������� ������� �� ����
                */

			// ���� � ��������� �����, �� �������� ������������� �������� ���� �
            // ����� ������������

                    //TK. �� , ���������

            // ������ �������� ������� � ������ ������������� �������� ����
            if ((*baseGameArray)[(nx+m_Size)%m_Size][(ny+m_Size)%m_Size])
                count++;
			
			// A.K. � �� ������� ������ ��� ���:
//			if ((*baseGameArray)[nx % m_Size][ny % m_Size])
//				++count;
                   /* TK.
                   �� ������ ������ {} � if for...(�������, �� �������) ����� ������������ ���������
                       https://ru.stackoverflow.com/a/424135

                   �������, ���� ������� ��������,  �������� ���� ������� - �������� ����� ������ ))
                   (� ���� �� IDE ���� ������).
*/
        }
    return count;
}

void GameArray::checkGameOverConditions()
{
	QList<QPoint> currentGenList;
    QList<QPoint> nextGenList;

    for (int x = 0; x < m_Size; x++)
        for (int y = 0;  y < m_Size; y++)
        {
/*			// A.K.
            if (nextGameArray->operator[](x).operator[](y)) +
*/			
			if ((*nextGameArray)[x][y])
                nextGenList.push_back(QPoint(x,y));
/*			// A.K.
            if (baseGameArray->operator[](x).operator[](y))
*/
			if ((*baseGameArray)[x][y])
                currentGenList.push_back(QPoint(x,y));
        }
	
/*	// A.K.
    if (nextGenList.size() == 0)
	{
        m_GameOver = true;
        return;
    }

    if (nextGenList.operator==(currentGenList))
        m_GameOver = true;
*/
	// ����� ��� - ��������
	m_GameOver = 
		nextGenList.size() == 0 ||
		nextGenList == currentGenList;
}

