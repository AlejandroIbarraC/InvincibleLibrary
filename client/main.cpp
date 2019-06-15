#include <iostream>
#include "GUI/menu.h"
#include "logic/Picture.h"
#include "connection/Connect.h"
#include <QApplication>
#include <iostream>
#include <QTime>


int main(int argc, char *argv[]){

    Picture picture1 = Picture("Hooo", "Kevin", 1999, "qwertyuiop");
    //picture1.setId(0);
    //picture1.setSize(10);
    Picture picture2 = Picture("Ayer", "Nose", 111, "");
    picture2.setId(1);
    picture2.setSize(14);

    Connect* connect = Connect::getInstance();
    connect->updatePicture(&picture2);

    /*QApplication a(argc, argv);
    Menu w;
    w.show();
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    return a.exec();*/

    return 0;

}

