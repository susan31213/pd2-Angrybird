#include "gameitem.h"
#include "mainwindow.h"
#include <QApplication>

int GameItem::score = 0;
bool GameItem::restart = false;
bool MainWindow::pressed = false;
bool MainWindow::release = false;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
