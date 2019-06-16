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
#include <QtWidgets/QLabel>

// Singleton initialization
Menu* Menu::menu = nullptr;

using namespace  std;
Menu::Menu(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::Menu) {
    // Initalize default parameters
    ui->setupUi(this);
    setAcceptDrops(true);
    ui->mainLogo->setGeometry(QRect(525, 100, 200, 200));
    ui->welcomeLabel->setVisible(false);
    ui->copyBackground->setVisible(false);
    ui->dropIcon->setVisible(false);
    ui->dropLabel->setVisible(false);
    ui->fillPromptLabel->setVisible(false);
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
    ButtonHoverWatcher* refreshWatcher = new ButtonHoverWatcher(this, ":/main/buttons/buttons/refreshButton.png",":/main/buttons/buttons/refreshButton_hovered.png");
    ui->addButton->installEventFilter(addWatcher);
    ui->enterButton->installEventFilter(enterWatcher);
    ui->refreshButton->installEventFilter(refreshWatcher);

    // Animation timers
    deletionTimer = new QTimer(this);
    deletionTimer->setInterval(1000);
    connect(deletionTimer, SIGNAL(timeout()), this, SLOT(deleteBackground()));
}

Menu::~Menu() {
    delete ui;
}

//! Adds image to grid.
void Menu::addToGrid(QImage image, QString name) {
    // Create pixmap and scale it
    QPixmap* pixmap = new QPixmap();
    pixmap->convertFromImage(image);
    QPixmap rPix = pixmap->scaled(53, 40);

    // Assign pixmap to image
    Image* currentImage = imageList->at(gridCount);
    currentImage->setVisible(true);
    currentImage->setPixmap(pixmap);
    currentImage->setBrush(rPix);
    currentImage->setName(name);
    gridCount++;
}

//! Adds image to server
void Menu::addToServer(QString name, QString author, QString date, QString pictureData) {
    // Connect to server
    Connect* connect = Connect::getInstance();

    // Create picture to send
    Picture* picture = new Picture();
    picture->setName(name.toStdString());
    picture->setAuthor(author.toStdString());
    picture->setYear(date.toInt());
    picture->setPictureData(pictureData.toStdString());

    // Insert in server
    connect->insertPicture(picture);
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
    ui->imageView->raise();
}

//! Deletes picture from server
void Menu::deletePicture(QString name) {
    // Connect to server
    Connect* connect = Connect::getInstance();

    // Find picture by name
    Picture* picture = new Picture();
    QList<Picture*> pictureList = connect->selectPictures();
    for (int i = 0; i < pictureList.length(); i++) {
        Picture* currentPicture = pictureList.at(i);
        if (QString::fromStdString(currentPicture->getName()) == name) {
            picture = currentPicture;
        }
    }
    connect->deletePicture(picture);
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
    QString emptyString = "";
    QString author = ui->authorEntry->displayText();
    QString date = ui->dateEntry->displayText();
    QString name = ui->nameEntry->displayText();
    if (author != emptyString && date != emptyString && name != emptyString){
        if (hasEntered) {
            // Define accepted image types
            QStringList accepted_types;
            accepted_types << "jpeg" << "jpg" << "png" << "heif" << "bmp";
            foreach(const QUrl& url, e->mimeData()->urls()) {
                QString fileName = url.toLocalFile();
                QFileInfo info(fileName);
                if (info.exists()) {
                    if (accepted_types.contains(info.suffix().trimmed(), Qt::CaseInsensitive)) {
                        QImage image(url.path());
                        addToGrid(image, name);
                        QString base64Image = pictureToString(image);
                        addToServer(name, author, date, base64Image);
                        ui->fillPromptLabel->setVisible(false);
                        ui->authorEntry->setText("");
                        ui->dateEntry->setText("");
                        ui->nameEntry->setText("");
                    }
                }
            }
        }
    } else {
        ui->fillPromptLabel->setVisible(true);
    }
    // Reset drop background elements
    ui->copyBackground->setVisible(false);
    ui->dropIcon->setVisible(false);
    ui->dropLabel->setVisible(false);
    ui->copyBackground->lower();
    ui->dropIcon->lower();
    ui->dropLabel->lower();
}

//! Initializes invisible empty image grid
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

QList<Image*>* Menu::getImageList() {
    return imageList;
}

Menu* Menu::getInstance() {
    return menu;
}

void Menu::on_addButton_clicked() {
    QString emptyString = "";
    QString author = ui->authorEntry->displayText();
    QString date = ui->dateEntry->displayText();
    QString name = ui->nameEntry->displayText();
    if (author != emptyString && date != emptyString && name != emptyString){
        // Selects image and adds it
        QUrl url = QFileDialog::getOpenFileName(this, tr("Select Image"), "/home/jana", tr("Image Files (*.jpeg *.jpg *.png *.heif *.bmp)"));
        QImage image(url.path());
        addToGrid(image, name);
        QString base64Image = pictureToString(image);
        addToServer(name, author, date, base64Image);
        ui->fillPromptLabel->setVisible(false);
        ui->authorEntry->setText("");
        ui->dateEntry->setText("");
        ui->nameEntry->setText("");
    }  else {
        ui->fillPromptLabel->setVisible(true);
    }
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

void Menu::on_refreshButton_clicked() {
    qDebug() << "refresh button clicked";
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

//! Raises image to make it bigger.
void Menu::raiseImage(Image* image) {
   QPixmap* imgPix = image->getPixmap();
   QPixmap scaledPix = imgPix->scaled(50, 50);
}

//! Decodes base64 encoded image to QPixmap
QPixmap* Menu::stringToPixmap(QString base64Image) {
    // Reads incoming string as QByteArray
    QByteArray byteImage = base64Image.toLatin1();

    // Convert QByteArray to QPixmap
    QPixmap* pixmap = new QPixmap();
    pixmap->loadFromData(QByteArray::fromBase64(byteImage));

    return pixmap;
}

//! Updates picture in server
void Menu::updatePicture(QString name) {
    // Connect to server
    Connect* connect = Connect::getInstance();

    // Find picture by name
    Picture* picture = new Picture();
    QList<Picture*> pictureList = connect->selectPictures();
    for (int i = 0; i < pictureList.length(); i++) {
        Picture* currentPicture = pictureList.at(i);
        if (QString::fromStdString(currentPicture->getName()) == name) {
            picture = currentPicture;
        }
    }

    // Update data from entries
    QString updatedName = ui->nameEntry->displayText();
    QString updatedAuthor = ui->authorEntry->displayText();
    QString updatedDate = ui->dateEntry->displayText();
    picture->setName(updatedName.toStdString());
    picture->setAuthor(updatedAuthor.toStdString());
    picture->setYear(updatedDate.toInt());

    // Send picture back to server
    connect->updatePicture(picture);
}

void Menu::setLabels(QString name) {
    Connect* connect = Connect::getInstance();
    QList<Picture*> pictureList = connect->selectPictures();
    for (int i = 0; i < pictureList.length(); i++) {
        if (QString::fromStdString(pictureList.at(i)->getName()) == name){

            ui->nameDisplay->setText(QString::fromStdString(pictureList.at(i)->getName()));

            ui->authorDisplay->setText(QString::fromStdString(pictureList.at(i)->getAuthor()));

            int year = pictureList.at(i)->getYear();
            QString date = QString::number(year);
            ui->dateDisplay->setText(date);

            ui->descriptionDisplay->setText(QString::fromStdString(pictureList.at(i)->getDescription()));

        }

    }
}