#ifndef IMAGE_H
#define IMAGE_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class Image : public QObject, public QGraphicsRectItem {
    Q_OBJECT
    Q_PROPERTY(QRect geometry READ geometry WRITE setGeometry)

public:
    Image(QObject* parent = nullptr);
    QRectF boundingRect() const;
    QRect geometry() const;
    int getID();
    QPixmap* getPixmap();
    void setGeometry(const QRect &value);
    void setID(int nID);
    void setPixmap(QPixmap* nPixmap);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);

private:
    int id;
    QPixmap* pixmap;
    QRect rect;

};

#endif // IMAGE_H
