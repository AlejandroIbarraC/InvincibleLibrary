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
    int getID();
    void setGeometry(const QRect &value);
    void setID(int nID);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);

private:
    int id;
    QRect rect;

};

#endif // IMAGE_H
