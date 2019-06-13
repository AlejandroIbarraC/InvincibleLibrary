//
// Created by kevin on 12/06/19.
//

#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>
#include "Picture.h"

const string &Picture::getName() const {
    return name;
}

void Picture::setName(const string &name) {
    Picture::name = name;
}

const string &Picture::getAuthor() const {
    return author;
}

void Picture::setAuthor(const string &author) {
    Picture::author = author;
}

int Picture::getYear() const {
    return year;
}

void Picture::setYear(int year) {
    Picture::year = year;
}

int Picture::getSize() const {
    return size;
}

void Picture::setSize(int size) {
    Picture::size = size;
}

const string &Picture::getPictureData() const {
    return pictureData;
}

void Picture::setPictureData(const string &pictureData) {
    Picture::pictureData = pictureData;
}

int Picture::getId() const {
    return id;
}

void Picture::setId(int id) {
    Picture::id = id;
}

string Picture::serialize() {
    QJsonObject jsonObject;
    jsonObject["name"] = QString::fromStdString(name);
    jsonObject["author"] = QString::fromStdString(author);
    jsonObject["year"] = year;
    jsonObject["pictureData"] = QString::fromStdString(pictureData);
    jsonObject["size"] = size;
    jsonObject["id"] = id;
    QJsonDocument jsonDocument(jsonObject);
    QByteArray byteArray = jsonDocument.toJson();
    QString qString = QString(byteArray);
    string json = qString.toStdString();
    return json;
}

void Picture::deserialize(string jsonPicture) {
    QJsonDocument jsonDocument = QJsonDocument::fromJson(QByteArray(jsonPicture.c_str()));
    QJsonObject jsonObject = jsonDocument.object();
    name = (jsonObject["name"].toString().toUtf8().constData());
    author = (jsonObject["author"].toString().toUtf8().constData());
    year = jsonDocument["year"].toInt();
    pictureData = (jsonObject["pictureData"].toString().toUtf8().constData());
    size = jsonDocument["size"].toInt();
    id = jsonObject["id"].toInt();
}