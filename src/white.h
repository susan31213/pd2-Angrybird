#ifndef WHITE_H
#define WHITE_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include <QList>
#include <egg.h>

#define BIRD_DENSITY 10.0f
#define BIRD_FRICTION 0.2f
#define BIRD_RESTITUTION 0.5f

class White : public GameItem
{
public:
    White(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void setLinearVelocity(b2Vec2 velocity);
    void startContact();
    void endContact();
    void spec();
    virtual int getEntityType();
    bool shooted = false;
    bool speced = false;
    Egg * egg;
public slots:
    virtual void collide();

private:
    int m_numContacts;
    QTimer * tt;
    b2World * ww;
    QGraphicsScene * ss;
};

#endif // WHITE_H
