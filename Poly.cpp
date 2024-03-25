/**
 * @file Poly.cpp
 * @author Trey Cosnowski
 *
 */

#include "pch.h"
#include "Poly.h"
#include "Consts.h"
#include <b2_body.h>
#include "ItemShape.h"

/**
 *
 * Constructor for poly
 * @param level
 */

Poly::Poly(Level *level) : ItemShape(level)
{

}

/**
 *
 * Sets the image for poly
 * @param file
 * @author Mannan Dhillon
 */
void Poly::SetImage(const std::wstring& file)
{
    // This save the first image supplied to SetImage to
    // a member variable so we can restore it later on
    Item::SetImage(file);
    if(!file.empty() && mPolyImageFile.empty())
    {
        mPolyImageFile = file;
    }


}
/**
 * Sets values for poly
 * @author Mannan Dhillon
 */
void Poly::XmlItem(wxXmlNode *node)
{

    auto file = node->GetAttribute(L"image", L"").ToStdWstring();
    auto child = node->GetChildren();
    int variable = 0;
    for( ; child; child = child->GetNext()) {
        if (child ->GetName() == L"v"){
            child->GetAttribute(L"x", L"0").ToDouble(&mFirstVertX);
            child->GetAttribute(L"y", L"0").ToDouble(&mFirstVertY);
            //b2Vec2 mFirstVertX;
            //b2Vec2 mFirstVertY;

            mVertices[variable].Set((float)mFirstVertX,(float)mFirstVertY);
            variable += 1;


        }



    }
    SetImage(file);
    ItemShape::XmlItem(node);

}
/**
 * Draws the poly
 * @author Mannan Dhillon
 */
void Poly::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    auto body = GetBody();
    if (body == nullptr){
        return;
    }
    auto position = body->GetPosition();
    auto angle = body->GetAngle();

    // Find the minimum and maximum x/y values
    b2Vec2 minimums = mVertices[0];
    b2Vec2 maximums = mVertices[0];
    for(auto v : mVertices)
    {
        minimums.x = fmin(minimums.x, v.x);
        minimums.y = fmin(minimums.y, v.y);
        maximums.x = fmax(maximums.x, v.x);
        maximums.y = fmax(maximums.y, v.y);
    }

    auto size = maximums - minimums;

    auto x = position.x * Consts::MtoCM;
    auto y = position.y * Consts::MtoCM;

    graphics->PushState();
    graphics->Translate(x, y);
    graphics->Rotate(angle);

    Item::Draw(graphics);
    std::shared_ptr<wxGraphicsBitmap> bitmap = std::make_shared<wxGraphicsBitmap>(Item::GetBitmap(graphics));

    graphics->Scale(1, -1);
    graphics->DrawBitmap(*bitmap,
                         minimums.x * Consts::MtoCM,
                         minimums.y * Consts::MtoCM,
                         size.x * Consts::MtoCM,
                         size.y * Consts::MtoCM);

    graphics->PopState();
}
/**
 * Installs the poly physics
 * @author Mannan Dhillon
 */
void Poly::InstallPhysics(std::shared_ptr<Physics> physics)
{
    //Create the polygon
    b2PolygonShape polygonShape;
    polygonShape.Set(mVertices,3);
    PassAttributes(physics, &polygonShape);
}