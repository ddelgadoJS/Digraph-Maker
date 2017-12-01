#include "menu.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    /*QApplication a(argc, argv);
    MainWindow w;
    w.show();*/

    QApplication a(argc, argv);
    Menu w;
    w.show();

    return a.exec();
}
