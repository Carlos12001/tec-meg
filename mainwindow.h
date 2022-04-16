/**
 * @author Carlos12001
 * @brief The class contains the client interface. It only stores that.
 */
#ifndef TEC_MEG_MAIN_WINDOW_H
#define TEC_MEG_MAIN_WINDOW_H
#include <iostream>
using namespace std;
#include <cstring>
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

/**
 * @brief It is the client GUI. Executes how the game should be seen so that the user can see it.
 */
class MainWindow : public QMainWindow{

    Q_OBJECT

public:

    /**
     * @brief It is the class constructor. He gets who the window is and sets it.
     * @param parent The window to run.
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destroy the object. Perform all the necessary steps to successfully close the program.
     */
    ~MainWindow();

private:

    /**
     * @brief The game's timer.
     */
    QTimer *timer = new QTimer;

    /**
     * @brief The game's time.
     */
    QTime time;

    /**
     * @brief The exit and completion message.
     */
    QMessageBox messageBox;

    /**
     * @brief It is the hash that stores the name of the selected cards.
     */
    QHash<QString, QString> hashCards;

    /**
     * @brief The hash of the card name and its assigned button.
     */
    QHash<QString, QPushButton*> hashButton;

    /**
     * @brief The unfinished pairs.
     */
    int unCompleteCouple = 0;

    /**
     * @brief First Player Points.
     */
    int pointsPlayer1 = 0;

    /**
     *  @brief Second Player Points.
     */
    int pointsPlayer2 = 0;

    /**
     * @brief Player 1 is playing.
     */
    bool playerOne = true;

    /**
     * @brief This is in the middle of a play.
     */
    bool inGame = false;

    /**
     * @brief The card is in memory.
     */
    bool inMemory = false;

    /**
     * @brief Previous card selected.
     */
    QPushButton* previousCard;

    /**
     * @brief Actual card selected.
     */
    QPushButton* actualCard;

    /**
     * @brief The socket connection.
     */
    ClientConnection connection  = ClientConnection();

public slots:

    /**
     * @brief The game starter. This initiates a lot of things between them are the connection of the client and the cards that the game.
     * @param numberPort The port's number where is located the server.
     */
    void initGame(int numberPort);

private slots:

    /**
     * @brief Update game status. Update things related to time.
     */
    void updateState();

    /**
     * @brief Update the weather. Update it in label.
     */
    void updateTimer();

    /**
     * @brief Define the end result. This performs the analysis if a final result is already possible.
     */
    void defineFinalResult();

    /**
     * @brief Check if the player's move was correct. It checks if the successful move
     */
    void defineMiddleResult();

    /**
     * @brief Check the card states. These states whether it is in the middle of the play or not.
     */
    void showCard();

    /**
    * @brief Shows the selected card. It asks the server for things and then sets them.
    */
    void showImage();

    /**
     * @brief Turn over the cards. This is executed if the cards were not the same so that it erases its information and hides them again.
     */
    void rebootCards();

    /**
     * @brief Create the card buttons. This creates all the buttons that will be seen on the screen so that the user can press them.
     * @param numbOfButtons Number of buttons to create.
     */
    void createButtonCards(int numbOfButtons);

    /**
     * @brief Receive the button image. This method receives information about a card from the server.
     * @return Returns the image of the card.
     */
    string receiveCard();

    /**
     * @brief Request information from this letter. Send a request to the server about the letter you need.
     * @param idCard The ID of the card.
     */
    void sendIdCard(string idCard);

    /**
     * @brief Get the basic information from the server. This information is like the number of minimum cards.
     * @return The number of cards
     */
    int receiveInformation();

    /**
     * @brief Shows the points of the players. It receives the new points and displays them.
     * @param addPoints The new points.
     */
    void showPoints(int addPoints);

    /**
     * @brief Change the color of the point labels.
     */
    void changeTurn();

private:

    /**
     * @brief The GUI window.
     */
    Ui::MainWindow *ui;

};

#endif

