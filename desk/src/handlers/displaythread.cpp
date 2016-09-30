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

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#if !wxUSE_THREADS
    #error "Define wxUSE_THREADS for compilation"
#endif // wxUSE_THREADS

#include <wx/progdlg.h>
#include <displaythread.h>

int wxDisplayThread::m_DevCount=0;
wxArrayThread wxDisplayThread::pDispThreads;

wxDisplayThread::wxDisplayThread( )
        : wxThread()
{

}

wxDisplayThread::~wxDisplayThread()
{

}

void wxDisplayThread::OnExit()
{
#if 0
    wxCriticalSectionLocker locker(wxGetApp().m_critSection);

    wxDisplayThread::pDispThreads.Remove(this);

    if ( pDispthreads.IsEmpty() )
    {
        if ( wxGetApp().m_closedAllThreads )
        {
            wxGetApp().m_closedAllThreads = FALSE;
            wxGetApp().m_semLock.Post();
        }
    }
#endif
}


void *wxDisplayThread::Entry()
{
    return NULL;
}


void wxDisplayThread::CreateThread(char *threadname,wxAcqConfig & cfile,wxPFdeviceapp & parent)
{
    wxDisplayThread *thread = new wxDisplayThread( );

    if ( thread->Create() != wxTHREAD_NO_ERROR )
    {
        wxLogError(wxT("Can't create thread!"));
    }

    wxCriticalSectionLocker enter(parent.m_critSection);
    wxDisplayThread::GetThreadArray().Add(thread);
     wxDisplayThread::IncCount();	
    return ;
}


int wxDisplayThread::DestroyThreads(void)
{

return 1;
}

		wxArrayThread wxDisplayThread::GetThreadArray()
		{
		return wxDisplayThread::pDispThreads;
		}
		void wxDisplayThread::IncCount()
		{
		m_DevCount=m_DevCount+ 1;
		}
		int wxDisplayThread::GetCount()
		{
		return m_DevCount;
		}

