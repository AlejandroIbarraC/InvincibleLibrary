#include "image.h"

#include "../menu.h"

Image::Image(QObject* parent) : QObject (parent) {
    pixmap = new QPixmap();
}

QRect Image::geometry() const {
    return rect;
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
        menu->raiseImage(this);
        this->setBrush(Qt::yellow);
}

void Image::setGeometry(const QRect &value) {
    if (rect!=value) {
        rect = value;
        update();
    }
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
