/**
 * @file Angry.cpp
 * @author Trey Cosnowski
 *
 */

#include "pch.h"
#include "Angry.h"
#include "AngrySparty.h"
#include "Level.h"
#include "Consts.h"
#include <map>
#include "SpartysVisitor.h"

using namespace std;
/**
 * Constructor
 * @param level The level this item is a member of
 */
Angry::Angry(Level *level) : ItemShape(level)
{
    mLevel = level;


}
/**
*  Destructor
*/
Angry::~Angry()
{
}



/**
 * Sets image
 * @param file Sets the Item's image
 */
void Angry::SetImage(const std::wstring &file)
{
    // This save the first image supplied to SetImage to
    // a member variable so we can restore it later on
    if(!file.empty() && mFile.empty())
    {
        mFile = file;
    }

    //Item::SetImage(mFile);
}

void Angry::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if(mAngryBitmap.IsNull())
    {
        mAngryBitmap = graphics->CreateBitmapFromImage(*mAngryImage);
    }
}

void Angry::XmlItem(wxXmlNode *node)
{
    auto parent = node->GetParent();
    parent->GetAttribute(L"spacing", "0").ToDouble(&mSpacing);
    mSpacing *= mLevel->GetNumSpartys();
    parent->GetAttribute(L"x", L"0").ToDouble(&mX);
    parent->GetAttribute(L"y", L"0").ToDouble(&mY);
    mStatic = node->GetAttribute(L"type", L"static").ToStdString();
    //mRadius = node->GetRadius();

}

/**
 * Installs the physics for the angry sparty body
 * @param physics the physics of the world
 */

void Angry::InstallPhysics(std::shared_ptr<Physics> physics)
{
    mDeleted = false;
    mPhysics = physics;
    b2World* world = physics->GetWorld();

    // Create the body definition
    b2BodyDef bodyDefinition;
    bodyDefinition.position = b2Vec2(mX + mSpacing, mY);
    bodyDefinition.angle = GetAngle() * (M_PI/180);

    std::vector<b2Vec2> vertices;
    b2PolygonShape poly;
    double deg = (180 * (8-2)) / 8;
    double step = 360 / 8;
    double rad = deg * (M_PI/180);


    for(int i = 0; i < 8; i++)
    {
        double x = 0.25* sin(rad);
        double y = 0.25* cos(rad);
        vertices.push_back(b2Vec2(x, y));
        deg-= step;
        rad= deg * (M_PI/180);
    }
    poly.Set(&vertices[0], vertices.size());
    PassAttributes(physics,&poly);

    auto body = world->CreateBody(&bodyDefinition);

    bool staticBool;
    if (mStatic == "static")
    {
        staticBool = true;
    }
    else
    {
        staticBool = false;
    }

    bodyDefinition.type = staticBool ? b2_staticBody : b2_dynamicBody;


    if(staticBool)
    {
        body->CreateFixture(&poly, 0.0f);
    }
    else
    {
        b2BodyDef bodyDefinition;
        bodyDefinition.position = b2Vec2(-6.5, 0.3); // Should this be mX, mY?
        //bodyDefinition.position = b2Vec2(mX, mY);
        bodyDefinition.angle = GetAngle() * (M_PI/180);
        bodyDefinition.type = b2_dynamicBody;
        bodyDefinition.angularDamping = 0.9;
        bodyDefinition.linearDamping = 0.1;
        body = world->CreateBody(&bodyDefinition);


        b2FixtureDef fixtureDef;
        fixtureDef.shape = &poly;
        fixtureDef.density = (float)5;
        fixtureDef.friction = 1;
        fixtureDef.restitution = 0.3;
        body->CreateFixture(&fixtureDef);

        //direction *= velocityFactor;
        //body->SetLinearVelocity(direction);
    }

    ItemShape::SetBody(body);

}

//std::shared_ptr<Angry> Angry::HitTest(int x, int y)
//{
//    auto fixture = mBody->GetFixtureList();
//    for( ; fixture != nullptr; fixture = fixture->GetNext())
//    {
//        if(fixture->TestPoint(b2Vec2(x, y)))
//        {
//            //return(this);
//        }
//    }
//}

/**
 * Sets the mX and mY values to the point
 *
 * @param point b2vec representing the point to use
 */

void Angry::SetPoint(b2Vec2 point)
{
    b2Body* body = GetBody();
    body->SetTransform(point, 0);
}

/**
 * Returns the status of the angry either static or dynamic
 * @return bool representing whether the status is dynamic
 */
bool Angry::IsDynamic()
{
    return mStatic == "dynamic";
}

/**
 * Sets the status of the angry to dynamic
 * @param physics
 */
void Angry::Launch(std::shared_ptr<Physics> physics)
{
    mStatic = "dynamic";
    b2Body* body = GetBody();
    b2World* world = physics->GetWorld();

    // Get the position and angle before
    // we destroy the body.
    auto position = body->GetPosition();
    auto angle = body->GetAngle();
    auto direction = initLocation;

    // Destroy the body in the physics system
    world->DestroyBody(body);

    // Create the body definition
    b2BodyDef bodyDefinition;
    bodyDefinition.position = position;
    bodyDefinition.angle = angle;
    bodyDefinition.type = b2_dynamicBody;
    bodyDefinition.angularDamping = 0.9;
    bodyDefinition.linearDamping = 0.1;
    body = world->CreateBody(&bodyDefinition);

    // Create the shape
    b2CircleShape circle;
    circle.m_radius = (float)mRadius;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circle;
    fixtureDef.density = (float)5;
    fixtureDef.friction = 1;
    fixtureDef.restitution = 0.3;

    body->CreateFixture(&fixtureDef);

    direction *= 3;
    body->SetLinearVelocity(direction);
    ItemShape::SetBody(body);
    mAir = true;

}

/**
 * Reset the location of the angrys
 */
void Angry::Reset()
{


    b2Body* body = GetBody();
    auto velo = body->GetLinearVelocity();
    if(velo.x <= 0.0f || velo.y <= 0.0f)
    {
        mPhysics->DestroyBody(body);
    }



}

void Angry::DeleteAngry(std::shared_ptr<Physics> physics)
{
    if(mAir == true)
    {
        physics->DestroyBody(GetBody());
        mDeleted = true;
        mAir = false;
    }
}







