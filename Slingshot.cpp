/**
 * @file Slingshot.cpp
 * @author Will Gamba
 */

#include "pch.h"
#include "Slingshot.h"
#include "box2d.h"
#include "Consts.h"

using namespace std;

/// Base filename for the slingshot image
const std::wstring WoodSlingshotBaseName = L"slingshot.png";

/// Filename for the slingshot front image
const std::wstring WoodSlingshotFrontName = L"slingshot-front.png";

/// Temporary file name for the Angry image
const std::wstring TempAngryName = L"helmet-sparty.png";

/// Size of the slingshot image in meters
const b2Vec2 WoodSlingshotSize = b2Vec2(0.5, 1.446);

/// Back band attachment point
const b2Vec2 WoodSlingshotBandAttachBack = b2Vec2(-0.15f, 1.12f);

/// Front band attachment point
const b2Vec2 WoodSlingshotBandAttachFront = b2Vec2(0.15f, 1.2f);

/// Minimum amount the slingshot can be pulled in meters
const double WoodSlingshotMinimumPull = 0.01;

/// Maximum amount the slingshot can be pulled in meters
const double WoodSlingshotMaximumPull = 1;

/// Pull angles from -pi to this value are allowed
const double SlingshotMaximumNegativePullAngle = -1.7;

/// Pull angles from +pi to this value are allowed
const double SlingshotMinimumPositivePullAngle = 2.42;

/// Width of the slingshot band in centimeters
const int SlingshotBandWidth = 15;

/// The slingshot band colour
const wxColour SlingshotBandColor = wxColour(55, 18, 1);

/// Pi
const double pi = 3.14159265358979323846;

/**
 * Constructor
 * @param level Level this slingshot is a member of
 */
Slingshot::Slingshot(Level *level) : Item(level)
{
    mLevel = level;
}

/**
 * Sets the image for the slingshot
 * @param file
 */
void Slingshot::SetImage(const std::wstring& file)
{
    if(!file.empty())
    {
        mSlingshotImageFile = file;
    }

    Item::SetImage(mSlingshotImageFile);

}

/**
 * Sets values for slingshot
 * @param node
 */
void Slingshot::XmlItem(wxXmlNode *node)
{
    auto file = WoodSlingshotBaseName;
    SetImage(file);
    Item::XmlItem(node);
}

/**
 * Draws the background slingshot object
 * @param graphics
 */
void Slingshot::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mAngry = mLevel->GetAngry();
    if (mAngry == nullptr)
    {
        mInitLoad = false;
        mAngry = nullptr;
        mCurrPoint = mAngryCenter;
        SetBand(mCurrPoint.x, mCurrPoint.y);
    }
    else if (mAngry->IsDynamic())
    {
        mInitLoad = false;
        mAngry->SetOrderDraw(true);
        mAngry = nullptr;
        mCurrPoint = mAngryCenter;
        SetBand(mCurrPoint.x, mCurrPoint.y);
    }
    if (mAngry != nullptr)
    {
        mAngry->SetOrderDraw(false);
        mCurrPoint = mAngry->GetPoint();
        SetBand(mCurrPoint.x, mCurrPoint.y);
    }

    graphics->PushState();

    auto positionX = Item::GetX();
    auto positionY = Item::GetY() + mOffsetY;
    auto angle = 0;

    graphics->Translate(positionX * Consts::MtoCM,
            positionY * Consts::MtoCM);
    graphics->Rotate(angle);

    // Make this is left side of the rectangle
    double x = -WoodSlingshotSize.x/2 * Consts::MtoCM;

    // And the top
    double y = WoodSlingshotSize.y/2 * Consts::MtoCM;

    // The width
    double xw = WoodSlingshotSize.x * Consts::MtoCM;

    Item::Draw(graphics);
    std::shared_ptr<wxGraphicsBitmap> bitmap = std::make_shared<wxGraphicsBitmap>(Item::GetBitmap(graphics));

    graphics->Translate(0, y);
    graphics->Scale(1, -1);
    graphics->DrawBitmap(*bitmap,
            x,
            0,
            xw, WoodSlingshotSize.y * Consts::MtoCM);

    graphics->PopState();

    DrawBackBand(graphics);
}

/**
 * Draws the back band of the slingshot
 * @param graphics
 */
void Slingshot::DrawBackBand(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();

    // Set the pen
    wxPen pen(SlingshotBandColor, SlingshotBandWidth);
    graphics->SetPen(pen);

    // Sets the (x1, y1) coordinate to the back left of the slingshot
    double x1 = (Item::GetX() + WoodSlingshotBandAttachBack.x) * Consts::MtoCM;
    double y1 = (Item::GetY() + WoodSlingshotBandAttachBack.y) * Consts::MtoCM;

    // Sets the (x2, y2) coordinate to the back of the sparty
    double x2 = mCurrPoint.x * Consts::MtoCM;
    double y2 = mCurrPoint.y * Consts::MtoCM;

    // Paints the line from the back left of the slingshot
    // to the back end of the sparty
    graphics->StrokeLine(x1, y1, x2, y2);

    graphics->PopState();
    DrawAngry(graphics);
}

/**
 * Draws the Angry in the slingshot
 * @param graphics
 */
void Slingshot::DrawAngry(std::shared_ptr<wxGraphicsContext> graphics)
{
    if (mAngry != nullptr) {
        if (!mInitLoad) // Set angry to the default position
        {
            mInitLoad = true;
            mAngry->SetPoint(mAngryCenter);
            mAngry->ReDraw(graphics);
        }
        else {
            mAngry->SetPoint(mCurrPoint);
            mAngry->ReDraw(graphics);
        }
    }

    DrawMiddleBand(graphics);
}

/**
 * Draws the middle band of the slingshot
 * @param graphics
 */
void Slingshot::DrawMiddleBand(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();

    // Set the pen
    wxPen pen(SlingshotBandColor, SlingshotBandWidth);
    graphics->SetPen(pen);

    // (x1, y1) coordinate is set to the middle of the sparty
    // Sets the (x2, y2) coordinate to the back of the sparty
    double x2 = mCurrPoint.x * Consts::MtoCM - (0.25 * Consts::MtoCM);
    double y2 = mCurrPoint.y * Consts::MtoCM;

    // Paints the line from the front right of the slingshot
    // to the middle of the sparty
    graphics->StrokeLine(mCurrPoint.x * Consts::MtoCM, mCurrPoint.y * Consts::MtoCM, x2, y2);

    graphics->PopState();
    DrawFront(graphics);
}

/**
 * Draws the front of the slingshot
 * @param graphics
 */
void Slingshot::DrawFront(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();

    auto positionX = Item::GetX();
    auto positionY = Item::GetY() + mOffsetY;
    auto angle = 0;

    graphics->Translate(positionX * Consts::MtoCM,
            positionY * Consts::MtoCM);
    graphics->Rotate(angle);

    // Make this is left side of the rectangle
    double x = -WoodSlingshotSize.x/2 * Consts::MtoCM;

    // And the top
    double y = WoodSlingshotSize.y/2 * Consts::MtoCM;

    // The width
    double xw = WoodSlingshotSize.x * Consts::MtoCM;

    const wstring filename = L"images/" + WoodSlingshotFrontName;
    mFrontImage = make_unique<wxImage>("images/" + WoodSlingshotFrontName, wxBITMAP_TYPE_ANY);
    auto tempBitmap = graphics->CreateBitmapFromImage(*mFrontImage);
    std::shared_ptr<wxGraphicsBitmap> bitmap = std::make_shared<wxGraphicsBitmap>(tempBitmap);

    graphics->Translate(0, y);
    graphics->Scale(1, -1);
    graphics->DrawBitmap(*bitmap,
            x,
            0,
            xw, WoodSlingshotSize.y * Consts::MtoCM);

    graphics->PopState();

    DrawFrontBand(graphics);
}

/**
 * Draws the front band of the slingshot
 * @param graphics
 */
void Slingshot::DrawFrontBand(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();

    // Set the pen
    wxPen pen(SlingshotBandColor, SlingshotBandWidth);
    graphics->SetPen(pen);

    // Sets the (x1, y1) coordinate to the front right of the slingshot
    double x1 = (Item::GetX() + WoodSlingshotBandAttachFront.x) * Consts::MtoCM;
    double y1 = (Item::GetY() + WoodSlingshotBandAttachFront.y) * Consts::MtoCM;

    // Paints the line from the front right of the slingshot
    // to the middle of the sparty
    graphics->StrokeLine(x1, y1, mCurrPoint.x * Consts::MtoCM, mCurrPoint.y * Consts::MtoCM);

    graphics->PopState();
}

/**
 * Sets the slingshot vector
 * @param x double representing x-coordinate
 * @param y double representing y-coordinate
 */
void Slingshot::SetBand(double x, double y)
{
    // This will get changed to update the position of the angry in the future
    b2Vec2 loadPoint = mAngryCenter;
    b2Vec2 mouseLocation = b2Vec2(x, y);

    // Compute the angle
    double theta = atan2(mouseLocation.y - loadPoint.y, mouseLocation.x - loadPoint.x);

    // Handles if the angle is too low
    if (theta > SlingshotMaximumNegativePullAngle && theta < 0) // Q3
    {
        mouseLocation.x =  loadPoint.x - (sin(-1 * SlingshotMaximumNegativePullAngle - pi / 2));
        mouseLocation.y =  loadPoint.y - (cos(-1 * SlingshotMaximumNegativePullAngle - pi / 2));
    }

    // Handles if the angle is too high
    if (theta < SlingshotMinimumPositivePullAngle && theta > 0) // Q2
    {
        mouseLocation.x =  loadPoint.x - (sin(SlingshotMinimumPositivePullAngle - pi / 2));
        mouseLocation.y =  loadPoint.y + (cos(SlingshotMinimumPositivePullAngle - pi / 2));
    }

    // Compute the length
    b2Vec2 toAngry = mouseLocation - loadPoint;
    double len = sqrt((toAngry.x * toAngry.x) + (toAngry.y * toAngry.y));

    // Handles if the length is too long
    double maxLen = WoodSlingshotMaximumPull + 0.01;
    if (len > maxLen)
    {
        if (theta > SlingshotMinimumPositivePullAngle && theta < pi) // Q2
        {
            mouseLocation.x =  loadPoint.x - (sin(theta - pi / 2));
            mouseLocation.y =  loadPoint.y + (cos(theta - pi / 2));
        }
        else // Q3
        {
            mouseLocation.x =  loadPoint.x - (sin(-1 * theta - pi / 2));
            mouseLocation.y =  loadPoint.y - (cos(-1 * theta - pi / 2));
        }
    }

    // Handles if the length is too short
    if (len < WoodSlingshotMinimumPull)
    {
        mouseLocation.x = loadPoint.x;
        mouseLocation.y = loadPoint.y;
    }

    mCurrPoint.x = mouseLocation.x;
    mCurrPoint.y = mouseLocation.y;

    toAngry = mouseLocation - loadPoint; // Recompute after adjustments
    mLength = sqrt((toAngry.x * toAngry.x) + (toAngry.y * toAngry.y)); // Testing temp

}

