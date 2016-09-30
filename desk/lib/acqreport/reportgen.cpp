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
#include <acq/reportgen.h>

wxReportGen::wxReportGen (char *reportFile,bool bDevOpen)
{



}
 		 int wxReportGen::GetStatus ()
		{
		return statuscode;
		}
  	 bool wxReportGen::IsOpen () 	
	{ 
	return bOpen;
	}
 int wxReportGen::GetMaxReports( ) 	
	{ 
	return maxReports;
	}
	
	wxString wxReportGen::GetName()
	{
	return reportName;
	}
	int wxReportGen::GetMode()
	{
	return m_fileMode;
	}



   void wxReportGen::SetHeader(wxString headerStr)
	{
	dataHeader=headerStr;
	}	
   void wxReportGen::SetFooter(wxString footerStr)
	{
	dataFooter=footerStr;
	}
	
   void wxReportGen::SetStartDate(wxString dateStr)
	{
	startDate=dateStr;
	}	
   void wxReportGen::SetStartTime(wxString timeStr)
	{
	startTime=timeStr;
	}	
  void wxReportGen::EnableStartDate(bool val)
	{
	useStartDate=val;
	}
  void wxReportGen::EnableStartTime(bool val)
	{
	useStartTime=val;
	}



