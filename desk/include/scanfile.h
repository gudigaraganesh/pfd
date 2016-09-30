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
#ifndef _WXSCANFILE_H_
#define _WXSCANFILE_H_
#include <wx/wx.h>
#include <acq/acqplugin.h>
#ifndef __WX_MSW__
#include <linux/types.h>
#include <acq/version.h>
#endif
#ifdef __WX_MSW__
#define MAXPATHS 1
#define PLUGPATH1	"./"
#else
#define MAXPATHS 4
#define PLUGPATH1 "~/."
#define PLUGPATH2 "/usr/lib/"
#define PLUGPATH3 "../share/"
#define PLUGPATH4 DATADIRS
#endif
#define PLUGINPATH "plugins"
typedef struct scan_t {
	char plugin[100];
	bool paths[MAXPATHS];
} SCANPLUG;

class wxScanFile {
  public:
	wxScanFile();
	~wxScanFile();
	int SearchFile(char *filename);
	int AddToCache(char *filename, wxList * list);
	int SearchPlugin(char *pluginfile);
	wxList *GetPluginList();
	wxList *GetDumpFileList();
	wxList *GetReportFileList();
	wxList *GetGraphFileList();
	int GetFromCache(char *filename);
  private:
	 wxList * pluginfiles;
	wxList *dumpfiles;
	wxList *reportfiles;
	wxList *graphfiles;
};

#endif
