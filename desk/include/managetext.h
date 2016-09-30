/***************************************************************************
 *   Copyright (C) 2004 by Ganesh Gudigara                                 *
 *   ganeshgudigara@parappadi.com                                            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef WXMANAGETEXT_H
#define WXMANAGETEXT_H

#include <wx/wx.h>
#include <defines.h>
#include <multiplexdisp.h>
/**
@author Ganesh Gudigara
This Class used for drawing the channels/sensors information which was acquired from the device on a grid
which can be viewed on scren on line
*/
#include <wx/textctrl.h>
#include <displayframe.h>

class wxManageText:public wxTextCtrl {
  public:
	wxManageText() {
	};
	wxManageText(wxWindow * parent, wxWindowID id, const wxString & label,
				 const wxPoint & pos, const wxSize & size =
				 wxDefaultSize, wxColour & clr = *wxCYAN, long style =
				 0, const wxString & sz_title = "Buttons");
	~wxManageText();
  private:
	unsigned int m_presentmax;

	DECLARE_DYNAMIC_CLASS(wxManageText)
};

#endif
