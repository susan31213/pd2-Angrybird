#include "egg.h"
#include <QDebug>

Egg::Egg(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    // Set pixmap
    setPixmap(pixmap);
    setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSizeF(radius,radius);

    // Create Body
    b2BodyDef bodydef;
    bodydef.type = b2_dynamicBody;
    bodydef.bullet = true;
    bodydef.position.Set(x,y);
    bodydef.userData = this;
    g_body = world->CreateBody(&bodydef);
    b2CircleShape bodyshape;
    bodyshape.m_radius = radius;
    b2FixtureDef fixturedef;
    fixturedef.shape = &bodyshape;
    fixturedef.density = EGG_DENSITY;
    fixturedef.friction = EGG_FRICTION;
    fixturedef.restitution = EGG_RESTITUTION;
    g_body->SetAngularDamping(1);
    g_body->CreateFixture(&fixturedef);

    // set contacting
    m_numContacts = 0;
    datatype = 99;

    // Bound timer
    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));
    connect(timer, SIGNAL(timeout()), this,SLOT(collide()));

    scene->addItem(&g_pixmap);
}

void Egg::setLinearVelocity(b2Vec2 velocity)
{
    g_body->SetLinearVelocity(velocity);
}

void Egg::startContact() { m_numContacts++; }

void Egg::endContact() { m_numContacts--; }

int Egg::getEntityType()
{
    return 99;
}

void Egg::collide()
{

}
