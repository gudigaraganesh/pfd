
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
 *   along  Copyright (C) 2004 by Ganesh Gudigara                                 *
 *   ganeshgudigara@parappadi.com                                            *
 *          with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include <acqconfig.h>
#ifndef __WX_MSW__
#include <linux/types.h>
#endif
#include <defaultheader.h>
#ifndef OLDTEST
struct channels_profile defchannels[DEFAULTANACHAN+DEFAULTDIGCHAN];
void InitChannels()
{
int counter=0;
defchannels[counter].channelname.Printf("VOLTAGE");
defchannels[counter+1].channelname.Printf("VOLTAGE");
defchannels[counter].channelunit.Printf("mV");
defchannels[counter+1].channelunit.Printf("mV");
for(int ind=0;ind<DEFAULTANACHAN+DEFAULTDIGCHAN;ind++)
{
if(ind >=DEFAULTDIGCHAN)
defchannels[ind].channeltype=1;   //0 indicates analog
else
defchannels[ind].channeltype=0;   //0 indicates analog
defchannels[ind].bAvg=false;   
defchannels[ind].bHex=false;
defchannels[ind].samplemin=defchannels[ind].calibmin=0;
defchannels[ind].samplemax=defchannels[ind].calibmax=2048;
}
}
#else
extern struct channels_profile defchannels[DEFAULTANACHAN+DEFAULTDIGCHAN];
extern void InitChannels();
#endif







wxAcqConfig::wxAcqConfig()
{
InitAll();
}


void wxAcqConfig::InitAll( )
{
  wxConfigBase *pConfig = wxConfigBase::Get();
  pConfig->SetVendorName(_T("G3 Innotronix"));
  pConfig->SetAppName(_T("pfdevice")); // not needed, it's the default value
  pConfig->SetRecordDefaults();
	wxAcqConfig::FirstDefaults();
}

wxAcqConfig::~wxAcqConfig( )
{

}

wxConfigBase *wxAcqConfig::Get()
{
return wxConfigBase::Get();
}

void wxAcqConfig::Set(wxConfigBase *pconfig)
{
wxConfigBase::Set(pconfig);
}

	void wxAcqConfig::CreateChannelProfile(struct channels_profile & chan_conf)
	{
	wxConfigBase *pConfig=wxAcqConfig::Get();
	wxString prName(chan_conf.profname);
	prName.Prepend("/");
	prName.Append("/");
	wxString chanName=prName+wxString("Channel");
  	pConfig->Write(chanName, chan_conf.channelname);
	wxString unitd=prName+wxString("Unit");
  	pConfig->Write(unitd,chan_conf.channelunit);
	wxString typed=prName+wxString("Type");
  	pConfig->Write(typed,chan_conf.channeltype);
	wxString sammin=prName+wxString("SampleCountMin");
  	pConfig->Write(sammin,chan_conf.samplemin);
	wxString sammax=prName+wxString("SampleCountMax");
  	pConfig->Write(sammax,chan_conf.samplemax);
	wxString calmin=prName+wxString("CaliberConstantMin");
  	pConfig->Write(calmin,chan_conf.calibmin);
	wxString calmax=prName+wxString("CaliberConstantMax");
  	pConfig->Write(calmax,chan_conf.calibmax);
	wxString allowad=prName+wxString("AllowAverage");
  	pConfig->Write(allowad,chan_conf.bAvg);
	wxString allowhd=prName+wxString("AllowHex");
  	pConfig->Write(allowhd,chan_conf.bHex);
	}

	void wxAcqConfig::CreateDeviceProfile(struct device_profile & dev_conf)
	{
	wxConfigBase *pConfig=wxAcqConfig::Get();
	wxString prName(dev_conf.profname);
	prName.Prepend("/");
	prName.Append("/");
	wxString devName=prName+wxString("Device");
  	pConfig->Write(devName, dev_conf.devicename);
	wxString commd=prName+wxString("CommDevice");
  	pConfig->Write(commd,dev_conf.devprof);
	wxString noofc=prName+wxString("NoofChannels");
  	pConfig->Write(noofc,dev_conf.noofchannels);
	wxString rpt=prName+wxString("Report");
  	pConfig->Write(rpt,dev_conf.defaultreport);
		for(int index=0;index < dev_conf.noofchannels; index++)
		{
		wxString chan_nos;
		chan_nos.Printf("Channel_%d",index);
		wxString chans=prName+chan_nos;
  		pConfig->Write(chans,dev_conf.channels[index]);
        	}
	}

	wxString wxAcqConfig::GetComDeviceInfo(wxString & type,bool loop)
	{
	return wxString("hello");
	}
	wxString wxAcqConfig::GetDeviceInfo(bool loop)
	{
	return wxString("hello");
	}

	wxString wxAcqConfig::GetChannelInfo(bool loop)
	{
	return wxString("hello");
	}

	wxString wxAcqConfig::GetReportInfo(bool loop)
	{
	return wxString("hello");
	}
	
	wxString wxAcqConfig::GetNoofChannels(wxString & device)
	{
	return wxString("hello");
	}
	
	void wxAcqConfig::SetGlobalConfig(struct global_conf & g_conf)
	{
	wxConfigBase *pConfig=wxAcqConfig::Get();
  	pConfig->Write(_T("/global/DefaultReport"), g_conf.defaultreport);
  	pConfig->Write(_T("/global/DefaultDevice"), g_conf.defaultdev);
  	pConfig->Write(_T("/global/NoofDevices"), g_conf.noofdevices);
  	pConfig->Write(_T("/global/NoofReports"), g_conf.noofreports);
	for(int index=0;index<g_conf.noofdevices;index++)
	{
	wxString dName;
	dName.Printf("/global/Device_%d",index);
  	pConfig->Write(dName,g_conf.devices[index]);
	}
	for(int index=0;index<g_conf.noofreports;index++)
	{
	wxString rName;
	rName.Printf("/global/Report_%d",index);
  	pConfig->Write(rName,g_conf.reports[index]);
	}
	}
	
	void wxAcqConfig::SetGlobalReportProfile(wxString & str)
	{
	wxConfigBase *pConfig=wxAcqConfig::Get();
  	pConfig->Write(_T("/global/DefaultReport"), str);
	}

	void wxAcqConfig::SetGlobalDeviceProfile(wxString & str)
	{
	wxConfigBase *pConfig=wxAcqConfig::Get();
  	pConfig->Write(_T("/global/DefaultDevice"), str);
	}
	void wxAcqConfig::CreateUSBDevProfile(struct usbdev_profile & u_conf)
	{


	}
	void wxAcqConfig::CreateSerDevProfile(struct serdev_profile & s_conf)
	{
	wxConfigBase *pConfig=wxAcqConfig::Get();
	wxString prName(s_conf.profname);
	prName.Prepend("/");
	prName.Append("/");
	wxString devName=prName+wxString("Device");
  	pConfig->Write(devName, s_conf.devicename);
	wxString dataB=prName+wxString("DataBits");
  	pConfig->Write(dataB,s_conf.dataBit);
	wxString parB=prName+wxString("ParityBits");
  	pConfig->Write(parB,s_conf.parityBit);
	wxString stopB=prName+wxString("StopBits");
  	pConfig->Write(stopB,s_conf.stopBit);
	wxString baudR=prName+wxString("BaudRate");
  	pConfig->Write(baudR,s_conf.baudRate);
	wxString flwC=prName+wxString("FlowControl");
  	pConfig->Write(flwC,s_conf.flowControl);
	}

	void wxAcqConfig::CreateNetDevProfile(struct netdev_profile & n_conf)
	{
	wxConfigBase *pConfig=wxAcqConfig::Get();
	wxString prName(n_conf.profname);
	prName.Prepend("/");
	prName.Append("/");
	wxString devName=prName+wxString("Device");
  	pConfig->Write(devName, n_conf.devicename);
	wxString ethd=prName+wxString("EthernetDevice");
  	pConfig->Write(ethd,n_conf.ethDev);
	wxString ip=prName+wxString("IPAddr");
  	pConfig->Write(ip,n_conf.ipAddr);
	wxString cp=prName+wxString("ControlPort");
  	pConfig->Write(cp,n_conf.controlPort);
	wxString dp=prName+wxString("DataPort");
  	pConfig->Write(dp,n_conf.dataPort);
	wxString proto=prName+wxString("Protocol");
  	pConfig->Write(proto,n_conf.cProtocol);
	wxString maxc=prName+wxString("MaxConnections");
  	pConfig->Write(maxc,n_conf.maxConnections);
	wxString cmode=prName+wxString("Commmode");
  	pConfig->Write(cmode,n_conf.comMode);
	wxString bc=prName+wxString("NoControlPort");
  	pConfig->Write(bc,n_conf.noControl);
	}

	void    wxAcqConfig::FirstDefaults( )
	{
	wxConfigBase *pConfig=wxAcqConfig::Get();
	wxString ddev;
	
  	if ( ! pConfig->Read(_T("/global/DefaultDevice"), &ddev) )
	{
	struct global_conf g_conf;
	g_conf.defaultdev.Printf("Device000");
	g_conf.defaultreport.Printf("Report000");
	g_conf.noofdevices=2;
	g_conf.noofreports=1;
	g_conf.devices=new wxString[g_conf.noofdevices];
	g_conf.reports=new wxString[g_conf.noofreports];
	for(int rpts=0;rpts<g_conf.noofreports;rpts++)
	g_conf.reports[rpts].Printf("Report%03d",rpts);
	for(int devics=0;devics<g_conf.noofdevices;devics++)
	g_conf.devices[devics].Printf("Device%03d",devics);
	SetGlobalConfig(g_conf);
	delete [] g_conf.devices;
	delete [] g_conf.reports;
	
	fprintf(stderr,"global over\n");
	struct device_profile dev_conf;
	dev_conf.profname=g_conf.defaultdev;
	dev_conf.defaultreport=g_conf.defaultreport;
	dev_conf.devprof.Printf("Serial000");
	dev_conf.devicename.Printf("Normal");
	dev_conf.noofchannels=DEFAULTANACHAN+DEFAULTDIGCHAN;
	fprintf(stderr,"init channels\n");
	
	InitChannels();
	dev_conf.channels=new wxString[dev_conf.noofchannels];



		for(int chanindex=0;chanindex<DEFAULTANACHAN; chanindex++)
		{
		dev_conf.channels[chanindex].Printf("Analog%03d",chanindex);
		defchannels[chanindex].profname=dev_conf.channels[chanindex];
	fprintf(stderr,"channels\n");
		CreateChannelProfile(defchannels[chanindex]);
        	}
		for(int chanindex=DEFAULTANACHAN;chanindex<dev_conf.noofchannels; chanindex++)
		{
	fprintf(stderr,"xchannels\n");
		dev_conf.channels[chanindex].Printf("Digital%03d",chanindex-DEFAULTANACHAN);
		defchannels[chanindex].profname=dev_conf.channels[chanindex];
		CreateChannelProfile(defchannels[chanindex]);
        	}
	fprintf(stderr,"devprof\n");
		CreateDeviceProfile(dev_conf);
		struct serdev_profile s_conf;
		s_conf.profname=dev_conf.devprof;
		s_conf.devicename.Printf("COM1");
		s_conf.baudRate.Printf("9600");
		s_conf.flowControl.Printf("none");
		s_conf.dataBit=8;
		s_conf.parityBit=0;
		s_conf.stopBit=1;
	fprintf(stderr,"serial devprof\n");
		CreateSerDevProfile(s_conf);
		wxString newDevice("Device001");
		dev_conf.profname=newDevice;
		wxString netD("Network");
		dev_conf.devicename=netD;
		wxString netdevprof("Network000");
		dev_conf.devprof=netdevprof;
		CreateDeviceProfile(dev_conf);
		struct netdev_profile n_conf;
		n_conf.profname=dev_conf.devprof;
		n_conf.devicename.Append("Moxa");
		n_conf.ethDev.Append("eth0");
		n_conf.ipAddr.Append("192.168.0.1");
		n_conf.controlPort=950;
		n_conf.dataPort=951;
		 n_conf.cProtocol=0;
		n_conf.maxConnections=25;
		n_conf.comMode=0;
		n_conf.noControl=0;
		CreateNetDevProfile(n_conf);
		delete [] dev_conf.channels;
	struct report_profile repglobal;
	repglobal.profname.Append("Report000");
	repglobal.filename.Append("~/acqreport.txt");
	repglobal.filetype.Append("text");
	repglobal.fileheader.Append(COMPANYHEADER);
	repglobal.filefooter.Append(COMPANYFOOTER);
	repglobal.starttime=true;
	repglobal.startdate=true;
	repglobal.dumpstyle=0;
	repglobal.datatype=0;
	CreateReportProfile(repglobal);
	}	
	}


	 void wxAcqConfig::GetSerialProfile(wxString & profname,struct serdev_profile &serconf)
		{
	wxConfigBase *pConfig=wxAcqConfig::Get();
	wxString prName(profname);
	prName.Prepend("/");
	prName.Append("/");
	wxString devName=prName+wxString("Device");
  	pConfig->Read(devName,&serconf.devicename);
	wxString dataB=prName+wxString("DataBits");
  	pConfig->Read(dataB,&serconf.dataBit);
	wxString parB=prName+wxString("ParityBits");
  	pConfig->Read(parB,&serconf.parityBit);
	wxString stopB=prName+wxString("StopBits");
  	pConfig->Read(stopB,&serconf.stopBit);
	wxString baudR=prName+wxString("BaudRate");
  	pConfig->Read(baudR,&serconf.baudRate);
	wxString flwC=prName+wxString("FlowControl");
  	pConfig->Read(flwC,&serconf.flowControl);
	}
	 void wxAcqConfig::GetNetworkProfile(wxString & profname,struct netdev_profile &netconf)
		{
	wxConfigBase *pConfig=wxAcqConfig::Get();
	wxString prName(profname);
	prName.Prepend("/");
	prName.Append("/");
	wxString devName=prName+wxString("Device");
  	pConfig->Read(devName, &netconf.devicename);
	wxString ethd=prName+wxString("EthernetDevice");
  	pConfig->Read(ethd,&netconf.ethDev);
	wxString ip=prName+wxString("IPAddr");
  	pConfig->Read(ip,&netconf.ipAddr);
	wxString cp=prName+wxString("ControlPort");
	long port;
  	pConfig->Read(cp,&port);
	netconf.controlPort=port;
	wxString dp=prName+wxString("DataPort");
  	pConfig->Read(dp,&port);
	netconf.dataPort=port;
	wxString proto=prName+wxString("Protocol");
	long comp;
  	pConfig->Read(proto,&comp);
	netconf.cProtocol=comp;
	long max_con;
	wxString maxc=prName+wxString("MaxConnections");
  	pConfig->Read(maxc,&max_con);
	netconf.maxConnections=max_con;
	wxString cmode=prName+wxString("Commmode");
  	pConfig->Read(cmode,&netconf.comMode);
	wxString bc=prName+wxString("NoControlPort");
  	pConfig->Read(bc,&netconf.noControl);
	}
	 void wxAcqConfig::GetUSBProfile(wxString & profname,struct usbdev_profile &usbconf)
		{

		}
	 void wxAcqConfig::GetBluetoothProfile(wxString & profname,struct bluetoothdev_profile &blconf)
	{

	}
	 void wxAcqConfig::GetReportProfile(wxString & profname,struct report_profile &repconf)
	{
	wxConfigBase *pConfig=wxAcqConfig::Get();
	wxString prName(profname);
	prName.Prepend("/");
	prName.Append("/");
	wxString devName=prName+wxString("File");
  	pConfig->Read(devName, &repconf.filename);
	wxString dataB=prName+wxString("Type");
  	pConfig->Read(dataB,&repconf.filetype);
	wxString parB=prName+wxString("FileHeader");
  	pConfig->Read(parB,&repconf.fileheader);
	wxString stopB=prName+wxString("FileFooter");
  	pConfig->Read(stopB,&repconf.filefooter);
	wxString baudR=prName+wxString("EnableStartTime");
  	pConfig->Read(baudR,&repconf.starttime);
	baudR=prName+wxString("EnableStartDate");
  	pConfig->Read(baudR,&repconf.startdate);
	baudR=prName+wxString("DumpStyle");
	unsigned long tempdata;
  	pConfig->Write(baudR,&tempdata);
	repconf.dumpstyle=tempdata;
	baudR=prName+wxString("DataType");
  	pConfig->Write(baudR,&tempdata);
	repconf.datatype=tempdata;
	}
	void wxAcqConfig::CreateReportProfile(struct report_profile & repconf)
	{
	wxConfigBase *pConfig=wxAcqConfig::Get();
	wxString prName(repconf.profname);
	prName.Prepend("/");
	prName.Append("/");
	wxString devName=prName+wxString("File");
  	pConfig->Write(devName, repconf.filename);
	wxString dataB=prName+wxString("Type");
  	pConfig->Write(dataB,repconf.filetype);
	wxString parB=prName+wxString("FileHeader");
  	pConfig->Write(parB,repconf.fileheader);
	wxString stopB=prName+wxString("FileFooter");
  	pConfig->Write(stopB,repconf.filefooter);
	wxString baudR=prName+wxString("EnableStartTime");
  	pConfig->Write(baudR,repconf.starttime);
	baudR=prName+wxString("EnableStartDate");
  	pConfig->Write(baudR,repconf.startdate);
	baudR=prName+wxString("DumpStyle");
  	pConfig->Write(baudR,repconf.dumpstyle);
	baudR=prName+wxString("DataType");
  	pConfig->Write(baudR,repconf.datatype);
	}
