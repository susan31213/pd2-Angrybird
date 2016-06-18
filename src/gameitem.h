#ifndef GAMEITEM_H
#define GAMEITEM_H

#include <Box2D/Box2D.h>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QTransform>
#include <QtMath>
#include <QGraphicsTextItem>


class GameItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    GameItem(b2World *world, QGraphicsPixmapItem *parent=0);
    ~GameItem();
    static void setGlobalSize(QSizeF worldsize, QSizeF windowsize);
    b2Vec2 qt2b2Vec(QPointF qtpos);
    virtual int getEntityType() = 0;
    int datatype;
    static int score;
    bool shooted = false;
    bool speced = false;
    static bool restart;
    b2Body *g_body;


public slots:
    void paint();
    virtual void collide();

protected:

    QGraphicsPixmapItem g_pixmap;
    QSizeF g_size;
    b2World *g_world;
    static QSizeF g_worldsize, g_windowsize;

};

#endif // GAMEITEM_H
