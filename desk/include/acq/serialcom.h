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
#ifndef WXSERIALCOM_H
#define WXSERIALCOM_H
#include <stdio.h>
#include <sys/select.h>
#include <linux/types.h>
#include <acq/virtualcom.h>
#ifdef __WXMSW__
#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <io.h>
#include <memory.h>
#endif
#define BAUD_4800	4800
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



class wxSerialCom:public wxVirtualCom {
  public:
	wxSerialCom(char *virtDev = NULL, bool bOpen = false);
	// wxSerialCom (wxSerialCom & vCom);
	 virtual ~ wxSerialCom() {
	};

	virtual int OpenDevice(char *virtDev, int mode = 0);
	virtual int CloseDevice();
	virtual int ReadDevice(char *readBuf, int endMark, int cmd = 0);
	virtual int WriteDevice(char *writeBuf, int endMark, bool bFile = false);
	virtual int ConfigureDevice();
	__u8 GetDataBit();
	__u8 GetStopBit();
	__u8 GetParityBit();
	__u8 GetFlowControl();
	__u64 GetBaudRate();
	void SetDataBit(__u8 dataB);
	void SetParityBit(__u8 parityB);
	void SetStopBit(__u8 stopB);
	void SetFlowControl(__u8 flowC);
	void SetBaudRate(__u64 baudB);
	int Rselect(int fd, struct timeval *timeout);
	int Wselect(int fd, struct timeval *timeout);

#ifdef __WXMSW__
	HANDLE GetDevHandle();
	void SetHandle(HANDLE hnd);
#endif
	int SetSerialDTRRTS(int fd, bool rts, bool dtr);
	int SetSerialSpeed(int fd, int speed);
	int MapSpeed(int speed);
	int SetSerialDataBit(int fd, int databits);
	int MapDataBit(int databits);
	int SetSerialParityBit(int fd, int paritybits);
	int MapParityBit(int paritybits);
	int SetSerialStopBit(int fd, int stopbits);
	int MapStopBit(int stopbits);
	int SetSerialFlowControl(int fd, int flowctl);


  protected:
	__u8 stopBit;
	__u8 dataBit;
	__u8 parityBit;
	__u8 flowControl;
	__u64 baudRate;
	bool bRTS;
	bool bDCD;
	bool bDSR;
	__u64 maxSize;

#ifdef __WXMSW__
	HANDLE h_Dev;
	OVERLAPPED oRead, oWrite;
#endif
};

#endif
