#include "gui.h"
#include"controlwindow.h"

#include <QApplication>
#include<time.h>

int main(int argc, char *argv[])
{
    std::srand(std::time(0));
    QApplication a(argc, argv);
    controlWindow y;
    y.resize(600,300);
    y.show();
    return a.exec();
}
