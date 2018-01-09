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
#include <wx/dir.h>
#include <wx/filename.h>
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
		// Ignore unicode characters (isalpha() does not work with them)
		while (isalpha(str[j] < 0 ? 0 : str[j]) && j < strLen)
			++j;

		if (i < j) {
			// Ignore common and short words
			// (they just increase the likelihood of false positives)
			const std::string needle = str.substr(i, j - i);
			if (needle.length() >= 4 && rabinkarp(commonWords, needle).empty())
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
		wxDefaultSize, wxTE_READONLY | wxTE_MULTILINE | wxTE_RICH2);
	inputCtrl->SetFont(wxFont(wxFontInfo(11)));
	wxBoxSizer *controlLabelSizer1 = new wxBoxSizer(wxVERTICAL);
	controlLabelSizer1->Add(inputCtrl, 1, wxEXPAND);
	inputFilename = new wxStaticText(this, wxID_ANY, "");
	inputFilename->SetFont(wxFont(wxFontInfo(12)));
	controlLabelSizer1->AddSpacer(10);
	controlLabelSizer1->Add(inputFilename, 0, wxCENTER);

	matchCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
		wxDefaultSize, wxTE_READONLY | wxTE_MULTILINE | wxTE_RICH2);
	matchCtrl->SetFont(wxFont(wxFontInfo(11)));
	wxBoxSizer *controlLabelSizer2 = new wxBoxSizer(wxVERTICAL);
	controlLabelSizer2->Add(matchCtrl, 1, wxEXPAND);
	matchFilename = new wxStaticText(this, wxID_ANY, "");
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
	plagiarismLabel = new wxStaticText(this, wxID_ANY, "0%");
	plagiarismLabel->SetFont(wxFont(wxFontInfo(14)));
	topSizer->Add(plagiarismLabel, 0, wxCENTER);
	topSizer->AddSpacer(10);
	topSizer->Add(horizSizer, 1, wxEXPAND);
	topSizer->Add(new wxButton(this, wxID_ANY, "Check"), 0, wxCENTER);
	topSizer->AddSpacer(10);
	SetSizer(topSizer);
}

// Calculates the plagiarism percentage
int PFrame::calculate(const std::string &haystack, int matchedWords) {
	const int haystackLen = haystack.length();
	int totalWords = 0;
	// Calculate the total words in haystack, ignoring short and common words
	for (int i = 0; i < haystackLen; ++i) {
		int j = i;
		// Ignore unicode characters (isalpha() does not work with them)
		while (isalpha(haystack[j] < 0 ? 0 : haystack[j]) && j < haystackLen)
			++j;

		if (i < j) {
			// Ignore common and short words
			const std::string word = haystack.substr(i, j - i);
			if (word.length() >= 4 && rabinkarp(commonWords, word).empty())
				++totalWords;

			i = j;
		}
	}
	return (static_cast<double>(matchedWords) / totalWords) * 100;
}

// The main plagiarism detection function. This is the heart of the program
void PFrame::detect(const std::string &haystack) {
	// To ensure a file does not match to itself
	const wxString ignoreFilename = inputFilename->GetLabelText();
	const wxDir dataDir("data");
	// Loop through every file in the data directory and match them with the
	// input file. Pick the best match.
	std::vector<int> bestIndices;
	std::string bestContent;
	wxString bestFilename;
	wxString filename;
	bool cont = dataDir.GetFirst(&filename, wxEmptyString,
		wxDIR_FILES | wxDIR_HIDDEN | wxDIR_NO_FOLLOW);
	for (; cont != false; cont = dataDir.GetNext(&filename)) {
		if (filename == ignoreFilename)
			continue;

		const wxString filepath(dataDir.GetNameWithSep() + filename);
		std::ifstream file(std::string(filepath.c_str()));
		if (!file)
			return;

		std::ostringstream os;
		os << file.rdbuf();
		const std::string content = os.str();
		const std::vector<int> indices = rabinkarp(haystack,
			parse_needles(content));
		if (indices.size() > bestIndices.size()) {
			bestIndices = indices;
			bestFilename = filename;
			bestContent = content;
		}
	}
	matchCtrl->SetValue(bestContent);
	matchFilename->SetLabelText(bestFilename);
	bestIndices = highlightIndices(bestIndices, haystack);
	wxString plagiarismPercentage;
	// convert int to wxString
	plagiarismPercentage << calculate(haystack, bestIndices.size());
	plagiarismLabel->SetLabelText(plagiarismPercentage + "%");
}

// Highlights the matching words and removes any indices which may have been the
// result of a collision (if the word at the index is a common or short word, it 
// considers it a result of collision)
std::vector<int> PFrame::highlightIndices(const std::vector<int> &indices,
	const std::string &haystack) {
	std::vector<int> fixedIndices = indices;
	// Remove old highlights
	wxTextAttr textAttr;
	textAttr.SetBackgroundColour(*wxWHITE);
	const int haystackLen = haystack.length();
	inputCtrl->SetStyle(0, haystackLen, textAttr);
	// Add new highlights
	textAttr.SetBackgroundColour(*wxYELLOW);
	for (int i : indices) {
		int j = i;
		// Ignore unicode characters (isalpha() does not work with them)
		while (isalpha(haystack[j] < 0 ? 0 : haystack[j]) && j < haystackLen)
			++j;

		if (i < j) {
			const std::string word = haystack.substr(i, j - i);
			if (j - i >= 4 && rabinkarp(commonWords, word).empty()) {
				inputCtrl->SetStyle(i, j, textAttr);
			}
			else {
				// Remove the faulty index
				//
				auto it = std::find(fixedIndices.begin(),
					fixedIndices.end(), i);

				if (it != fixedIndices.end())
					fixedIndices.erase(it);
			}
		}
	}
	return fixedIndices;
}

wxBEGIN_EVENT_TABLE(PFrame, wxFrame)
	EVT_BUTTON(wxID_ANY, PFrame::onCheck)
	EVT_MENU(MENUFILE_OPEN, PFrame::onMenuFileOpen)
wxEND_EVENT_TABLE()

void PFrame::onCheck(wxCommandEvent &event) {
	const std::string haystack((inputCtrl->GetValue()).c_str());
	if (haystack.empty())
		return;

	detect(haystack);
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
	inputFilename->SetLabelText(openFileDialog.GetFilename());
}
