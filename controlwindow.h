#ifndef CONTROLWINDOW_H
#define CONTROLWINDOW_H
#include<QWidget>
#include<QMainWindow>
#include<QPushButton>
#include<QVBoxLayout>
#include<QGraphicsView>
#include<QGraphicsScene>
#include<QGraphicsTextItem>
#include<QFont>
#include <QGraphicsPixmapItem>
#include <QPixmap>

#include"gui.h"
/**
     * @brief Das ist ein Contro Window für Benutzer zu entscheiden, ob der allein mit Computer spielen oder zu Zweite spielen möchte.
     */
class controlWindow: public QMainWindow
{
    Q_OBJECT;
public:
    /**
        * @brief Konstruktur von class controlWindow
        */
    controlWindow(QWidget *parent=nullptr);
    /**
         * @brief Dekonstruktur von class controlWindow
         */
    ~controlWindow();

private slots:
    /**
        * @brief zwei Fenster zu öffnen
        */
    void zweiSpieler();
    /**
        *@brief ein Fenster zu öffnen
        */
    void alleinSpieler();

private:
    /**
         * @brief Ein Zeiger, der auf den Datentyp von GUI zeigt
         */
    GUI *w;
    /**
         * @brief Zweiter Zeiger, der auf den Datentyp von GUI zeigt
         */
    GUI *x;
};

#endif // CONTROLWINDOW_H
