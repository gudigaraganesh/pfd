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
#include <devicemanager.h>
#include <device.h>
#include <wxdefs.h>
#include <serialwiz.h>
#include <EmanEz.h>
#include <usbwiz.h>
#include <bluetoothwiz.h>
wxDeviceManager::wxDeviceManager()
{
bCreated=false;
}


wxDeviceManager::~wxDeviceManager()
{

}

void wxDeviceManager::CreateDevice(wxWindow *parent)
{
if(!bCreated)
{
wxBitmap bitmaps(newdevice_xpm);
hwdlg=new wxHardwareDlg(parent,ID_DLGCREATE,wxString("Add Device"),bitmaps);
wxDevOpts *wxpage=new wxDevOpts(hwdlg);
wxSerialWizard *wxspage=new wxSerialWizard(hwdlg);
  wxpage->AddSerialPage(wxspage);
wxUSBWizard *wxupage=new wxUSBWizard(hwdlg);
 wxpage->AddUSBPage(wxupage);
wxBluetoothWizard *wxbpage=new wxBluetoothWizard(hwdlg);
 wxpage->AddBluetoothPage(wxbpage);
wxNetWizard *wxnpage=new wxNetWizard(hwdlg);
wxpage->AddNetworkPage(wxnpage);
wxpage->SetNext(wxspage);
	bCreated=true;
	if(hwdlg->RunWizard(wxpage))
	{
	printf("testing\n");	
	}
	bCreated=false;
	hwdlg->Destroy();	

}
}
