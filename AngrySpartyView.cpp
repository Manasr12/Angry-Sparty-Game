/**
 * @file AngrySpartyView.cpp
 * @author Alex Bocchi
 */

#include "pch.h"
#include "ids.h"
#include "AngrySpartyView.h"
#include <wx/dcbuffer.h>
#include "Consts.h"

using namespace std;



/// Frame duration in seconds
const double FrameDuration = 1.0/60.0;


/**
 * Initialize function for AngrySpartyView
 * @param parent
 */
void AngrySpartyView::Initialize(wxFrame* parent)
{
    Create(parent, wxID_ANY,
            wxDefaultPosition, wxDefaultSize,
            wxFULL_REPAINT_ON_RESIZE);
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    /// Pushing

    mTimer.SetOwner(this);
    mTimer.Start(int(FrameDuration * 1000));

    Bind(wxEVT_TIMER, &AngrySpartyView::OnTimer, this);
    Bind(wxEVT_PAINT, &AngrySpartyView::OnPaint, this);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AngrySpartyView::OpenLevel1, this, IDM_LEVEL1);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AngrySpartyView::OpenLevel2, this, IDM_LEVEL2);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AngrySpartyView::OpenLevel3, this, IDM_LEVEL3);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AngrySpartyView::OpenLevel4, this, IDM_LEVEL4);

    Bind(wxEVT_LEFT_DOWN, &AngrySpartyView::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &AngrySpartyView::OnLeftUp, this);
    Bind(wxEVT_MOTION, &AngrySpartyView::OnMouseMove, this);

    mStopWatch.Start();
}



/**
* Paint event, draws the window
 * @param event Paint event object
*/
void AngrySpartyView::OnPaint(wxPaintEvent& event)
{
    // Unfinished update function


    // Update until the game time matches
    // the current time.
    auto newTime = mStopWatch.Time() * 0.001;
    while(mTime < newTime)
    {
        mTime += FrameDuration;
        mSparty.Update(FrameDuration);
        Refresh();
        mSparty.LevelState();
    }

    wxAutoBufferedPaintDC dc(this);

    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    auto size = GetClientSize();

    auto graphics = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create( dc ));
    graphics->SetInterpolationQuality(wxINTERPOLATION_BEST);

    mSparty.OnDraw(graphics, size.GetWidth() , size.GetHeight());

    // These can likely be switched into the update function once that is running
    mSparty.PrintLevelStatus(graphics);
}

void AngrySpartyView::OpenLevel4(wxCommandEvent& event){
    mSparty.SetLevel(3);


}

void AngrySpartyView::OpenLevel1(wxCommandEvent& event){
    mSparty.SetLevel(0);

}

void AngrySpartyView::OpenLevel2(wxCommandEvent& event){
    mSparty.SetLevel(1);

}

void AngrySpartyView::OpenLevel3(wxCommandEvent& event){
    mSparty.SetLevel(2);

}

/**
 * Redirects to AngrySparty::OnLeftDown
 * @param event
 */
void AngrySpartyView::OnLeftDown(wxMouseEvent &event)
{
    mSparty.OnLeftDown(event);
}

/**
 * Redirects to AngrySparty::OnLeftUp
 * @param event
 */
void AngrySpartyView::OnLeftUp(wxMouseEvent &event)
{
    mSparty.OnLeftUp(event);
}

/**
 * Redirects to AngrySparty::OnMouseMove
 * @param event
 */
void AngrySpartyView::OnMouseMove(wxMouseEvent &event)
{
    mSparty.OnMouseMove(event);
}

/**
 * Handle timer events
 * @param event Timer event
 */
void AngrySpartyView::OnTimer(wxTimerEvent &event)
{
    Refresh();
}


