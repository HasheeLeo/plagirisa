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
#include <wx/filedlg.h>
#include <wx/menu.h>
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
	// Create and set menu
	wxMenu *menuFile = new wxMenu;
	menuFile->Append(MENUFILE_OPEN, "&Open\tCtrl+O");
	wxMenuBar *menu = new wxMenuBar;
	menu->Append(menuFile, "&File");
	SetMenuBar(menu);

	// Create and add the controls
	inputCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
		wxDefaultSize, wxTE_MULTILINE | wxTE_RICH2);
	inputCtrl->SetFont(wxFont(wxFontInfo(11)));
	wxBoxSizer *controlLabelSizer1 = new wxBoxSizer(wxVERTICAL);
	controlLabelSizer1->Add(inputCtrl, 1, wxEXPAND);
	inputFilename = new wxStaticText(this, wxID_ANY, "Filename.txt");
	inputFilename->SetFont(wxFont(wxFontInfo(12)));
	controlLabelSizer1->AddSpacer(10);
	controlLabelSizer1->Add(inputFilename, 0, wxCENTER);

	matchCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
		wxDefaultSize, wxTE_MULTILINE | wxTE_RICH2);
	matchCtrl->SetFont(wxFont(wxFontInfo(11)));
	wxBoxSizer *controlLabelSizer2 = new wxBoxSizer(wxVERTICAL);
	controlLabelSizer2->Add(matchCtrl, 1, wxEXPAND);
	matchFilename = new wxStaticText(this, wxID_ANY, "Filename.txt");
	matchFilename->SetFont(wxFont(wxFontInfo(12)));
	controlLabelSizer2->AddSpacer(10);
	controlLabelSizer2->Add(matchFilename, 0, wxCENTER);

	wxBoxSizer *horizSizer = new wxBoxSizer(wxHORIZONTAL);
	horizSizer->AddSpacer(15);
	horizSizer->Add(controlLabelSizer1, 1, wxEXPAND);
	horizSizer->AddSpacer(20);
	horizSizer->Add(controlLabelSizer2, 1, wxEXPAND);
	horizSizer->AddSpacer(15);

	wxBoxSizer *topSizer = new wxBoxSizer(wxVERTICAL);
	plagiarismLabel = new wxStaticText(this, wxID_ANY, "Plagiarism: 0%");
	plagiarismLabel->SetFont(wxFont(wxFontInfo(14)));
	topSizer->Add(plagiarismLabel, 0, wxCENTER);
	topSizer->AddSpacer(10);
	topSizer->Add(horizSizer, 1, wxEXPAND);
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
	EVT_MENU(MENUFILE_OPEN, PFrame::onMenuFileOpen)
wxEND_EVENT_TABLE()

void PFrame::onCheck(wxCommandEvent &event) {
	const std::string haystack((inputCtrl->GetValue()).c_str());
	const std::string needles((matchCtrl->GetValue()).c_str());
	const std::vector<int> indices = rabinkarp(haystack,
		parse_needles(needles));
	highlightIndices(indices, haystack);
}

void PFrame::onMenuFileOpen(wxCommandEvent &event) {
	wxFileDialog openFileDialog(this, "Select a text file", "", "",
		"Text File (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;

	const std::string filepath = openFileDialog.GetPath();
	std::ifstream file(filepath);
	if (!file) {
		wxMessageBox("Access denied to given file.", "Error",
			wxOK | wxICON_ERROR, this);
		return;
	}

	std::ostringstream os;
	os << file.rdbuf();
	inputCtrl->SetValue(os.str());

	// Set the label
	inputFilename->SetLabel(openFileDialog.GetFilename());
}
