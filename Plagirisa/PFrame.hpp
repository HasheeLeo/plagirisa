/*******************************************************************************
    File: PFrame.hpp
    Purpose: Defines the main frame (window) of the app.

    This file is property of Hashir Ahmad and Daud Akhtar Naveed from SEECS,
    NUST batch of 2k16, section 6C.
*******************************************************************************/

#ifndef PFRAME_HPP
#define PFRAME_HPP

#include <wx/frame.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>

#include <string>
#include <vector>

bool update_filter_words();

class PFrame : public wxFrame {
public:
	PFrame(const wxString &title, const wxPoint &pos, const wxSize &size,
		long style = wxDEFAULT_FRAME_STYLE);

private:
	static constexpr int MENUFILE_OPEN = 101;

	wxStaticText *plagiarismLabel;
	wxTextCtrl *inputCtrl;
	wxStaticText *inputFilename;
	wxTextCtrl *matchCtrl;
	wxStaticText *matchFilename;

	// Calculates the plagiarism percentage
	int calculate(const std::string &haystack, int matchedWords);

	// The main plagiarism detection function. This is the heart of the program
	void detect(const std::string &haystack);

	// Highlights the matching words and removes any indices which may have been
	// the result of a collision (if the word at the index is a common or short
	// word, it considers it a result of collision)
	std::vector<int> highlightIndices(const std::vector<int> &indices,
		const std::string &haystack);

	// Handlers
	void onCheck(wxCommandEvent &event);
	void onMenuFileOpen(wxCommandEvent &event);

	wxDECLARE_EVENT_TABLE();
};

#endif // PFRAME_HPP
