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
#include <defines.h>
#include <device.h>
#include <acq/serialcom.h>
#include <acq/tcpcom.h>
#include <acq/usbcom.h>
#include <acq/bluetoothcom.h>
#include <acq/textreportgen.h>
#include <acq/xlsreportgen.h>
wxDevice::~wxDevice()
{
if(bCreated)
{		
delete [] ChannelUnits;
delete [] m_device.channels;
delete [] dataQueue;
delete [] m_report;
delete [] m_comobj;
}
}


wxDevice::wxDevice()
{
}

void wxDevice::UpdateDeviceProfile(struct device_profile &devprof)
{
m_device.profname=devprof.profname;
m_device.devicename=devprof.devicename;
m_device.defaultreport=devprof.defaultreport;
m_device.devprof=devprof.devprof;
m_device.noofchannels=devprof.noofchannels;
m_device.channels=new wxString[m_device.noofchannels];
for(int i=0;i<m_device.noofchannels;i++)
{
m_device.channels[i]=devprof.channels[i];
}
}
void wxDevice::CreateCommProfile()
{

switch(m_devicetype)
{
case DEVICESERIAL:
			wxAcqConfig::GetSerialProfile(m_device.devprof,serprof);
			#if	!defined(__WXMSW___)
			m_comobj=new wxSerialCom(MapDeviceName(serprof.devicename),false);
			#else
			m_comobj=new wxSerialCom((char *)serprof.devicename.c_str(),false);
			
			#endif	
		break;
case DEVICENETWORK:
			wxAcqConfig::GetNetworkProfile(m_device.devprof,netprof);
			#if	!defined(__WXMSW___)
			m_comobj=new wxTcpCom((char *)netprof.devicename.c_str(),false);
			#else
			m_comobj=new wxTcpCom((char *)netprof.devicename.c_str(),false);
			
			#endif	
			break;
case DEVICEUSB:
			wxAcqConfig::GetUSBProfile(m_device.devprof,usbprof);
			#if	!defined(__WXMSW___)
			m_comobj=new wxUSBCom((char *)usbprof.devicename.c_str(),false);
			#else
			m_comobj=new wxUSBCom((char *)usbprof.devicename.c_str(),false);
			#endif
			break;
case DEVICEBLUETOOTH:
			wxAcqConfig::GetBluetoothProfile(m_device.devprof,blprof);
			#if	!defined(__WXMSW___)
			m_comobj=new wxBluetoothCom((char *)blprof.devicename.c_str(),false);
			#else
			m_comobj=new wxBluetoothCom((char *)blprof.devicename.c_str(),false);
			#endif
			break;
}

}

void wxDevice::SetDeviceType(int type)
{
m_devicetype=type;
}
char  *wxDevice::MapDeviceName(wxString & devname)
	{
	wxString sdev;
	int num;
	wxString commdev=devname.SubString(0,2);
	if(commdev.CmpNoCase("COM")==0)
	{
	sdev.Append("/dev/ttyS");
	wxString nums=devname.SubString(3,3);
	unsigned long devnums;
	nums.ToULong(&devnums);
	devnums=devnums-1;
	char buf[4];
	sprintf(buf,"%d",devnums);
	sdev.Append(buf);
	return (char *)sdev.c_str();
	}
	else
	return 	(char *)devname.c_str();
	}
	void wxDevice::SetReportType(int rtype)
	{
	m_filetype=rtype;
	}
	void wxDevice::CreateReportProfile()
	{
		 wxAcqConfig::GetReportProfile(m_device.defaultreport,repprof);	
		switch(m_filetype)
		{
		case REPORTTEXT:
				m_report=new wxTextReportGen((char *)repprof.filename.c_str(),false);
				break;
		case REPORTXLS:
				m_report=new wxXLSReportGen((char *)repprof.filename.c_str(),false);
				break;
		}
	}
