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

#ifndef _WXPFDEVICE_H_
#define _WXPFDEVICE_H_

#define ID_TEXTDISP 10020
/**
 * @short Application Main Window
 * @author Ganesh Gudigara <ganeshgudigara@parappadi.com>
 * @version 0.1
 */
#include <tableinfo.h>
#include <multiplexdisp.h>
#include <displayframe.h>
#include <channelgrid.h>
#include <mcontrols.h>
#include <managetext.h>
#include <devicemanager.h>
#include <wx/mdi.h>
#include <wx/docview.h>
#include <wx/docmdi.h>
#include <acqpanel.h>
class wxDocManager;
class wxPFdeviceFrame;
class wxPFdeviceapp:public wxApp {
  public:
	wxPFdeviceapp();
	virtual ~ wxPFdeviceapp();
	wxCriticalSection m_critSection;
	wxSemaphore m_semLock;
	bool m_closeAllThreads;
	bool OnInit();
	void CreateMenuForAW(wxPFdeviceFrame * frameMain);
	wxMDIChildFrame *CreateChildFrame(wxDocument * doc, wxView * view,
									  bool isCanvas);
  protected:
	 wxDocManager * docManager;
};

DECLARE_APP(wxPFdeviceapp)
	class wxPFdeviceFrame:public wxDocMDIParentFrame {

		//   DECLARE_CLASS(wxPFdeviceFrame)
	  public:


		wxPFdeviceFrame(wxDocManager * manager, wxFrame * parent,
						const wxString & title, const wxPoint & pos,
						const wxSize & size, long style);
		void OnQuit(wxCommandEvent & event);
		void OnOpen(wxCommandEvent & event);
		void OnClose(wxCommandEvent & event);
		void OnPrint(wxCommandEvent & event);
		void OnSave(wxCommandEvent & event);
		void OnSaveAs(wxCommandEvent & event);

		void OnEditUndo(wxCommandEvent & event);
		void OnEditRedo(wxCommandEvent & event);
		void OnEditCut(wxCommandEvent & event);
		void OnEditCopy(wxCommandEvent & event);
		void OnEditPaste(wxCommandEvent & event);

		void OnViewGraph(wxCommandEvent & event);
		void OnViewChannel(wxCommandEvent & event);
		void OnViewDevice(wxCommandEvent & event);
		void OnViewRawData(wxCommandEvent & event);
		void OnViewReport(wxCommandEvent & event);
		void OnViewConfig(wxCommandEvent & event);

		void OnNewDevice(wxCommandEvent & event);
		void OnClick(wxMouseEvent & event);
		void OnDeviceOptions(wxCommandEvent & event);
		void OnSerialDevice(wxCommandEvent & event);
		void OnNetworkDevice(wxCommandEvent & event);
		void OnUSBDevice(wxCommandEvent & event);
		void OnDeviceConnect(wxCommandEvent & event);
		void OnMapDevice(wxCommandEvent & event);

		void OnGeneralSettings(wxCommandEvent & event);
		void OnChannelSettings(wxCommandEvent & event);
		void OnGraphSettings(wxCommandEvent & event);
		void OnReportSettings(wxCommandEvent & event);

		void OnHelpAbout(wxCommandEvent & event);
		void OnHelpContents(wxCommandEvent & event);
		void OnHelpContact(wxCommandEvent & event);



		//void OnPaint (wxPaintEvent & event);
		// void OnErase (wxEraseEvent & event);
		void OnSize(wxSizeEvent & evmax);
		bool BuildAWToolbar();

		void CloseThreads();
		void StartThread(int type, wxAcqConfig & cConfig);
		void LaunchNewDeviceCreator(wxAcqConfig * m_config);
		void CreateMuxWindow(int horiz = 200, int vert = 50);
		void CreateControlRoom(wxMultiplexDisp * controlroom, int horiz,
							   int vert);
		void ResizeMuxWindow(int horiz = 200, int vert = 50);
		void ResizeControlRoom(wxMultiplexDisp * controlroom, int horiz,
							   int vert);

		wxTableInfo *tblinfo;
		wxAcqPanel *m_muxdisp;	// For Data Display
		wxMultiplexDisp *m_frmHandle;
		wxMControls *ctrladd;
		wxMControls *ctrlscan;
		wxMControls *ctrlchg;
		wxMControls *ctrlexit;
		wxMControls *ctrlgo;
		wxMControls *ctrlstop;
		wxMControls *ctrlrpt;
		wxDeviceManager *m_devicemanager;
		wxStaticText *sellbl;
		wxManageText *txtinf;
		wxComboBox *cbdispmode;
		wxRadioButton *rbdevicemode;
		wxChannelGrid *dialog1;

		wxMenuBar *menuBar;
		wxMenu *menuFile;
		wxMenu *menuEdit;
		wxMenu *menuView;
		wxMenu *menuDevice;
		wxMenu *menuSettings;
		wxMenu *menuHelp;


		wxFileDialog *m_fileopendlg;
		wxTextCtrl *m_textreport;
		wxString sz_report;
		wxAcqConfig *m_confUpdate;
	  private:
		 bool b_fileopen;
		wxRect m_clrect;
		wxPoint m_porig;
		 DECLARE_EVENT_TABLE()
	};

	enum {
		Menu_File_Quit = 100,
		Menu_File_Open,
		Menu_File_Close,
		Menu_File_Print,
		Menu_File_Save,
		Menu_File_SaveAs
	};
	enum {
		Menu_Edit_Undo = 200,
		Menu_Edit_Redo,
		Menu_Edit_Cut,
		Menu_Edit_Copy,
		Menu_Edit_Paste
	};
	enum {
		Menu_View_GraphManager = 300,
		Menu_View_Channel,
		Menu_View_Device,
		Menu_View_RawData,
		Menu_View_Report,
		Menu_View_Config
	};
	enum {
		Menu_Device_New = 400,
		Menu_Device_Options,
		Menu_Device_Serial,
		Menu_Device_Network,
		Menu_Device_USB,
		Menu_Device_Connect,
		Menu_Device_Mapping
	};
	enum {
		Menu_Settings_General = 500,
		Menu_Settings_Report,
		Menu_Settings_Channel,
		Menu_Settings_Graph
	};
	enum {
		Menu_Help_About = 600,
		Menu_Help_Contents,
		Menu_Help_Contact
	};


	extern wxPFdeviceFrame *GetMainFrame();
	extern wxDocMDIParentFrame *GetReportFrame();
	extern wxDialog *GetReportDialog();
#endif							// _WXPFDEVICE_H_
