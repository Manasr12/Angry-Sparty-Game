/**
 * @file MainFrame.h
 * @author Alex Bocchi
 *
 * Class that initializes the mainframe
 */

#ifndef PROJECT_1_MAINFRAME_H
#define PROJECT_1_MAINFRAME_H


class AngrySpartyView;
/**
 *  The top-level (main) frame of the application
 */
class MainFrame : public wxFrame {
private:
    void OnExit(wxCommandEvent& event);
    void AboutApp(wxCommandEvent& event);
    AngrySpartyView* mAngrySpartyView;


public:
    void Initialize();
    void OnClose(wxCloseEvent &event);




};

#endif //PROJECT_1_MAINFRAME_H
