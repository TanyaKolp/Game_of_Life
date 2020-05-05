#include "gamearray.h"

using namespace std;

// A.K. Ќеинициализированные переменные - зло
// ¬се переменные - члены класса, не имеющие конструкторов по умолчанию, должны
// быть инициализированы, хоть компил€тор этого и не требует.
// ≈сли така€ переменна€ не инициализирована, то в ней в release-сборке будет мусор.
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
	// A.K. выделенна€ пам€ть все-таки полностью не освобождалась
	delete baseGameArray;
	delete nextGameArray;	
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

QList<QPoint> GameArray::getAliveCellList()
{
    // A.K. ¬ этом коде есть нека€ странность
	// — одной стороны, данна€ функци€ возвращает перечень точек
	// с другой стороны - записывает, сколько их.
	// Ћогика подсказывает, что подсчет количества точек следует делать там,
	// где эти самые точки устанавливаютс€, а данна€ функци€ должна стать
	// константной.
	
	QList<QPoint> p;
    for (int x = 0;  x < m_Size;  x++)
        for (int y = 0;  y < m_Size;  y++)
        {
/*
			bool cell = (*baseGameArray)[x][y];
            if (cell)
                p.push_back(QPoint(x,y));
*/
			// A.K. лучше так - быстрее и меньше пам€ти расходуетс€
			if ((*baseGameArray)[x][y])
                p.push_back(QPoint(x,y));
        }
	
    m_CellAmount = p.size();	// A.K. данному коду здесь не место, он должен быть в computeNextGeneration
    return p;
}

void GameArray::addOrDeleteAliveCell(const QPoint& cell)
{
/*
	if ((*baseGameArray)[cell.x()][cell.y()])
	{
        (*baseGameArray)[cell.x()][cell.y()] = false;
    } 
	else 
	{
        (*baseGameArray)[cell.x()][cell.y()] = true;
    }
*/
	
	// A.K. Ћучше написать так; насколько € понимаю - то же самое
	// если € правильно пон€л твой код - написана проста€ инверси€
	(*baseGameArray)[cell.x()][cell.y()] = !(*baseGameArray)[cell.x()][cell.y()];
}

void GameArray::changeGeneration()
{
    delete baseGameArray;
    baseGameArray = nextGameArray;
	
	// A.K. если так не сделать, будут проблемы при уничтожении данных в деструкторе
	// ≈сли не будет очистки пам€ти в деструкторе, будет утечка.
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
	// A.K. ƒанный кусок кода можно написать одним выражением
	return 
		neighbourCount == 3 || 
		((*baseGameArray)[x][y] && neighbourCount == 2);
}

int GameArray::countNeighbours(int x, int y)
{
    int count = 0;
	
	// A.K. «десь это не принципиально, ибо цикл короткий, но условие конца 
	// цикла for вычисл€етс€ на каждой итерации заново. ѕоэтому, если 
	// уcловие конца заведомо не измен€етс€ в ходе работы цикла, то лучше
	// вычислить условие один раз и сложить его в отдельную переменную
	// (int xLast - x + 1, yLast = y + 1)
    for (int nx = x - 1;  nx <= x + 1;  nx++)
        for (int ny = y - 1;  ny <= y + 1;  ny++)
		{
            if (nx == x && ny == y)
                continue;
			// A.K.  од мне непон€тен
			// когда такое написано, лучше комментировать, зачем так написано
			// ƒело в том, что (n + s) % s == n % s, разве нет?
			// ≈сли € правильно пон€л, ты написала зацикленность игрового пол€ в
			// обоих направлени€х
            bool alive = (*baseGameArray)[(nx+m_Size)%m_Size][(ny+m_Size)%m_Size];
            if (alive)
                count++;
			
			// A.K. я бы написал данный код так:
//			if ((*baseGameArray)[nx % m_Size][ny % m_Size])
//				++count;
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
			if (nextGameArray->operator[](x).operator[](y))
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
	// лучше так - пон€тнее
	m_GameOver = 
		nextGenList.size() == 0 ||
		nextGenList == currentGenList;
}

