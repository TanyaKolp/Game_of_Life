#include "gamearray.h"

using namespace std;	// A.K. Добавлено
/*
// старый код
GameArray::GameArray(int sizeValue)
{
    size = sizeValue;
    baseGameArray = new vector<vector<bool> >(sizeValue, vector< bool >(sizeValue, 0));
    nextGameArray = new vector<vector<bool> >(sizeValue, vector< bool >(sizeValue, 0));
}
*/

// новый код
// A.K. В отличие от java, в C++ нет сборщика мусора, поэтому все, что
// размещается в куче, должно быть оттуда удалено.
// Память, выделенная в конструкторе, нигде не освобождается.
GameArray::GameArray(int sizeValue) :
	size(sizeValue)						// A.K. инициализировать лучше так
{
    baseGameArray = new TArrayData(size, TBoolVector(sizeValue, 0));
    nextGameArray = new TArrayData(size, TBoolVector(sizeValue, 0));
}

void GameArray::clearGame()
{
    baseGameArray = new vector<vector<bool> >(size, vector< bool >(size, 0));
    cellAmount = 0;
    generationNumber = 0;
    gameOver = false;
}

QList<QPoint> GameArray::computeNextGeneration()
{
    QList<QPoint> nextGen;
    nextGameArray = new vector<vector<bool> >(size, vector< bool >(size, 0));
    for (int x = 0;  x < size; x++)
//    {
        for (int y = 0;  y < size; y++)
        {
            if (willSurvive(x, y)){
				// A.K. Можно так: (*nextGameArray)[x][y] = true; // (это общая проблема данного файла)
                nextGameArray->operator[](x).operator[](y).operator=(true);
                nextGen.push_back(QPoint(x,y));
            }
//        }
    }

    checkGameOverConditions();
    changeGeneration();
    generationNumber++;
    return nextGen;
}

int GameArray::getCurrentGenerationNumber() const
{
    return generationNumber;
}

int GameArray::getAliveCellAmount()	// A.K. почему не const?
{
    return cellAmount;
}

QList<QPoint> GameArray::getAliveCellList()
{
    QList<QPoint> p;
    for ( int x = 0; x < size; x++)
//	{
        for (int y = 0;  y < size; y++)
        {
            // A.K. Можно написать так: bool cell = (*baseGameArray)[x][y];
			bool cell = baseGameArray->operator[](x).operator[](y);
            if (cell)
//			{
                p.push_back(QPoint(x,y));
//			}
        }
//    }
    cellAmount = p.size();
    return p;
}

void GameArray::addOrDeleteAliveCell(QPoint cell)
{
    if (baseGameArray->operator[](cell.x()).operator[](cell.y())){
        baseGameArray->operator[](cell.x()).operator[](cell.y()).operator=(false);
    } else {
        baseGameArray->operator[](cell.x()).operator[](cell.y()).operator=(true);
    }
}

void GameArray::changeGeneration()
{
    baseGameArray = nextGameArray;
}

bool GameArray::willSurvive(int x, int y)
{
    int neighborsCount = countNeighbors(x, y);
    bool cell = baseGameArray->operator[](x).operator[](y);
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
            bool alive = baseGameArray->operator[]((nx+size)%size).operator[]((ny+size)%size);
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

    for ( int x = 0; x < size; x++)
    {
        for (int y = 0;  y < size; y++)
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
        gameOver = true;
        return;
    }

    if (nextGenList.operator==(currentGenList)){
        gameOver = true;
    }
}

int GameArray::getGridSize()
{
    return size;
}

bool GameArray::isGameOver()
{
    return gameOver;
}

