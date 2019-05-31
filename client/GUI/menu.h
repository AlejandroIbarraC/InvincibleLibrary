#ifndef MENU_H
#define MENU_H

#include <QDebug>
#include <QDragEnterEvent>
#include <QFileDialog>
#include <QFileInfo>
#include <QGraphicsOpacityEffect>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QMimeData>
#include <QPropertyAnimation>
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

protected:
    void dragEnterEvent(QDragEnterEvent *e);
    void dragLeaveEvent(QDragLeaveEvent *e);
    void dropEvent(QDropEvent *e);

private slots:
    void deleteBackground();
    void on_addButton_clicked();
    void on_enterButton_clicked();

private:
    Ui::Menu *ui;
    QTimer* deletionTimer;
    bool hasEntered = false;
    QGraphicsScene* scene;

    void initializeGrid();

};

#endif // MENU_H
