#ifndef TEC_MEG_MAIN_WINDOW_H
#define TEC_MEG_MAIN_WINDOW_H
#include <iostream>
using namespace std;
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
#include "connection.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{

    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private:

    QTimer *timer = new QTimer;

    QTime time;

    QMessageBox messageBox;

    QHash<QString, QString> hashCards;

    QHash<QString, QPushButton*> hashButton;

    int unCompleteCouple = 0;

    int pointsPlayer1 = 0;

    int pointsPlayer2 = 0;

    bool playerOne = true;

    bool inGame = false;

    QPushButton* previousCard;

    QPushButton* actualCard;

    ClientConnection connection  = ClientConnection();

public slots:

    void initGame(int numberPort);

private slots:

    void updateState();

    void updateTimer();

    void defineFinalResult();

    void defineMiddleResult();

    void showCard();

    void showImage();

    void rebootCards();

    void createButtonCards(int numbOfButtons);

    string receiveCard();

    void sendIdCard(string idCard);

    int receiveInformation();

    void showPoints(int addPoints);

    void changeTurn();

private:

    Ui::MainWindow *ui;

};
#endif

