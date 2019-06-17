#ifndef IMAGE_H
#define IMAGE_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class Image :  public QGraphicsRectItem {

public:
    Image(QGraphicsRectItem* parent = nullptr);

    int getID();
    QString getName();
    QPixmap* getPixmap();
    void setID(int nID);
    void setName(QString nName);
    void setPixmap(QPixmap* nPixmap);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);

private:
    int id;
    QString name;
    QPixmap* pixmap;

};

#endif // IMAGE_H
