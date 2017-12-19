/*******************************************************************************
    File: PFrame.cpp
    Purpose: Implements the main frame (window) of the app.

    This file is property of Hashir Ahmad and Daud Akhtar Naveed from SEECS,
    NUST batch of 2k16, section 6C.
*******************************************************************************/

#include "stdafx.hpp"
#include "PFrame.hpp"

#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>

PFrame::PFrame(const wxString &title, const wxPoint &pos, const wxSize &size,
	long style)
	: wxFrame(nullptr, wxID_ANY, title, pos, size, style)
{
	wxBoxSizer *horizSizer = new wxBoxSizer(wxHORIZONTAL);
	horizSizer->AddSpacer(15);
	horizSizer->Add(new wxTextCtrl(this, wxID_ANY), 1, wxEXPAND);
	horizSizer->AddSpacer(20);
	horizSizer->Add(new wxTextCtrl(this, wxID_ANY), 1, wxEXPAND);
	horizSizer->AddSpacer(15);

	wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
	topSizer->AddSpacer(10);
	topSizer->Add(horizSizer, 1, wxEXPAND);
	topSizer->AddSpacer(15);
	topSizer->Add(new wxButton(this, wxID_ANY, "Check"), 0, wxCENTER);
	topSizer->AddSpacer(10);
	SetSizer(topSizer);
}
