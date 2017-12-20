/*******************************************************************************
    File: PApp.cpp
    Purpose: Implements the entry point of the app.

    This file is property of Hashir Ahmad and Daud Akhtar Naveed from SEECS,
    NUST batch of 2k16, section 6C.
*******************************************************************************/

#include "stdafx.hpp"
#include "PFrame.hpp"
#include "PApp.hpp"

#include <wx/display.h>

extern const wxString APP_NAME = "Plagirisa";

IMPLEMENT_APP(PApp)

bool PApp::OnInit() {
	// Set the window size according to the screen size.
	const wxRect screenRect = wxDisplay().GetClientArea();
	PFrame *mainFrame = new PFrame(APP_NAME, wxPoint(0, 0),
		wxSize(screenRect.GetWidth() - 250, screenRect.GetHeight() - 150));
	mainFrame->Show();

	return true;
}
