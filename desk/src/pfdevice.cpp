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
#include "wx/wx.h"
#endif

#if !wxUSE_THREADS
#error "Define wxUSE_THREADS for compilation"
#endif							// wxUSE_THREADS
#include <wx/thread.h>
#include <wx/dynarray.h>
#include <wx/progdlg.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/msgdlg.h>
#include <wx/toolbar.h>
//#include <wx/wx.h>
#include <wx/log.h>
//#include "devicemanager.h"
#include <displaythread.h>
#include <connectionthread.h>
#include <acqconfig.h>
#include <hardwaredlg.h>
#include <pfdevice.h>
#include <images.h>
#include <scanfile.h>


#if !wxUSE_DOC_VIEW_ARCHITECTURE
#error You must set wxUSE_DOC_VIEW_ARCHITECTURE to 1 in setup.h!
#endif

#if !wxUSE_MDI_ARCHITECTURE
#error You must set wxUSE_MDI_ARCHITECTURE to 1 in setup.h!
#endif
#include <acqreportdoc.h>
#include <acqreportview.h>
#define ID_TOOLBAR 10010

wxPFdeviceFrame *frmIAcqMain = (wxPFdeviceFrame *) NULL;
wxDocMDIParentFrame *frmRpt = (wxDocMDIParentFrame *) NULL;

IMPLEMENT_APP(wxPFdeviceapp)

wxPFdeviceapp::wxPFdeviceapp():m_semLock()
{
	m_closeAllThreads = FALSE;
	docManager = (wxDocManager *) NULL;
}

wxPFdeviceapp::~wxPFdeviceapp()
{


}








bool wxPFdeviceapp::OnInit()
{
	docManager = new wxDocManager;
  	SetVendorName(_T("G3 Innotronix"));
  	SetAppName(_T("pfdevice")); // not needed, it's the default value
  	wxConfigBase *pConfig = wxAcqConfig::Get();
  	wxAcqConfig::InitAll();
	(void) new wxDocTemplate(docManager, _T("Text"), _T("*.txt"), _T(""),
							 _T("txt"), _T("Text Doc"), _T("Text View"),
							 CLASSINFO(wxAcqReportDoc),
							 CLASSINFO(wxAcqReportView));

	//// Create the main frame window
	frmIAcqMain =
		new wxPFdeviceFrame((wxDocManager *) docManager, (wxFrame *) NULL,
							_T("pFDevice"), wxPoint(0, 0), wxSize(500, 400),
							wxDEFAULT_FRAME_STYLE |
							wxNO_FULL_REPAINT_ON_RESIZE);

#ifdef __WXMSW__
	frmIAcqMain->SetIcon(wxICON(iacq));
#endif
#ifdef __X__
	frmIAcqMain->SetIcon(wxIcon(_T("../images/aw.xpm")));
#endif


	CreateMenuForAW(frmIAcqMain);
	//Createa ToolBar
	frmIAcqMain->BuildAWToolbar();
	frmIAcqMain->Centre(wxBOTH);
	frmIAcqMain->Show(TRUE);
	SetTopWindow(frmIAcqMain);
	return TRUE;
}


void wxPFdeviceapp::CreateMenuForAW(wxPFdeviceFrame * frameMain)
{
//Creating All the Menus

	frameMain->menuFile = new wxMenu;
	frameMain->menuEdit = new wxMenu;
	frameMain->menuView = new wxMenu;
	frameMain->menuDevice = new wxMenu;
	frameMain->menuSettings = new wxMenu;
	frameMain->menuHelp = new wxMenu;
	frameMain->menuFile->Append(wxID_OPEN, wxT("&Open..."));
	frameMain->menuFile->AppendSeparator();
	frameMain->menuFile->Append(wxID_CLOSE, wxT("&Close..."));
	frameMain->menuFile->AppendSeparator();
	frameMain->menuFile->Append(wxID_SAVE, wxT("&Save..."));
	frameMain->menuFile->AppendSeparator();
	frameMain->menuFile->Append(wxID_SAVEAS, wxT("S&aveAs..."));
	frameMain->menuFile->AppendSeparator();
	frameMain->menuFile->Append(wxID_PRINT, wxT("&Print..."));
	frameMain->menuFile->AppendSeparator();
	frameMain->menuFile->Append(wxID_PRINT_SETUP, wxT("Pr&int Setup..."));
	frameMain->menuFile->AppendSeparator();
	frameMain->menuFile->Append(wxID_PREVIEW, wxT("P&revie..."));
	frameMain->menuFile->AppendSeparator();
	frameMain->menuFile->Append(Menu_File_Quit, wxT("E&xit"));
	docManager->FileHistoryUseMenu(frameMain->menuFile);

//Create frameMain->menu items Edit Menu
	frameMain->menuEdit->Append(wxID_UNDO, wxT("&Undo..."));
	frameMain->menuEdit->AppendSeparator();
	frameMain->menuEdit->Append(wxID_REDO, wxT("&Redo..."));
	frameMain->menuEdit->AppendSeparator();
	frameMain->menuEdit->Append(wxID_CUT, wxT("C&ut..."));
	frameMain->menuEdit->AppendSeparator();
	frameMain->menuEdit->Append(wxID_COPY, wxT("&Copy..."));
	frameMain->menuEdit->AppendSeparator();
	frameMain->menuEdit->Append(wxID_PASTE, wxT("&Paste..."));
	frameMain->menuEdit->AppendSeparator();
	frameMain->menuEdit->Append(wxID_SELECTALL, wxT("&SelectAll..."));
	frameMain->menuEdit->AppendSeparator();

	frameMain->menuView->Append(Menu_View_GraphManager, wxT("Graph..."));
	frameMain->menuView->AppendSeparator();
	frameMain->menuView->Append(Menu_View_Channel, wxT("Channel..."));
	frameMain->menuView->AppendSeparator();
	frameMain->menuView->Append(Menu_View_Device, wxT("Device..."));
	frameMain->menuView->AppendSeparator();
	frameMain->menuView->Append(Menu_View_RawData, wxT("Dump..."));
	frameMain->menuView->AppendSeparator();
	frameMain->menuView->AppendSeparator();
	frameMain->menuView->Append(Menu_View_Report, wxT("Report..."));
	frameMain->menuView->AppendSeparator();
	frameMain->menuView->Append(Menu_View_Config, wxT("Config..."));
	frameMain->menuView->AppendSeparator();

//Creates All Device Menu Items
	frameMain->menuDevice->Append(Menu_Device_New, wxT("New..."));
	frameMain->menuDevice->AppendSeparator();
	frameMain->menuDevice->Append(Menu_Device_Options, wxT("Options..."));
	frameMain->menuDevice->AppendSeparator();
	frameMain->menuDevice->Append(Menu_Device_Serial, wxT("Serial..."));
	frameMain->menuDevice->AppendSeparator();
	frameMain->menuDevice->Append(Menu_Device_Network, wxT("Network..."));
	frameMain->menuDevice->AppendSeparator();
	frameMain->menuDevice->Append(Menu_Device_USB, wxT("USB..."));
	frameMain->menuDevice->AppendSeparator();
	frameMain->menuDevice->Append(Menu_Device_Connect, wxT("Connect..."));
	frameMain->menuDevice->AppendSeparator();
	frameMain->menuDevice->Append(Menu_Device_Mapping, wxT("Map..."));
	frameMain->menuDevice->AppendSeparator();

	frameMain->menuSettings->Append(Menu_Settings_General, wxT("General..."));
	frameMain->menuSettings->AppendSeparator();
	frameMain->menuSettings->Append(Menu_Settings_Graph, wxT("Graph..."));
	frameMain->menuSettings->AppendSeparator();
	frameMain->menuSettings->Append(Menu_Settings_Channel, wxT("Channel..."));
	frameMain->menuSettings->AppendSeparator();
	frameMain->menuSettings->Append(Menu_Settings_Report, wxT("Report..."));
	frameMain->menuSettings->AppendSeparator();

	frameMain->menuHelp->Append(Menu_Help_About, wxT("About..."));
	frameMain->menuHelp->AppendSeparator();
	frameMain->menuHelp->Append(Menu_Help_Contents, wxT("Contents..."));
	frameMain->menuHelp->AppendSeparator();
	frameMain->menuHelp->Append(Menu_Help_Contact, wxT("Contact..."));
	frameMain->menuBar = new wxMenuBar;
	frameMain->menuBar->Append(frameMain->menuFile, wxT("&File"));
	frameMain->menuBar->Append(frameMain->menuEdit, wxT("&Edit"));
	frameMain->menuBar->Append(frameMain->menuView, wxT("&View"));
	frameMain->menuBar->Append(frameMain->menuDevice, wxT("&Device"));
	frameMain->menuBar->Append(frameMain->menuSettings, wxT("&Settings"));
	frameMain->menuBar->Append(frameMain->menuHelp, wxT("&Help"));
#if wxUSE_MENUS
//Add frameMain->menubar
	frameMain->SetMenuBar(frameMain->menuBar);
#endif
}

wxMDIChildFrame *wxPFdeviceapp::CreateChildFrame(wxDocument * doc,
												 wxView * view, bool isCanvas)
{
	printf("Called to create\n");
	wxDocMDIChildFrame *subframe =
		new wxDocMDIChildFrame(doc, view, (wxDocMDIParentFrame *) frmRpt, -1,
							   _T("Child Frame"),
							   wxPoint(0, 0), wxSize(300, 300),
							   wxDEFAULT_FRAME_STYLE |
							   wxNO_FULL_REPAINT_ON_RESIZE);
#ifdef __WXMSW__
	subframe->SetIcon(wxICON(iacq));
#endif
	wxMenu *file_menu = new wxMenu;

	file_menu->Append(wxID_OPEN, _T("&Open..."));
	file_menu->Append(wxID_CLOSE, _T("&Close"));
	file_menu->Append(wxID_SAVE, _T("&Save"));
	file_menu->Append(wxID_SAVEAS, _T("Save &As..."));
	file_menu->AppendSeparator();
	file_menu->Append(wxID_PRINT, _T("&Print..."));
	file_menu->Append(wxID_PRINT_SETUP, _T("Print &Setup..."));
	file_menu->Append(wxID_PREVIEW, _T("Print Pre&view"));
	wxMenu *edit_menu = (wxMenu *) NULL;
	wxMenu *help_menu = new wxMenu;

	edit_menu = new wxMenu;
	edit_menu->Append(wxID_UNDO, _T("&Undo"));
	edit_menu->Append(wxID_REDO, _T("&Redo"));
	edit_menu->AppendSeparator();
	edit_menu->Append(wxID_CUT, _T("C&ut"));
	edit_menu->AppendSeparator();
	edit_menu->Append(wxID_COPY, _T("&Copy"));
	edit_menu->AppendSeparator();
	edit_menu->Append(wxID_PASTE, _T("&Paste"));
	edit_menu->AppendSeparator();
	edit_menu->Append(wxID_SELECTALL, wxT("&SelectAll..."));
	doc->GetCommandProcessor()->SetEditMenu(edit_menu);
	help_menu->Append(Menu_Help_About, _T("&About"));
	wxMenuBar *menu_bar = new wxMenuBar;

	menu_bar->Append(file_menu, _T("&File"));
	menu_bar->Append(edit_menu, _T("&Edit"));
	menu_bar->Append(help_menu, _T("&Help"));
	//// Associate the menu bar with the frame
	subframe->SetMenuBar(menu_bar);
	return subframe;
}

/**************************End of App Class ***********************************/

/******************************************************************************/














wxPFdeviceFrame::wxPFdeviceFrame(wxDocManager * manager, wxFrame * parent, const wxString & title, const wxPoint & pos, const wxSize & size, long styles):wxDocMDIParentFrame(manager, (wxFrame *) NULL, -1, title, pos,
					size,
					styles)
{
	frmRpt =
		new wxDocMDIParentFrame(manager, (wxFrame *) this, 5556, title, pos,
								wxSize(300, 300));
	CreateStatusBar(2);
	m_devicemanager = new wxDeviceManager();
	//Creates the Status Bar
	SetStatusText(wxT("Loading All Settings....."));
	wxBoxSizer *topsizer = new wxBoxSizer(wxHORIZONTAL);
	int width = GetClientRect().GetWidth();
	int hgt = GetClientRect().GetHeight();

	CreateMuxWindow((width * 3) / 4, hgt);
	wxColour clr(50, 50, 100);
	wxSize size1(width / 4, hgt);

	m_muxdisp =
		new wxAcqPanel((wxWindow *) this, -1, wxDefaultPosition, size1, clr);
	topsizer->Add(m_muxdisp, 0, wxEXPAND);
	topsizer->Add(tblinfo, 1, wxEXPAND);
	SetAutoLayout(TRUE);
	SetSizer(topsizer);

}




/* Closing the App */
void wxPFdeviceFrame::OnQuit(wxCommandEvent & WXUNUSED(event))
{
	frmRpt->Close(TRUE);
	Close(TRUE);
}



/*****************************************************************************
Function 		: OnViewGraph
Description		 : Shows the Graph Window Selection Box
Arguments		 : wxCommandEvent
Return Value		 : none
Author			 : Ganesh Gudigara
******************************************************************************/
void wxPFdeviceFrame::OnViewGraph(wxCommandEvent & WXUNUSED(event))
{
//wxGetApp().printk();
}

/*****************************************************************************
Function 		: OnViewChannel
Description		 : Shows the Graph Window Selection Box
Arguments		 : wxCommandEvent
Return Value		 : none
Author			 : Ganesh Gudigara
******************************************************************************/
void wxPFdeviceFrame::OnViewChannel(wxCommandEvent & WXUNUSED(event))
{
	wxMessageBox(wxT("Implementing Soon"),
				 wxT("Welcome To Acquireware From GG"),
				 wxOK | wxICON_INFORMATION, this);
}

/*****************************************************************************
Function 		: OnViewDevice
Description		 : Shows the Graph Window Selection Box
Arguments		 : wxCommandEvent
Return Value		 : none
Author			 : Ganesh Gudigara
******************************************************************************/
void wxPFdeviceFrame::OnViewDevice(wxCommandEvent & WXUNUSED(event))
{
	wxMessageBox(wxT("Implementing Soon"),
				 wxT("Welcome To Acquireware From GG"),
				 wxOK | wxICON_INFORMATION, this);
}


/*****************************************************************************
Function 		: OnViewRawData
Description		 : Shows the Graph Window Selection Box
Arguments		 : wxCommandEvent
Return Value		 : none
Author			 : Ganesh Gudigara
******************************************************************************/
void wxPFdeviceFrame::OnViewRawData(wxCommandEvent & WXUNUSED(event))
{
	wxMessageBox(wxT("Implementing Soon"),
				 wxT("Welcome To Acquireware From GG"),
				 wxOK | wxICON_INFORMATION, this);
}


/*****************************************************************************
Function 		: OnViewReport
Description		 : Shows the Graph Window Selection Box
Arguments		 : wxCommandEvent
Return Value		 : none
Author			 : Ganesh Gudigara
******************************************************************************/
void wxPFdeviceFrame::OnViewReport(wxCommandEvent & WXUNUSED(event))
{
	wxMessageBox(wxT("Implementing Soon"),
				 wxT("Welcome To Acquireware From GG"),
				 wxOK | wxICON_INFORMATION, this);
}

/*****************************************************************************
Function 		: OnViewConfig
Description		 : Shows the Graph Window Selection Box
Arguments		 : wxCommandEvent
Return Value		 : none
Author			 : Ganesh Gudigara
******************************************************************************/
void wxPFdeviceFrame::OnViewConfig(wxCommandEvent & WXUNUSED(event))
{
	wxMessageBox(wxT("Implementing Soon"),
				 wxT("Welcome To Acquireware From GG"),
				 wxOK | wxICON_INFORMATION, this);
}


/*****************************************************************************
Function 		: OnNewDevice
Description		 : Shows the Graph Window Selection Box
Arguments		 : wxCommandEvent
Return Value		 : none
Author			 : Ganesh Gudigara
******************************************************************************/
void wxPFdeviceFrame::OnNewDevice(wxCommandEvent & WXUNUSED(event))
{
//LaunchNewDeviceCreator(&m_confUpdate);
	if (m_devicemanager != NULL)
		m_devicemanager->CreateDevice(this);
}


/*****************************************************************************
Function 		: OnDeviceOptions
Description		 : Shows the Graph Window Selection Box
Arguments		 : wxCommandEvent
Return Value		 : none
Author			 : Ganesh Gudigara
******************************************************************************/
void wxPFdeviceFrame::OnDeviceOptions(wxCommandEvent & WXUNUSED(event))
{
	wxMessageBox(wxT("Implementing Soon"),
				 wxT("Welcome To Acquireware From GG"),
				 wxOK | wxICON_INFORMATION, this);
}

/*****************************************************************************
Function 		: OnSerialDevice
Description		 : Shows the Graph Window Selection Box
Arguments		 : wxCommandEvent
Return Value		 : none
Author			 : Ganesh Gudigara
******************************************************************************/
void wxPFdeviceFrame::OnSerialDevice(wxCommandEvent & WXUNUSED(event))
{
	wxMessageBox(wxT("Implementing Soon"),
				 wxT("Welcome To Acquireware From GG"),
				 wxOK | wxICON_INFORMATION, this);
}


/*****************************************************************************
Function 		: OnNetworkDevice
Description		 : Shows the Graph Window Selection Box
Arguments		 : wxCommandEvent
Return Value		 : none
Author			 : Ganesh Gudigara
******************************************************************************/
void wxPFdeviceFrame::OnNetworkDevice(wxCommandEvent & WXUNUSED(event))
{
	wxMessageBox(wxT("Implementing Soon"),
				 wxT("Welcome To Acquireware From GG"),
				 wxOK | wxICON_INFORMATION, this);
}


/*****************************************************************************
Function 		: OnUSBDevice
Description		 : Shows the Graph Window Selection Box
Arguments		 : wxCommandEvent
Return Value		 : none
Author			 : Ganesh Gudigara
******************************************************************************/
void wxPFdeviceFrame::OnUSBDevice(wxCommandEvent & WXUNUSED(event))
{
	wxMessageBox(wxT("Implementing Soon"),
				 wxT("Welcome To Acquireware From GG"),
				 wxOK | wxICON_INFORMATION, this);
}


/*****************************************************************************
Function 		: OnDeviceConnect
Description		 : Shows the Graph Window Selection Box
Arguments		 : wxCommandEvent
Return Value		 : none
Author			 : Ganesh Gudigara
******************************************************************************/
void wxPFdeviceFrame::OnDeviceConnect(wxCommandEvent & WXUNUSED(event))
{
	wxMessageBox(wxT("Implementing Soon"),
				 wxT("Welcome To Acquireware From GG"),
				 wxOK | wxICON_INFORMATION, this);
}


/*****************************************************************************
Function 		: OnMapDevice
Description		 : Shows the Graph Window Selection Box
Arguments		 : wxCommandEvent
Return Value		 : none
Author			 : Ganesh Gudigara
******************************************************************************/
void wxPFdeviceFrame::OnMapDevice(wxCommandEvent & WXUNUSED(event))
{
	wxMessageBox(wxT("Implementing Soon"),
				 wxT("Welcome To Acquireware From GG"),
				 wxOK | wxICON_INFORMATION, this);
}



/*****************************************************************************
Function 		: OnGeneralSettings
Description		 : Shows the Graph Window Selection Box
Arguments		 : wxCommandEvent
Return Value		 : none
Author			 : Ganesh Gudigara
******************************************************************************/
void wxPFdeviceFrame::OnGeneralSettings(wxCommandEvent & WXUNUSED(event))
{
	wxMessageBox(wxT("Implementing Soon"),
				 wxT("Welcome To Acquireware From GG"),
				 wxOK | wxICON_INFORMATION, this);
}




/*****************************************************************************
Function 		: OnChannelSettings
Description		 : Shows the Graph Window Selection Box
Arguments		 : wxCommandEvent
Return Value		 : none
Author			 : Ganesh Gudigara
******************************************************************************/
void wxPFdeviceFrame::OnChannelSettings(wxCommandEvent & WXUNUSED(event))
{
	wxMessageBox(wxT("Implementing Soon"),
				 wxT("Welcome To Acquireware From GG"),
				 wxOK | wxICON_INFORMATION, this);
}






/*****************************************************************************
Function 		: OnGraphSettings
Description		 : Shows the Graph Window Selection Box
Arguments		 : wxCommandEvent
Return Value		 : none
Author			 : Ganesh Gudigara
******************************************************************************/
void wxPFdeviceFrame::OnGraphSettings(wxCommandEvent & WXUNUSED(event))
{
	wxMessageBox(wxT("Implementing Soon"),
				 wxT("Welcome To Acquireware From GG"),
				 wxOK | wxICON_INFORMATION, this);
}




/*****************************************************************************
Function 		: OnReportSettings
Description		 : Shows the Graph Window Selection Box
Arguments		 : wxCommandEvent
Return Value		 : none
Author			 : Ganesh Gudigara
******************************************************************************/
void wxPFdeviceFrame::OnReportSettings(wxCommandEvent & WXUNUSED(event))
{
	wxMessageBox(wxT("Implementing Soon"),
				 wxT("Welcome To Acquireware From GG"),
				 wxOK | wxICON_INFORMATION, this);
}



/*****************************************************************************
Function 		: OnHelpAbout
Description		 : Shows the Graph Window Selection Box
Arguments		 : wxCommandEvent
Return Value		 : none
Author			 : Ganesh Gudigara
******************************************************************************/
void wxPFdeviceFrame::OnHelpAbout(wxCommandEvent & WXUNUSED(event))
{
	wxMessageBox(wxT("Implementing Soon"),
				 wxT("Welcome To Acquireware From GG"),
				 wxOK | wxICON_INFORMATION, this);
}

/*****************************************************************************
Function 		: OnHelpContents
Description		 : Shows the Graph Window Selection Box
Arguments		 : wxCommandEvent
Return Value		 : none
Author			 : Ganesh Gudigara
******************************************************************************/
void wxPFdeviceFrame::OnHelpContents(wxCommandEvent & WXUNUSED(event))
{
	wxMessageBox(wxT("Implementing Soon"),
				 wxT("Welcome To Acquireware From GG"),
				 wxOK | wxICON_INFORMATION, this);
}


/*****************************************************************************
Function 		: OnHelpContact
Description		 : Shows the Graph Window Selection Box
Arguments		 : wxCommandEvent
Return Value		 : none
Author			 : Ganesh Gudigara
******************************************************************************/
void wxPFdeviceFrame::OnHelpContact(wxCommandEvent & WXUNUSED(event))
{
	wxMessageBox(wxT("Implementing Soon"),
				 wxT("Welcome To Acquireware From GG"),
				 wxOK | wxICON_INFORMATION, this);
}

bool wxPFdeviceFrame::BuildAWToolbar()
{
	wxBitmap tbimgs[8];

#if !defined(__WXMW__)
	tbimgs[0] = wxBitmap(open_xpm);
	tbimgs[1] = wxBitmap(close_xpm);
	tbimgs[2] = wxBitmap(print_xpm);
	tbimgs[3] = wxBitmap(connect_xpm);
	tbimgs[4] = wxBitmap(help_xpm);
	tbimgs[5] = wxBitmap(stop_xpm);
	tbimgs[6] = wxBitmap(ethernet_xpm);
	tbimgs[7] = wxBitmap(ppp_xpm);
#else
	tbimgs[0] = wxBITMAP(open);
	tbimgs[1] = wxBITMAP(close);
	tbimgs[2] = wxBITMAP(print);
	tbimgs[3] = wxBITMAP(connect);
	tbimgs[4] = wxBITMAP(help);
	tbimgs[5] = wxBITMAP(stop);
	tbimgs[6] = wxBITMAP(ethernet);
	tbimgs[7] = wxBITMAP(ppp);
#endif



//All Bitmaps for the Toolbar


	int width = 32;

	//Creates A toolbar the AW frame  
	CreateToolBar(wxNO_BORDER | wxHORIZONTAL | wxTB_FLAT, ID_TOOLBAR);
	GetToolBar()->SetMargins(2, 2);
	wxToolBar *toolBar = GetToolBar();
	int currentX = 5;

	toolBar->AddSeparator();
	toolBar->AddTool(wxID_OPEN, tbimgs[0], wxNullBitmap, false, currentX, -1,
					 (wxObject *) NULL, "Open file");
	currentX += width + 5;
	toolBar->AddTool(wxID_CLOSE, tbimgs[1], wxNullBitmap, false, currentX, -1,
					 (wxObject *) NULL, "Close file");
	currentX += width + 5;
	toolBar->AddTool(wxID_PRINT, tbimgs[2], wxNullBitmap, false, currentX, -1,
					 (wxObject *) NULL, "Print file");
	currentX += width + 5;
	toolBar->AddSeparator();
	toolBar->AddTool(Menu_Device_Connect, tbimgs[3], wxNullBitmap, false,
					 currentX, -1, (wxObject *) NULL, "Connect");
	currentX += width + 5;
	toolBar->AddSeparator();
	toolBar->AddTool(Menu_View_Channel, tbimgs[4], wxNullBitmap, false,
					 currentX, -1, (wxObject *) NULL, "Show Channel");
	currentX += width + 5;
	toolBar->AddTool(Menu_View_GraphManager, tbimgs[5], wxNullBitmap, false,
					 currentX, -1, (wxObject *) NULL, "Show Graph");
	currentX += width + 5;
	toolBar->AddSeparator();
	toolBar->AddTool(Menu_Device_Network, tbimgs[6], wxNullBitmap, false,
					 currentX, -1, (wxObject *) NULL, "Network Device");
	currentX += width + 5;
	toolBar->AddSeparator();
	toolBar->AddTool(Menu_Device_Serial, tbimgs[7], wxNullBitmap, false,
					 currentX, -1, (wxObject *) NULL, "Serial Device");
	toolBar->Realize();
	// Can delete the bitmaps since they're reference counted
	return true;
}


void wxPFdeviceFrame::CloseThreads(void)
{
	int thr_count = 0;

	wxGetApp().m_critSection.Enter();
	thr_count = wxDisplayThread::DestroyThreads();
	thr_count = wxConnectionThread::DestroyThreads();
	wxGetApp().m_closeAllThreads = TRUE;
	wxGetApp().m_critSection.Leave();
	if (thr_count) {
		wxGetApp().m_semLock.Wait();
	}
}

void wxPFdeviceFrame::StartThread(int type, wxAcqConfig & cFile)
{
	char thr_nambuf[30];

	sprintf(thr_nambuf, "THREAD%02d-%04d-DISPLAY", type,
			wxDisplayThread::GetCount() + 1);
	wxDisplayThread::CreateThread(thr_nambuf, cFile, wxGetApp());
	sprintf(thr_nambuf, "THREAD%02d-%04d-CONNECTION", type,
			wxConnectionThread::GetCount() + 1);
	wxConnectionThread::CreateThread(thr_nambuf, cFile, wxGetApp());
}


void wxPFdeviceFrame::LaunchNewDeviceCreator(wxAcqConfig * m_config)
{
	int status = wxHardwareDlg::Launch(m_config, this);

	if (status)
		StartThread(1, *m_config);
}


void wxPFdeviceFrame::CreateMuxWindow(int horiz, int vert)
{
	wxPoint posi(0, 0);
	wxString devlbl("DeviceTable");
	wxColour bkclr(255, 255, 200);

//wxColour bkclr(100,100,200);
	wxColour foreclr(0, 0, 0);
	wxColour linclr(0, 40, 40);

	tblinfo =
		new wxTableInfo((wxWindow *) this, ID_MGRID, posi, wxDefaultSize,
						devlbl, bkclr, foreclr, linclr);
	tblinfo->CreateGrid(12, 6);
	tblinfo->EnableEditing(false);
	tblinfo->SetColLabelValue(0, wxString("Device Name"));
	tblinfo->SetColLabelValue(1, wxString("Status"));
	tblinfo->SetColLabelValue(2, wxString("Type"));
	tblinfo->SetColLabelValue(3, wxString("Port"));
	tblinfo->SetColLabelValue(4, wxString("IP Address"));
	tblinfo->SetColLabelValue(5, wxString("Settings"));
	tblinfo->SetLastGridColSize(horiz);
}
void wxPFdeviceFrame::ResizeMuxWindow(int horiz, int vert)
{
	if (tblinfo != NULL) {
		tblinfo->SetSize(0, 0, horiz, vert);
		tblinfo->SetLastGridColSize(horiz);
	}
	if (m_frmHandle != NULL) {
		m_frmHandle->SetSize(0, vert, horiz, vert);
	}
}


void wxPFdeviceFrame::CreateControlRoom(wxMultiplexDisp * controlroom,
										int horiz, int vert)
{
	ctrladd =
		new wxMControls(controlroom, ID_BADD, wxString("Add Device"),
						wxPoint(10, 10), wxSize(110, 30));
	ctrlscan =
		new wxMControls(controlroom, ID_BSCN, wxString("Search Device"),
						wxPoint(10, 60), wxSize(110, 30));
	ctrlchg =
		new wxMControls(controlroom, ID_BCHG, wxString("Device Settings"),
						wxPoint(10, 110), wxSize(110, 30));
	ctrlexit =
		new wxMControls(controlroom, ID_BEXIT, wxString("Exit"),
						wxPoint(10, 160), wxSize(110, 30));
	ctrlgo =
		new wxMControls(controlroom, ID_BGO, wxString("Go"), wxPoint(140, 10),
						wxSize(110, 30));
	ctrlstop =
		new wxMControls(controlroom, ID_BSTP, wxString("Stop"),
						wxPoint(270, 10), wxSize(110, 30));
	ctrlrpt =
		new wxMControls(controlroom, ID_BSTP, wxString("Show Report"),
						wxPoint(400, 10), wxSize(110, 30));
	static const wxString strAr[] = {
		wxString("Channel Window Mode"),
		wxString("Graph Window Mode"),
		wxString("Hexdata Dump Mode")
	};

	cbdispmode =
		new wxComboBox((wxWindow *) controlroom, ID_CBMOD, strAr[0],
					   wxPoint(290, 60), wxSize(150, 30), 3,
					   (const wxString *) strAr,
					   wxCB_SIMPLE | wxCB_READONLY | wxCB_DROPDOWN);

	txtinf =
		new wxManageText((wxWindow *) controlroom, ID_TINF, wxString(""),
						 wxPoint(140, 110), wxSize(horiz - 140, vert - 110),
						 *wxWHITE,
						 wxTE_READONLY | wxSUNKEN_BORDER | wxTE_MULTILINE);



	wxString msgt("Select Display Mode");
	wxSize siz(140, 20);
	wxPoint posx(140, 60);
	wxColour clrs(controlroom->GetBackgroundColour());
	long int styles = wxTE_READONLY | wxNO_BORDER;

	controlroom->SetForegroundColour(*wxWHITE);
	wxFont fontdef = controlroom->GetFont();

	fontdef.SetPointSize(16);
	controlroom->SetFont(fontdef);
	sellbl =
		new wxStaticText((wxWindow *) controlroom, ID_TCSEL, msgt, posx, siz);
	rbdevicemode =
		new wxRadioButton(controlroom, ID_RBDM,
						  wxString("Device Info/Console"), wxPoint(460, 60));
}

void wxPFdeviceFrame::ResizeControlRoom(wxMultiplexDisp * controlroom,
										int horiz, int vert)
{

	int vertsize = 140, horsize = 460;

//printf("%d",horiz);
//printf("%d",vert);
	if (controlroom != NULL) {
		if (horiz > 140)
			horsize = horiz - 140;
		if (vert > 110)
			vertsize = vert - 110;
		if (txtinf != NULL)
			txtinf->SetSize(horsize, vertsize);
	}

}

void wxPFdeviceFrame::OnClick(wxMouseEvent & event)
{

	printf("Hello How r u");
}

//IMPLEMENT_CLASS(wxPFdeviceFrame, wxDocMDIParentFrame)
BEGIN_EVENT_TABLE(wxPFdeviceFrame, wxDocMDIParentFrame)
EVT_MENU(Menu_File_Quit, wxPFdeviceFrame::OnQuit)
//EVT_PAINT (wxPFdeviceFrame::OnPaint)
	EVT_MENU(Menu_View_GraphManager, wxPFdeviceFrame::OnViewGraph)
	EVT_MENU(Menu_View_Channel, wxPFdeviceFrame::OnViewChannel)
	EVT_MENU(Menu_View_Device, wxPFdeviceFrame::OnViewDevice)
	EVT_MENU(Menu_View_RawData, wxPFdeviceFrame::OnViewRawData)
	EVT_MENU(Menu_View_Report, wxPFdeviceFrame::OnViewReport)
	EVT_MENU(Menu_View_Config, wxPFdeviceFrame::OnViewConfig)
	EVT_MENU(Menu_Device_New, wxPFdeviceFrame::OnNewDevice)
	EVT_MENU(Menu_Device_Options, wxPFdeviceFrame::OnDeviceOptions)
	EVT_MENU(Menu_Device_Serial, wxPFdeviceFrame::OnSerialDevice)
	EVT_MENU(Menu_Device_Network, wxPFdeviceFrame::OnNetworkDevice)
	EVT_MENU(Menu_Device_USB, wxPFdeviceFrame::OnUSBDevice)
	EVT_MENU(Menu_Device_Connect, wxPFdeviceFrame::OnDeviceConnect)
	EVT_MENU(Menu_Device_Mapping, wxPFdeviceFrame::OnMapDevice)
	EVT_MENU(Menu_Settings_General, wxPFdeviceFrame::OnGeneralSettings)
	EVT_MENU(Menu_Settings_Channel, wxPFdeviceFrame::OnChannelSettings)
	EVT_MENU(Menu_Settings_Graph, wxPFdeviceFrame::OnGraphSettings)
	EVT_MENU(Menu_Settings_Report, wxPFdeviceFrame::OnReportSettings)
	EVT_MENU(Menu_Help_About, wxPFdeviceFrame::OnHelpAbout)
	EVT_MENU(Menu_Help_Contents, wxPFdeviceFrame::OnHelpContents)
EVT_MENU(Menu_Help_Contact, wxPFdeviceFrame::OnHelpContact)
//EVT_ERASE_BACKGROUND (wxPFdeviceFrame::OnErase)
	EVT_BUTTON(ID_BADD, wxPFdeviceFrame::OnNewDevice)
END_EVENT_TABLE()

	wxPFdeviceFrame *GetMainFrame()
{
	return frmIAcqMain;
}

wxDocMDIParentFrame *GetReportFrame()
{
	return frmRpt;
}
