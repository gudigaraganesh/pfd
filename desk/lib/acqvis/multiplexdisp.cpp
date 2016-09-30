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
#include <wx/grid.h>
#include <multiplexdisp.h>
#include <wx/wx.h>
#include <wx/image.h>
#include <wx/file.h>
#include <wx/fontdlg.h>
IMPLEMENT_DYNAMIC_CLASS(wxMultiplexDisp, wxScrolledWindow)


BEGIN_EVENT_TABLE(wxMultiplexDisp, wxScrolledWindow)
  EVT_PAINT(wxMultiplexDisp::OnPaint)
  EVT_RIGHT_DOWN(wxMultiplexDisp::OnClick)
END_EVENT_TABLE()

wxMultiplexDisp::wxMultiplexDisp( wxWindow *parent, wxWindowID id,
                    const wxPoint &pos, const wxSize &size,wxColour & clr)
        : wxPlotWindow( parent, id, pos, size, wxSUNKEN_BORDER|wxPLOT_DEFAULT )
{
    
  //  wxBitmap	bitmap( 100, 100 );
    //wxMemoryDC	dc;

     SetBackgroundColour(clr);
    //dc.SelectObject( bitmap );
    //dc.SetBrush( wxBrush( "orange", wxSOLID ) );
    //dc.SetPen( *wxBLACK_PEN );
    //dc.DrawRectangle( 0, 0, 100, 100 );
    //dc.SetBrush( *wxWHITE_BRUSH );
    //dc.DrawRectangle( 20, 20, 60, 60 );
    //dc.SelectObject( wxNullBitmap );

}

wxMultiplexDisp::~wxMultiplexDisp()
{
}

void wxMultiplexDisp::OnPaint (wxPaintEvent &WXUNUSED(event))
{
   #if 0
    wxPaintDC dc( this );
    PrepareDC( dc );
    wxString legend;
	
    dc.SetPen( *wxBLACK_PEN );
    dc.SetBrush( *wxGREEN_BRUSH );
	dc.SetFont(m_font);
	
	int tasks = 1;
	for (int i = 10; i < 4000; i += 40)
	{	legend.Printf("Task %d", tasks);
		tasks++;
		dc.DrawText(legend, 5, i);
    		dc.DrawRectangle( 100, i, 2000, 5 );
    	for (int j = 100; j < 2000; j += 100)
    		{	dc.DrawRectangle(j, i - 5, 3, 20);
    			legend.Printf("%d", j);
    			dc.DrawText(legend, j, i + 10);
    		}
	}
#endif
}


void wxMultiplexDisp::WriteData(int x,int y,wxString & strs,wxColour & tclr)
{
//wxDC dcobj=GetDC();
//wxColour orig=GetForegroundColour();
//SetForegroundColour(tclr);
//dc.DrawText(strs,wxCoord(x),wxCoord(y));
//SetForegroundColour(orig);
}
void wxMultiplexDisp::OnClick(wxMouseEvent & event)
{
fprintf(stderr,"mux displayed\n");
}
