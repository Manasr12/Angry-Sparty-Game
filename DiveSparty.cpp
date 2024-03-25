/**
 * @file DiveSparty.cpp
 * @author Trey Cosnowski
 *
 */

#include "pch.h"
#include "DiveSparty.h"
#include "Consts.h"
#include "Level.h"
#include "AngrySparty.h"

/// The image to use for this sparty
const std::wstring DiveSpartyImage = L"images/dive-sparty.png";

/// The radius in meters
const double DiveSpartyRadius = 0.25;

/// The velocity factor for Gruff Sparty
const float DiveSpartyVelocityFactor = 9.0;
const float Gravity = -9.8f;

DiveSparty::DiveSparty(Level *level) : Angry(level)
{

}

/**
 * Sets the image for the block
 * @param file
 */
void DiveSparty::SetImage(const std::wstring& file)
{
    // This save the first image supplied to SetImage to
    // a member variable so we can restore it later on
    if(!file.empty() && mDiveImageFile.empty())
    {
        mDiveImageFile = file;
    }

    Angry::SetImage(mDiveImageFile);
}
/**
 * Sets values for block
 * @param node
 */
void DiveSparty::XmlItem(wxXmlNode *node)
{
    auto file = DiveSpartyImage;

    SetImage(file);
    Angry::XmlItem(node);
}

void DiveSparty::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if (mOrderDraw) {
        b2Body* body = GetBody();
        if (GetDeleted()== true) {
            return;
        }
        graphics->PushState();
        auto position = body->GetPosition();
        auto angle = body->GetAngle();

        auto wid = DiveSpartyRadius*Consts::MtoCM*2;
        auto x = position.x*Consts::MtoCM;
        auto y = position.y*Consts::MtoCM;

        graphics->Translate(x, y);
        graphics->Rotate(angle);

        std::shared_ptr<wxImage> imag = std::make_shared<wxImage>(DiveSpartyImage, wxBITMAP_TYPE_ANY);
        wxGraphicsBitmap bitmap = graphics->CreateBitmapFromImage(*imag);

        graphics->Scale(1, -1);
        graphics->DrawBitmap(bitmap,
                             -wid/2,
                             -wid/2,
                             wid, wid);

        graphics->PopState();
    }
}

void DiveSparty::ReDraw(std::shared_ptr<wxGraphicsContext> graphics)
{
    b2Body* body = GetBody();
    if (GetDeleted()== true) {
        return;
    }
    graphics->PushState();
    auto position = body->GetPosition();
    auto angle = body->GetAngle();

    auto wid = DiveSpartyRadius*Consts::MtoCM*2;
    auto x = position.x*Consts::MtoCM;
    auto y = position.y*Consts::MtoCM;

    graphics->Translate(x, y);
    graphics->Rotate(angle);

    std::shared_ptr<wxImage> imag = std::make_shared<wxImage>(DiveSpartyImage, wxBITMAP_TYPE_ANY);
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
void DiveSparty::SetPoint(b2Vec2 point)
{
    b2Body* body = GetBody();
    body->SetTransform(point, 0);
}

/**
 * Gets the mX and mY values to the point
 *
 * @param center b2vec representing the point to use
 */
b2Vec2 DiveSparty::GetPoint()
{
    b2Body* body = GetBody();
    return body->GetPosition();
}

/**
 * Sets the drawing status of GruffSparty
 *
 * @param isDraw bool to determine if GruffSparty should draw or not
 */
void DiveSparty::SetOrderDraw(bool isDraw)
{
    mOrderDraw = isDraw;
}
void DiveSparty::InAir()
{

    GetBody()->SetLinearVelocity( b2Vec2(0.0f, Gravity) );
}


