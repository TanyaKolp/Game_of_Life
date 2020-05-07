#include "gamearray.h"

using namespace std;

// A.K. Неинициализированные переменные - зло
// Все переменные - члены класса, не имеющие конструкторов по умолчанию, должны
// быть инициализированы, хоть компилятор этого и не требует.
// Если такая переменная не инициализирована, то в ней в release-сборке будет мусор.
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
	// A.K. выделенная память все-таки полностью не освобождалась
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
    // A.K. В этом коде есть некая странность       +
	// С одной стороны, данная функция возвращает перечень точек
	// с другой стороны - записывает, сколько их.
	// Логика подсказывает, что подсчет количества точек следует делать там,
    // где эти самые точки устанавливаются, а данная функция должна стать  +
	// константной.
	
    QList<QPoint>* p = new QList<QPoint>;
    for (int x = 0;  x < m_Size;  x++)
        for (int y = 0;  y < m_Size;  y++)
        {
/*
			bool cell = (*baseGameArray)[x][y];
            if (cell)
                p.push_back(QPoint(x,y));
*/
			// A.K. лучше так - быстрее и меньше памяти расходуется
			if ((*baseGameArray)[x][y])
                p->push_back(QPoint(x,y));
        }
	
// +   m_CellAmount = p->size();	// A.K. данному коду здесь не место, он должен быть в computeNextGeneration
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

	
    // A.K. Лучше написать так; насколько я понимаю - то же самое       +
	// если я правильно понял твой код - написана простая инверсия
//	(*baseGameArray)[cell.x()][cell.y()] = !(*baseGameArray)[cell.x()][cell.y()];

    //TK. да, была простая инверсия. но здесь была еще ошибка согласованности данных.

    emit modelChanged();
}

void GameArray::changeGeneration()
{
    delete baseGameArray;
    baseGameArray = nextGameArray;
	
	// A.K. если так не сделать, будут проблемы при уничтожении данных в деструкторе
	// Если не будет очистки памяти в деструкторе, будет утечка.
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
    // A.K. Данный кусок кода можно написать одним выражением   +
	return 
		neighbourCount == 3 || 
		((*baseGameArray)[x][y] && neighbourCount == 2);
}

int GameArray::countNeighbours(int x, int y)
{
    int count = 0;
	
	// A.K. Здесь это не принципиально, ибо цикл короткий, но условие конца 
	// цикла for вычисляется на каждой итерации заново. Поэтому, если 
	// уcловие конца заведомо не изменяется в ходе работы цикла, то лучше
	// вычислить условие один раз и сложить его в отдельную переменную
    // (int xLast - x + 1, yLast = y + 1)

    //+ТК. ясно
    int xLast = x + 1;
    int yLast = y + 1;
    for (int nx = x - 1;  nx <= xLast;  nx++)
        for (int ny = y - 1;  ny <= yLast;  ny++)
		{
            if (nx == x && ny == y)
                continue;
			// A.K. Код мне непонятен
			// когда такое написано, лучше комментировать, зачем так написано

                    /* TK. как принято писать комментарии в команде?
                     * например, строго на английском, описавать методы (параметры, ограничения) и тд
                    */
			// Дело в том, что (n + s) % s == n % s, разве нет?

                /*TK. -5 % 10 = -5
                       5 % 10 =  5
                 а мне нужно положительное цисло для индекса, поэтому прибавляю size
                    (-5 + 10) % 10 = 5
                     (5 + 10) % 10 = 5

                  хотя можно было просто взять модуль , что сработает быстрее не знаю
                */

			// Если я правильно понял, ты написала зацикленность игрового поля в
            // обоих направлениях

                    //TK. да , правильно

            // расчет индексов соседей с учетом зацикленности игрового поля
            if ((*baseGameArray)[(nx+m_Size)%m_Size][(ny+m_Size)%m_Size])
                count++;
			
			// A.K. Я бы написал данный код так:
//			if ((*baseGameArray)[nx % m_Size][ny % m_Size])
//				++count;
                   /* TK.
                   по поводу скобок {} в if for...(ставить, не ставить) сразу вспоминаются страшилки
                       https://ru.stackoverflow.com/a/424135

                   наверно, ваша команда привыкла,  поначалу буду ставить - привычка очень сильна ))
                   (к тому же IDE сама ставит).
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
	// лучше так - понятнее
	m_GameOver = 
		nextGenList.size() == 0 ||
		nextGenList == currentGenList;
}

