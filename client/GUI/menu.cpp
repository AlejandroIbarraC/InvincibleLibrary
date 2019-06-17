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
    ui->selectPromptLabel->setVisible(false);
    imageList = new QList<Image*>();

    // Set scene
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 890, 550);
    ui->imageView->setScene(scene);

    // Bring initial elements to front
    ui->invincibleLabel->raise();
    ui->enterButton->raise();
    ui->mainLogo->raise();

    // Button hover watchers
    ButtonHoverWatcher* addWatcher = new ButtonHoverWatcher(this, ":/main/buttons/buttons/addButton.png",":/main/buttons/buttons/addButton_hovered.png");
    ButtonHoverWatcher* editWatcher = new ButtonHoverWatcher(this, ":/main/buttons/buttons/editButton.png",":/main/buttons/buttons/editButton_hovered.png");
    ButtonHoverWatcher* enterWatcher = new ButtonHoverWatcher(this, ":/main/buttons/buttons/enterButton.png",":/main/buttons/buttons/enterButton_hovered.png");
    ButtonHoverWatcher* refreshWatcher = new ButtonHoverWatcher(this, ":/main/buttons/buttons/refreshButton.png",":/main/buttons/buttons/refreshButton_hovered.png");
    ButtonHoverWatcher* trashWatcher = new ButtonHoverWatcher(this, ":/main/buttons/buttons/trashButton.png",":/main/buttons/buttons/trashButton_hovered.png");
    ui->addButton->installEventFilter(addWatcher);
    ui->editButton->installEventFilter(editWatcher);
    ui->enterButton->installEventFilter(enterWatcher);
    ui->refreshButton->installEventFilter(refreshWatcher);
    ui->trashButton->installEventFilter(trashWatcher);

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
    QPixmap rPix = pixmap->scaled(imgDimX, imgDimY, Qt::KeepAspectRatioByExpanding);

    // Assign pixmap to image
    Image* currentImage = imageList->at(gridCount);
    currentImage->setBrush(rPix);
    currentImage->setVisible(true);
    currentImage->setPixmap(pixmap);
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
    picture->setYear(date.toStdString());
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
    int gridColumns = 5;
    int gridRows = 5;
    int x = 20;
    int y = 20;
    int id = 0;

    for (int i = 0; i < gridRows; i++) {
        for (int i = 0; i < gridColumns; i++) {
            Image* image = new Image();
            image->setRect(0, 0, imgDimX, imgDimY);
            image->setX(x);
            image->setY(y);
            image->setID(id);
            image->setVisible(false);
            image->setPen(Qt::NoPen);
            scene->addItem(image);
            x += 160;
            imageList->append(image);
            id++;
        }
        x = 20;
        y += 110;
    }
}

QList<Image*>* Menu::getImageList() {
    return imageList;
}

Menu* Menu::getInstance() {
    if (!menu) {
        menu = new Menu;
    }
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

void Menu::on_editButton_clicked() {
    QString nameToEdit = ui->nameDisplay->text();
    if (nameToEdit != "") {
        updatePicture(nameToEdit);
        ui->selectPromptLabel->setVisible(false);
    } else {
        ui->selectPromptLabel->setVisible(true);
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
    on_refreshButton_clicked();
}

void Menu::on_refreshButton_clicked() {
    updateGrid();
}

void Menu::on_trashButton_clicked() {
    QString nameToDelete = ui->nameDisplay->text();
    if (nameToDelete != "") {
        updatePicture(nameToDelete);
        ui->selectPromptLabel->setVisible(false);
    } else {
        ui->selectPromptLabel->setVisible(true);
    }
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

//! Sets info briefing labels in UI
void Menu::setLabels(QString name) {
    // Retrieve data from server
    Connect* connect = Connect::getInstance();
    QList<Picture*> pictureList = connect->selectPictures();

    // Search server data for selected image info
    for (int i = 0; i < pictureList.length(); i++) {
        if (QString::fromStdString(pictureList.at(i)->getName()) == name){
            // Update image info
            QString nameString = QString::fromStdString(pictureList.at(0)->getName());
            ui->nameDisplay->setText(nameString);
            ui->authorDisplay->setText(QString::fromStdString(pictureList.at(i)->getAuthor()));
            ui->dateDisplay->setText(QString::fromStdString(pictureList.at(i)->getYear()));
            ui->descriptionDisplay->setText(QString::fromStdString(pictureList.at(i)->getDescription()));

            // Update selected image preview
            QPixmap* pixmap = stringToPixmap(QString::fromStdString(pictureList.at(i)->getPictureData()));
            QPixmap rPix = pixmap->scaled(selImgX, selImgY, Qt::KeepAspectRatioByExpanding);
            ui->selectedImageLabel->setPixmap(rPix);
        }
    }
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

//! Updates whole grid
void Menu::updateGrid() {
    // Connect to server
    Connect* connect = Connect::getInstance();
    QList<Picture*> pictures = connect->selectPictures();
    gridCount = 0;

    // Disable all UI image squares
    for (int i = 0; i < imageList->length(); i++) {
        imageList->at(i)->setVisible(false);
    }

    // Update name and pixmap in UI
    for (int i = 0; i < pictures.length(); i++) {
        Picture* currentPicture = pictures.at(i);
        QPixmap* pixmap = stringToPixmap(QString::fromStdString(currentPicture->getPictureData()));
        QImage image (pixmap->toImage());
        addToGrid(image, QString::fromStdString(currentPicture->getName()));
    }
}

//! Updates picture in server
void Menu::updatePicture(QString name) {
    QString updatedName = ui->nameEntry->displayText();
    QString updatedAuthor = ui->authorEntry->displayText();
    QString updatedDate = ui->dateEntry->displayText();

    if (updatedAuthor != "" && updatedDate != "" && updatedName != "") {
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
        picture->setName(updatedName.toStdString());
        picture->setAuthor(updatedAuthor.toStdString());
        picture->setYear(updatedDate.toStdString());

        // Send picture back to server
        connect->updatePicture(picture);
        ui->fillPromptLabel->setVisible(false);
    } else {
        ui->fillPromptLabel->setVisible(true);
    }
}
