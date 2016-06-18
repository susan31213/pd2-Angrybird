#ifndef MYCONTACTLISTENER_H
#define MYCONTACTLISTENER_H

#include <Box2D/Box2D.h>
#include <QMediaPlayer>


class MyContactListener: public b2ContactListener
{
public:
    MyContactListener();
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);
private:
    QMediaPlayer * psound;
};

#endif // MYCONTACTLISTENER_H
