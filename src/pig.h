#ifndef PIG_H
#define PIG_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include <QList>

#define PIG_DENSITY 10.0f
#define PIG_FRICTION 0.2f
#define PIG_RESTITUTION 0.5f

class Pig : public GameItem
{
public:
    Pig(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    void setLinearVelocity(b2Vec2 velocity);
    void startContact();
    void endContact();
    void addscore();
    virtual int getEntityType();

public slots:
    virtual void collide();

private:
    int m_numContacts;
};

#endif // PIG_H
