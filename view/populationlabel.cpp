#include "populationlabel.h"

PopulationLabel::PopulationLabel(QWidget *parent) : QLabel(parent)
{
    setText("Population: 0");
    adjustSize();
    setVisible(true);
}

void PopulationLabel::setModel(GameArray* modelValue)
{
    m_Model = modelValue;
}

void PopulationLabel::paintEvent(QPaintEvent * e)
{
    QLabel::paintEvent(e);
    setText(QString("Population: %1\n# Generation: %2")
            .arg(m_Model->getAliveCellAmount())
            .arg(m_Model->getCurrentGenerationNumber()));
}
