#include "gui.h"
#include "ui_gui.h"


GUI::GUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GUI)
{

    ui->setupUi(this);


    ui->pBVerbinden->setDisabled(true);
    ui->pBStarten->setDisabled(true);
    ui->tB1->append("Wähle Player 1 oder Player 2.");
    connect(ui->pBClient, SIGNAL(clicked()), this, SLOT(isClient()));
    connect(ui->pBServer, SIGNAL(clicked()), this, SLOT(isServer()));
    connect(ui->pBVerbinden, SIGNAL(clicked()), this, SLOT(verbinden()));
    connect(ui->pBStarten, SIGNAL(clicked()), this, SLOT(changepage()));
    connect(ui->pBStarten, SIGNAL(clicked()), this, SLOT(setNewBoard()));
    connect(this, SIGNAL(spielenMitComputer()), this, SLOT(randomPlace()));
    connect(this, SIGNAL(boardbereit()), this, SLOT(zweiPerson()));
    connect(ui->pBBeenden, SIGNAL(clicked()), this, SLOT(popUPEnd()));
    QPushButton *v = new QPushButton(), *h = new QPushButton();
    v->setText("Vertikal");
    h->setText("Horizontal");
    msgBox.setText("Wähle eine Richtung von dem Schiff.");
    msgBox.setInformativeText("Das Schiff kann nur nach rechts oder nach unten gedreht werden. ");
    msgBox.addButton(v, QMessageBox::ActionRole);
    msgBox.addButton(h, QMessageBox::ActionRole);
    verboten.setText("Man darf nicht so platziren! ");
    verboten.setDefaultButton(QMessageBox::Ok);
    connect(v, SIGNAL(clicked()), this, SLOT(_direction()));
    connect(h, SIGNAL(clicked()), this, SLOT(_direction()));
    connect(ui->pBRandomPlace, SIGNAL(clicked()), this, SLOT(randomtest()));
    connect(ui->pBrC, SIGNAL(clicked()), this, SLOT(randomChoose()));

}

GUI::~GUI()
{
    delete ui;
    //delete all push buttons
}



void GUI::_SmC()
{
    ui->rolle->setText("Spieler");
    _SpielerZahl=1;
    taketurn=true;
    changepage();
    setNewBoard();
    //    ui->pBStarten->setEnabled(true);
    emit spielenMitComputer();
}

void GUI::isServer(){
//    _SpielerZahl=2;
    taketurn=0;
    ui->rolle->setText("Player 1");
    ui->tB1->append("Du bist jetzt Player 1.");
//    ui->pBVerbinden->setEnabled(true);
    ui->pBClient->setDisabled(true);
    ui->pBServer->setDisabled(true);
    ui->pBStarten->setEnabled(true);
}

void GUI::isClient(){
//    _SpielerZahl=2;
    taketurn=1;
    ui->rolle->setText("Player 2");
    ui->tB1->append("Du bist jetzt Player 2.");
//    ui->pBVerbinden->setEnabled(true);
    ui->pBServer->setDisabled(true);
    ui->pBClient->setDisabled(true);
     ui->pBStarten->setEnabled(true);
}

void GUI::zweiPerson() //dass man ein Signal mit g2 uebertragen kann
{
     ui->pBVerbinden->setDisabled(true);
     QVector<QPushButton *> temp;
     temp=player1.g2;
     emit playervonGegner(temp);
}
void GUI::zweiPlace(QVector<QPushButton *> a)
{

     player2.g2=a;
     if(taketurn)
     {
        for(QPushButton *a: player1.g1)
        {
            a->setEnabled(true);
        }
     }
     else
     {
        for(QPushButton *a: player1.g1)
        {
            a->setDisabled(true);
        }
     }
}
void GUI::zweiPlay(int a)
{

     //      QPushButton* receiveP=(QPushButton*)(sender());
     int p=a;
     if(taketurn)
     {
        for(QPushButton *temp:player1.g1)
        {
            temp->setEnabled(true);
        }
        if(player1.g2[p]->text()=="S")
        {
            player1.g2[p]->setStyleSheet("Background-color: red; ");
            player2._anzahl2--;
        }
        else
        {
            player1.g2[p]->setStyleSheet("Background-color:blue;");
        }
     }
     else
     {
        for(QPushButton *temp:player1.g1)
        {
            temp->setDisabled(true);
        }
        if(player1.g2[p]->text()=="S")
        {
            player1.g2[p]->setStyleSheet("Background-color:red; ");
            player1._anzahl2--;
        }
        else
        {
            player1.g2[p]->setStyleSheet("Background-color:blue;");
        }
     }
     switchTurn();
}

void GUI::switchTurn()
{
//    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    taketurn=!taketurn;
    if(taketurn)
    {
        for(QPushButton* tmp: player1.g1)
        {
            if(tmp->text()=="X"||tmp->text()=="O")
            {
                tmp->setDisabled(true);
                continue;
            }
            tmp->setEnabled(true);
        }
    }
    else
    {
        for(QPushButton* tmp: player1.g1)
        {
            tmp->setDisabled(true);
        }
    }
}

void GUI::delay()
{
    QTime dieTime= QTime::currentTime().addMSecs(100);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


void GUI::randomPlace() //Computer platziert die Schiffe zufaellig
{
    int _loop;
    bool weiter=1; //pruefer, ob die Schiffe Kollision oder ueber Feld platziert werdne.
    for(int i=0; i<100; i++)
    {
        player2.g2.insert(i, new QPushButton());
        player2.g2[i]->setText(QString::number(i));
    }

    while(player2._mal)
    {
        player2._rotation=std::rand()%2;
        int a=std::rand()%100;
        switch(player2._mal)
        {
        case(10):
            _loop = 4;break;
        case(9):case(8):
            _loop = 3;break;
        case(7):case(6):case(5):
            _loop = 2;break;
        case(4):case(3):case(2):case(1):
            _loop = 1;break;
        default: _loop=0;
        }
        if(player2._rotation)
        {
            if((a+10 * _loop)> 100)    //out of range
            {
                continue;
            }
            for(int j=0; j<=_loop; j++)
            {
                if(player2.g2[a + 10*j]->text()=="S") //Kollisionverboten
                {
                    weiter=0;
                    break;
                }
            }
            if(weiter==1)
            {
                player2._mal--;
                for(int j=0; j<=_loop; j++)
                {
                    player2.g2[a + 10*j]->setText("S");

                }
            }
        }
        else{
            if(a/10 != (a + _loop) / 10)
            {
                continue;
            }
            for(int j=0; j<=_loop; j++)
            {
                if(player2.g2[a + 1*j]->text()=="S")
                {
                    weiter=0;
                    break;
                }

            }
            if(weiter==1)
            {
                player2._mal--;
                for(int j=0; j<=_loop; j++)
                {
                    player2.g2[a + 1*j]->setText("S");
                }
            }
        }
        weiter=1;
    }

    emit overSignal(_isGameOver2);
    QMessageBox timesControl;
    timesControl.setText("Du kannst jetzt mit Computer spielen. ");
    timesControl.setDefaultButton(QMessageBox::Cancel);
    timesControl.exec();
}

void GUI::randomPlay()
{
    while(taketurn)
    {
        if(_isGameOver2)
            return;
        int p=std::rand()%100;
        if(player1.g2[p]->text()=="O"||player1.g2[p]->text()=="X")
        {
            continue;
        }
        else
        {

            if(player1.g2[p]->text()=="S")
            {
                player1.g2[p]->setStyleSheet("Background-color: red; ");
                player1.g2[p]->setText("X");
                player1._anzahl2--;
                switchTurn();
            }
            else
            {
                player1.g2[p]->setStyleSheet("Background-color: blue;");
                player1.g2[p]->setText("O");
                switchTurn();
            }
        }
      }
}

void GUI::changepage(){
       ui->pBrC->setDisabled(true);
    ui->sW->setCurrentIndex(1);
    QMessageBox _regelung;
    _regelung.setText("In diesem Spiel platziert man die Schiffe in folgende Reihenfolge: 1 Schlachtschiff (5 Kästchen)"
                      ",2 Kreuzer (je 4 Kästchen) ,3 Zerstörer (je 3 Kästchen), 4 U-Boote (je 2 Kästchen)\n "
                      "Außerdem kann man nur die Position des ersten Kästchens des Schiffes wählen, und die Schiffe werden dann nach unten oder nach rechts platziert. \n"
                      "\n Die Farbe: Auf dem GegnerBoard: schwarz: Daneben geschossen; grün: Schiff getroffen\n"
                      "Auf eingenem Board: schwarz: platziertes Schiff; rot: Schiff getroffen; blau: Der Gegner hat dieses Kätschen gewählt ");
    _regelung.setDefaultButton(QMessageBox::Ok);
    _regelung.exec();
}

void GUI::verbinden(){
    ui->tB1->append("Versuche zu verbinden.....");
    QString _adress;
    QString _port;
    _adress=ui->lEIPAdresse->text();
    _port=ui->lEPort->text();
    ui->pBStarten->setEnabled(true);// the position has to be discussed.
    ui->pBVerbinden->setDisabled(true);
}

void GUI::setNewBoard(){  //alle Board werden am Anfang des Spiels angezeigt.
    for(int i=0; i<10; i++)
    {
        for(int j=0; j<10; j++)
        {
            player1.g1.insert(i * 10 + j, new QPushButton());
            player1.g1[i * 10 + j]->setText(QString::number(i * 10 + j));
            player1.g1[i * 10 + j]->setStyleSheet("color: white;");
            //g1[i*10+j]->setFlat(true);
            //g1[i*10+j]->setStyleSheet("border: 1px solid Black;");//->setStyleSheet("border: 1px; border color: black;"); //setStyleSheet("border:5px solid #ff0000;");
            player1.g2.insert(i * 10 + j, new QPushButton());
            player1.g2[i * 10 + j]->setText(QString::number(i * 10 + j));
            player1.g2[i * 10 + j]->setStyleSheet("color: white;");
            ui->Board1->addWidget(player1.g1[i * 10 + j], i, j);
            //connect(g1[i * 10 + j], SIGNAL(clicked()), this, SLOT(buttonPressed(i*10+j)));
            ui->Board2->addWidget(player1.g2[i * 10 + j], i, j);
            //            emit signal();
                switch (_SpielerZahl)
                {
                case 1:
                connect(player1.g1[i * 10 + j], SIGNAL(clicked()), this, SLOT(randomPlay()));
                break;
//                case 2:
//                connect(player1.g1[i * 10 + j], SIGNAL(clicked()), this, SLOT(zweiPerson()));
                default:
                break;
                }
            connect(player1.g1[i * 10 + j], SIGNAL(clicked()), this, SLOT(getPosition1()));
            connect(player1.g2[i * 10 + j], SIGNAL(clicked()), this, SLOT(getPosition2()));
            connect(player1.g1[i * 10 + j], SIGNAL(clicked()), this, SLOT(switchTurn()));
            connect(player1.g1[i*10 + j], SIGNAL(clicked()), this, SLOT(gameOver()));
        }
    }

    for (QPushButton * notouch: player1.g1)
    {
        notouch->setDisabled(true);
    }
}

void GUI::getPosition1()                    //wählen wir PushButton anzugreifen.
{

    QPushButton* button = (QPushButton*)(sender());  //bekommen die Siganel von Board 1 , die gedrückten Buttons
    emit sendPos(button->text().toInt());            //senden die Position von Player zu anderem Player
    button->setDisabled(true);
    int b=button->text().toInt();
    QString _b= QString::number(b);
    ui->textBrowser->append("Du hast: "+ _b  +" von Gegner gewählt. ");
    if(player2.g2[b]->text()=="S")
    {
        button->setDisabled(true);
        button->setText("O");
        player2._anzahl2--;
        button->setStyleSheet("Background-color: green;");
        //        player2.g2[b]->setStyleSheet("Background-color: red; ");
    }
    else
    {
        button->setDisabled(true);
        button->setText("X");
        button->setStyleSheet("color: red; Background-color:black; ");
    }
    emit overSignal(_isGameOver2);
}

//void GUI::setField(int *a, int b){
//    //color buttons
//    emit ship(a, b, c, d);
//}

void GUI::_direction(){
    QPushButton *button=(QPushButton*)(sender());
    QString c = button->text();
    if(c == "Vertikal"){
        player1._rotation = 1;
    }
    else{
        player1._rotation = 0;
    }
}

void GUI::getPosition2()                    //platzieren wir die Schiffe auf Board 2.
{
    QPushButton* button = (QPushButton*)(sender());

    //    button->setStyleSheet("Background-color: Black;");
    //    button->setDisabled(true);
    int a = button->text().toInt();
    //emit(int posx, int posy, bool vertikal);
    int _loop;
    switch(player1._mal){
    case(10):
        _loop = 4;break;
    case(9):case(8):
        _loop = 3;break;
    case(7):case(6):case(5):
        _loop = 2;break;
    case(4):case(3):case(2):case(1):
        _loop = 1;break;
    default: _loop=0;
    }
    if(_loop)
    {
        msgBox.exec();
        if(player1._rotation)
        {
            if(a+10 * _loop > 100)
            {
                //                player1._mal++;
                verboten.exec();
                //                continue;
                return;
            }
            for(int j=0; j<=_loop; j++)
            {
                if(player1.g2[a + 10*j]->text()=="S")
                {
                    verboten.exec();
                    return;
                }
            }


                player1._mal--;
                for(int j=0; j<=_loop; j++)
                {
                    player1.g2[a + 10*j]->setStyleSheet("Background-color: Black;");
                    player1.g2[a + 10*j]->setDisabled(true);
                    player1.g2[a + 10*j]->setText("S");

                }

        }
        else{
            if(a/10 != (a + _loop) / 10)
            {
                //                player1._mal++;
                verboten.exec();
                return;
            }
            for(int j=0; j<=_loop; j++)
            {
                if(player1.g2[a + 1*j]->text()=="S")
                {
                    verboten.exec();
                    return;
                }

            }
                player1._mal--;
                for(int j=0; j<=_loop; j++)
                {
                    player1.g2[a +1*j]->setStyleSheet("Background-color: Black;");
                    player1.g2[a+j]->setDisabled(true);
                    player1.g2[a + 1*j]->setText("S");


                }
        }

        if(player1._mal==0)
        {
            for (QPushButton * notouch: player1.g1)
            {
                notouch->setDisabled(true);
            }
        }
//        player1._mal--;
    }
    else{
        QMessageBox timesControl;
        timesControl.setText("Du darfst nur 10 Schiffe platzieren!");
        timesControl.setDefaultButton(QMessageBox::Cancel);
        timesControl.exec();
        ui->textBrowser->append("Du darfst nur 10 Schiffe platziren!");}
    if(player1._mal > 0){
        ui->textBrowser->append("Du hast: " + QString::number(a) + " von Selbst gewählt. ");
            int x = a % 10;
        int y = (a - x) / 10;
        ui->textBrowser->append(QString::number(x) + " " + QString::number(y));
    }
    if(player1._mal==0)
    {
        for (QPushButton * notouch: player1.g2)
        {
            notouch->setEnabled(true);
        }
        emit boardbereit();
    }
    if(player2._mal==0&&player1._mal==0)
    {
        for(QPushButton *touch: player1.g1)
        {
            touch->setEnabled(true);
        }
    }
}

void GUI::randomtest(){
    int _loop;
    bool weiter=1; //pruefer, ob die Schiffe Kollision oder ueber Feld platziert werdne.
    while(player1._mal)
    {
        player1._rotation=std::rand()%2;
        int a=std::rand()%100;
        switch(player1._mal)
        {
        case(10):
            _loop = 4;break;
        case(9):case(8):
            _loop = 3;break;
        case(7):case(6):case(5):
            _loop = 2;break;
        case(4):case(3):case(2):case(1):
            _loop = 1;break;
        default: _loop=0;
        }
        if(player1._rotation)
        {
            if((a+10 * _loop)> 100)
            {
                continue;
            }
            for(int j=0; j<=_loop; j++)
            {
                if(player1.g2[a + 10*j]->text()=="S")
                {
                    weiter=0;
                    break;
                }
            }
            if(weiter==1)
            {
                player1._mal--;
                for(int j=0; j<=_loop; j++)
                {
                    player1.g2[a + 10*j]->setText("S");
                    player1.g2[a + 10*j]->setStyleSheet("Background-color: black; ");
                }
            }
        }
        else{
            if(a/10 != (a + _loop) / 10)
            {
                continue;
            }
            for(int j=0; j<=_loop; j++)
            {
                if(player1.g2[a + 1*j]->text()=="S")
                {
                    weiter=0;
                    break;
                }

            }
            if(weiter==1)
            {
                player1._mal--;
                for(int j=0; j<=_loop; j++)
                {
                    player1.g2[a + 1*j]->setText("S");
                    player1.g2[a + 1*j]->setStyleSheet("Background-color: black; ");
                }
            }
        }
        weiter=1;
    }
    if(player1._mal==0)
    {
        for (QPushButton * notouch: player1.g2)
        {
            notouch->setDisabled(true);
        }
        ui->pBRandomPlace->setDisabled(true);
        //        ui->Board2->setEnabled(false);
        emit boardbereit();
        ui->pBrC->setEnabled(true);
    }
    if(player2._mal==0&&player1._mal==0)
    {
        for(QPushButton *touch: player1.g1)
        {
            touch->setEnabled(true);
        }
    }
}
void GUI::randomChoose()
{
    while(taketurn)
    {
        if(_isGameOver2)
            return;
        int p=std::rand()%100;
        if(player1.g1[p]->text()=="O"||player1.g1[p]->text()=="X")
        {
            continue;
        }
        else
        {
            delay();
            emit player1.g1[p]->clicked();
        }
    }
    emit overSignal(_isGameOver2);
}

void GUI::gameOver2(bool isGameOver)
{
    if(isGameOver)
    {
        player2._anzahl2=0;
    }
    if(player2._anzahl2==0)
    {
        gameOver();
    }
    else
        return;
}
void GUI::gameOver(){
    if(player1._anzahl2==0)
    {
        over.setText(ui->rolle->text()+" hat verloren !");
        _isGameOver2=1;
    }
    else if(player2._anzahl2==0)
    {
        over.setText(ui->rolle->text()+" gewonnen!");
        _isGameOver2=1;
    }
    if(_isGameOver2)
    {
        over.exec();
        for(QPushButton *notouch: player1.g2)
        {
            notouch->setDisabled(true);
        }
        for(QPushButton *notouch: player1.g1)
        {
            notouch->setDisabled(true);
        }
    }
}

void GUI::popUPEnd()                //bei ZweiPlay nur nach Platzieren moeglich, aber bei alleinem Spiel passt immer
{
    over.setText("Du hast das Spiel beendet. ");
    over.setDefaultButton(QMessageBox::Cancel);
    _isGameOver2=1;
    gameOver();
    ui->textBrowser->append("Das Spiel wird beendet. \n");
    emit overSignal(_isGameOver2);
}

