//
// Created by kevin on 12/06/19.
//

#ifndef MYINVINCIBLELIBRARY_CONNECT_H
#define MYINVINCIBLELIBRARY_CONNECT_H


#include <QtGui/QList>
#include "../logic/Picture.h"

using namespace std;

class Connect{

public:

    static Connect* getInstance();

    const string &getIp() const;
    void setIp(const string &ip);

    void insertPicture(Picture* picture);
    void deletePicture(Picture* picture);
    void updatePicture(Picture* picture);
    QList<Picture*> selectPictures();

private:

    Connect() = default;
    Connect(Connect const&) = default;
    Connect& operator = (Connect const&) = default;

    static Connect* conector;

    string ip = "192.168.100.5";

};


#endif //MYINVINCIBLELIBRARY_CONNECT_H
