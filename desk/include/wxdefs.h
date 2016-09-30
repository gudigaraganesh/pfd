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
#ifndef _WXDEFS_H
#define _WXDEFS_H
#include <wx/thread.h>
#include <wx/dynarray.h>
class wxThread;

WX_DEFINE_ARRAY(wxThread *, wxArrayThread);
#define ID_MFRM  21000
#define ID_MGRID 21001
#define ID_MCTL  21002
#define ID_BADD  21003
#define ID_BSCN  21004
#define ID_BCHG  21005
#define ID_BEXIT  21006
#define ID_BGO  21007
#define ID_BSTP  21008
#define ID_BRPT  21009
#define ID_TCSEL  21010
#define ID_CBMOD  21011
#define ID_RBDM   21112
#define ID_TINF   21113
#define ID_DLGCREATE 21114
#endif
