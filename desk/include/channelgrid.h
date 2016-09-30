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
#ifndef WXCHANNELGRID_H
#define WXCHANNELGRID_H

#include <wx/wx.h>
#include "defines.h"
#include <multiplexdisp.h>
/**
@author Ganesh Gudigara
This Class used for drawing the channels/sensors information which was acquired from the device on a grid
which can be viewed on scren on line
*/
#include <wx/grid.h>
class wxChannelGrid:public wxGrid {
  public:
	wxChannelGrid() {
	};
	wxChannelGrid(wxWindow * parent, wxWindowID id, const wxPoint & pos,
				const wxSize & size, const wxString & sz_title =
				"ChannelDisplay", wxColour & clr =
				*wxBLACK, wxColour & foreclr = *wxWHITE, wxColour & lclr =
				*wxCYAN);
	~wxChannelGrid();
	void SetLastGridColSize(int presentsize);

  private:
	unsigned int m_presentmax;

	DECLARE_DYNAMIC_CLASS(wxChannelGrid)
};

#endif
