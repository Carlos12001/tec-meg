#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <iostream>
using namespace std;
#include <string.h>
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
    QHash<QString, string> hashCards;
    int unCompleteCouple = 0;
    int points = 0;

public slots:
    void initGame();
private slots:
    void updateState();
    void updateTimer();
    void defineFinalResult();
    void scopeEventClick();
    void showCard(QPushButton*& buttonPushed);
    void mixCards();
    void distributeCards();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
