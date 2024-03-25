/**
 * @file SpartysVisitor.cpp
 * @author ihcco
 */

#include "pch.h"
#include "SpartysVisitor.h"
#include "Angry.h"
#include "AngrySparty.h"
#include "Physics.h"

SpartysVisitor::SpartysVisitor(AngrySparty *angrySparty) : mAngrySparty(angrySparty)
{

}

void SpartysVisitor::VisitAngrySparty(Angry* angry)
{
    auto body = angry->GetBody();
    auto velo = body->GetLinearVelocity();
    if (velo.x <= 0.1f || velo.y <= 0.1f)
    {
        auto physics = mAngrySparty->GetPhysics();
        angry->DeleteAngry(physics);


    }

}
