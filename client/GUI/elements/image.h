#ifndef IMAGE_H
#define IMAGE_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class Image : public QObject, public QGraphicsRectItem {
    Q_OBJECT
    Q_PROPERTY(QRect geometry READ geometry WRITE setGeometry)

public:
    Image(QObject* parent = nullptr);
    QRect geometry() const;
    int getID();
    QString getName();
    QPixmap* getPixmap();
    void setGeometry(const QRect &value);
    void setID(int nID);
    void setName(QString nName);
    void setPixmap(QPixmap* nPixmap);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);

private:
    int id;
    QString name;
    QPixmap* pixmap;
    QRect rect;

};

#endif // IMAGE_H
