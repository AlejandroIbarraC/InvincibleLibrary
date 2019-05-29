#ifndef MENU_H
#define MENU_H

#include <QDebug>
#include <QDragEnterEvent>
#include <QFileDialog>
#include <QFileInfo>
#include <QMainWindow>
#include <QMimeData>
#include <string>

#include "elements/buttonhoverwatcher.h"

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
    void dropEvent(QDropEvent *e);

private slots:
    void on_addButton_clicked();

private:

    Ui::Menu *ui;

};

#endif // MENU_H
