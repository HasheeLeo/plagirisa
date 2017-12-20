/*******************************************************************************
    File: PFrame.hpp
    Purpose: Defines the main frame (window) of the app.

    This file is property of Hashir Ahmad and Daud Akhtar Naveed from SEECS,
    NUST batch of 2k16, section 6C.
*******************************************************************************/

#ifndef PFRAME_HPP
#define PFRAME_HPP

class PFrame : public wxFrame {
public:
	PFrame(const wxString &title, const wxPoint &pos, const wxSize &size,
		long style = wxDEFAULT_FRAME_STYLE);

private:
	wxTextCtrl *inputCtrl;
	wxTextCtrl *matchCtrl;

	// Handlers
	void onCheck(wxCommandEvent &event);

	wxDECLARE_EVENT_TABLE();
};

#endif // PFRAME_HPP
