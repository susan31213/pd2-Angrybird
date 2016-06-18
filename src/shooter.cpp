#include "shooter.h"

Shooter::Shooter(float x, float y, float w, float h, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{

    // Set pixmap
    g_pixmap.setPixmap(pixmap);
    g_size = QSizeF(w,h);

    // Create body
    b2BodyDef bodyDef;
    bodyDef.userData = this;
    bodyDef.position.Set(x,y);
    g_body = world->CreateBody(&bodyDef);
    b2PolygonShape bodyBox;
    bodyBox.SetAsBox(w,h*1/3);
    g_body->CreateFixture(&bodyBox,9.0f);

    scene->addItem(&g_pixmap);
    paint();
}

int Shooter::getEntityType()
{
    return 0;
}
