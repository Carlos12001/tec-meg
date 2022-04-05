#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    cout << "Initialize MainWindow" << endl;
    connect(timer, SIGNAL(timeout()), this,
            SLOT(updateState()));

    scopeEventClick();

    initGame();
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::initGame() {

}

void MainWindow::scopeEventClick() {
//    connect(ui->cardI0J0, SIGNAL(clicked()), this,
//            SLOT(showCard(ui->cardI0J0)));
//    connect(ui->cardI0J1, SIGNAL(clicked()), this,
//            SLOT(tarjetaDescubierta(ui->cardI0J1)));
//    connect(ui->cardI1J0, SIGNAL(clicked()), this,
//            SLOT(showCard(ui->cardI1J0)));
//    connect(ui->cardI1J1, SIGNAL(clicked()), this,
//            SLOT(showCard(ui->cardI1J1)));
//    connect(ui->cardI2J1, SIGNAL(clicked()), this,
//            SLOT(showCard(ui->cardI2J1)));
//    connect(ui->cardI3J0, SIGNAL(clicked()), this,
//            SLOT(showCard(ui->cardI3J0)));
//    connect(ui->cardI4J1, SIGNAL(clicked()), this,
//            SLOT(showCard(ui->cardI4J1)));
//    connect(ui->cardI5J0, SIGNAL(clicked()), this,
//            SLOT(showCard(ui->cardI5J0)));
//    connect(ui->cardI6J1, SIGNAL(clicked()), this,
//            SLOT(showCard(ui->cardI6J1)));
//    connect(ui->cardI7J0, SIGNAL(clicked()), this,
//            SLOT(showCard(ui->cardI7J0)));
//    connect(ui->cardI8J1, SIGNAL(clicked()), this,
//            SLOT(showCard(ui->cardI8J1)));
//    connect(ui->cardI9J0, SIGNAL(clicked()), this,
//            SLOT(showCard(ui->cardI9J0)));
}

void MainWindow::showCard(QPushButton*& buttonPushed) {
    string name = (buttonPushed->objectName()).toStdString();
    cout<< name << endl;
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
        messageBox.setText("¡Ganaste! Puntaje final: " + QString::number(points*1000) + "\nVolver a jugar?");
        if (QMessageBox::Yes == messageBox.exec()){
            initGame();
        }
        else{
            QCoreApplication::quit();
        }
    }
    else{
        if (time.toString()=="00:00:00"){
            timer->stop();
            ui->frameMatriz->setEnabled(false);
            messageBox.setText("Perdiste ;( \n¿Volver a jugar?");
            if (QMessageBox::Yes == messageBox.exec()){
                initGame();
            }
            else{
                QCoreApplication::quit();
            }
        }
    }
}

void MainWindow::mixCards() {

}

void MainWindow::distributeCards() {

}

