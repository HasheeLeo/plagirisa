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

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

static std::string commonWords;

bool update_filter_words() {
	std::ifstream file("common-words.txt");
	if (!file)
		return false;

	// Read the words into "commonWords"
	std::ostringstream os;
	os << file.rdbuf();
	commonWords = os.str();
	return true;
}

// Adds all the needles (delimited by non-alpha characters) to a vector and
// returns it
static std::vector<std::string> parse_needles(const std::string &str) {
	std::vector<std::string> needles;
	const int strLen = str.length();
	for (int i = 0; i < strLen; ++i) {
		int j = i;
		// We are ignoring everything except alphabets
		while (isalpha(str[j]) && j < strLen)
			++j;

		if (i < j) {
			// Ignore common and short words
			// (they just increase the likelihood of false positives)
			const std::string needle = str.substr(i, j - i);
			if (needle.length() < 4 ||
				rabinkarp(commonWords, needle).size() > 0)
				continue;

			needles.push_back(needle);
			i = j;
		}
	}
	return needles;
}

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

void PFrame::highlightIndices(const std::vector<int> &indices,
	const std::string &haystack) {
	// Remove old highlights
	wxTextAttr textAttr;
	textAttr.SetBackgroundColour(*wxWHITE);
	const int haystackLen = haystack.length();
	inputCtrl->SetStyle(0, haystackLen, textAttr);
	// Add new highlights
	textAttr.SetBackgroundColour(*wxYELLOW);
	for (int i : indices) {
		int j = i;
		while (isalpha(haystack[j]) && j < haystackLen)
			++j;

		if(i < j)
			inputCtrl->SetStyle(i, j, textAttr);
	}
}

wxBEGIN_EVENT_TABLE(PFrame, wxFrame)
	EVT_BUTTON(wxID_ANY, PFrame::onCheck)
wxEND_EVENT_TABLE()

void PFrame::onCheck(wxCommandEvent &event) {
	const std::string haystack((inputCtrl->GetValue()).c_str());
	const std::string needles((matchCtrl->GetValue()).c_str());
	const std::vector<int> indices = rabinkarp(haystack,
		parse_needles(needles));
	highlightIndices(indices, haystack);
}
