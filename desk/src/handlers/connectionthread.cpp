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
#include <wx/wxprec.h>

#ifdef __BORLANDC__
    #pragma hdrstop
#endif
#include <wx/app.h>
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#if !wxUSE_THREADS
    #error "Define wxUSE_THREADS for compilation"
#endif // wxUSE_THREADS

#include <wx/progdlg.h>
#include <connectionthread.h>


wxArrayThread wxConnectionThread::pConThreads;
int wxConnectionThread::m_DevCount=0;


wxConnectionThread::wxConnectionThread( )
        : wxThread()
{

}

wxConnectionThread::~wxConnectionThread()
{

}

void wxConnectionThread::OnExit()
{

}

void *wxConnectionThread::Entry()
{
    return NULL;
}


void wxConnectionThread::CreateThread(char *threadname,wxAcqConfig & file,wxPFdeviceapp & parent)
{
    wxConnectionThread *thread = new wxConnectionThread( );

    if ( thread->Create() != wxTHREAD_NO_ERROR )
    {
        wxLogError(wxT("Can't create thread!"));
    }

    wxCriticalSectionLocker enter(parent.m_critSection);
     wxConnectionThread::GetThreadArray().Add(thread);
	wxConnectionThread::IncCount();
	return;
}

int wxConnectionThread::DestroyThreads(void)
{
return 1;
}
wxArrayThread wxConnectionThread::GetThreadArray()
	{
	return pConThreads;
	}	

 int wxConnectionThread::GetCount()
	{
	return m_DevCount;
	}
 void wxConnectionThread::IncCount()
	{
	m_DevCount=m_DevCount+1;
	}




