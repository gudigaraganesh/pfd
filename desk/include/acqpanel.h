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
#ifndef WXACQPANEL_H
#define WXACQPANEL_H
/**
@author Ganesh Gudigara
*/
#include <wx/wx.h>
#define ID_MUXDISP 20010
class wxAcqPanel:public wxPanel {
  public:
	wxAcqPanel() {
	};
	wxAcqPanel(wxWindow * parent, wxWindowID id, const wxPoint & pos,
			   const wxSize & size, wxColor & clr = *wxBLACK);
	~wxAcqPanel();
	void OnPaint(wxPaintEvent & event);
	const wxFont & GetTextFont() const {
		return m_font;
	} const wxColour & GetColour() const {
		return m_colour;
	} void SetTextFont(const wxFont & font) {
		m_font = font;
		this->SetFont(m_font);
	}
	void SetColour(const wxColour & colour) {
		m_colour = colour;
	}
	void WriteData(int x, int y, wxString & strs, wxColour & tclr = *wxWHITE);
	void OnClick(wxMouseEvent & event);

  private:
	wxColour m_colour;
	wxFont m_font;

	DECLARE_DYNAMIC_CLASS(wxAcqPanel)
		DECLARE_EVENT_TABLE()
};

#endif
