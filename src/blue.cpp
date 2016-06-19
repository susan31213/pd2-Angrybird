#include "blue.h"
#include <QTimer>
#include "mainwindow.h"

#include <QDebug>

Blue::Blue(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    tt = timer;
    ww = world;
    ss = scene;

    // Set pixmap
    setPixmap(pixmap);
    setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSizeF(radius*2,radius*2);

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
    datatype = 5;

    new1 = NULL;
    new2 = NULL;

    // Bound timer
    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));
    connect(timer, SIGNAL(timeout()), this,SLOT(collide()));

    scene->addItem(&g_pixmap);
}

void Blue::setLinearVelocity(b2Vec2 velocity)
{
    g_body->SetLinearVelocity(velocity);
}

void Blue::startContact() {  }

void Blue::endContact() { m_numContacts--; }

void Blue::spec()
{
    b2Vec2 pos = g_body->GetPosition();
    float xx = pos.x;
    float yy = pos.y;

    new1 = new Blue(xx, yy, 0.28f, tt, QPixmap(":/image/blue.png").scaled(600/12.0,600/12.0), ww, ss);
    new1->setLinearVelocity(b2Vec2(g_body->GetLinearVelocity().x+5,g_body->GetLinearVelocity().y+5));
    new2 = new Blue(xx, yy, 0.28f, tt, QPixmap(":/image/blue.png").scaled(600/12.0,600/12.0), ww, ss);
    new2->setLinearVelocity(b2Vec2(g_body->GetLinearVelocity().x+5,g_body->GetLinearVelocity().y-5));
    setLinearVelocity(b2Vec2(g_body->GetLinearVelocity().x+5,g_body->GetLinearVelocity().y));
}

int Blue::getEntityType()
{
    return 5;
}

void Blue::collide()
{


}
