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

string Picture::getYear() const {
    return year;
}

void Picture::setYear(string year) {
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

const string &Picture::getDescription() const {
    return description;
}

void Picture::setDescription(const string &description) {
    Picture::description = description;
}

//! Serializes a picture to a json object
//! \return json with the serialized picture
string Picture::serialize() {
    QJsonObject jsonObject;
    jsonObject["name"] = QString::fromStdString(name);
    jsonObject["author"] = QString::fromStdString(author);
    jsonObject["year"] = QString::fromStdString(year);
    jsonObject["pictureData"] = QString::fromStdString(pictureData);
    jsonObject["size"] = size;
    jsonObject["id"] = id;
    jsonObject["description"] = QString::fromStdString(description);
    QJsonDocument jsonDocument(jsonObject);
    QByteArray byteArray = jsonDocument.toJson();
    QString qString = QString(byteArray);
    string json = qString.toStdString();
    return json;
}

//! Deserilizes a picture from a json object
//! \param jsonObject containing the picture to be deserialized
void Picture::deserialize(QJsonObject jsonObject) {
    name = (jsonObject["name"].toString().toUtf8().constData());
    author = (jsonObject["author"].toString().toUtf8().constData());
    year = jsonObject["year"].toString().toUtf8().constData();
    pictureData = (jsonObject["pictureData"].toString().toUtf8().constData());
    size = jsonObject["size"].toInt();
    id = jsonObject["id"].toInt();
    description = jsonObject["description"].toString().toUtf8().constData();
}