#include "controlwindow.h"
#include <QApplication>

controlWindow::controlWindow(QWidget *parent)
    : QMainWindow(parent), w(new GUI(nullptr)), x(new GUI(nullptr))

{
    QWidget *wdg=new QWidget(this);
    QVBoxLayout *vlay=new QVBoxLayout(wdg);
    QPushButton *zuZweit=new QPushButton("Zwei Spieler");
    QPushButton *allein=new QPushButton("Ein Spieler");
    QGraphicsView *qGV= new QGraphicsView();
    QGraphicsScene *qGS = new QGraphicsScene();
    QPixmap backgroundImage(":/fotovonSchiffe.jpg");
    QGraphicsPixmapItem *backgroundItem = new QGraphicsPixmapItem(backgroundImage);
    qGS->addItem(backgroundItem);
    qGS->setSceneRect(420,200, 300, 200);
    qGV->setScene(qGS);
    vlay->addWidget(qGV);
    vlay->addWidget(allein);
    vlay->addWidget(zuZweit);
    setCentralWidget(wdg);
    connect(zuZweit, &QPushButton::clicked, this, &controlWindow::zweiSpieler);
    connect(allein, &QPushButton::clicked, this, &controlWindow::alleinSpieler);
     QObject::connect(allein, &QPushButton::clicked,w, &GUI::_SmC);
}

controlWindow::~controlWindow()
{
    delete w;
    if(x!=nullptr)
        delete x;
}

void controlWindow::zweiSpieler()
{
    this->close();
    w->show();
    x->show();
    QObject::connect(x, &GUI::playervonGegner, w, &GUI::zweiPlace);
    QObject::connect(w, &GUI::playervonGegner, x, &GUI::zweiPlace);
    QObject::connect(w, &GUI::sendPos, x, &GUI::zweiPlay);
    QObject::connect(x, &GUI::sendPos, w, &GUI::zweiPlay);
    QObject::connect(x, &GUI::overSignal, w, &GUI::gameOver2);
    QObject::connect(w, &GUI::overSignal, x, &GUI::gameOver2);

}

void controlWindow::alleinSpieler()
{
    this->close();
    w->show();
}

