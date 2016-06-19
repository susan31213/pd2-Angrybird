#include "wood.h"

#include <QDebug>

Wood::Wood(float x, float y, float w, float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    // Set pixmap
    setPixmap(pixmap.scaled(w*g_windowsize.width()/g_worldsize.width(),h*g_windowsize.height()/g_worldsize.height()));
    setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSizeF(w,h);

    // Create Body
    b2BodyDef bodydef;
    bodydef.type = b2_dynamicBody;
    bodydef.bullet = true;
    bodydef.position.Set(x,y);
    bodydef.userData = this;
    g_body = world->CreateBody(&bodydef);
    b2PolygonShape bodyBox;
    bodyBox.SetAsBox(w,h);
    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyBox;
    fixturedef.density = WOOD_DENSITY;
    fixturedef.friction = WOOD_FRICTION;
    fixturedef.restitution = WOOD_RESTITUTION;
    g_body->SetAngularDamping(3);
    g_body->CreateFixture(&fixturedef);
    g_body->SetLinearVelocity(b2Vec2(0,0));

    // set contacting
    m_numContacts = 0;

    // Bound timer
    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));
    connect(timer, SIGNAL(timeout()), this,SLOT(collide()));

    scene->addItem(&g_pixmap);
    datatype=2;
}

int Wood::getEntityType()
{
    return 2;
}

void Wood::startContact()
{
    m_numContacts++;
}

void Wood::endContact()
{
    addscore();
}

void Wood::addscore()
{
    GameItem::score += 5;
}

void Wood::collide()
{

}
