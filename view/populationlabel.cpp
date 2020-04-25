#include "populationlabel.h"

PopulationLabel::PopulationLabel(QWidget *parent) : QLabel(parent)
{
    setText("Population: 0");
    adjustSize();
    setVisible(true);
}

void PopulationLabel::setModel(Game* modelValue)
{
    model = modelValue;
}


void PopulationLabel::paintEvent(QPaintEvent * e)
{
    QLabel::paintEvent(e);
    setText(QString("Population: %1\n# Generation: %2")
            .arg(model->getAliveCellAmount())
            .arg(model->getCurrentGenerationNumber()));
}
