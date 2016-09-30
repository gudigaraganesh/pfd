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
#ifndef WXTCPCOM_H
#define WXTCPCOM_H
#include <stdio.h>
#include <sys/select.h>
#include <linux/types.h>
#include <acq/virtualcom.h>
#define BAUD_4200	4200
#define BAUD_9600	9600
#define BAUD_19200      19200
#define BAUD_38400      38400
#define BAUD_115200     115200
#define DATABIT_5        5
#define DATABIT_6        6
#define DATABIT_7        7
#define DATABIT_8        8
#define DATABIT_9        9
#define PAR_EVEN         2
#define PAR_ODD		 1
#define PAR_NONE         0
#define STOP_0           0
#define STOP_1           1
#define STOP_2           2
#define FLOW_XONXOF      3
#define FLOW_SOFTWARE   2
#define FLOW_HARDWARE    1
#define FLOW_NONE        0



class wxTcpCom:public wxVirtualCom {
  public:
	wxTcpCom(char *virtDev = NULL, bool bOpen = false);
	// wxTcpCom (wxTcpCom & vCom);
	 virtual ~ wxTcpCom() {
	};

	virtual int OpenDevice(char *virtDev, int mode = 0);
	virtual int CloseDevice();
	virtual int ReadDevice(char *readBuf, int endMark, int cmd = 0);
	virtual int WriteDevice(char *writeBuf, int endMark, bool bFile = false);
	virtual int ConfigureDevice();
	__u16 GetPort();
	unsigned long GetIP();
	void SetPort(__u16 port);
	void SetIP(unsigned long ipAddr);
	void SetIP(char *ipAddr);
	int Rselect(int fd, struct timeval *timeout);
	int Wselect(int fd, struct timeval *timeout);

  protected:
	__u16 tcpPort;
	__u64 maxSize;
};

#endif
