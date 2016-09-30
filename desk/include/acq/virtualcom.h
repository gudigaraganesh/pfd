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

/**
@author Ganesh Gudigara
*/
#ifndef WXVIRTUALCOM_H
#define WXVIRTUALCOM_H

#include <stdio.h>



#define MAXDEVNAME 150



class wxVirtualCom {
  public:
	wxVirtualCom(char *virtDev = NULL, bool bOpen = false);
	// wxVirtualCom (wxVirtualCom & vCom);
	 virtual ~ wxVirtualCom() {
	};

	virtual int OpenDevice(char *virtDev, int mode = 0) {
		return 0;
	};
	virtual int CloseDevice() {
		return 0;
	};
	virtual int ReadDevice(char *readBuf, int endMark, int cmd = 0) {
		return 0;
	};
	virtual int WriteDevice(char *writeBuf, int endMark, bool bFile = false) {
		return 0;
	};
	virtual int ConfigureDevice() {
		return 0;
	};
	virtual int GetStatus();
	virtual bool IsOpen();
	virtual bool IsConnected();
	virtual int GetMaxDevices();
	virtual int GetHandle();
	virtual void SetHandle(int handle);
	virtual char *GetName();

  protected:
	int devHandle;
	char devName[MAXDEVNAME];
	bool bOpen;
	bool bConnected;
	int statuscode;
	int maxDevs;
	bool bEnableRead;
	int m_CommMode;
};

#endif
