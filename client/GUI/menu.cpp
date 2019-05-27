#include "menu.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::Menu)
{
    ui->setupUi(this);
    ui->background->setStyleSheet("QLabel { background-color : red; color : white; }");
}

Menu::~Menu()
{
    delete ui;
}
