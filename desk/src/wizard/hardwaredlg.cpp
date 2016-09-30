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
#include <hardwaredlg.h>
BEGIN_EVENT_TABLE(wxDevOpts, wxWizardPageSimple)
    EVT_WIZARD_PAGE_CHANGING(-1, wxDevOpts::OnWizardPageChanging)
        EVT_WIZARD_CANCEL(-1, wxDevOpts::OnWizardCancel)
END_EVENT_TABLE()

	





wxHardwareDlg::wxHardwareDlg(wxWindow *parent,wxWindowID id,const wxString & title,wxBitmap & bitmap,const wxPoint & pos,long style)
 : wxWizard(parent,id,title,bitmap,pos)
{
printf("DD");
//SetBackgroundColour(wxColour(80,100,120));
}


wxHardwareDlg::~wxHardwareDlg()
{
SetBackgroundColour(wxColour(80,100,120));
}



int wxHardwareDlg::Launch(wxAcqConfig *cConfig,wxWindow *parent)
{
	return 1;
}

    wxDevOpts::wxDevOpts(wxWizard *parent) : wxWizardPageSimple(parent)
    {
        wxString choices[4];
        choices[0] = _T("Serial");
        choices[1] = _T("Network");
        choices[2] = _T("USB");
        choices[3] = _T("Bluetooth");

        m_radio = new wxRadioBox(this, -1, _T("Which Device You Want To Add?"),
                                 wxDefaultPosition, wxDefaultSize,
                                 WXSIZEOF(choices), choices,
                                 1, wxRA_SPECIFY_COLS);
        m_radio->SetSelection(false);
	m_label=new wxStaticText((wxWindow *)this,-1,wxString("Type The new Device Profile name"),wxDefaultPosition,wxDefaultSize);
	m_text=new wxTextCtrl((wxWindow *)this,-1,wxString(""),wxDefaultPosition,wxDefaultSize,0);
    m_checkbox = new wxCheckBox((wxWindow *)this,-1,_T("&Make This As Default Device"));
        wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
        mainSizer->Add(
            m_radio,
            0, // No stretching
            wxALL,
            5 // Border
        );
        mainSizer->Add(
            m_label,
            0, // No stretching
            wxALL,
            5 // Border
	);
        mainSizer->Add(
            m_text,
            0, // No stretching
            wxALL,
            5 // Border
        );
        mainSizer->Add(
            m_checkbox,
            0, // No stretching
            wxALL,
            5 // Border
        );
        SetSizer(mainSizer);
        mainSizer->Fit(this);
    }

    // wizard event handlers
    void wxDevOpts::OnWizardCancel(wxWizardEvent& event)
    {
        if ( wxMessageBox(_T("Do you really want to cancel?"), _T("Question"),
                          wxICON_QUESTION | wxYES_NO, this) != wxYES )
        {
            // not confirmed
            event.Veto();
        }
    }

    void wxDevOpts::OnWizardPageChanging(wxWizardEvent& event)
    {
        int sel = m_radio->GetSelection();
	printf("value selected%d length%d\n",sel,m_text->GetLineLength(0));
        if ( event.GetDirection() )
	{
	if(m_text->GetLineLength(0))
	{
	switch(sel)
	{
	case 0:
		this->SetNext(serpage);
		break;
	case 1:
		//this->SetNext(serpage);
		break;
	case 2:
		//this->SetNext(serpage);
		break;
	case 3:
		//this->SetNext(serpage);
		break;
	
	}	
        return;
	}	
       }
        wxMessageBox(_T("Please Type The Profile name"), _T("No Profile"),
                     wxICON_WARNING | wxOK, this);

        event.Veto();
   }

void wxDevOpts::AddSerialPage(wxSerialWizard *spage)
{
serpage=spage;
}
void wxDevOpts::AddUSBPage(wxUSBWizard *spage)
{
upage=spage;
}
void wxDevOpts::AddNetworkPage(wxNetWizard *spage)
{
npage=spage;
}
void wxDevOpts::AddBluetoothPage(wxBluetoothWizard *spage)
{
bpage=spage;
}
     //wxWizardPage *wxDevOpts::GetPrev() const 
	//{ 
	//return m_prev; 
	//}
     wxWizardPage *wxDevOpts::GetNext() const
    {
	switch(m_radio->GetSelection())
	{
	case 0:
		serpage->SetPrev((wxWizardPage *)this);
		return serpage;
		break;
	case 1:
		npage->SetPrev((wxWizardPage *)this);
		return npage;
		break;
	case 2:
		upage->SetPrev((wxWizardPage *)this);
		return upage;
		break;
	case 3:
		bpage->SetPrev((wxWizardPage *)this);
		return bpage;
		break;
	}
	}
