#include "image.h"

Image::Image(QObject* parent) : QObject (parent) {

}

QRectF Image::boundingRect() const {
    return QRectF(rect);
}

QRect Image::geometry() const {
    return rect;
}

void Image::mousePressEvent(QGraphicsSceneMouseEvent *event) {

}

void Image::setGeometry(const QRect &value) {
    if (rect!=value) {
        rect = value;
        update();
    }
}
