#include "menu.h"
#include "ui_menu.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>

using namespace  std;
Menu::Menu(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::Menu)
{
    // Initalize default parameters
    ui->setupUi(this);
    setAcceptDrops(true);
    ui->mainLogo->setGeometry(QRect(450, 100, 200, 200));
    ui->welcomeLabel->setVisible(false);
    ui->copyBackground->setVisible(false);
    ui->dropIcon->setVisible(false);
    ui->dropLabel->setVisible(false);
    imageList = new QList<Image*>();

    // Set scene
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 850, 450);
    ui->imageView->setScene(scene);

    // Bring initial elements to front
    ui->invincibleLabel->raise();
    ui->enterButton->raise();
    ui->mainLogo->raise();

    // Button hover watchers
    ButtonHoverWatcher* addWatcher = new ButtonHoverWatcher(this, ":/main/buttons/buttons/addButton.png",":/main/buttons/buttons/addButton_hovered.png");
    ButtonHoverWatcher* enterWatcher = new ButtonHoverWatcher(this, ":/main/buttons/buttons/enterButton.png",":/main/buttons/buttons/enterButton_hovered.png");
    ui->addButton->installEventFilter(addWatcher);
    ui->enterButton->installEventFilter(enterWatcher);

    // Animation timers
    deletionTimer = new QTimer(this);
    deletionTimer->setInterval(1000);
    connect(deletionTimer, SIGNAL(timeout()), this, SLOT(deleteBackground()));
}

Menu::~Menu()
{
    delete ui;
}

//! Adds image to grid.
void Menu::addToGrid(QUrl url) {
    QImage image(url.path());

    // Create pixmap and scale it
    QPixmap* pixmap = new QPixmap();
    //pixmap.convertFromImage(image);
    pixmap = stringToPixmap(pictureToString(image));
    QPixmap rPix = pixmap->scaled(53, 40);

    // Assign pixmap to image
    Image* currentImage = imageList->at(gridCount);
    currentImage->setVisible(true);
    currentImage->setPixmap(pixmap);
    currentImage->setBrush(rPix);
    gridCount++;
}

//! Deletes background. Executed by timer when entering app.
void Menu::deleteBackground() {
    ui->invincibleLabel->lower();
    deletionTimer->stop();
    hasEntered = true;

    // Fade in welcome label
    QGraphicsOpacityEffect *fade = new QGraphicsOpacityEffect(this);
    ui->welcomeLabel->setVisible(true);
    ui->welcomeLabel->setGraphicsEffect(fade);
    QPropertyAnimation *fadeOut = new QPropertyAnimation(fade,"opacity");
    fadeOut->setDuration(1000);
    fadeOut->setStartValue(0);
    fadeOut->setEndValue(1);
    fadeOut->start(QPropertyAnimation::DeleteWhenStopped);
}

//! Executes while dragging file to window
void Menu::dragEnterEvent(QDragEnterEvent* e) {
    if(hasEntered) {
        if (e->mimeData()->hasUrls()) {
            e->acceptProposedAction();
        }
        ui->copyBackground->raise();
        ui->dropIcon->raise();
        ui->dropLabel->raise();
        ui->copyBackground->setVisible(true);
        ui->dropIcon->setVisible(true);
        ui->dropLabel->setVisible(true);
    }
}

//! Executes while leaving drag area of window
void Menu::dragLeaveEvent(QDragLeaveEvent* e) {
    if (hasEntered) {
        ui->copyBackground->setVisible(false);
        ui->dropIcon->setVisible(false);
        ui->dropLabel->setVisible(false);
    }
}


//! Executes when dropping file in window
void Menu::dropEvent(QDropEvent* e) {
    if (hasEntered) {
        // Define accepted image types
        QStringList accepted_types;
        accepted_types << "jpeg" << "jpg" << "png" << "heif" << "bmp";
        foreach(const QUrl& url, e->mimeData()->urls()) {
            QString fileName = url.toLocalFile();
            QFileInfo info(fileName);
            if (info.exists()) {
                if (accepted_types.contains(info.suffix().trimmed(), Qt::CaseInsensitive)) {
                    addToGrid(url);
                }
            }
        }

        // Reset drop background elements
        ui->copyBackground->setVisible(false);
        ui->dropIcon->setVisible(false);
        ui->dropLabel->setVisible(false);
        ui->copyBackground->lower();
        ui->dropIcon->lower();
        ui->dropLabel->lower();
    }
}

//! Initializes empty image grid
void Menu::initializeGrid() {
    int gridColumns = 12;
    int gridRows = 9;
    int x = 20;
    int y = 20;
    int id = 0;

    for (int i = 0; i < gridRows; i++) {
        for (int i = 0; i < gridColumns; i++) {
            Image* image = new Image();
            image->setRect(x, y, imgDimX, imgDimY);
            image->setBrush(QBrush(Qt::red));
            image->setID(id);
            image->setVisible(false);
            scene->addItem(image);
            x += 80;
            imageList->append(image);
            id++;
        }
        x = 20;
        y += 60;
    }
}

void Menu::on_addButton_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Select Image"), "/home/jana", tr("Image Files (*.jpeg *.jpg *.png *.heif *.bmp)"));
    qDebug() << fileName;
}

void Menu::on_enterButton_clicked() {
    // Fade out window
    QGraphicsOpacityEffect *fade = new QGraphicsOpacityEffect(this);
    ui->invincibleLabel->setGraphicsEffect(fade);
    QPropertyAnimation *fadeOut = new QPropertyAnimation(fade,"opacity");
    fadeOut->setDuration(1000);
    fadeOut->setStartValue(1);
    fadeOut->setEndValue(0);
    fadeOut->start(QPropertyAnimation::DeleteWhenStopped);

    // Move logo to top left
    QLabel* logo = ui->mainLogo;
    QPropertyAnimation *moveLogo = new QPropertyAnimation(logo, "geometry");
    moveLogo->setDuration(1000);
    moveLogo->setStartValue(QRect(380, 100, 200, 200));
    moveLogo->setEndValue(QRect(20, 20, 100, 100));
    moveLogo->start();

    // Delete background and button
    deletionTimer->start();
    ui->enterButton->deleteLater();

    // Initalize image grid
    initializeGrid();
}


//! Encodes photo in Base64 QString
QString Menu::pictureToString(QImage image) {
    // Initialize buffer to store image
    QByteArray byteArray;
    QBuffer buffer(&byteArray);

    // Save image and encode it in Base64
    image.save(&buffer, "PNG");
    QString iconBase64 = QString::fromLatin1(byteArray.toBase64().data());

    return iconBase64;
}

QPixmap* Menu::stringToPixmap(QString base64Image) {
    QByteArray byteImage = base64Image.toLatin1();
    QPixmap* pixmap = new QPixmap();
    pixmap->loadFromData(QByteArray::fromBase64(byteImage));
    return pixmap;
}
