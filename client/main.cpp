#include <iostream>
#include "GUI/menu.h"
#include "logic/Picture.h"
#include "connection/Connect.h"
#include <QApplication>
#include <iostream>
#include <QTime>


int main(int argc, char *argv[]){

    QApplication a(argc, argv);
    Menu* menu = Menu::getInstance();
    menu->show();
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    return a.exec();

}

