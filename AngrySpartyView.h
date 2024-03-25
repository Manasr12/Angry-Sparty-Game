/**
 * @file AngrySpartyView.h
 * @author Alex Bocchi
 *
 * Initializes the Angry Sparty view class
 */

#include "AngrySparty.h"
#ifndef PROJECT_1_ANGRYSPARTYVIEW_H
#define PROJECT_1_ANGRYSPARTYVIEW_H

/**
 * Angry Sparty view class
 */
class AngrySpartyView : public wxWindow{
private:
    /// The current AngrySparty
    AngrySparty mSparty;

    /// The timer at allows for animation
    wxTimer mTimer;

    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;

    /// The last stopwatch time
    double mTime = 0;

    void OnPaint(wxPaintEvent& event);

public:
    void Initialize(wxFrame *parent);
    /**
     * open level 4
     * @param event
     */
    void OpenLevel4(wxCommandEvent& event);
    /**
     * open level 1
     * @param event
     */
    void OpenLevel1(wxCommandEvent& event);
    /**
     * open level 2
     * @param event
     */
    void OpenLevel2(wxCommandEvent& event);
    /**
     * open level 3
     * @param event
     */
    void OpenLevel3(wxCommandEvent& event);
    void OnLeftDown(wxMouseEvent &event);
    void OnLeftUp(wxMouseEvent &event);
    void OnMouseMove(wxMouseEvent &event);
    void OnTimer(wxTimerEvent &event);

    /**
     * Stop the timer so the window can close
     */
    void Stop() {mTimer.Stop();}

};

#endif //PROJECT_1_ANGRYSPARTYVIEW_H
