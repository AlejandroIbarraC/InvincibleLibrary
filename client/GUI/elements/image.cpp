#include "image.h"

#include "../menu.h"

Image::Image(QGraphicsRectItem* parent) : QGraphicsRectItem (parent) {
    // Initialize default attributes
    pixmap = new QPixmap();
    name = "";
}

int Image::getID() {
    return id;
}

QString Image::getName() {
    return name;
}

QPixmap* Image::getPixmap() {
    return pixmap;
}

void Image::mousePressEvent(QGraphicsSceneMouseEvent *event) {
        Menu* menu = Menu::getInstance();
        menu->setLabels(this->getName());
}

void Image::setID(int nID) {
    id = nID;
}

void Image::setName(QString nName) {
    name = nName;
}

void Image::setPixmap(QPixmap* nPixmap) {
    pixmap = nPixmap;
}
