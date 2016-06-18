#ifndef BLUE_H
#define BLUE_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include <QList>

#define BIRD_DENSITY 10.0f
#define BIRD_FRICTION 0.2f
#define BIRD_RESTITUTION 0.5f

class Blue : public GameItem
{
public:
    Blue(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void setLinearVelocity(b2Vec2 velocity);
    void startContact();
    void endContact();
    void spec();
    virtual int getEntityType();
    bool shooted = false;
    bool speced = false;
    Blue * new1;
    Blue * new2;
public slots:
    virtual void collide();

private:
    int m_numContacts;
    QTimer * tt;
    b2World * ww;
    QGraphicsScene * ss;
};

#endif // BLUE_H
