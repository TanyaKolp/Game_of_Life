#ifndef GAMEARRAY_H
#define GAMEARRAY_H	// A.K. - перенесено

// A.K. 
// 1) Свои include следует ставить после системных
// 2) cледует следить за дублированием include'ов (<vector> сдублирован)
// 3) мы в своих исходниках ставим сначала файлы Qt, затем файлы STL, 
//    затем файлы CRT (системные библиотеки C/C++), а затем уже свои файлы

// A.K. было
//#include "game.h"
//#include <vector>
//#include <QList>
//#include <vector>	

// A.K. так надо
#include <QList>
#include <vector>
#include "game.h"

// A.K. Страж включения ставится строго сверху; для отклонения от этого правила
// нужны веские основания.
// В данном случае компилятор нагружается дополнительной работой по повторному
// включению системных include'ов <vector>, <QList>, <QPoint>
//#define GAMEARRAY_H	// A.K. - убрано

// A.K. Ставить "using namespace std" в h-файлах - порочная практика
// Дело в том, что во всех файлах, куда будет включен gamearray.h,
// появится неявное подключение области имен std. Разработчик, который
// будет использовать данный файл в качестве подключаемого будет зело удивлен
// Как надо: using namespace std ставится в cpp-файле, а в h-файле пространство
// имен следует указывать явно
//using namespace std;	


// A.K. имена функций лучше выравнивать, повышая тем самым читаемость кода
class GameArray : public Game
{
public:
    GameArray(int sizeValue);

    // Game interface
public:
    void			clearGame();
    QList<QPoint>	computeNextGeneration();
    int				getCurrentGenerationNumber() const;
    int				getAliveCellAmount();
    QList<QPoint>	getAliveCellList();
    void			addOrDeleteAliveCell(QPoint cell);
    int				getGridSize();
    bool			isGameOver();
	
    // GameArray interface
private:
	
	// A.K. синтаксически, это правильно, но лучше в таких конструкциях 
	// использовать typedef'ы
//    vector< vector<bool> >* baseGameArray;
//    vector< vector<bool> >* nextGameArray;
	
	// новый код
	typedef std::vector<bool> TBoolVector;
	typedef std::vector<TBoolVector> TArrayData;
	TArrayData*		baseGameArray;
	TArrayData*		nextGameArray;
	
	// A.K. Синтаксически все правильно. Но, при выборе имен переменных,
	// лучше использовать суффиксы/префиксы для private-переменных членов
	// класса. Для public-членов, напротив, префиксы и суффиксы лучше не
	// использовать.
	// Мы используем префикс m_, а имена после подчеркивания пишем с
	// большой буквы
    int				size;				// m_Size
    int				cellAmount;			// m_CellAmount;
    int				generationNumber;	// m_GenerationNumber
    bool			gameOver;			// m_GameOver

    void			changeGeneration();
    bool			willSurvive(int x, int y);
    int				countNeighbors(int x, int y);
    void			checkGameOverConditions();
};

#endif // GAMEARRAY_H
