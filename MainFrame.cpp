/**
 * @file MainFrame.cpp
 * @author Alex Bocchi
 */

#include "pch.h"
#include "ids.h"
#include "MainFrame.h"
#include "AngrySpartyView.h"
#include "Consts.h"
#include <wx/wxprec.h>

/**
 * Initialize the MainFrame window
 */

void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"Angry Sparty App",
            wxDefaultPosition, wxSize(1100, 700));

#ifdef WIN32
    SetIcon(wxIcon(L"mainframe", wxBITMAP_TYPE_ICO_RESOURCE));
#endif

    // Create a sizer that will lay out child windows vertically
    // one above each other
    auto sizer = new wxBoxSizer( wxVERTICAL );

    // Create the view class object as a child of MainFrame
    mAngrySpartyView = new AngrySpartyView();
    mAngrySpartyView->Initialize(this);

    // Add it to the sizer
    sizer->Add(mAngrySpartyView,1, wxEXPAND | wxALL );

    // Set the sizer for this frame
    SetSizer( sizer );

    // Layout (place) the child windows.
    Layout();

    auto menuBar = new wxMenuBar();
    auto fileMenu = new wxMenu();
    auto helpMenu = new wxMenu();
    auto levelsMenu = new wxMenu();


    menuBar->Append(fileMenu, L"&File" );
    menuBar->Append(levelsMenu, L"&Levels");
    menuBar->Append(helpMenu, L"&Help");
    fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");
    levelsMenu->Append(IDM_LEVEL1, L"&Level 0", L"Level 0");
    levelsMenu->Append(IDM_LEVEL2, L"&Level 1", L"Level 1");
    levelsMenu->Append(IDM_LEVEL3, L"&Level 2", L"Level 2");
    levelsMenu->Append(IDM_LEVEL4, L"&Level 3", L"Level 3");
    helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");


    SetMenuBar(menuBar);

    CreateStatusBar(1, wxSTB_SIZEGRIP, wxID_ANY);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::AboutApp, this, wxID_ABOUT);

    Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);



}



/**
* Exit menu option handlers
 * @param event
*/
void MainFrame::OnExit(wxCommandEvent& event)
{

    Close(true);
}

/**
* About menu option handlers
 * @param event
*/
void MainFrame::AboutApp(wxCommandEvent& event)
{
    wxMessageBox(L"Angry Sparty App!",
            L"About Angry Sparty App",
            wxOK,
            this);
}

void MainFrame::OnClose(wxCloseEvent& event)
{
    mAngrySpartyView->Stop();
    Destroy();
}


