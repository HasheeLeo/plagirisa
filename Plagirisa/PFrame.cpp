/*******************************************************************************
    File: PFrame.cpp
    Purpose: Implements the main frame (window) of the app.

    This file is property of Hashir Ahmad and Daud Akhtar Naveed from SEECS,
    NUST batch of 2k16, section 6C.
*******************************************************************************/

#include "stdafx.hpp"
#include "PFrame.hpp"
#include "rabinkarp.hpp"

#include <wx/button.h>
#include <wx/sizer.h>

#include <string>
#include <vector>

PFrame::PFrame(const wxString &title, const wxPoint &pos, const wxSize &size,
	long style)
	: wxFrame(nullptr, wxID_ANY, title, pos, size, style)
{
	// Create and add the controls
	wxBoxSizer *horizSizer = new wxBoxSizer(wxHORIZONTAL);
	horizSizer->AddSpacer(15);
	inputCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
		wxDefaultSize, wxTE_MULTILINE | wxTE_RICH2);
	horizSizer->Add(inputCtrl, 1, wxEXPAND);
	horizSizer->AddSpacer(20);
	matchCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
		wxDefaultSize, wxTE_MULTILINE | wxTE_RICH2);
	horizSizer->Add(matchCtrl, 1, wxEXPAND);
	horizSizer->AddSpacer(15);

	wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
	topSizer->AddSpacer(10);
	topSizer->Add(horizSizer, 1, wxEXPAND);
	topSizer->AddSpacer(15);
	topSizer->Add(new wxButton(this, wxID_ANY, "Check"), 0, wxCENTER);
	topSizer->AddSpacer(10);
	SetSizer(topSizer);
}

wxBEGIN_EVENT_TABLE(PFrame, wxFrame)
	EVT_BUTTON(wxID_ANY, PFrame::onCheck)
wxEND_EVENT_TABLE()

void PFrame::onCheck(wxCommandEvent &event) {
	const std::string haystack((inputCtrl->GetValue()).c_str());
	const std::string needle((matchCtrl->GetValue()).c_str());
	// Remove last highlights
	wxTextAttr textAttr;
	textAttr.SetBackgroundColour(*wxWHITE);
	inputCtrl->SetStyle(0, haystack.length(), textAttr);
	// Add new highlights
	textAttr.SetBackgroundColour(*wxYELLOW);

	// TODO: Fix this to work with new rabinkarp algorithm (multiple patterns)
	//const std::vector<int> indices = rabinkarp(haystack, needle);
	//for (int i : indices)
		//inputCtrl->SetStyle(i, i + needle.length(), textAttr);
}
