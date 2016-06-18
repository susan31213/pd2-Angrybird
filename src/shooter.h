#ifndef SHOOTER_H
#define SHOOTER_H

#include <gameitem.h>
#include <QGraphicsScene>

class Shooter : public GameItem
{
public:
    Shooter(float x, float y, float w, float h, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    virtual int getEntityType();
};

#endif // SHOOTER_H
