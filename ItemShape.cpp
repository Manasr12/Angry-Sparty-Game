/**
 * @file ItemShape.cpp
 * @author Trey Cosnowski
 */

#include "pch.h"
#include "ItemShape.h"


ItemShape::ItemShape(Level *level) :  Item(level)
{

}
void ItemShape::XmlItem(wxXmlNode *node)
{
    node->GetAttribute(L"friction", L".5").ToDouble(&mFriction);
    node->GetAttribute(L"restitution", L".5").ToDouble(&mRestituation);
    node->GetAttribute(L"density", L"1").ToDouble(&mDensity);
    Item::XmlItem(node);
}


void ItemShape::PassAttributes(std::shared_ptr<Physics> physics, b2PolygonShape *shape)
{
    b2World* world = physics->GetWorld();

    // Create the body definition
    b2BodyDef bodyDefinition;
    bodyDefinition.position = b2Vec2(GetX(), GetY());
    bodyDefinition.angle = GetAngle() * (M_PI/180);

    bool staticBool;
    if (GetStatic() == "static")
    {
        staticBool = true;
    }
    else
    {
        staticBool = false;
    }

    bodyDefinition.type = staticBool ? b2_staticBody : b2_dynamicBody;

    auto body = world->CreateBody(&bodyDefinition);

    if(staticBool)
    {
        body->CreateFixture(shape, 0.0f);
    }
    else
    {
        b2FixtureDef fixtureDef;
        fixtureDef.shape = shape;
        fixtureDef.density = (float)mDensity;
        fixtureDef.friction = (float)mFriction;
        fixtureDef.restitution = (float)mRestituation;
        body->CreateFixture(&fixtureDef);
    }

    mBody = body;
}
