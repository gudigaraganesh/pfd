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
#ifndef WXDEVICE_H
#define WXDEVICE_H

/**
@author Ganesh Gudigara
*/
#include <acqconfig.h>
#include <acq/protocolhandler.h>
#include <acq/reportgen.h>
#include <acq/virtualcom.h>
class wxDevice {
  public:
	wxDevice();

	~wxDevice();
	void UpdateDeviceProfile(struct device_profile & devprof);
	void SetDeviceType(int type);
	void CreateCommProfile();
	char *MapDeviceName(wxString & devname);
	void SetReportType(int type);
	void CreateReportProfile();
  private:
	struct netdev_profile netprof;
	struct serdev_profile serprof;
	struct usbdev_profile usbprof;
	struct bluetoothdev_profile blprof;
	wxString *ChannelUnits;
	wxReportGen *m_report;
	wxVirtualCom *m_comobj;
	int m_devicetype;
	int m_filetype;
	struct device_profile m_device;
	struct report_profile repprof;
	wxProtocolHandler m_protohandler;
	bool bActive;
	bool bDefault;
	wxList *dataQueue;
	wxString m_starttime;
	wxString m_startdate;
	bool bCreated;
};

#endif
