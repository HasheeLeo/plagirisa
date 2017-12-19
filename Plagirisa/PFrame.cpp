/*******************************************************************************
    File: PFrame.cpp
    Purpose: Implements the main frame (window) of the app.

    This file is property of Hashir Ahmad and Daud Akhtar Naveed from SEECS,
    NUST batch of 2k16, section 6C.
*******************************************************************************/

#include "stdafx.hpp"
#include "PFrame.hpp"

PFrame::PFrame(const wxString &title, const wxPoint &pos, const wxSize &size,
	long style)
	: wxFrame(nullptr, wxID_ANY, title, pos, size, style)
{
	// TODO: Add controls to the window here
}
