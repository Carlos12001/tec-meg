#ifndef MAINWINDOW_H
#define MAINWINDOW_H
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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTimer *timer = new QTimer;
    QTime time;
    QMessageBox messageBox;
    QVector<QString> vectorCards;
    QHash<QString, QString> hashCards;
    int unCompleteCouple = 0;
    int points = 0;
    bool inGame = false;
    QPushButton* previousCard;
    QPushButton* actualCard;

public slots:
    void initGame();
private slots:
    void updateState();
    void updateTimer();
    void defineFinalResult();
    void defineMiddleResult();
    void scopeEventClick();
    void showCard();
    void mixCards();
    void distributeCards();
    void showImage();
    void rebootCards();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

