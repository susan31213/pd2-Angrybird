#ifndef WOOD_H
#define WOOD_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include <QList>

#define WOOD_DENSITY 1.0f
#define WOOD_FRICTION 0.5f
#define WOOD_RESTITUTION 0.0f

class Wood : public GameItem
{
public:
    Wood(float x, float y, float w, float h,QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    virtual int getEntityType();
    void startContact();
    void endContact();
    void addscore();

public slots:
    virtual void collide();

private:
    int m_numContacts;
};

#endif // WOOD_H
