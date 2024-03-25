/**
 * @file Background.cpp
 * @author Alex Bocchi
 */
#include "pch.h"
#include "Background.h"
#include "Consts.h"
#include "Item.h"



/**
 * Constructor for background
 *
 */
Background::Background(Level *level) : Item(level)
{

}
/**
 * Sets the image for the background
 * @param file
*/
void Background::SetImage(const std::wstring& file)
{

    if (!file.empty() && mBackground.empty())
    {
        mBackground = "images/" + file;

    }

    Item::SetImage(file);
}

/**
 * Set value for the background
 * @param node
 */
 void Background::XmlItem(wxXmlNode *node)
{
     auto file = node->GetAttribute(L"image", L"").ToStdWstring();
     node->GetAttribute(L"height", L"0").ToDouble(&mHeight);
     node->GetAttribute(L"width", L"0").ToDouble(&mWidth);
     SetSize(mWidth, mHeight);
     SetImage(file);
     Item::XmlItem(node);
}


/**
 * Draw the background
 * @param graphics
 */
 void Background::Draw(std::shared_ptr<wxGraphicsContext> graphics)
 {
     auto wid = mWidth * Consts::MtoCM;
     auto hit = mHeight * Consts::MtoCM;

     if (!mBackground.empty())
     {
         std::shared_ptr<wxImage> imag = std::make_shared<wxImage>(mBackground, wxBITMAP_TYPE_ANY);
         mBitmap = graphics->CreateBitmapFromImage(*imag);

         graphics->PushState();
         graphics->Scale(1, -1);
         graphics->DrawBitmap(mBitmap,
                 -wid/2,
                 -hit,
                 wid, hit);
         graphics->PopState();
     }
 }





