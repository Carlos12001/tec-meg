#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtGui>
#include <QtWidgets>
#include <string.h>
#include <random>
#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <QMessageBox>
#include <QFrame>
#include <QString>
#include <QHash>
#include <QVector>


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    cout << "Initialize MainWindow" << endl;
    connect(timer, SIGNAL(timeout()), this,
            SLOT(updateState()));

    int numberCards = 10 + receiveSizeMatrix();
    unCompleteCouple = numberCards/2;
    createButtonCards(numberCards);
    initGame();
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::initGame() {
    inGame = false;

    //Player 1
    pointsPlayer1 = 0;
    ui->labelPointsP1->setText(QString::fromStdString("Points Player 1: ") + QString::number(pointsPlayer1 * 100));

    time.setHMS(0, 5, 0);
    ui->labelTimer->setText(time.toString("m::ss"));
    timer->start(1000);
}


void MainWindow::updateState() {
    updateTimer();
    defineFinalResult();
}

void MainWindow::updateTimer() {
    time = time.addSecs(-1);
    ui->labelTimer->setText(time.toString("m:ss"));
}

void MainWindow::defineFinalResult() {
    messageBox.setWindowTitle("Juego terminado");
    messageBox.setIcon(QMessageBox::Information);
    messageBox.setStandardButtons(QMessageBox::Yes);
    messageBox.addButton(QMessageBox::No);
    messageBox.setDefaultButton(QMessageBox::Yes);
    messageBox.setEscapeButton(QMessageBox::No);

    if (unCompleteCouple == 0){
        timer->stop();
        QString winnerName;
        QString winnerPoints;
        if(pointsPlayer2<pointsPlayer1){
            winnerName = "Player 1";
            winnerPoints = QString::number(pointsPlayer1 * 100);
        }
        else if (pointsPlayer2>pointsPlayer1){
            winnerName = "Player 2";
            winnerPoints = QString::number(pointsPlayer2 * 100);
        }
        else {
            winnerName = "Player 1 y Player 2";
            winnerPoints = QString::number(pointsPlayer2 * 100);
        }
        messageBox.setText("¡Ganaste " + winnerName +"! Puntaje final: " + winnerPoints );
        if (QMessageBox::Yes == messageBox.exec()) {
            QCoreApplication::quit();
        }
    }
    else{
        if (time.toString()=="00:00:00"){
            timer->stop();
            ui->frameMatriz->setEnabled(false);
            messageBox.setText("Perdieron ;(");
            if (QMessageBox::Yes == messageBox.exec()){
                QCoreApplication::quit();
            }
        }
    }
}


void MainWindow::showCard() {
    actualCard = qobject_cast<QPushButton*>(sender());
    showImage();
    actualCard->setEnabled(false);

    if (!inGame){
        previousCard = actualCard;
        inGame = true;
    }
    else{
        defineMiddleResult();
        hashCards.clear();
        inGame = false;
    }
}

void MainWindow::defineMiddleResult() {
    //check if there is a match (the current tile matches the previous tile in the turn)
    if (hashCards[actualCard->objectName()]==hashCards[previousCard->objectName()]){
        showPoints(15);
        unCompleteCouple--;

        //if there is a match, find out if all tiles have been matched.
        defineFinalResult();
    }
    else{
        showPoints(-5);
        changeTurn();
        ui->matrixGame->setEnabled(false);

        QTimer::singleShot(1000, this, SLOT(rebootCards()));
    }
}

void MainWindow::showImage() {
    QString cardName = actualCard->objectName();
    //Llama pide informacion al server
    sendIdCard(cardName.toStdString());
    //Recibe la informacion
    string image = receiveImage();
    hashCards[cardName] = QString::fromStdString(image);

    actualCard->setStyleSheet("#" +
                              cardName + "{\n"
                            + " border-image: url(:/images/" + QString::fromStdString(image) + ") 0 0 0 0 stretch stretch;\n"
                            + "}");
}

void MainWindow::rebootCards() {
    previousCard->setStyleSheet("#" + previousCard->objectName() + "{ }");
    actualCard->setStyleSheet("#" + actualCard->objectName() + "{ }");

    actualCard->setEnabled(true);
    previousCard->setEnabled(true);

    ui->matrixGame->setEnabled(true);
}

void MainWindow::createButtonCards(int numbOfButtons) {
    int sizeI = 10;
    int sizeJ = numbOfButtons/10;
    for (int i = 0; i < sizeI ; ++i) {
        for (int j = 0; j < sizeJ ; ++j) {
            QPushButton* button = new QPushButton();
            QString idButton = QString("cardI") + QString::number(i) + QString("J") + QString::number(j);
            button->setObjectName(idButton);
            button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
            // Set minimum size
            button->setMinimumSize(50, 30);
            ui->matrixGame->addWidget(button, i, j);
            hashButton[idButton] = button;
            connect(button, SIGNAL(clicked()), this,
                    SLOT(showCard()));
        }
    }
}

string MainWindow::receiveImage() {
    return "5.png";
}

void MainWindow::sendIdCard(string idCard) {
}

int MainWindow::receiveSizeMatrix() {
    return 0;
}

void MainWindow::changeTurn(){
    playerOne = !playerOne;
    if(playerOne){
        ui->labelPointsP1->setStyleSheet("#labelPointsP1{ \n color: rgb(255, 255, 255); \n background-color: rgb(38, 162, 105); \n }");
        ui->labelPointsP2->setStyleSheet("#labelPointsP2{ \n color: rgb(255, 255, 255); \n background-color: rgb(154, 153, 150); \n }");
    }
    else{
        ui->labelPointsP1->setStyleSheet("#labelPointsP1{ \n color: rgb(255, 255, 255); \n background-color: rgb(154, 153, 150); \n }");
        ui->labelPointsP2->setStyleSheet("#labelPointsP2{ \n color: rgb(255, 255, 255); \n background-color: rgb(38, 162, 105); \n }");
    }
}

void MainWindow::showPoints(int addPoints) {
    if(playerOne){
        pointsPlayer1 += addPoints;
    }else{
        pointsPlayer2 += addPoints;
    }
    ui->labelPointsP1->setText(QString::fromStdString("Points Player 1: ") + QString::number(pointsPlayer1*100));
    ui->labelPointsP2->setText(QString::fromStdString("Points Player 2: ") + QString::number(pointsPlayer2*100));
}

