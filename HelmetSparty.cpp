/**
 * @file HelmetSparty.cpp
 * @author Trey Cosnowski
 *
 */

#include "pch.h"
#include "HelmetSparty.h"
#include "Consts.h"
#include "AngrySparty.h"
#include "Level.h"


/// The image to use for this sparty
const std::wstring HelmetSpartyImage = L"images/helmet-sparty.png";

/// The radius in meters
const double HelmetSpartyRadius = 0.25;

/// The velocity factor for Helmet Sparty
const float HelmetSpartyVelocityFactor = 20.0;

HelmetSparty::HelmetSparty(Level *level) : Angry(level)
{

}

/**
 * Sets the image for the block
 * @param file
 */
void HelmetSparty::SetImage(const std::wstring& file)
{
    // This save the first image supplied to SetImage to
    // a member variable so we can restore it later on
    if(!file.empty() && mHelmetImageFile.empty())
    {
        mHelmetImageFile = file;
    }

    Angry::SetImage(mHelmetImageFile);
}
/**
 * Sets values for block
 * @param node
 */
void HelmetSparty::XmlItem(wxXmlNode *node)
{

    auto file = HelmetSpartyImage;
    SetImage(file);
    Angry::XmlItem(node);
}


void HelmetSparty::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if (mOrderDraw) {
        b2Body* body = GetBody();
        if (GetDeleted()== true) {
            return;
        }
        graphics->PushState();
        auto position = body->GetPosition();
        auto angle = body->GetAngle();

        auto wid = HelmetSpartyRadius*Consts::MtoCM*2;
        auto x = position.x*Consts::MtoCM;
        auto y = position.y*Consts::MtoCM;

        graphics->Translate(x, y);
        graphics->Rotate(angle);

        std::shared_ptr<wxImage> imag = std::make_shared<wxImage>(HelmetSpartyImage, wxBITMAP_TYPE_ANY);
        wxGraphicsBitmap bitmap = graphics->CreateBitmapFromImage(*imag);

        graphics->Scale(1, -1);
        graphics->DrawBitmap(bitmap,
                -wid/2,
                -wid/2,
                wid, wid);

        graphics->PopState();
    }
}

void HelmetSparty::ReDraw(std::shared_ptr<wxGraphicsContext> graphics)
{
    b2Body* body = GetBody();
    if (GetDeleted()== true) {
        return;
    }
    graphics->PushState();
    auto position = body->GetPosition();
    auto angle = body->GetAngle();

    auto wid = HelmetSpartyRadius*Consts::MtoCM*2;
    auto x = position.x*Consts::MtoCM;
    auto y = position.y*Consts::MtoCM;

    graphics->Translate(x, y);
    graphics->Rotate(angle);

    std::shared_ptr<wxImage> imag = std::make_shared<wxImage>(HelmetSpartyImage, wxBITMAP_TYPE_ANY);
    wxGraphicsBitmap bitmap = graphics->CreateBitmapFromImage(*imag);

    graphics->Scale(1, -1);
    graphics->DrawBitmap(bitmap,
            -wid/2,
            -wid/2,
            wid, wid);

    graphics->PopState();
}

/**
 * Sets the mX and mY values to the point
 *
 * @param center b2vec representing the point to use
 */

void HelmetSparty::SetPoint(b2Vec2 point)
{
    b2Body* body = GetBody();
    body->SetTransform(point, 0);
}

/**
 * Gets the mX and mY values to the point
 *
 * @param center b2vec representing the point to use
 */
b2Vec2 HelmetSparty::GetPoint()
{
    b2Body* body = GetBody();
    return body->GetPosition();
}

/**
 * Sets the drawing status of HelmetSparty
 *
 * @param isDraw bool to determine if GruffSparty should draw or not
 */
void HelmetSparty::SetOrderDraw(bool isDraw)
{
    mOrderDraw = isDraw;
}

