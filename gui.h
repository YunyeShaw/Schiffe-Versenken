#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include<QGraphicsScene>
#include<QGraphicsView>
#include<QPushButton>
#include<QVector>
#include<QTextBrowser>
#include<QString>
#include<QMessageBox>
#include <iostream>
#include<random>
#include<thread>
#include<chrono>
#include<QTime>

/**
     * @brief ein namespace für ui
     */
QT_BEGIN_NAMESPACE
namespace Ui { class GUI;}
QT_END_NAMESPACE

/**
     * @brief eine Klasse von Player, die nötigen Daten für einen Player speichern
     */
class player
{
public:
    /**
         * @brief Konstruktur von player Klasse
         */
    player()=default;

    /**
         * @brief Dekonstruktur von player Klasse
         */
    ~player()=default;

    /**
         * @brief Ein QVector für  Board 1 (links) auf dem Fenster
         */
    QVector<QPushButton*> g1;

    /**
         * @brief zweiter QVector für Board 2 (rechts) auf dem Fenster
         */
    QVector<QPushButton*> g2;

    /**
         * @brief Eine friend Klasse Deklaration, da die GUI möchte alle Daten von Player zugreifen
         */
    friend class GUI;

private:

    /**
         * @brief  Ob man senkrecht oder waagerecht paltzieren will
         */
    bool _rotation;

    /**
         * @brief Wie oft man Schiffe platzieren kann
         */
    int _mal=10;

    /**
         * @brief Die Menge von Kätschen von allen Schiffen
         */
    int _anzahl2=30;
};


/**
     * @brief Main Fenster, wo man die Schiffe platzieren oder die von Gegners wählen kann
     */
class GUI : public QMainWindow
{

    Q_OBJECT
public:

    /**
         * @brief Die Konstruktur von GUI
         */
    GUI(QWidget *parent = nullptr);

    /**
         * @brief Die Dekonstruktur von GUI
         */
    ~GUI();

    /**
         * @brief QMessageBox, zur Info der Regelung des Spiels
         */
    QMessageBox msgBox;

    /**
         * @brief QMessageBox, bei Platzieren außerhalb des Feld und Kollision mit anderen Schiffen vorkommt
         */
    QMessageBox verboten;

    /**
         * @brief  QMessageBox, bei Ende des Spiels oder wenn man früher das Spiel beenden möchte vorkommt
         */
    QMessageBox over;

    /**
         * @brief Player 1, der das Fenster einspielt.
         */
    player player1;

    /**
         * @brief Player 2, der hinter dem Fenster einspielt, Computer oder die Daten von menschliem Gegner
         */
    player player2;


public slots:
    /**
         * @brief Informiert die controlWindow, das der Benutzer zwei Player gewählt hat
         */
    void zweiPerson();

    /**
         * @brief bearbeitet die Daten, wo der Gegner auf dem Board 2 platziert hat
         */
    void zweiPlace(QVector<QPushButton *> a);

    /**
         * @brief bearbeitet die Daten, wo der Gegner auf dem Board 1 gewählt hat
         */
    void zweiPlay(int a);

    /**
         * @brief informiert die randomPlace Funktion, die aufgerufen werden soll
         */
    void _SmC();

    /**
         * @brief bekomme das Signal des Gegner, ob er keine Kätschen auf Board 2 hat oder früher das Spiel beendet
         */
    void gameOver2(bool isGameOver);  //gameOver for 2 Players

private slots:

    /**
         * @brief weise die Anzahl der menschlischen Spieler, die Rolle 'Player 1 oder Player 2'auf, setze andere QPushButton Disabled
         */
    void isClient();

    /**
         * @brief weise die Anzahl der menschlischen Spieler, die Rolle 'Player 1 oder Player 2'auf, setze andere QPushButton Disabled
         */
    void isServer();

    /**
         * @brief Nach drücken des QPushButtons 'Verbinden' wird das Verbinden der zwei Player begonnen, wird hier nicht benutzt
         */
    void verbinden();

    /**
         * @brief change page auf 2, wo zwei Boards stehen
         */
    void changepage();

    /**
         * @brief zwei Boards(200 QPushButtons) auf dem QWidget platziert
         */
    void setNewBoard();

    /**
         * @brief Aufgerufen, wenn die Horizotal oder vertikal QPushButton gedrückt wird
         */
    void _direction();

    /**
         * @brief Benutzer wählt die Kätschen von Board 1, schätzt die Position der Schiffe von Gegner
         */
    void getPosition1();

    /**
         * @brief Benutzer platziert ihre Schiffe
         */
    void getPosition2();

    /**
         * @brief Rundenwechsel
         */
    void switchTurn();

    /**
         * @brief Platziert das Computer die Schiffe zufällig
         */
    void randomPlace();

    /**
         * @brief Spielt das Computer auf Board 1 zufällig
         */
    void randomPlay();

    /**
         * @brief zufälliges Platzieren auf Board 2 für Benutzer
         */
    void randomtest();

    /**
         * @brief zufälliges Wählen auf Board 1 für Benutzer
         */
    void randomChoose();

    /**
         * @brief Verzögerung auf automatischem Spielen mit Computer, macht das anschaulicher
         */
    void delay();

    /**
         * @brief Ausgerufen, wenn die bool _isGameOver2 gleich 1
         */
    void gameOver();  ///gameOver for 1 Player

    /**
         * @brief ausgeführt, wenn man das QPushButton 'Beenden' drückt
         */
    void popUPEnd();

private:
    /**
         * @brief Eine Pointer für ui
         */
    Ui::GUI *ui;
    /**
         * @brief Anzahl der menschlichen Spieler
         */
    int _SpielerZahl;

    /**
         * @brief ändert sich nach Drücken auf Board 1 von einer der zwei Player
         */
    bool taketurn;

    /**
         * @brief kontrolliert ob das Spiel beendet wird
         */
    bool _isGameOver2=0;    //gameOverSignal for 1 Player


signals:

    /**
         * @brief ermittiert, nachdem beide Players auf Board 2 fertig platziert haben
         */
    void boardbereit();

    /**
         * @brief ermittiert, nach Ausführen von Funktion _SmC
         */
    void spielenMitComputer();

    /**
         * @brief ermittiert nach Gegners Board 1, nachdem boardbereit innerhalb der Systems die SLOT zweiPerson aufruft
         */
    void playervonGegner(QVector<QPushButton *> a);

    /**
         * @brief ermittiert, nachdem Gegner oder Benutzer auf Board 1 gedrückt hat, und die Position nach Gegner oder zu selbst geschickt
         */
    void sendPos(int a);

    /**
         * @brief ermittiert gegenseitig, wenn das Spiel sich beenden soll
         */
    void overSignal(bool isGameOver);       //gameOverSiganl for 2 Players
};

#endif
