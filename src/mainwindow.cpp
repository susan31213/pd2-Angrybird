#include <QGraphicsView>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mycontactlistener.h"
#include <QFont>

#include <QDebug>

MyContactListener myContactListenerInstance;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Enable the event Filter
    qApp->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{

    blue = NULL;
    yellow = NULL;
    white = NULL;

    // Setting the QGraphicsScene
    scene = new QGraphicsScene(0,0,width(),ui->graphicsView->height());
    ui->graphicsView->setScene(scene);
    scene->setBackgroundBrush (QBrush(QImage(":/image/bg.png").scaledToHeight(600).scaledToWidth(800)));
    // Create world
    world = new b2World(b2Vec2(0.0f, -9.8f));
    world->SetContactListener(&myContactListenerInstance);
    // Setting Size
    GameItem::setGlobalSize(QSizeF(32,18),size());
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // Create ground (You can edit here)
    itemList.push_back(new Land(16.0,1.5,32.0,2.0,QPixmap(":/ground.png").scaled(width(),height()/5.0),world,scene));
    // Create shooter
    itemList.push_back(new Shooter(3,6,0.5,2.5,QPixmap(":/image/shooter.png").scaled(width()/15.0,height()/3),world,scene));
    // Create wood
    w1 = new Wood(10.0f,8.0f,0.3f,3.3f,&timer,QPixmap(":/image/thinwood1.png").scaled(width()/60.0,height()/3.0),world,scene);
    w2 = new Wood(15.0f,8.0f,0.3f,3.3f,&timer,QPixmap(":/image/thinwood1.png").scaled(width()/60.0,height()/3.0),world,scene);
    w3 = new Wood(20.0f,8.0f,0.3f,3.3f,&timer,QPixmap(":/image/thinwood1.png").scaled(width()/60.0,height()/3.0),world,scene);
    w4 = new Wood(25.0f,8.0f,0.3f,3.3f,&timer,QPixmap(":/image/thinwood1.png").scaled(width()/60.0,height()/3.0),world,scene);
    itemList.push_back(w1);
    itemList.push_back(w2);
    itemList.push_back(w3);
    itemList.push_back(w4);
    // Create pig
    pig = new Pig(17.3f,3.0f,0.28f,&timer,QPixmap(":/image/pig.png").scaled(height()/13.0,height()/13.0),world,scene);
    itemList.push_back(pig);
    // Create bird (You can edit here)
    bird = new Bird(3.0f,10.0f,0.28f,&timer,QPixmap(":/bird.png").scaled(height()/13.0,height()/13.0),world,scene);
    // Setting the Velocity
    bird->setLinearVelocity(b2Vec2(0,0));
    itemList.push_back(bird);
    // Set score text
    text.setPlainText(QString("Score: ") + QString::number(GameItem::score)); // Score: 0
    text.setDefaultTextColor(Qt::blue);
    text.setFont(QFont("times",20));
    scene->addItem(&text);
    // Timer
    connect(&timer,SIGNAL(timeout()),this,SLOT(tick()));
    connect(&timer,SIGNAL(timeout()),this,SLOT(printscore()));
    connect(&timer,SIGNAL(timeout()),this,SLOT(CHECKWIN()));
    connect(this,SIGNAL(quitGame()),this,SLOT(QUITSLOT()));
    timer.start(100/6);
    // Button for exit
    exit = new QPushButton();
    exit->setIcon(QIcon(QPixmap(":/image/exit.png")));
    exit->setGeometry(900,478,60,60);
    exit->setIconSize(QSize(50,50));
    connect(exit,SIGNAL(clicked(bool)),this,SLOT(QUITSLOT()));
    scene->addWidget(exit);
    // Button for restart
    restart = new QPushButton();
    restart->setIcon(QIcon(QPixmap(":/image/restart.png")));
    restart->setGeometry(840,478,60,60);
    restart->setIconSize(QSize(50,50));
    connect(restart,SIGNAL(clicked(bool)),this,SLOT(RESTARTSLOT()));
    scene->addWidget(restart);
    restart->hide();
    // win
    result = new QLabel();
    result->setPixmap(QPixmap(":/image/win.jpg"));
    scene->addWidget(result);
    result->hide();
    result->setGeometry(300,150,250,273);
    // Set sound
    sound = new QMediaPlayer();
    sound->setMedia(QUrl("qrc:/image/577.mp3"));

}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    // Hint: Notice the Number of every event!
    int x,y,x1,y1;
    double dx,dy;
    setMouseTracking(true);
    if(event->type() == QMouseEvent::MouseButtonPress)
    {

        if (pressed == false)
        {
            /* TODO : add your code here */
            x = 105;
            y = 289;

            if (white && white->shooted == true && white->speced == false && yellow->speced == true)
            {
                white->spec();
                white->speced = true;
                restart->show();
            }
            if (yellow && yellow->shooted == true && yellow->speced == false && blue->speced == true)
            {
                yellow->spec();
                yellow->speced = true;
                white = new White(3.0f,10.0f,0.28f,&timer,QPixmap(":/image/white.png").scaled(height()/15.0,width()/20.0),world,scene);
            }
            if (blue && blue->shooted == true && blue->speced == false && bird->speced == true)
            {
                blue->spec();
                blue->speced = true;
                yellow = new Yellow(3.0f,10.0f,0.28f,&timer,QPixmap(":/image/yellow.png").scaled(height()/13.0,height()/13.0),world,scene);
            }
            if (bird->shooted == true && bird->speced == false)
            {
                bird->spec();
                bird->speced = true;
                blue = new Blue(3.0f,10.0f,0.28f,&timer,QPixmap(":/image/blue.png").scaled(height()/13.0,height()/13.0),world,scene);

            }
            //std::cout << "Press ! " << std::endl;
            pressed = true;
        }
    }

    if(event->type() == QMouseEvent::MouseMove)
    {
        if(pressed==true)
        {
            QMouseEvent * m = static_cast<QMouseEvent *>(event);
            if (white && white->shooted == false)
            {
                white->g_body->SetActive(false);
                //world->SetGravity(b2Vec2(0,0));
                white->g_body->SetTransform(white->qt2b2Vec(m->pos()),white->g_body->GetAngle());
            }
            if (yellow && yellow->shooted == false)
            {
                yellow->g_body->SetActive(false);
                //world->SetGravity(b2Vec2(0,0));
                yellow->g_body->SetTransform(yellow->qt2b2Vec(m->pos()),yellow->g_body->GetAngle());
            }
            if (blue && blue->shooted == false)
            {
                blue->g_body->SetActive(false);
                //world->SetGravity(b2Vec2(0,0));
                blue->g_body->SetTransform(blue->qt2b2Vec(m->pos()),blue->g_body->GetAngle());
            }
            if (bird->shooted == false)
            {
                bird->g_body->SetActive(false);
                //world->SetGravity(b2Vec2(0,0));
                bird->g_body->SetTransform(bird->qt2b2Vec(m->pos()),bird->g_body->GetAngle());
            }

        }


    }
    if(event->type() == QMouseEvent::MouseButtonRelease)
    {
        /* TODO : add your code here */

        if(pressed == true)
        {
            //std::cout << "Release !" << std::endl ;
            pressed = false;
            if (yellow == NULL && blue == NULL && bird->speced == false){
                bird->g_body->SetActive(true);
                x1 = dynamic_cast<QMouseEvent*>(event)->x();
                y1 = dynamic_cast<QMouseEvent*>(event)->y();
                dx = ((x-x1))/10.0;
                dy = ((y1-y))/10.0;
                bird->setLinearVelocity(b2Vec2(dx*1.5,dy*1.5));
                bird->shooted = true;
                if(sound->state() == QMediaPlayer::PlayingState) {
                    sound->setPosition(0);
                }
                else if (sound->state() == QMediaPlayer::StoppedState) {
                    sound->play();
                }

            }
            else if (yellow == NULL && blue->speced == false && bird->speced == true){
                blue->g_body->SetActive(true);
                x1 = dynamic_cast<QMouseEvent*>(event)->x();
                y1 = dynamic_cast<QMouseEvent*>(event)->y();
                dx = ((x-x1))/10.0;
                dy = ((y1-y))/10.0;
                blue->setLinearVelocity(b2Vec2(dx*1.5,dy*1.5));
                blue->shooted = true;
                if(sound->state() == QMediaPlayer::PlayingState) {
                    sound->setPosition(0);
                }
                else if (sound->state() == QMediaPlayer::StoppedState) {
                    sound->play();
                }

            }
            else if (white == NULL && yellow->shooted == false && yellow->speced == false && blue->speced == true && bird->speced == true){
                yellow->g_body->SetActive(true);
                x1 = dynamic_cast<QMouseEvent*>(event)->x();
                y1 = dynamic_cast<QMouseEvent*>(event)->y();
                dx = ((x-x1))/10.0;
                dy = ((y1-y))/10.0;
                yellow->setLinearVelocity(b2Vec2(dx*1.5,dy*1.5));
                yellow->shooted = true;
                if(sound->state() == QMediaPlayer::PlayingState) {
                    sound->setPosition(0);
                }
                else if (sound->state() == QMediaPlayer::StoppedState) {
                    sound->play();
                }
            }
            else if (white->shooted == false && white->speced == false && yellow->speced == true){
                white->g_body->SetActive(true);
                x1 = dynamic_cast<QMouseEvent*>(event)->x();
                y1 = dynamic_cast<QMouseEvent*>(event)->y();
                dx = ((x-x1))/10.0;
                dy = ((y1-y))/10.0;
                white->setLinearVelocity(b2Vec2(dx*1.5,dy*1.5));
                white->shooted = true;
                if(sound->state() == QMediaPlayer::PlayingState) {
                    sound->setPosition(0);
                }
                else if (sound->state() == QMediaPlayer::StoppedState) {
                    sound->play();
                }
            }
        }


    }
    return false;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    // Close event
    emit quitGame();
}

void MainWindow::tick()
{
    world->Step(1.0/60.0,6,2);
    scene->update();
}

void MainWindow::printscore()
{
    text.setPlainText(QString("Score: ") + QString::number(GameItem::score) + QString("/800"));
}

void MainWindow::QUITSLOT()
{
    // For debug
    std::cout << "Quit Game Signal receive !" << std::endl ;
}

void MainWindow::RESTARTSLOT()
{
    restart->hide();
    qDebug() << "Restart!" << endl;
    delete bird;
    if (blue->new1 != NULL)
        delete blue->new1;
    if (blue->new2!= NULL)
        delete blue->new2;
    delete blue;
    delete yellow;
    if (white->egg!= NULL)
        delete white->egg;
    delete white;
    delete w1;
    delete w2;
    delete w3;
    delete w4;
    delete pig;
    bird = NULL;
    blue = NULL;
    yellow = NULL;
    white = NULL;
    w1 = new Wood(10.0f,8.0f,0.3f,3.3f,&timer,QPixmap(":/image/thinwood1.png").scaled(width()/60.0,height()/3.0),world,scene);
    w2 = new Wood(15.0f,8.0f,0.3f,3.3f,&timer,QPixmap(":/image/thinwood1.png").scaled(width()/60.0,height()/3.0),world,scene);
    w3 = new Wood(20.0f,8.0f,0.3f,3.3f,&timer,QPixmap(":/image/thinwood1.png").scaled(width()/60.0,height()/3.0),world,scene);
    w4 = new Wood(25.0f,8.0f,0.3f,3.3f,&timer,QPixmap(":/image/thinwood1.png").scaled(width()/60.0,height()/3.0),world,scene);
    pig = new Pig(17.3f,3.0f,0.28f,&timer,QPixmap(":/image/pig.png").scaled(height()/13.0,height()/13.0),world,scene);
    bird = new Bird(3.0f,10.0f,0.28f,&timer,QPixmap(":/bird.png").scaled(height()/13.0,height()/13.0),world,scene);
    GameItem::score = 0;
    GameItem::restart = false;
    result->hide();
}

void MainWindow::CHECKWIN()
{
    if (GameItem::score >= 800)
    {
        result->show();
        restart->show();
    }

}
