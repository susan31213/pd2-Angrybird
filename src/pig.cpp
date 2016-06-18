#include "pig.h"

#include <QDebug>

Pig::Pig(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
{
    // Set pixmap
    setPixmap(pixmap);
    setTransformOriginPoint(g_pixmap.boundingRect().width()/1.5,g_pixmap.boundingRect().height()/1.5);
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/1.5,g_pixmap.boundingRect().height()/1.5);
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
    fixturedef.density = PIG_DENSITY;
    fixturedef.friction = PIG_FRICTION;
    fixturedef.restitution = PIG_RESTITUTION;
    g_body->SetAngularDamping(3);
    g_body->CreateFixture(&fixturedef);
    g_body->SetLinearVelocity(b2Vec2(0,0));

    // set contacting
    m_numContacts = 0;
    datatype = 3;

    // Bound timer
    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));
    connect(timer, SIGNAL(timeout()), this,SLOT(collide()));

    scene->addItem(&g_pixmap);
}

void Pig::setLinearVelocity(b2Vec2 velocity)
{
    g_body->SetLinearVelocity(velocity);
}

void Pig::startContact() { m_numContacts++; }

void Pig::endContact() { addscore(); }

void Pig::addscore()
{
    GameItem::score += 100;
}

int Pig::getEntityType()
{
    return 3;
}

void Pig::collide()
{
    //if ( m_numContacts > 0 )
        //qDebug() << "pig hitted" << m_numContacts <<  endl;
    //else
        //qDebug() << "pig not hitted" << m_numContacts << endl;

}
