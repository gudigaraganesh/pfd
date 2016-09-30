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
#include <scanfile.h>
#if defined(__WXMSW__)
	static char *sz_plugpaths[MAXPATHS]=
				{
				PLUGPATH1
				};
	#else 
    #include <dirent.h>
	static char *sz_plugpaths[MAXPATHS]=
				{
				PLUGPATH1,
				PLUGPATH2,
				PLUGPATH3,
				PLUGPATH4
				};
				#endif
		
static char *plugindirs[]=
			{
			"com",
			"input",
			"visual",
			"protocol"
			};

	wxScanFile::wxScanFile()
	{
	pluginfiles=new wxList();
	dumpfiles=new wxList();
	reportfiles=new wxList();
	graphfiles=new wxList();
	}
	
	wxScanFile::~wxScanFile()
	{


	}

	int wxScanFile::SearchFile(char *filename)
	{
	FILE *fcfg;
	
	if(filename==NULL)
	return -1;
	printf("File %s\n",filename);
	if((fcfg=fopen(filename,"r"))==NULL)
	return -1;
	fclose(fcfg);
	return 0;
	}

	int wxScanFile::AddToCache(char *filename,wxList *list)
	{
	return 0;	
	}
	int wxScanFile::SearchPlugin(char *pluginfile)
	{
		wxString  szplug(pluginfile);
		for(int index=0;index<MAXPATHS;index++)
		{
		wxString szpathstr(sz_plugpaths[index]);
		wxString sznewstr=szpathstr+APPNAME+"/"+PLUGINPATH+"/";
		if( SearchFile((char *)sznewstr.GetData())==0 )
		{
			if( GetFromCache((char *)sznewstr.GetData()) != 0 )
			{
			AddToCache((char *)sznewstr.GetData(),pluginfiles);		
			}

		}	
		return 0;
		}
	}
	wxList *wxScanFile::GetPluginList()
	{
	return pluginfiles;
	}
	wxList *wxScanFile::GetDumpFileList()
	{
	return dumpfiles;
	}
	wxList *wxScanFile::GetReportFileList()
	{
	return reportfiles;
	}
	wxList *wxScanFile::GetGraphFileList()
	{
	return graphfiles;
	}

	int wxScanFile::GetFromCache(char *filename)
	{
	return 0;
	}
	
