//
// Created by kevin on 12/06/19.
//

#ifndef MYINVINCIBLELIBRARY_CONNECT_H
#define MYINVINCIBLELIBRARY_CONNECT_H


#include <QtGui/QList>
#include "../logic/Picture.h"

using namespace std;

class Connect : public QObject{

    Q_OBJECT

public:

    static Connect* getInstance();

    const QString &getIp() const;
    void setIp(const QString &ip);

    void insertPicture(Picture* picture);
    void deletePicture(Picture* picture);
    void updatePicture(Picture* picture);
    QList<Picture>* selectPicture();

private:

    Connect() = default;
    Connect(Connect const&) = default;
    Connect& operator = (Connect const&) = default;

    static Connect* conector;

    QString ip = "192.168.100.5";

};


#endif //MYINVINCIBLELIBRARY_CONNECT_H
