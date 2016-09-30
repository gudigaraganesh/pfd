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
#include <serialwiz.h>
BEGIN_EVENT_TABLE(wxSerialWizard, wxWizardPageSimple)
    EVT_WIZARD_PAGE_CHANGING(-1, wxSerialWizard::OnWizardPageChanging)
        EVT_WIZARD_CANCEL(-1, wxSerialWizard::OnWizardCancel)
END_EVENT_TABLE()

	







 wxSerialWizard::wxSerialWizard(wxWizard *parent) : wxWizardPageSimple(parent)
    {
	wxString choices[2];
	choices[0]=_T("Serial000");
	choices[1]=_T("Serial001");
	//int noofdevs=wxAcqConfig::GetSerialDevices();
	//for(int index=0;index<noofdevs;index)
	//choices[index]=GetSerDeviceProfile(1);
        m_profile = new wxListBox(this, -1, 
                                 wxDefaultPosition, wxDefaultSize,
                                 WXSIZEOF(choices), choices,
                                 0);
        
        wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
        mainSizer->Add(
            m_profile,
            0, // No stretching
            wxALL,
            5 // Border
        );
        SetSizer(mainSizer);
        mainSizer->Fit(this);
    }

    // wizard event handlers
    void wxSerialWizard::OnWizardCancel(wxWizardEvent& event)
    {
        if ( wxMessageBox(_T("Do you really want to cancel?"), _T("Question"),
                          wxICON_QUESTION | wxYES_NO, this) != wxYES )
        {
            // not confirmed
            event.Veto();
        }
    }

    void wxSerialWizard::OnWizardPageChanging(wxWizardEvent& event)
    {
	int sel;
        if ( !event.GetDirection())
            return;

        wxMessageBox(_T("You can't go there"), _T("Not allowed"),
                     wxICON_WARNING | wxOK, this);

        event.Veto();
   }
