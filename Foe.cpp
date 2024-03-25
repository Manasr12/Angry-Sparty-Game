/**
 * @file Foe.cpp
 * @author Alex Bocchi
 */

#include "pch.h"
#include "Foe.h"
#include "AngrySparty.h"
#include "Consts.h"
#include <vector>
#include <math.h>

using namespace std;


/**
 * Constructor
 * @param level the level this foe is in
 */
Foe::Foe(Level *level) : ItemShape(level)
{

}
/**
*  Destructor
*/
Foe::~Foe()
{
}

void Foe::SetImage(const std::wstring& file)
{
    // This save the first image supplied to SetImage to
    // a member variable so we can restore it later on
    if(!file.empty() && mFoeImageFile.empty())
    {
        mFoeImageFile = file;
    }

    Item::SetImage(mFoeImageFile);
}
/**
 * Sets values for block
 * @param node
 */
void Foe::XmlItem(wxXmlNode *node)
{
    node->GetAttribute(L"radius", L"0").ToDouble(&mRadius);
    node->GetAttribute(L"down", L"0").ToDouble(&mDown);
    auto file = node->GetAttribute(L"image", L"").ToStdWstring();

    SetImage(file);
    Item::XmlItem(node);
}

void Foe::Draw(std::shared_ptr<wxGraphicsContext> graphics){
    if (mFoeState)
    {

        auto body = GetBody();
        if (body == nullptr) {
            return;
        }
        auto position = body->GetPosition();
        auto angle = body->GetAngle();

        auto wid = mRadius * Consts::MtoCM * 2;
        auto x = position.x * Consts::MtoCM;
        auto y = position.y * Consts::MtoCM;

        graphics->PushState();
        graphics->Translate(x, y);
        graphics->Rotate(angle);

        Item::Draw(graphics);
        std::shared_ptr<wxGraphicsBitmap> bitmap = std::make_shared<wxGraphicsBitmap>(Item::GetBitmap(graphics));

        graphics->Scale(1, -1);
        graphics->DrawBitmap(*bitmap,
                             -wid / 2,
                             -wid / 2,
                             wid, wid);

        graphics->PopState();
    }
}

void Foe::InstallPhysics(std::shared_ptr<Physics> physics)
{
    mFoeState = true;
    std::vector<b2Vec2> vertices;
    b2PolygonShape poly;
    double deg = (180 * (8-2)) / 8;
    double step = 360 / 8;
    double rad = deg * (M_PI/180);

    for(int i = 0; i < 8; i++)
    {
        double x = mRadius* sin(rad);
        double y = mRadius* cos(rad);
        vertices.push_back(b2Vec2(x, y));
        deg-= step;
        rad= deg * (M_PI/180);
    }
    poly.Set(&vertices[0], vertices.size());
    PassAttributes(physics,&poly);


}
void Foe::SetAlive(bool alive, std::shared_ptr<Physics> physics)
{
    mFoeState = alive;

    physics->DestroyBody(GetBody());
}
//bool Foe::TestDown(){
//    auto body = GetBody();
//    //get position
//    auto position = body->GetPosition();
//
//    if (position.y < mDown)
//    {
//        return true;
//    }
//    else
//        return false;
//    //check if y is greater mdown
//    //
//}