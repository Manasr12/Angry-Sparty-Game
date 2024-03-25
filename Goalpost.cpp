/**
 * @file Goalpost.cpp
 * @author Will Gamba
 */

#include "pch.h"
#include "Goalpost.h"
#include "box2d.h"
#include "Consts.h"

using namespace std;

/// Base filename for the goalpost image
const std::wstring GoalpostBaseName = L"goalposts.png";

/// Filename for the goalpost front image
const std::wstring GoalpostFrontName = L"goalposts-front.png";

/// Temporary file name for the Angry image
const std::wstring TempAngryName = L"helmet-sparty.png";

/// Size of the goalpost image in meters
const b2Vec2 GoalpostSize = b2Vec2(1, 2.649);

/// Back band attachment point
const b2Vec2 GoalpostBandAttachBack = b2Vec2(-0.42f, 2.3f);

/// Front band attachment point
const b2Vec2 GoalpostBandAttachFront = b2Vec2(0.34f, 2.32f);

/// Minimum amount the Goalpost can be pulled in meters
const double GoalpostMinimumPull = 0.01;

/// Maximum amount the Goalpost can be pulled in meters
const double GoalpostMaximumPull = 2;

/// Pull angles from -pi to this value are allowed
const double GoalpostMaximumNegativePullAngle = -1.7;

/// Pull angles from +pi to this value are allowed
const double GoalpostMinimumPositivePullAngle = 2.42;

/// Width of the Goalpost band in centimeters
const int GoalpostBandWidth = 15;

/// The v band colour
const wxColour GoalpostBandColor = wxColour(55, 18, 1);

/// Pi
const double pi = 3.14159265358979323846;

/**
 * Constructor
 * @param level Level this Goalpost is a member of
 */
Goalpost::Goalpost(Level *level) : Item(level)
{
    mLevel = level;
}

/**
 * Sets the image for the Goalpost
 * @param file
 */
void Goalpost::SetImage(const std::wstring& file)
{
    if(!file.empty())
    {
        mGoalpostImageFile = file;
    }

    Item::SetImage(mGoalpostImageFile);

}

/**
 * Sets values for Goalpost
 * @param node
 */
void Goalpost::XmlItem(wxXmlNode *node)
{
    auto file = GoalpostBaseName;
    SetImage(file);
    Item::XmlItem(node);
}

/**
 * Draws the background Goalpost object
 * @param graphics
 */
void Goalpost::Draw(std::shared_ptr<wxGraphicsContext> graphics)
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
    double x = -GoalpostSize.x/2 * Consts::MtoCM;

    // And the top
    double y = GoalpostSize.y/2 * Consts::MtoCM;

    // The width
    double xw = GoalpostSize.x * Consts::MtoCM;

    Item::Draw(graphics);
    std::shared_ptr<wxGraphicsBitmap> bitmap = std::make_shared<wxGraphicsBitmap>(Item::GetBitmap(graphics));

    graphics->Translate(0, y);
    graphics->Scale(1, -1);
    graphics->DrawBitmap(*bitmap,
            x,
            0,
            xw, GoalpostSize.y * Consts::MtoCM);

    graphics->PopState();
    DrawBackBand(graphics);
}

/**
 * Draws the back band of the Goalpost
 * @param graphics
 */
void Goalpost::DrawBackBand(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();

    // Set the pen
    wxPen pen(GoalpostBandColor, GoalpostBandWidth);
    graphics->SetPen(pen);

    // Sets the (x1, y1) coordinate to the back left of the Goalpost
    double x1 = (Item::GetX() + GoalpostBandAttachBack.x) * Consts::MtoCM;
    double y1 = (Item::GetY() + GoalpostBandAttachBack.y) * Consts::MtoCM;

    // Sets the (x2, y2) coordinate to the back of the sparty
    double x2 = mCurrPoint.x * Consts::MtoCM;
    double y2 = mCurrPoint.y * Consts::MtoCM;

    // Paints the line from the back left of the Goalpost
    // to the back end of the sparty
    graphics->StrokeLine(x1, y1, x2, y2);

    graphics->PopState();
    DrawAngry(graphics);
}

/**
 * Draws the Angry in the Goalpost
 * @param graphics
 */
void Goalpost::DrawAngry(std::shared_ptr<wxGraphicsContext> graphics)
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
 * Draws the middle band of the Goalpost
 * @param graphics
 */
void Goalpost::DrawMiddleBand(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();

    // Set the pen
    wxPen pen(GoalpostBandColor, GoalpostBandWidth);
    graphics->SetPen(pen);

    // (x1, y1) coordinate is set to the middle of the sparty
    // Sets the (x2, y2) coordinate to the back of the sparty
    double x2 = mCurrPoint.x * Consts::MtoCM - (0.25 * Consts::MtoCM);
    double y2 = mCurrPoint.y * Consts::MtoCM;

    // Paints the line from the front right of the Goalpost
    // to the middle of the sparty
    graphics->StrokeLine(mCurrPoint.x * Consts::MtoCM, mCurrPoint.y * Consts::MtoCM, x2, y2);

    graphics->PopState();
    DrawFront(graphics);
}

/**
 * Draws the front of the Goalpost
 * @param graphics
 */
void Goalpost::DrawFront(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();

    auto positionX = Item::GetX();
    auto positionY = Item::GetY() + mOffsetY;
    auto angle = 0;

    graphics->Translate(positionX * Consts::MtoCM,
            positionY * Consts::MtoCM);
    graphics->Rotate(angle);

    // Make this is left side of the rectangle
    double x = -GoalpostSize.x/2 * Consts::MtoCM;

    // And the top
    double y = GoalpostSize.y/2 * Consts::MtoCM;

    // The width
    double xw = GoalpostSize.x * Consts::MtoCM;

    const wstring filename = L"images/" + GoalpostFrontName;
    mFrontImage = make_unique<wxImage>("images/" + GoalpostFrontName, wxBITMAP_TYPE_ANY);
    auto tempBitmap = graphics->CreateBitmapFromImage(*mFrontImage);
    std::shared_ptr<wxGraphicsBitmap> bitmap = std::make_shared<wxGraphicsBitmap>(tempBitmap);

    graphics->Translate(0, y);
    graphics->Scale(1, -1);
    graphics->DrawBitmap(*bitmap,
            x,
            0,
            xw, GoalpostSize.y * Consts::MtoCM);

    graphics->PopState();

    DrawFrontBand(graphics);
}

/**
 * Draws the front band of the Goalpost
 * @param graphics
 */
void Goalpost::DrawFrontBand(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();

    // Set the pen
    wxPen pen(GoalpostBandColor, GoalpostBandWidth);
    graphics->SetPen(pen);

    // Sets the (x1, y1) coordinate to the front right of the Goalpost
    double x1 = (Item::GetX() + GoalpostBandAttachFront.x) * Consts::MtoCM;
    double y1 = (Item::GetY() + GoalpostBandAttachFront.y) * Consts::MtoCM;

    // Paints the line from the front right of the Goalpost
    // to the middle of the sparty
    graphics->StrokeLine(x1, y1, mCurrPoint.x * Consts::MtoCM, mCurrPoint.y * Consts::MtoCM);

    graphics->PopState();
}

/**
 * Sets the goalpost band vector
 * @param x double representing x-coordinate
 * @param y double representing y-coordinate
 */
void Goalpost::SetBand(double x, double y)
{
    // This will get changed to update the position of the angry in the future
    b2Vec2 loadPoint = mAngryCenter;
    b2Vec2 mouseLocation = b2Vec2(x, y);

    // Compute the angle
    double theta = atan2(mouseLocation.y - loadPoint.y, mouseLocation.x - loadPoint.x);

    // Handles if the angle is too low
    if (theta > GoalpostMaximumNegativePullAngle && theta < 0) // Q3
    {
        mouseLocation.x =  loadPoint.x - (sin(-1 * GoalpostMaximumNegativePullAngle - pi / 2) * GoalpostMaximumPull);
        mouseLocation.y =  loadPoint.y - (cos(-1 * GoalpostMaximumNegativePullAngle - pi / 2) * GoalpostMaximumPull);
    }

    // Handles if the angle is too high
    if (theta < GoalpostMinimumPositivePullAngle && theta > 0) // Q2
    {
        mouseLocation.x =  loadPoint.x - (sin(GoalpostMinimumPositivePullAngle - pi / 2) * GoalpostMaximumPull);
        mouseLocation.y =  loadPoint.y + (cos(GoalpostMinimumPositivePullAngle - pi / 2) * GoalpostMaximumPull);
    }

    // Compute the length
    b2Vec2 toAngry = mouseLocation - loadPoint;
    double len = sqrt((toAngry.x * toAngry.x) + (toAngry.y * toAngry.y));

    // Handles if the length is too long
    double maxLen = GoalpostMaximumPull + 0.01;
    if (len > maxLen)
    {
        if (theta > GoalpostMinimumPositivePullAngle && theta < pi) // Q2
        {
            mouseLocation.x =  loadPoint.x - (sin(theta - pi / 2) * GoalpostMaximumPull);
            mouseLocation.y =  loadPoint.y + (cos(theta - pi / 2) * GoalpostMaximumPull);
        }
        else // Q3
        {
            mouseLocation.x =  loadPoint.x - (sin(-1 * theta - pi / 2) * GoalpostMaximumPull);
            mouseLocation.y =  loadPoint.y - (cos(-1 * theta - pi / 2) * GoalpostMaximumPull);
        }
    }

    // Handles if the length is too short
    if (len < GoalpostMinimumPull)
    {
        mouseLocation.x = loadPoint.x;
        mouseLocation.y = loadPoint.y;
    }

    mCurrPoint.x = mouseLocation.x;
    mCurrPoint.y = mouseLocation.y;

    toAngry = mouseLocation - loadPoint; // Recompute after adjustments
    mLength = sqrt((toAngry.x * toAngry.x) + (toAngry.y * toAngry.y)); // Testing temp

}

