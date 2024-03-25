/**
 * @file FoeVisitor.cpp
 *
 * @author Mannan Dhillon
 *
 */


#include "pch.h"
#include "FoeVisitor.h"
#include "Foe.h"
#include "AngrySparty.h"

FoeVisitor::FoeVisitor(AngrySparty *angrySparty) : mAngrySparty(angrySparty)
{

}
void FoeVisitor::VisitFoe(Foe* foe)
{
    auto body  = foe->GetBody();
    auto position = body->GetPosition();
    auto velo = body->GetLinearVelocity();
    if ( foe->GetDown() > position.y && foe->FoeCheck() && velo == b2Vec2(0.0f,0.0f))
    {

        std::shared_ptr<Physics> physics = mAngrySparty->GetPhysics();
        foe->SetAlive(false,physics);
        ///mAngrySparty->GetCurrentLevel()->Remove(foe);
        mKilledFoes+=1;


    }

}