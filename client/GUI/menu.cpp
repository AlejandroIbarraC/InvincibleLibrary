#include "menu.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::Menu)
{
    // Initalize default parameters
    ui->setupUi(this);
    setAcceptDrops(true);

    // Button hover watchers
    ButtonHoverWatcher* addWatcher = new ButtonHoverWatcher(this, ":/main/buttons/buttons/addButton.png",":/main/buttons/buttons/addButton_hovered.png");
    ui->addButton->installEventFilter(addWatcher);
}

Menu::~Menu()
{
    delete ui;
}

//! Executes while dragging file to window
void Menu::dragEnterEvent(QDragEnterEvent* e) {
    if (e->mimeData()->hasUrls()) {
        e->acceptProposedAction();
    }
}

//! Executes when dropping file in window
void Menu::dropEvent(QDropEvent* e) {
    QStringList accepted_types;
    accepted_types << "jpeg" << "jpg" << "png" << "heif" << "bmp";
    foreach(const QUrl & url, e->mimeData()->urls()) {
        QString fileName = url.toLocalFile();
        QFileInfo info(fileName);
        if (info.exists()) {
            if (accepted_types.contains(info.suffix().trimmed(), Qt::CaseInsensitive))
                qDebug() << fileName;
        }
    }
}

void Menu::on_addButton_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "/home/jana", tr("Image Files (*.jpeg *.jpg *.png *.heif *.bmp)"));
    qDebug() << fileName;
}
