/**
 * @file AngrySparty.cpp
 * @author ihcco
 */


#include "pch.h"
#include "Consts.h"
#include "Item.h"
#include "Block.h"
#include "Scoreboard.h"
#include "Slingshot.h"
#include "AngrySparty.h"
#include <cmath>
#include "Level.h"
#include "Images.h"
#include "Physics.h"
#include "DebugDraw.h"
#include "SpartysVisitor.h"

#ifdef WIN32
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#endif


using namespace std;

/// Level 0 file
const std::wstring Level0FileName = L"levels/level0.xml";

/// Level 1 file
const std::wstring Level1FileName = L"levels/level1.xml";

/// Level 2 file
const std::wstring Level2FileName = L"levels/level2.xml";

/// Level 3 file
const std::wstring Level3FileName = L"levels/level3.xml";

/// Directory containing the project images
const std::wstring ImagesDirectory = L"/images";

/// Max time the text is displayed
const double MaxLevelTextDuration = 3;

/// Max time the Sparty is shot
const double MaxSpartyDuration = 5;


/**
 * Draw Angry Sparty
 * @param graphics The graphics context to draw on
 * @param width The width
 * @param height The height
 */
void AngrySparty::OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height)
{
    wxBrush background(*wxBLACK);
    graphics->SetBrush(background);
    graphics->DrawRectangle(0,0,width, height);

    graphics->PushState();
    b2Vec2 playingAreaSize(mActiveLevel->GetWidth(), mActiveLevel->GetHeight());
    playingAreaSize *= Consts::MtoCM;


//     Automatic Scaling
//     We use CM display units instead of meters
//     because a 1-meter wide line is very wide

    auto scaleX = double(height) / double(playingAreaSize.y);
    auto scaleY = double(width) / double(playingAreaSize.x);
    mScale = scaleX < scaleY ? scaleX : scaleY;
    graphics->Scale(mScale, -mScale);

    // Determine the virtual size in cm
    auto virtualWidth = (double)width / mScale;
    auto virtualHeight = (double)height / mScale;

    // And the offset to the middle of the screen
    mXOffset = virtualWidth / 2.0;
    mYOffset = -(virtualHeight - playingAreaSize.y) / 2.0 - playingAreaSize.y;

    graphics->Translate(mXOffset, mYOffset);


//     From here we are dealing with centimeter pixels
//     and Y up being increase values
//
//     INSERT YOUR DRAWING CODE HERE
    mActiveLevel->Draw(graphics);

    //graphics->PopState();

    int levelScoreInt = mScoreboard.GetLevelScore();
    int totalScoreInt = mScoreboard.GetTotalScore();
    wxString levelScoreStr = wxString::Format(wxT("%i"), levelScoreInt);
    wxString totalScoreStr = wxString::Format(wxT("%i"), totalScoreInt);

    int offset = int(log10(levelScoreInt) + 1);
    if (levelScoreInt == 0)
    {
        offset = 1;
    }

    int xCoordLevel = playingAreaSize.x / 2 - 48 - (37 * (offset - 1));
    int xCoordTotal = -playingAreaSize.x / 2 + 10;
    int yCoord = -1 * (playingAreaSize.y - 10);

    int yyFont = 69;
    wxFont font(wxSize(0, yyFont),
            wxFONTFAMILY_SWISS,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_BOLD);
    graphics->SetFont(font, *wxRED);

    graphics->Scale(1, -1);
    graphics->DrawText(totalScoreStr,xCoordTotal,yCoord);
    graphics->DrawText(levelScoreStr,xCoordLevel,yCoord);


    graphics->PopState();
}
/**
* Angry Sparty Constructor
*/
AngrySparty::AngrySparty()
{
    SetImagesDirectory(L".");
    LoadLevels();
    SetLevel(1);

}

void AngrySparty::LoadLevels()
{

    auto fileName = Level0FileName;

    Load(fileName);

    fileName = Level1FileName;

    Load(fileName);

    fileName = Level2FileName;

    Load(fileName);

    fileName = Level3FileName;

    Load(fileName);


}
/**
 * Set the directory the images are stored in
 * @param dir
 */
void AngrySparty::SetImagesDirectory(const std::wstring &dir)
{
    mImagesDirectory = dir + ImagesDirectory;
}

/**
 * Loads the level
 *
 * @param filename The current file
 * @author Alex Bocchi
 */
void AngrySparty::Load(const std::wstring &filename)
{
    wxXmlDocument xmlDoc;

    if (!xmlDoc.Load(filename))
    {
        wxMessageBox(L"Unable to load Angry Sparty File");
        return;
    }


    auto root = xmlDoc.GetRoot();
    shared_ptr<Level> level;
    level = make_shared<Level>(this);

    mLevels.push_back(level);

    if (root->GetName() == L"level")
    {
        level->XmlLevel(root); /// Needs to be looked at
    }
    auto node = root->GetChildren();

    for( ; node; node = node->GetNext())
    {

        ///Pushing
        if (node->GetName() == L"items")
        {
            level->XmlItems(node);
        }

        else if (node->GetName() == L"angry")
        {
            level->XmlAngrys(node);
        }
    }

}

/**
 * Sets the image map
 *
 * @param filename The current file
 * @param image The current image
 * @author Alex Bocchi
 */
void AngrySparty::SetImageMap(const std::wstring filename, Images image){

    mImageMap[filename] = image;

}

/**
 * Sets the level
 *
 * @param level The current level
 * @author Alex Bocchi
 */

void AngrySparty::SetLevel(int level)
{
    mActiveLevel = mLevels[level];
    mActiveLevel->SetTraversal();
    mLevelNumber = level;
    mLevelTextDuration = 0;

    mSpartyShotTime = 2;
    mInit = false;

    double width = mActiveLevel->GetWidth();
    double height = mActiveLevel->GetHeight();

    b2Vec2 levelSize = b2Vec2(width, height);

    mPhysics = std::make_shared<Physics>(levelSize);

    mActiveLevel->InstallPhysics(mPhysics);
}

void AngrySparty::Update(double frameRate)
{
    mPhysics->Update(frameRate);
    UpdateLevelStatus(frameRate);
}

/**
 * Handle the left mouse button down event
 * @param event
 * @author Will Gamba
 */
void AngrySparty::OnLeftDown(wxMouseEvent &event)
{
    std::shared_ptr<Angry> active = mActiveLevel->GetActiveAngry();
    if(active != nullptr && active->GetAir())
    {
        active->InAir();
        //active->Bomb();
    }

    HitTest();
}

/**
* Handle the left mouse button up event
* @param event
* @author Will Gamba
*/
void AngrySparty::OnLeftUp(wxMouseEvent &event)
{
    if (mGrabbingItem)
    {
        std::shared_ptr<Angry> active = mActiveLevel->GetActiveAngry();
        active->Launch(mPhysics);
        mSpartyShotTime = 0;

        // Handler for released
        //double foekill = mActiveLevel->KillFoe();
    }

    mGrabbingItem = false;




}

void AngrySparty::LevelState()
{
    double check = mActiveLevel->CheckSpartys();
    int score = mActiveLevel->KillFoe() * 100;
    mScoreboard.SetLevelScore(score);
    if (check == 1)
    {
        if( mLevelNumber != 3)
        {
            mLevelNumber = mLevelNumber + 1;

        }

        mScoreboard.SetTotalScore(mScoreboard.GetLevelScore());
        mScoreboard.ResetLevelScore();
        mLevelTextDuration = 0;
        ResetLevelVariables();
        SetLevel(mLevelNumber);
    }
    if(check == 2)
    {
        mScoreboard.ResetLevelScore();
        mLevelTextDuration = 0;
        ResetLevelVariables();
        SetLevel(mLevelNumber);
    }
}

/**
 * Function to reset the variables needed to construct the level
 */
void AngrySparty::ResetLevelVariables()
{
    mMouseLocation = b2Vec2(0, 0);
    mGrabbingItem = false;
    mLevelTextDuration = 0;
    mSpartyShotTime = 2;
    mInit = false;
}

/**
* Handle the mouse move event
* @param event
* @author Will Gamba
*/
void AngrySparty::OnMouseMove(wxMouseEvent &event)
{
    auto x = (event.m_x / mScale - mXOffset) * Consts::CMtoM;
    auto y = (event.m_y / -mScale - mYOffset) * Consts::CMtoM;
    mMouseLocation = b2Vec2(x, y);

    if (mGrabbingItem)
    {
        std::shared_ptr<Angry> active = mActiveLevel->GetActiveAngry();
        active->SetPoint(mMouseLocation);
    }

}

/**
* Generic implementation for HitTest
* @return bool
* @author Will Gamba
*/
bool AngrySparty::HitTest()
{
    double testSlingX = -5.50;
    double testSlingY = 1.35;

    double testGoalX = -5.51;
    double testGoalY = 2.56;

    bool compX = (abs(mMouseLocation.x - testSlingX) < .25) || (abs(mMouseLocation.x - testGoalX) < .25);
    bool compY = (abs(mMouseLocation.y - testSlingY) < .25) || (abs(mMouseLocation.y - testGoalY) < .25);

    if (compX && compY)
    {
        mGrabbingItem = true;
    }
    else
    {
        mGrabbingItem = false;
    }
    return mGrabbingItem;
}

/**
 * Updates the duration that the image is displayed
 *
 * @param framerate double representing the duration of a frame
 */
void AngrySparty::UpdateLevelStatus(double framerate)
{
    if (mLevelTextDuration < MaxLevelTextDuration)
    {
        mLevelTextDuration += framerate;
    }

    if (mLevelTextDuration < MaxLevelTextDuration)
    {
        mLevelTextDuration += framerate;
    }


    if (mSpartyShotTime < MaxSpartyDuration && mSpartyShotTime >= 0)
    {
        mSpartyShotTime += framerate;
    }

    else if (mSpartyShotTime != -1 && !mInit)
    {
        mActiveLevel->LoadAngry();
        mSpartyShotTime = -1;
        mInit = true;
    }

    else if (mSpartyShotTime != -1)
    {

        mActiveLevel->RemoveActiveAngry();

        mSpartyShotTime = -1;
        LevelState();

    }

}

/**
 * Prints the current state of the level. Either start, completed or failed
 *
 * @param graphics pointer to the current stack for the graphics
 */
void AngrySparty::PrintLevelStatus(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();

    wxString startText = L"Level " + to_string(mLevelNumber) +  " Start";
    wxString winText = "Level " + to_string(mLevelNumber) + "Complete!";
    wxString failText = "Level " + to_string(mLevelNumber) + "Failed!";

    int yyFont = 69;

    wxFont font(wxSize(0, yyFont),
            wxFONTFAMILY_SWISS,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_BOLD);

    graphics->SetFont(font, *wxBLUE);

    // Use if statements here to check for game status
    if (mLevelTextDuration < MaxLevelTextDuration)
    {
        graphics->DrawText(startText, 346, 292);
    }

    /**
    if (mLevelTextDuration < MaxLevelTextDuration && Game is won)
    {
        graphics->DrawText(winText, 256, 292);
    }

    if (mLevelTextDuration < MaxLevelTextDuration && Game is lost
    {
        graphics->DrawText(failText, 316, 292);
    }
    */

    graphics->PopState();
}










