#ifndef IMAGE_H
#define IMAGE_H

#include <QGraphicsRectItem>


class Image : public QGraphicsRectItem {

public:
    Image(QGraphicsRectItem* parent = nullptr);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);

private:


};

#endif // IMAGE_H
