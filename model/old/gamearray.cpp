#include "gamearray.h"

using namespace std;

// A.K. В отличие от java, в C++ нет сборщика мусора, поэтому все, что
// размещается в куче, должно быть оттуда удалено.
// Память, выделенная в конструкторе, нигде не освобождается.
GameArray::GameArray(int sizeValue) :
    m_Size(sizeValue)
{
    m_GenerationNumber = 0;
    m_GameOver = false;
    m_CellAmount = 0;
    baseGameArray = new TArrayData(sizeValue, TBoolVector(sizeValue, 0));
}

QList<QPoint> GameArray::computeNextGeneration()
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
    m_GenerationNumber++;
    return nextGen;
}

int GameArray::getCurrentGenerationNumber() const
{
    return m_GenerationNumber;
}

int GameArray::getAliveCellAmount()	const// A.K. почему не const?
{
    return m_CellAmount;
}

QList<QPoint> GameArray::getAliveCellList()
{
    QList<QPoint> p;
    for ( int x = 0; x < m_Size; x++)
        for (int y = 0;  y < m_Size; y++)
        {
            bool cell = (*baseGameArray)[x][y];
            if (cell)
                p.push_back(QPoint(x,y));
        }
    m_CellAmount = p.size();
    return p;
}

void GameArray::addOrDeleteAliveCell(QPoint cell)
{
    if ((*baseGameArray)[cell.x()][cell.y()]){
        (*baseGameArray)[cell.x()][cell.y()] = false;
    } else {
        (*baseGameArray)[cell.x()][cell.y()] = true;
    }
}

void GameArray::changeGeneration()
{
    delete baseGameArray;
    baseGameArray = nextGameArray;
}

bool GameArray::willSurvive(int x, int y)
{
    int neighborsCount = countNeighbors(x, y);
    bool cell = (*baseGameArray)[x][y];
    if (neighborsCount == 3){
        return true;
    } else if (cell == true && neighborsCount == 2){
        return true;
    }
    return false;
}

int GameArray::countNeighbors(int x, int y)
{
    int count = 0;
    for (int nx = x - 1;  nx <= x + 1;  nx++){
        for (int ny = y - 1; ny <= y + 1; ny++){
            if (nx == x && ny == y){
                continue;
            }
            bool alive = (*baseGameArray)[(nx+m_Size)%m_Size][(ny+m_Size)%m_Size];
            if (alive){
                count++;
            }
        }
    }
    return count;
}

void GameArray::checkGameOverConditions()
{
    QList<QPoint> currentGenList;
    QList<QPoint> nextGenList;

    for ( int x = 0; x < m_Size; x++)
    {
        for (int y = 0;  y < m_Size; y++)
        {
            if (nextGameArray->operator[](x).operator[](y)){
                nextGenList.push_back(QPoint(x,y));
            }
            if (baseGameArray->operator[](x).operator[](y)){
                currentGenList.push_back(QPoint(x,y));
            }
        }
    }

    if (nextGenList.size() == 0){
        m_GameOver = true;
        return;
    }

    if (nextGenList.operator==(currentGenList)){
        m_GameOver = true;
    }
}

int GameArray::getGridSize() const
{
    return m_Size;
}

bool GameArray::isGameOver() const
{
    return m_GameOver;
}

