#ifndef MENU_H
#define MENU_H

#include <QBuffer>
#include <QDebug>
#include <QDragEnterEvent>
#include <QFileDialog>
#include <QFileInfo>
#include <QGraphicsOpacityEffect>
#include <QGraphicsScene>
#include <QImage>
#include <QList>
#include <QMainWindow>
#include <QMimeData>
#include <QParallelAnimationGroup>
#include <QPoint>
#include <QPropertyAnimation>
#include <QSizePolicy>
#include <QTimer>
#include <string>

#include "elements/buttonhoverwatcher.h"
#include "elements/image.h"

using namespace std;

namespace Ui {
    class Menu;
}

class Menu : public QMainWindow
{
Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();
    static Menu* getInstance();
    void raiseImage(int index);

protected:
    void dragEnterEvent(QDragEnterEvent *e);
    void dragLeaveEvent(QDragLeaveEvent *e);
    void dropEvent(QDropEvent *e);

private slots:
    void deleteBackground();
    void on_addButton_clicked();
    void on_enterButton_clicked();

private:
    Ui::Menu* ui;
    QTimer* deletionTimer;
    bool hasEntered = false;
    int gridCount = 0;
    int imgDimX  = 53;
    int imgDimY = 40;
    QList<Image*>* imageList;
    static Menu* menu;
    QGraphicsScene* scene;

    void addToGrid(QUrl url);
    void initializeGrid();
    QString pictureToString(QImage image);
    QPixmap* stringToPixmap(QString base64Image);

};

#endif // MENU_H
