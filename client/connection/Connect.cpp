//
// Created by kevin on 12/06/19.
//

#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include "Connect.h"

Connect* Connect::conector = nullptr;

/**
 * Singleton of the collector class.
 * @return the instance of the collector.
 */
Connect* Connect::getInstance() {
    if (!conector){
        conector = new Connect();
    }
    return conector;
}

const QString &Connect::getIp() const {
    return ip;
}

void Connect::setIp(const QString &ip) {
    Connect::ip = ip;
}

void Connect::insertPicture(Picture* picture) {
    QNetworkRequest qNetworkRequest = QNetworkRequest(QUrl("http://" + ip + ":9080/MyInvincibleLibrary_war_exploded/library/insert"));
    QNetworkAccessManager* qNetworkAccessManager = new QNetworkAccessManager(this);
    QNetworkReply* qNetworkReply = qNetworkAccessManager->get(qNetworkRequest);

    connect(qNetworkReply, &QNetworkReply::finished, [this, qNetworkReply](){
        qDebug() << sender();
        qDebug() << qNetworkReply->errorString();
        qDebug() << qNetworkReply->readAll();
        qNetworkReply->deleteLater();
    });
}

void Connect::deletePicture(Picture* picture) {
    QNetworkRequest qNetworkRequest = QNetworkRequest(QUrl("http://" + ip + ":9080/MyInvincibleLibrary_war_exploded/library/delete"));
    QNetworkAccessManager* qNetworkAccessManager = new QNetworkAccessManager(this);
    QNetworkReply* qNetworkReply = qNetworkAccessManager->get(qNetworkRequest);

    connect(qNetworkReply, &QNetworkReply::finished, [this, qNetworkReply](){
        qDebug() << sender();
        qDebug() << qNetworkReply->errorString();
        qDebug() << qNetworkReply->readAll();
        qNetworkReply->deleteLater();
    });
}

void Connect::updatePicture(Picture* picture) {
    QNetworkRequest qNetworkRequest = QNetworkRequest(QUrl("http://" + ip + ":9080/MyInvincibleLibrary_war_exploded/library/update"));
    QNetworkAccessManager* qNetworkAccessManager = new QNetworkAccessManager(this);
    QNetworkReply* qNetworkReply = qNetworkAccessManager->get(qNetworkRequest);

    connect(qNetworkReply, &QNetworkReply::finished, [this, qNetworkReply](){
        qDebug() << sender();
        qDebug() << qNetworkReply->errorString();
        qDebug() << qNetworkReply->readAll();
        qNetworkReply->deleteLater();
    });
}

QList<Picture>* Connect::selectPicture() {
    QNetworkRequest qNetworkRequest = QNetworkRequest(QUrl("http://" + ip + ":9080/MyInvincibleLibrary_war_exploded/library/select/all"));
    QNetworkAccessManager* qNetworkAccessManager = new QNetworkAccessManager(this);
    QNetworkReply* qNetworkReply = qNetworkAccessManager->get(qNetworkRequest);

    connect(qNetworkReply, &QNetworkReply::finished, [this, qNetworkReply](){
        qDebug() << sender();
        qDebug() << qNetworkReply->errorString();
        qDebug() << qNetworkReply->readAll();
        qNetworkReply->deleteLater();
    });
}