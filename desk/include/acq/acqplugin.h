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
#ifndef _ACQPLUGIN_H_
#define _ACQPLUGIN_H_
#include <wx/wx.h>
#include <acq/protocolhandler.h>
#include <acq/virtualcom.h>
#include <sys/types.h>
#if !defined(__WXMSW__)
#include <linux/types.h>
#else	/*  */
#include <acq/acqtypes.h>
#endif	/*  */
 
#define PLUGIN_NONE	      1
#define PLUGIN_PROTO	      2
#define PLUGIN_COM	      4
#define PLUGIN_DISPLAY        16
#define PLUGIN_FONT           32
#define PLUGIN_ALGO           64
#define PLUGIN_DSP            128
#define PLUGIN_MUST_PRELOAD   0x40
#define PLUGIN_NO_UNLOAD      0x20
#define PLUGIN_TYPE_MASK      0x0f
#define ACQ_CMD_MODE  8
#define ACQ_DATA_MODE  16
#define ACQ_CMD_ERR    2
#define ACQ_DATA_ERR   4
/*This is the plugin architecture used for communicating with the pFDevice */
/*Required Data structs and typedefs */
	class wxProtocolHandler;
class wxVirtualCom;

typedef void acq_data;

typedef struct acq_display {
	int type;
	wxWindow *parent;
} acq_display_t;

typedef enum {
	LINEAR_DATAFORMAT = 0x100,
	GRID_DATAFORMAT,
	GRAPH_DATAFORMAT,
} Dataformat_t;

typedef struct acq_displayplugin {
	int (*draw) (unsigned short *, int x, int y, wxWindow *);
	int (*setcolour) (int r, int g, int b, int x, int y, int fgbg);
	int (*setfont) (void *, __u8);
	int (*getcursor) (int *x, int *y);
	int (*setcursor) (int x, int y);
	int (*readConfigFile) (char *);
	int (*WriteConfigFile) (char *);
} acq_displayplugin_t;
typedef struct {
	__u8 type;			//plugin type 
	char *plugin_name;	//plugin name
	char *version;		//version of plugin
	void *plugin_data;	//plugin specific data
	int (*init) (void *plugin_func, void *plugin_data);
} plugin_info_t;

typedef struct acq_proto {
	char date[11];		//holds the date information
	char time[10];		//holds time of the day
	bool bsetdate;		// whether to read from the device
	bool bsettime;		//whether to read from protocol
	int dataformat;		// Format of data display on screen
	int databytes;		// No of bytes per data
	int rows;			//no of display rows    
	int columns;		// no of display columns
	char units[20];		// no of display units
	bool isunitreq;		// unit required
	unsigned char *pktbuf;	// data buffer
} acq_proto_t;

typedef struct acq_protoplugin {
	int (*command) (void *, __u8);
	int (*processdata) (void *, char *, int);
	int (*get_packet) (acq_data *);
	int (*display) (acq_display *);
	int (*readConfigFile) (char *);
	int (*WriteConfigFile) (char *);
} acq_protoplugin_t;

typedef struct acq_com {
	int fd;
	int type;
	unsigned long speed;
	unsigned int databits;
	unsigned int startbits;
	unsigned int stopbits;
	unsigned int portnum;
	unsigned char comaddr[128];
} acq_com_t;

typedef struct acq_complugin {
	int (*opendevice) (char *, int);
	int (*closedevice) ();
	int (*readdevice) (void *, __u8);
	int (*writedevice) (void *, __u8);
	int (*readConfigFile) (char *);
	int (*WriteConfigFile) (char *);
	int (*configdevice) (acq_com_t *);
} acq_complugin_t;



#endif
