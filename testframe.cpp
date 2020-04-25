#include <QPainter>
#include <QDebug>
#include "testframe.h"

// A.K. ѕравила хорошего тона вел€т системные include ставить выше своих
//#include <QPainter>
//#include <QDebug>

/*	// A.K.  од, который не используетс€, следует комментировать
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
