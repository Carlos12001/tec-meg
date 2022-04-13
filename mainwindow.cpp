#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    cout << "Initialize MainWindow" << endl;
    connect(timer, SIGNAL(timeout()), this,
            SLOT(updateState()));
    vectorCards = {"cardI0J0","cardI0J1","cardI1J0","cardI1J1",
                   "cardI2J1","cardI3J0","cardI4J1","cardI5J0",
                   "cardI6J1","cardI7J0","cardI8J1","cardI9J0"};

    scopeEventClick();

    initGame();
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::initGame() {
    inGame = false;

    points = 0;
    ui->labelPointsP1->setText(QString::fromStdString("Points: ") + QString::number(points));

    unCompleteCouple = 6;

    time.setHMS(0, 1, 0);
    ui->labelTimer->setText(time.toString("m::ss"));

    timer->start(1000);

    mixCards();
    distributeCards();
}

void MainWindow::scopeEventClick() {
    connect(ui->cardI0J0, SIGNAL(clicked()), this,
            SLOT(showCard()));
    connect(ui->cardI0J1, SIGNAL(clicked()), this,
            SLOT(showCard()));
    connect(ui->cardI1J0, SIGNAL(clicked()), this,
            SLOT(showCard()));
    connect(ui->cardI1J1, SIGNAL(clicked()), this,
            SLOT(showCard()));
    connect(ui->cardI2J1, SIGNAL(clicked()), this,
            SLOT(showCard()));
    connect(ui->cardI3J0, SIGNAL(clicked()), this,
            SLOT(showCard()));
    connect(ui->cardI4J1, SIGNAL(clicked()), this,
            SLOT(showCard()));
    connect(ui->cardI5J0, SIGNAL(clicked()), this,
            SLOT(showCard()));
    connect(ui->cardI6J1, SIGNAL(clicked()), this,
            SLOT(showCard()));
    connect(ui->cardI7J0, SIGNAL(clicked()), this,
            SLOT(showCard()));
    connect(ui->cardI8J1, SIGNAL(clicked()), this,
            SLOT(showCard()));
    connect(ui->cardI9J0, SIGNAL(clicked()), this,
            SLOT(showCard()));
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
        inGame = false;
    }
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
        messageBox.setText("¡Ganaste! Puntaje final: " + QString::number(points*1000));
        if (QMessageBox::Yes == messageBox.exec()){
            QCoreApplication::quit();
        }
        else{
            QCoreApplication::quit();
        }
    }
    else{
        if (time.toString()=="00:00:00"){
            timer->stop();
            ui->frameMatriz->setEnabled(false);
            messageBox.setText("Perdiste ;(");
            if (QMessageBox::Yes == messageBox.exec()){
                QCoreApplication::quit();
            }
            else{
                QCoreApplication::quit();
            }
        }
    }
}

void MainWindow::mixCards() {
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(vectorCards.begin(), vectorCards.end(), default_random_engine(seed));


}

void MainWindow::distributeCards() {
    auto iterator=vectorCards.begin();
    for (int i=0; i<=5; i++){
        QString file_name= QString::number(i)+".png";
        hashCards[(*iterator)]=file_name;
        iterator++;
        hashCards[(*iterator)]=file_name;
        iterator++;
    }
}

void MainWindow::defineMiddleResult() {
    //check if there is a match (the current tile matches the previous tile in the turn)
    if (hashCards[actualCard->objectName()]==hashCards[previousCard->objectName()]){
        points+=15;
        ui->labelPointsP1->setText(QString::fromStdString("Points: ") + QString::number(points));
        unCompleteCouple--;

        //if there is a match, find out if all tiles have been matched.
        defineFinalResult();
    }
    else{
        points -= 5;
        ui->labelPointsP1->setText(QString::fromStdString("Points: ") + QString::number(points));

        ui->matrixGame->setEnabled(false);

        QTimer::singleShot(1000, this, SLOT(rebootCards()));
    }
}

void MainWindow::showImage() {
    QString cardName= actualCard->objectName();
    //Llama pide informacion al server
    //Recibe la informacion
    QString img = hashCards[cardName];
    actualCard->setStyleSheet("#" +
                              cardName + "{ background-image: url(:/images/" + img + ") }");
}

void MainWindow::rebootCards() {
    previousCard->setStyleSheet("#" + previousCard->objectName() + "{ }");
    actualCard->setStyleSheet("#" + actualCard->objectName() + "{ }");

    actualCard->setEnabled(true);
    previousCard->setEnabled(true);

    ui->matrixGame->setEnabled(true);
}

