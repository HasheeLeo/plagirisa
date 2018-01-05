/*******************************************************************************
    File: stdafx.hpp
    Purpose: For managing precompiled header files.

    This file is property of Hashir Ahmad and Daud Akhtar Naveed from SEECS,
    NUST batch of 2k16, section 6C.
*******************************************************************************/

#ifndef STDAFX_HPP
#define STDAFX_HPP

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#define WX_PRECOMP
#warning "Ensure precompiled headers are supported. "
         "Otherwise, #undef WX_PRECOMP"
#endif // WX_PRECOMP

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif // WX_PRECOMP

#define _UNICODE

#endif // STDAFX_HPP
