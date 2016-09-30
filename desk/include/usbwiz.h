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
#ifndef WXUSBWIZ_H
#define WXUSBWIZ_H

#include <wx/wx.h>
#include <acqconfig.h>
#include <wx/wizard.h>
#include <images.h>

class wxAcqConfig;

/**
@author Ganesh Gudigara
*/





class wxUSBWizard:public wxWizardPageSimple {
  public:
	wxUSBWizard(wxWizard * parent);
	void OnWizardCancel(wxWizardEvent & event);
	void OnWizardPageChanging(wxWizardEvent & event);
  private:
	 wxListBox * m_profile;
	wxComboBox *m_device;
	wxComboBox *m_baud;
	wxComboBox *m_databit;
	wxComboBox *m_paritybit;
	wxComboBox *m_stopbit;
	wxComboBox *m_flowcontrol;
	wxCheckBox *m_dsrcheck;
	wxCheckBox *m_dcdcheck;
	 DECLARE_EVENT_TABLE()
};
#endif
