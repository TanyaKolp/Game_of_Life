#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>
#include <QString>
#include <QDebug>
#include <iostream>
#include <QLibraryInfo>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator appTranslator;
    QString locale = QLocale::system().name();
    qDebug()<< "locale = " << locale;
    bool localLoad = appTranslator.load(QLocale::system(), "game","_", ":/resources");
    qDebug() << "translation = " << localLoad;
    a.installTranslator(&appTranslator);

    MainWindow w;
    w.show();
    return a.exec();
}
