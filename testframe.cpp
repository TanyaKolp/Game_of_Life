#include <QPainter>
#include <QDebug>
#include "testframe.h"

// A.K. ������� �������� ���� ����� ��������� include ������� ���� �����
//#include <QPainter>
//#include <QDebug>

/*	// A.K. ���, ������� �� ������������, ������� ��������������
TestFrame::TestFrame(QWidget *parent) : QFrame(parent)
{
    setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    setFixedSize(320,320);
}

void TestFrame::paintEvent(QPaintEvent* e)
{
    QFrame::paintEvent(e);
    qDebug()<<"in paint";
    QPainter p(this);
    p.setBrush(Qt::CrossPattern);
    p.drawRect(QRect(0,0,this->width(),this->height()));
}
*/
