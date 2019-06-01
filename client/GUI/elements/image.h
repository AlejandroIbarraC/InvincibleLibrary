#ifndef IMAGE_H
#define IMAGE_H

#include <QGraphicsRectItem>


class Image : public QObject, public QGraphicsRectItem {
    Q_OBJECT
    Q_PROPERTY(QRect geometry READ geometry WRITE setGeometry)

public:
    Image(QObject* parent = nullptr);
    QRectF boundingRect() const;
    QRect geometry() const;
    void setGeometry(const QRect &value);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);

private:
    QRect rect;

};

#endif // IMAGE_H
