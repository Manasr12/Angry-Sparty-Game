/**
 * @file Item.cpp
 * @author Trey Cosnowski
 *
 */

#include "pch.h"
#include "Item.h"
#include "AngrySparty.h"
#include "Level.h"
#include "box2d.h"


using namespace std;
/**
 * Constructor
 * @param angrySparty The angrySparty this item is a member of
 */
Item::Item(Level *level) : mLevel(level)
{

}

/**
*  Destructor
*/
Item::~Item()
{
}


/**
 * Sets image
 * @param file Sets the Item's image
 */
void Item::SetImage(const std::wstring &file)
{
    AngrySparty* angrySparty = mLevel->GetAngrySparty();
    auto imageMap = angrySparty->GetImageMap();


    if (!file.empty())
    {

        const wstring filename = L"images/" + file;
        if (imageMap.find(filename) != imageMap.end())
        {
            mItemImage = imageMap[filename].GetImage();

        }
        else
        {
            Images image;
            mItemImage = make_shared<wxImage>(filename, wxBITMAP_TYPE_ANY);
            image.SetImage(mItemImage);

            angrySparty->SetImageMap(filename, image);
        }


    }

    mFile = file;
}

void Item::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if(mItemBitmap.IsNull())
    {
        mItemBitmap = graphics->CreateBitmapFromImage(*mItemImage);
    }

}

wxGraphicsBitmap Item::GetBitmap(std::shared_ptr<wxGraphicsContext> graphics)
{

    return mItemBitmap;

}

void Item::XmlItem(wxXmlNode *node)
{
    node->GetAttribute(L"x", L"0").ToDouble(&mX);
    node->GetAttribute(L"y", L"0").ToDouble(&mY);
    node->GetAttribute(L"angle", L"0").ToDouble(&mAngle);
    mStatic = node->GetAttribute(L"type", L"dynamic").ToStdString();
}










