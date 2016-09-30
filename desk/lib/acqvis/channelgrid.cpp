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
#include <channelgrid.h>

IMPLEMENT_DYNAMIC_CLASS(wxChannelGrid, wxGrid)


wxChannelGrid::wxChannelGrid(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size ,const wxString & sz_title,wxColour & clr,wxColour & foreclr,wxColour & lclr)
  :wxGrid(parent,id,pos,size)
{
SetCellBackgroundColour(clr);
SetCellTextColour(foreclr);
SetLabelBackgroundColour(clr);
SetLabelTextColour(foreclr);
SetGridLineColour(lclr);
}



wxChannelGrid::~wxChannelGrid()
{
}
void wxChannelGrid::SetLastGridColSize(int presentwidth)
{
int newwidth;
int addwidth=0;
for (int i=0;i<GetNumberCols();i++)
addwidth+=GetColSize(i);
addwidth+=GetRowLabelSize();
if(addwidth<presentwidth)
{
addwidth=presentwidth-addwidth;
addwidth +=GetColSize(GetNumberCols()-1);
SetColSize(GetNumberCols()-1,addwidth);
}
}
