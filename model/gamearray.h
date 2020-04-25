#ifndef GAMEARRAY_H
#define GAMEARRAY_H	// A.K. - ����������

// A.K. 
// 1) ���� include ������� ������� ����� ���������
// 2) c������ ������� �� ������������� include'�� (<vector> �����������)
// 3) �� � ����� ���������� ������ ������� ����� Qt, ����� ����� STL, 
//    ����� ����� CRT (��������� ���������� C/C++), � ����� ��� ���� �����

// A.K. ����
//#include "game.h"
//#include <vector>
//#include <QList>
//#include <vector>	

// A.K. ��� ����
#include <QList>
#include <vector>
#include "game.h"

// A.K. ����� ��������� �������� ������ ������; ��� ���������� �� ����� �������
// ����� ������ ���������.
// � ������ ������ ���������� ����������� �������������� ������� �� ����������
// ��������� ��������� include'�� <vector>, <QList>, <QPoint>
//#define GAMEARRAY_H	// A.K. - ������

// A.K. ������� "using namespace std" � h-������ - �������� ��������
// ���� � ���, ��� �� ���� ������, ���� ����� ������� gamearray.h,
// �������� ������� ����������� ������� ���� std. �����������, �������
// ����� ������������ ������ ���� � �������� ������������� ����� ���� �������
// ��� ����: using namespace std �������� � cpp-�����, � � h-����� ������������
// ���� ������� ��������� ����
//using namespace std;	


// A.K. ����� ������� ����� �����������, ������� ��� ����� ���������� ����
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
	
	// A.K. �������������, ��� ���������, �� ����� � ����� ������������ 
	// ������������ typedef'�
//    vector< vector<bool> >* baseGameArray;
//    vector< vector<bool> >* nextGameArray;
	
	// ����� ���
	typedef std::vector<bool> TBoolVector;
	typedef std::vector<TBoolVector> TArrayData;
	TArrayData*		baseGameArray;
	TArrayData*		nextGameArray;
	
	// A.K. ������������� ��� ���������. ��, ��� ������ ���� ����������,
	// ����� ������������ ��������/�������� ��� private-���������� ������
	// ������. ��� public-������, ��������, �������� � �������� ����� ��
	// ������������.
	// �� ���������� ������� m_, � ����� ����� ������������� ����� �
	// ������� �����
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
