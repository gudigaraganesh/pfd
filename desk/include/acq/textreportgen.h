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
#ifndef WXTEXTREPORTGEN_H
#define WXTEXTREPORTGEN_H

#include <stdio.h>
#include <wx/wx.h>
#include <acq/reportgen.h>

#define MAXREPORTS 150



class wxTextReportGen:public wxReportGen {
  public:
	wxTextReportGen(char *reportFile = NULL, bool bOpen = false);
	 virtual ~ wxTextReportGen() {
	};
	virtual int OpenReport(char *reportFile, int mode = 0);
	virtual int CloseReport();
	virtual int ReadReport(void *readBuf, int endMark, int cmd = 0);
	virtual int WriteReport(void *writeBuf, int endMark, int cmd = 0);
	virtual int SetReportParams(void *params);
};

#endif
