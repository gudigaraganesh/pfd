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
#ifndef WXDISPLAYTHREAD_H
#define WXDISPLAYTHREAD_H
#include <wx/wx.h>
#include <wxdefs.h>
#include <acqconfig.h>
#include <acqconfig.h>
#include <pfdevice.h>


class wxDeviceWindow;
class wxDeviceScreen;
class wxConfigFile;
class wxAcqConfig;

//WX_DEFINE_ARRAY_PTR(wxThread *,wxArrayThread);






class wxDisplayThread:public wxThread {
  private:
	wxDeviceWindow * pDevWin;
	wxDeviceScreen *pDevScreen;
	wxConfigFile *pDevConfig;
	bool bTerminate;
	bool bFocus;

  public:
	 wxDisplayThread();
	~wxDisplayThread();
	static void CreateThread(char *ThreadName, wxAcqConfig & config,
							 wxPFdeviceapp & parent);
	virtual void *Entry();
	virtual void OnExit();
	static int m_DevCount;
	static wxArrayThread pDispThreads;
	static int DestroyThreads(void);
	static wxArrayThread GetThreadArray();
	static void IncCount();
	static int GetCount();
};
#endif
