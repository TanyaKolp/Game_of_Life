#ifndef GAMEARRAY_H
#define GAMEARRAY_H

#include <QList>
#include <QPoint>
#include <vector>


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
    int				countNeighbors(int x, int y);
    void			checkGameOverConditions();
};

#endif // GAMEARRAY_H
