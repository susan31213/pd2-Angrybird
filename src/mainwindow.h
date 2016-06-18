#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QDesktopWidget>
#include <QTimer>
#include <Box2D/Box2D.h>
#include <QMouseEvent>
#include <QGraphicsTextItem>
#include <iostream>
#include <QPushButton>
#include <QLabel>
#include <QMediaPlayer>

#include <gameitem.h>
#include <land.h>
#include <bird.h>
#include <shooter.h>
#include <wood.h>
#include <pig.h>
#include <yellow.h>
#include <blue.h>
#include <white.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *,QEvent *event);
    void closeEvent(QCloseEvent *);
    QTimer timer;
    QGraphicsScene *scene;
    b2World *world;

signals:
    // Signal for closing the game
    void quitGame();

private slots:
    void tick();
    void printscore();
    // For debug slot
    void QUITSLOT();
    void RESTARTSLOT();
    void CHECKWIN();

private:
    Ui::MainWindow *ui;
    QList<GameItem *> itemList;
    QGraphicsTextItem text;
    Bird* bird;
    Blue* blue;
    Yellow * yellow;
    White * white;
    Wood * w1;
    Wood * w2;
    Wood * w3;
    Wood * w4;
    Pig * pig;
    int x,y,x1,y1;
    static bool pressed;
    static bool release;
    QPushButton * exit;
    QPushButton * restart;
    QLabel * result;
    QMediaPlayer * sound;
};

#endif // MAINWINDOW_H
