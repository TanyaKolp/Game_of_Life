#ifndef POPULATIONLABEL_H
#define POPULATIONLABEL_H

#include <QLabel>
#include <QWidget>

#include <model/gamearray.h>

/*
	A.K. Данный класс следует реализовывать по-другому
	Если я правильно понял, то данные из m_Model берутся актуальными
	в тот момент, когда надо перерисовывать данный PopulationLabel
	
	Надо заметить, что перерисовка будет производиться дважды, если
	тест метки изменился - сначала перерисовка, потому что сказал кто-то
	снаружи, а потом перерисовка, потому что изменился текст - это инициирует
	сам QLabel.
	
	Правильнее сделать GameArray потомком QObject, сделать там сигнал
	changed(), который будет появляться на свет, когда в данных что-то
	изменилось. Данный сигнал обрабатывать в неком месте, где отдается
	команда на перерисовку поля и там же назначать текст QLabel'у. 
	
	В такой архитектуре класс PopulationLabel становится не нужен.
	Вообще, класс QLabel наследуется крайне редко - он умеет отображать и
	картинки и html и простой текст.
	
	В paintEvent почти никогда не меняются данные класса. Если это все-таки
	требуется, надо смотреть, нет ли архитектурной ошибки.
*/

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
