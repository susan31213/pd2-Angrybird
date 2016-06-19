#include "mycontactlistener.h"
#include "bird.h"
#include "gameitem.h"
#include "land.h"
#include "wood.h"
#include "pig.h"


#include <QDebug>

#define BIRD 1
#define WOOD 2
#define PIG 3

MyContactListener::MyContactListener()
{
    psound = new QMediaPlayer();
    psound->setMedia((QUrl("qrc:/image/pig.wav")));
}

void MyContactListener::BeginContact(b2Contact *contact)
{
    //check if fixture A was a bird
    void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    if ( bodyUserData )
        if(static_cast<GameItem*>( bodyUserData )->datatype==BIRD) {
            //qDebug()<< "hit bird!" <<endl;
            static_cast<Bird*>( bodyUserData )->startContact();
        }
        if(static_cast<GameItem*>( bodyUserData )->datatype==WOOD) {
            //qDebug()<< "hit wood!" <<endl;
            //static_cast<Wood*>( bodyUserData )->startContact();

        }
        if(static_cast<GameItem*>( bodyUserData )->datatype==PIG) {
            //qDebug()<< "hit wood!" <<endl;
            //static_cast<Pig*>( bodyUserData )->startContact();
        }
    //check if fixture B was a bird
    bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
    if ( bodyUserData ){
        //qDebug()<< static_cast<GameItem*>( bodyUserData )->datatype<<endl;
        if(static_cast<GameItem*>( bodyUserData )->datatype==BIRD) {
            static_cast<Bird*>( bodyUserData )->startContact();
            //qDebug()<< "hit bird!" <<endl;
        }
        if(static_cast<GameItem*>( bodyUserData )->datatype==WOOD)
            //static_cast<Wood*>( bodyUserData )->startContact();
            ;//qDebug()<< "hit wood!" <<endl;
        if(static_cast<GameItem*>( bodyUserData )->datatype==PIG)
            //static_cast<Pig*>( bodyUserData )->startContact();
            ;//qDebug()<< "hit wood!" <<endl;

    }
}

void MyContactListener::EndContact(b2Contact *contact)
{
    //check if fixture A was a bird
    void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    if ( bodyUserData ) {
        if(static_cast<GameItem*>( bodyUserData )->datatype==BIRD) {
            //static_cast<Bird*>( bodyUserData )->endContact();
        }
        if(static_cast<GameItem*>( bodyUserData )->datatype==WOOD) {
            static_cast<Wood*>( bodyUserData )->endContact();
        }
        if(static_cast<GameItem*>( bodyUserData )->datatype==PIG) {
            static_cast<Pig*>( bodyUserData )->endContact();
            if(psound->state() == QMediaPlayer::PlayingState) {
                psound->setPosition(0);
            }
            else if (psound->state() == QMediaPlayer::StoppedState) {
                psound->play();
            }
        }
    }
    //check if fixture B was a bird
    bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
    if ( bodyUserData ){
        //qDebug()<< static_cast<GameItem*>( bodyUserData )->datatype<<endl;
        if(static_cast<GameItem*>( bodyUserData )->datatype==BIRD)
            //static_cast<Bird*>( bodyUserData )->endContact();
        if(static_cast<GameItem*>( bodyUserData )->datatype==WOOD);
            //static_cast<Wood*>( bodyUserData )->endContact();
        if(static_cast<GameItem*>( bodyUserData )->datatype==PIG);
    }
}




