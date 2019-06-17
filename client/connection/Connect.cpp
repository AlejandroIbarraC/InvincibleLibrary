//
// Created by kevin on 12/06/19.
//

#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtCore/QUrlQuery>
#include <cpr/cpr.h>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include "Connect.h"

Connect* Connect::conector = nullptr;

Connect* Connect::getInstance() {
    if (!conector){
        conector = new Connect();
    }
    return conector;
}

const string &Connect::getIp() const {
    return ip;
}

void Connect::setIp(const string &ip) {
    Connect::ip = ip;
}

//! Sends a picture to the server that will be inserted into the database
//! \param picture that will be inserted
void Connect::insertPicture(Picture* picture) {
    string json = picture->serialize();
    auto response = cpr::Post(cpr::Url {"http://" + ip + ":9080/MyInvincibleLibrary_war_exploded/library/insert"}, cpr::Body{json}, cpr::Header{{"Content-Type", "application/json"}});
}

//! Sends a picture that will be deleted from the database
//! \param picture that will be deleted
void Connect::deletePicture(Picture* picture) {
    string json = picture->serialize();
    auto response = cpr::Post(cpr::Url {"http://" + ip + ":9080/MyInvincibleLibrary_war_exploded/library/delete"}, cpr::Body{json}, cpr::Header{{"Content-Type", "application/json"}});
}

//! Sends a picture that will be updated in the database
//! \param picture that will be updated
void Connect::updatePicture(Picture* picture) {
    string json = picture->serialize();
    auto response = cpr::Post(cpr::Url {"http://" + ip + ":9080/MyInvincibleLibrary_war_exploded/library/update"}, cpr::Body{json}, cpr::Header{{"Content-Type", "application/json"}});
}

//! Receives all the pictures from the database
//! \return a list with the pictures
QList<Picture*> Connect::selectPictures() {
    auto response = cpr::Get(cpr::Url {"http://" + ip + ":9080/MyInvincibleLibrary_war_exploded/library/select/all"});
    string json = response.text;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QByteArray(json.c_str()));
    QJsonArray jsonArray = jsonDocument.array();
    QList<Picture*> pictureList;
    if (!jsonArray.empty()){
        for (int i = 0; i < jsonArray.size(); i++){
            QJsonObject node = jsonArray[i].toObject();
            Picture* tmp = new Picture();
            tmp->deserialize(node);
            pictureList.push_back(tmp);
        }
    }
    return pictureList;
}