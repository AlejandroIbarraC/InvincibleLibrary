#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include <string>

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

private slots:

private:

    Ui::Menu *ui;

};

#endif // MENU_H
