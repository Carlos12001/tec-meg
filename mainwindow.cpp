#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtWidgets>
#include <random>
#include <QMainWindow>
#include <QTimer>
#include <QMessageBox>
#include <QFrame>
#include <QString>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

/**
     * @brief It is the class constructor. He gets who the window is and sets it.
     * @param parent The window to run.
     */
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    cout << "Initialize MainWindow" << endl;
    connect(timer, SIGNAL(timeout()), this,
            SLOT(updateState()));


}

/**
     * @brief Destroy the object. Perform all the necessary steps to successfully close the program.
     */
MainWindow::~MainWindow(){
    sendIdCard("FINISH");
    delete ui;
}

/**
     * @brief The game starter. This initiates a lot of things between them are the connection of the client and the cards that the game.
     * @param numberPort The port's number where is located the server.
     */
void MainWindow::initGame(int numberPort) {
    connection.setPortNumber(numberPort);
    connection.initConnection();

    int numberCards = receiveInformation();
    unCompleteCouple = numberCards/2;
    createButtonCards(numberCards);


    inGame = false;

    //Player 1
    pointsPlayer1 = 0;
    ui->labelPointsP1->setText(QString::fromStdString("Points Player 1: ") + QString::number(pointsPlayer1));
    ui->labelPointsP1->setStyleSheet("#labelPointsP1{ \n color: rgb(255, 255, 255); \n background-color: rgb(38, 162, 105); \n }");

    //Player 2
    pointsPlayer1 = 0;
    ui->labelPointsP1->setText(QString::fromStdString("Points Player 2: ") + QString::number(pointsPlayer1));

    time.setHMS(0, 5, 0);
    ui->labelTimer->setText(time.toString("m::ss"));
    timer->start(1000);
}

/**
     * @brief Update game status. Update things related to time.
     */
void MainWindow::updateState() {
    updateTimer();
    defineFinalResult();
}

/**
     * @brief Update the weather. Update it in label.
     */
void MainWindow::updateTimer() {
    time = time.addSecs(-1);
    ui->labelTimer->setText(time.toString("m:ss"));
}

/**
     * @brief Define the end result. This performs the analysis if a final result is already possible.
     */
void MainWindow::defineFinalResult() {
    messageBox.setWindowTitle("Juego terminado");
    messageBox.setIcon(QMessageBox::Information);
    messageBox.setStandardButtons(QMessageBox::Yes);
    messageBox.addButton(QMessageBox::No);
    messageBox.setDefaultButton(QMessageBox::Yes);
    messageBox.setEscapeButton(QMessageBox::No);

    if (unCompleteCouple == 0){
        sendIdCard("FINISH");
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
    else if (time.toString()=="00:00:00"){
            sendIdCard("FINISH");
            timer->stop();
            ui->frameMatriz->setEnabled(false);
            messageBox.setText("Perdieron ;(");
            if (QMessageBox::Yes == messageBox.exec()){
                QCoreApplication::quit();
            }
        }
}

/**
     * @brief Check if the player's move was correct. It checks if the successful move
     */
void MainWindow::defineMiddleResult() {

    //check if there is a match (the current tile matches the previous tile in the turn)
    if (hashCards[actualCard->objectName()]==hashCards[previousCard->objectName()]){
        showPoints(15);
        unCompleteCouple--;

        //Extra Points if(extraPoints)

        //if there is a match, find out if all tiles have been matched.
        defineFinalResult();

        showInMemory();
        succesfull++;
        extraPoints();
    }
    else{
        showPoints(-5);
        changeTurn();
        ui->matrixGame->setEnabled(false);
        QTimer::singleShot(1000, this, SLOT(rebootCards()));
        succesfull = 0;
    }
    inMemory = false;
}

/**
     * @brief Check the card states. These states whether it is in the middle of the play or not.
     */
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

/**
    * @brief Shows the selected card. It asks the server for things and then sets them.
    */
void MainWindow::showImage() {
    QString cardName = actualCard->objectName();
    //Llama pide informacion al server
    sendIdCard(cardName.toStdString());
    //Recibe la informacion
    string image = receiveCard();
    hashCards[cardName] = QString::fromStdString(image);

    actualCard->setStyleSheet("#" +
                              cardName + "{\n"
                            + " border-image: url(:/images/" + QString::fromStdString(image) + ") 0 0 0 0 stretch stretch;\n"
                            + "}");
}

/**
     * @brief Turn over the cards. This is executed if the cards were not the same so that it erases its information and hides them again.
     */
void MainWindow::rebootCards() {
    previousCard->setStyleSheet("#" + previousCard->objectName() + "{ }");
    actualCard->setStyleSheet("#" + actualCard->objectName() + "{ }");

    actualCard->setEnabled(true);
    previousCard->setEnabled(true);

    ui->matrixGame->setEnabled(true);
}

/**
     * @brief Create the card buttons. This creates all the buttons that will be seen on the screen so that the user can press them.
     * @param numbOfButtons Number of buttons to create.
     */
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

/**
     * @brief Receive the button image. This method receives information about a card from the server.
     * @return Returns the image of the card.
     */
string MainWindow::receiveCard() {
    string data = connection.getMessage();
    json jsonCard;
    jsonCard= json::parse(data);
    string image = jsonCard["image"];
    inMemory = jsonCard["inMemory"] || inMemory;
    return image;
}

/**
     * @brief Request information from this letter. Send a request to the server about the letter you need.
     * @param idCard The ID of the card.
     */
void MainWindow::sendIdCard(string idCard) {
    json jsonIDCard;
    jsonIDCard = {{"id", idCard}};
    connection.sendMessage(jsonIDCard.dump(4));
    return;
}

/**
     * @brief Get the basic information from the server. This information is like the number of minimum cards.
     * @return The number of cards
     */
int MainWindow::receiveInformation() {
    string data = connection.getMessage();
    json jsonNumOfCards;
    jsonNumOfCards = json::parse(data);
    int numOfCards = jsonNumOfCards["numOfCards"];
    return numOfCards;
}

/**
     * @brief Shows the points of the players. It receives the new points and displays them.
     * @param addPoints The new points.
     */
void MainWindow::showPoints(int addPoints) {
    if(playerOne){
        pointsPlayer1 += addPoints;
    }else{
        pointsPlayer2 += addPoints;
    }
    ui->labelPointsP1->setText(QString::fromStdString("Points Player 1: ") + QString::number(pointsPlayer1*100));
    ui->labelPointsP2->setText(QString::fromStdString("Points Player 2: ") + QString::number(pointsPlayer2*100));
}

/**
     * @brief Change the color of the point labels.
     */
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

void MainWindow::showInMemory(){
    if(inMemory){
        showPoints(5);
        ui->labelInMemory->setText("In memory the last Cards Selected : Yes");
        ui->labelInMemory->setStyleSheet("#labelInMemory{ \n color: rgb(255, 255, 255); \n background-color: rgb(38, 162, 105); \n }");
    }else{
        ui->labelInMemory->setText("In memory the last Cards Selected : No");
        ui->labelInMemory->setStyleSheet("#labelInMemory{ \n color: rgb(255, 255, 255); \n background-color: rgb(246, 97, 81); \n }");
    }
}
void MainWindow::extraPoints(){
    string extraPointsTypes[] = {"None", "Double Points", "+100 Points", "-100 Points Opponent"};
    int choose = rand() % 4;
    showExtraPoints(extraPointsTypes[choose]);
}

void MainWindow::showExtraPoints(string type){
   if(type=="None"){
       ui->labelExtraPointsImage->setStyleSheet("#labelExtraPointsImage{\n border-image: url(:/images/extraPoints0.png) 0 0 0 0 stretch stretch;\n}");
       ui->labelExtraPointsName->setText("Last Event Type: None");
   }
   else if (type=="Double Points"){
       showPoints(15);
       ui->labelExtraPointsImage->setStyleSheet("#labelExtraPointsImage{\n border-image: url(:/images/extraPoints1.png) 0 0 0 0 stretch stretch;\n}");
       ui->labelExtraPointsName->setText("Last Event Type: Double Points");
   }
   else if (type=="+100 Points"){
       showPoints(1);
       ui->labelExtraPointsImage->setStyleSheet("#labelExtraPointsImage{\n border-image: url(:/images/extraPoints2.png) 0 0 0 0 stretch stretch;\n}");
       ui->labelExtraPointsName->setText("Last Event Type: +100 Points");
   }
   else if(type=="-100 Points Opponent"){
       playerOne = !playerOne;
       showPoints(1);
       playerOne = !playerOne;
       ui->labelExtraPointsImage->setStyleSheet("#labelExtraPointsImage{\n border-image: url(:/images/extraPoints3.png) 0 0 0 0 stretch stretch;\n}");
       ui->labelExtraPointsName->setText("Last Event Type: -100 Points Opponent");
   }
}