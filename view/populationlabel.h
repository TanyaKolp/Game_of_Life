#ifndef POPULATIONLABEL_H
#define POPULATIONLABEL_H

#include <QLabel>
#include <QWidget>

#include <model/gamearray.h>

class PopulationLabel : public QLabel
{
    Q_OBJECT
public:
    explicit PopulationLabel(QWidget *parent = 0);

    void setModel(GameArray* modelValue);

signals:

private:
    GameArray* m_Model;


    // QWidget interface
protected:
    void paintEvent(QPaintEvent *);
};

#endif // POPULATIONLABEL_H
