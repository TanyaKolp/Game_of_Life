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
#include <QPoint>
#include <vector>

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
class GameArray
{
public:
    GameArray(int sizeValue);

    // Game interface
public:
    QList<QPoint>	computeNextGeneration();
    int				getCurrentGenerationNumber() const;
    int				getAliveCellAmount() const;
    QList<QPoint>	getAliveCellList();
    void			addOrDeleteAliveCell(QPoint cell);
    int				getGridSize() const;
    bool			isGameOver() const;
	
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
    int				m_Size;				// m_Size
    int				m_CellAmount;		// m_CellAmount;
    int				m_GenerationNumber;	// m_GenerationNumber
    bool			m_GameOver;			// m_GameOver

    void			changeGeneration();
    bool			willSurvive(int x, int y);
    int				countNeighbors(int x, int y);
    void			checkGameOverConditions();
};

#endif // GAMEARRAY_H
