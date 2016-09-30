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

#ifndef WXACQCONFTG_H
#define WXACQCONFTG_H
#include <wx/wx.h>
#include <wx/config.h>
#include <linux/types.h>
#define OLDTEST

struct global_conf {
	wxString defaultdev;
	wxString defaultreport;
	__u16 noofdevices;
	wxString *devices;
	__u16 noofreports;
	wxString *reports;
};

struct device_profile {
	wxString profname;
	wxString devicename;
	wxString devprof;
	wxString defaultreport;
	wxString *channels;
	__u8 noofchannels;
};






struct channels_profile {
	wxString profname;
	wxString channelname;
	wxString channelunit;
	__u16 channeltype;
	double samplemin;
	double samplemax;
	double calibmin;
	double calibmax;
	bool bAvg;
	bool bHex;
};




struct report_profile {
	wxString profname;
	wxString filename;
	wxString filetype;
	wxString fileheader;
	wxString filefooter;
	bool startdate;
	bool starttime;
	__u8 dumpstyle;
	__u8 datatype;
};



struct serdev_profile {
	wxString profname;
	wxString devicename;
	__u8 dataBit;
	__u8 parityBit;
	__u8 stopBit;
	wxString baudRate;
	wxString flowControl;
};
struct netdev_profile {
	wxString profname;
	wxString devicename;
	wxString ethDev;
	wxString ipAddr;
	__u16 controlPort;
	__u16 dataPort;
	__u16 cProtocol;
	__u16 maxConnections;
	bool comMode;
	bool noControl;
};
struct usbdev_profile {
	wxString profname;
	wxString devicename;
	wxString usbClass;
	__u16 speed;
};
struct bluetoothdev_profile {
	wxString profname;
	wxString devicename;
	wxString blid;
	__u16 speed;
};


#ifdef OLDTEST
#define DEFAULTANACHAN 22
#define DEFAULTDIGCHAN 3
#else
#define DEFAULTANACHAN 1
#define DEFAULTDIGCHAN 1
#endif



class wxAcqConfig:public wxConfigBase {
  public:
	wxAcqConfig();
	virtual ~ wxAcqConfig();
	static wxConfigBase *Get();
	static void Set(wxConfigBase * pconfig);
	static void SetGlobalConfig(struct global_conf &g_conf);
	static void SetGlobalReportProfile(wxString & rname);
	static void SetGlobalDeviceProfile(wxString & dname);
	static void CreateReportProfile(struct report_profile & repconf);
	static void CreateUSBDevProfile(struct usbdev_profile &u_conf);
	static void CreateNetDevProfile(struct netdev_profile &n_conf);
	static void CreateSerDevProfile(struct serdev_profile &s_conf);
	static void CreateDeviceProfile(struct device_profile &dev_conf);
	static void CreateChannelProfile(struct channels_profile &chan_conf);
	static wxString GetComDeviceInfo(wxString & type, bool loop);
	static wxString GetDeviceInfo(bool loop);
	static wxString GetChannelInfo(bool loop);
	static wxString GetReportInfo(bool loop);
	static wxString GetNoofChannels(wxString & device);
	static void FirstDefaults();
	static void InitAll();
	static void GetSerialProfile(wxString & profname,struct serdev_profile &serconf);
	static void GetNetworkProfile(wxString & profname,struct netdev_profile &netconf);
	static void GetUSBProfile(wxString & profname,struct usbdev_profile &usbconf);
	static void GetBluetoothProfile(wxString & profname,struct bluetoothdev_profile &blconf);
	static void GetReportProfile(wxString & profname,struct report_profile &repconf);
};	
#endif							// WXACQCONFTG_H
