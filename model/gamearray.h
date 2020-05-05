#ifndef GAMEARRAY_H
#define GAMEARRAY_H

#include <QList>
#include <QPoint>
#include <vector>


class GameArray
{
public:
    GameArray(int sizeValue);
	~GameArray();

    // Game interface
public:
    QList<QPoint>	computeNextGeneration();
	
	// �.�. �������� ������� ����� ������������� ����� � h-������
	// �������� ���������, �������, ���������� ������� �������� � h-�����,
	// ��������������� ��� �������������� (inline); ��� �������� �������, ���
	// �������, ��������� ������, ��� ��������, �� ������������ - ������ ������
	// ���������� ����������� ��� ���� �������
	int				getCurrentGenerationNumber() const	{ return m_GenerationNumber; }
	int				getAliveCellAmount() const			{ return m_CellAmount; }
	int				getGridSize() const					{ return m_Size; }
	bool			isGameOver() const					{ return m_GameOver; }
	
    QList<QPoint>	getAliveCellList();
    void			addOrDeleteAliveCell(const QPoint& cell);
	
    // GameArray interface
private:
	typedef std::vector<bool> TBoolVector;
	typedef std::vector<TBoolVector> TArrayData;
	TArrayData*		baseGameArray;
	TArrayData*		nextGameArray;
	
    int				m_Size;
    int				m_CellAmount;
    int				m_GenerationNumber;
    bool			m_GameOver;

    void			changeGeneration();
    bool			willSurvive(int x, int y);
    int				countNeighbours(int x, int y);
    void			checkGameOverConditions();
};

#endif // GAMEARRAY_H
