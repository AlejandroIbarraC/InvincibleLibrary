#include <iostream>
#include "GUI/menu.h"
#include <QApplication>
#include <iostream>
#include <QTime>


int main(int argc, char *argv[]){

    QApplication a(argc, argv);
    Menu w;
    w.show();
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    return a.exec();

}

