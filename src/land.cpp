#include "land.h"

Land::Land(float x, float y, float w, float h, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    // Set pixmap
    setPixmap(pixmap);
    g_pixmap.setPixmap(pixmap.scaled(w*g_windowsize.width()/g_worldsize.width(),h*g_windowsize.height()/g_worldsize.height()));
    g_size = QSizeF(w,h);

    // Create body
    b2BodyDef bodyDef;
    bodyDef.userData = this;
    bodyDef.position.Set(x,y);
    g_body = world->CreateBody(&bodyDef);
    b2PolygonShape bodyBox;
    bodyBox.SetAsBox(w,h);
    g_body->CreateFixture(&bodyBox,9.0f);

    scene->addItem(&g_pixmap);
    datatype=0;
    paint();
}

int Land::getEntityType()
{
    return 0;
}

void Land::addscore()
{

}
