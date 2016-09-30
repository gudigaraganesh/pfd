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
#ifndef WXHARDWAREDLG_H
#define WXHARDWAREDLG_H

#include <wx/wx.h>
#include <acqconfig.h>
#include <wx/wizard.h>
#include <images.h>
#include <serialwiz.h>
#include <usbwiz.h>
#include <EmanEz.h>
#include <bluetoothwiz.h>
class wxAcqConfig;

/**
@author Ganesh Gudigara
*/



class wxHardwareDlg:public wxWizard {
  public:
	wxHardwareDlg(wxWindow * parent, wxWindowID id, const wxString & title,
				  wxBitmap & bitmap = wxNullBitmap, const wxPoint & pos =
				  wxDefaultPosition, long style =
				  wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER);

	~wxHardwareDlg();

	static int wxHardwareDlg::Launch(wxAcqConfig * cConfig,
									 wxWindow * parent);
};


class wxDevOpts:public wxWizardPageSimple {
  public:
	wxDevOpts(wxWizard * parent);
	void OnWizardCancel(wxWizardEvent & event);
	void OnWizardPageChanging(wxWizardEvent & event);
	void AddSerialPage(wxSerialWizard * spage);
	void AddUSBPage(wxUSBWizard * spage);
	void AddNetworkPage(wxNetWizard * spage);
	void AddBluetoothPage(wxBluetoothWizard * spage);
	//virtual wxWizardPage *GetPrev() const;   
	virtual wxWizardPage *GetNext() const;
  private:
	 wxSerialWizard * serpage;
	wxUSBWizard *upage;
	wxNetWizard *npage;
	wxBluetoothWizard *bpage;
	wxRadioBox *m_radio;
	wxStaticText *m_label;
	wxTextCtrl *m_text;
	wxCheckBox *m_checkbox;

	 DECLARE_EVENT_TABLE()
};

//class wxChannelOpts : public wxWizardPage
//{
//public:
//private:
   // wxWizardPage *m_prev,
 //                *m_next;
//
  //  wxCheckBox *m_checkbox;
//};

#endif
