
#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <iostream>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);




    MainWindow w;
    w.show();

//#ifdef BORNAGAIN_CRASHHANDLER
//    std::cout << "BORNAGAIN_CRASHHANDLER" << std::endl;
//    StackTraceSetup s;
//#endif

//    QVector<double> vector;
//    double d = vector[0]+0.1;
//    qDebug() << "main double:" << d;


//    return a.exec();

    const int r = a.exec();

    return r;
}
