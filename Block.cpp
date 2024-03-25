/**
 * @file Block.cpp
 * @author Trey Cosnowski
 *
 */

#include "pch.h"
#include "Block.h"
#include "box2d.h"
#include "Consts.h"
#include <cmath>
#include "ItemShape.h"
/**
 *
 * Sets the image for block
 * @param file
 */

Block::Block(Level *level) : ItemShape(level)
{

}

/**
 * Sets the image for the block
 * @param file
 */
void Block::SetImage(const std::wstring& file)
{
    // This save the first image supplied to SetImage to
    // a member variable so we can restore it later on
    if(!file.empty() && mBlockImageFile.empty())
    {
        mBlockImageFile = file;
    }

    Item::SetImage(mBlockImageFile);
}
/**
 * Sets values for block
 * @param node
 */
void Block::XmlItem(wxXmlNode *node)
{

    auto file = node->GetAttribute(L"image", L"").ToStdWstring();
    node->GetAttribute(L"repeat-x", L"1").ToDouble(&mRepeatX);
    node->GetAttribute(L"width", L"0").ToDouble(&mWidth);
    node->GetAttribute(L"height", L"0").ToDouble(&mHeight);

    SetImage(file);
    ItemShape::XmlItem(node);
}

void Block::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    b2Body* body = GetBody();
    if (body == nullptr){
        return;
    }
    graphics->PushState();
    auto position = body->GetPosition();
    auto angle = body->GetAngle();


    graphics->Translate(position.x * Consts::MtoCM,
                        position.y * Consts::MtoCM);
    graphics->Rotate(angle);

    // Make this is left side of the rectangle
    double x = -mWidth/2 * Consts::MtoCM;

    // And the top
    double y = mHeight/2 * Consts::MtoCM;

    // The width of each repeated block
    double xw = mWidth / mRepeatX * Consts::MtoCM;

    Item::Draw(graphics);
    std::shared_ptr<wxGraphicsBitmap> bitmap = std::make_shared<wxGraphicsBitmap>(Item::GetBitmap(graphics));

    graphics->Translate(0, y);
    graphics->Scale(1, -1);
    for(int ix=0; ix<mRepeatX;  ix++)
    {
        graphics->DrawBitmap(*bitmap,
                             x,
                             0,
                             xw, mHeight * Consts::MtoCM);

        x += xw;
    }

    graphics->PopState();
}

void Block::InstallPhysics(std::shared_ptr<Physics> physics)
{
    // Create the box
    b2PolygonShape box;
    box.SetAsBox(mWidth/2, mHeight/2);
    PassAttributes(physics, &box);
}