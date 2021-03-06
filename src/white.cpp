#include "white.h"

#include <QDebug>

White::White(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):GameItem(world)
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
    datatype = 6;

    egg = NULL;

    // Bound timer
    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));
    connect(timer, SIGNAL(timeout()), this,SLOT(collide()));

    scene->addItem(&g_pixmap);
}

void White::setLinearVelocity(b2Vec2 velocity)
{
    g_body->SetLinearVelocity(velocity);
}

void White::startContact() {  }

void White::endContact() { m_numContacts--; }

void White::spec()
{
    setLinearVelocity(b2Vec2(g_body->GetLinearVelocity().x+20,g_body->GetLinearVelocity().y+20));
    b2Vec2 pos = g_body->GetPosition();
    float xx = pos.x;
    float yy = pos.y-0.5;
    egg = new Egg(xx,yy,0.05,tt,QPixmap(":/image/egg.png").scaled(30,25),ww,ss);
    egg->setLinearVelocity(b2Vec2(5.0,-20.0));
    return;
}

int White::getEntityType()
{
    return 6;
}

void White::collide()
{
    //if ( m_numContacts > 0 )
        //qDebug() << "bird hitted" <<m_numContacts <<  endl;
    //else
        //qDebug() << "bird not hitted" <<m_numContacts << endl;

}
