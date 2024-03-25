/**
 * @file AngrySpartyApp.cpp
 * @author Mannan Dhillon
 *
 */
#include "pch.h"
#include "AngrySpartyApp.h"
#include <MainFrame.h>

/**
 * Initialize the application.
 * @return
 */
bool AngrySpartyApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    // Add image type handlers
    wxInitAllImageHandlers();

    auto frame = new MainFrame();
    frame->Initialize();
    frame->Show(true);

    return true;
}