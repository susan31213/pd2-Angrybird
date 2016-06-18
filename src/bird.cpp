#include "bird.h"

#include <QDebug>

Bird::Bird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
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
    fixturedef.density = BIRD_DENSITY;
    fixturedef.friction = BIRD_FRICTION;
    fixturedef.restitution = BIRD_RESTITUTION;
    g_body->SetAngularDamping(3);
    g_body->CreateFixture(&fixturedef);

    // set contacting
    m_numContacts = 0;
    datatype = 1;

    // Bound timer
    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));
    connect(timer, SIGNAL(timeout()), this,SLOT(collide()));

    scene->addItem(&g_pixmap);
}

void Bird::setLinearVelocity(b2Vec2 velocity)
{
    g_body->SetLinearVelocity(velocity);
}

void Bird::startContact() { m_numContacts++; }

void Bird::endContact() { m_numContacts--; }

void Bird::spec()
{

}

int Bird::getEntityType()
{
    return 1;
}

void Bird::collide()
{


}
