#ifndef POPULATIONLABEL_H
#define POPULATIONLABEL_H

#include <QLabel>
#include <QWidget>

#include <model/game.h>

class PopulationLabel : public QLabel
{
    Q_OBJECT
public:
    explicit PopulationLabel(QWidget *parent = 0);

    void setModel(Game* modelValue);

signals:

private:
    Game* model;


    // QWidget interface
protected:
    void paintEvent(QPaintEvent *);
};

#endif // POPULATIONLABEL_H
