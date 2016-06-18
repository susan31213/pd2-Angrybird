#ifndef EGG_H
#define EGG_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include <QList>

#define EGG_DENSITY 100.0f
#define EGG_FRICTION 2.0f
#define EGG_RESTITUTION 0.5f

class Egg : public GameItem
{
public:
    Egg(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void setLinearVelocity(b2Vec2 velocity);
    void startContact();
    void endContact();
    virtual int getEntityType();
    void addscore();

public slots:
    virtual void collide();

private:
    int m_numContacts;
};

#endif // EGG_H
