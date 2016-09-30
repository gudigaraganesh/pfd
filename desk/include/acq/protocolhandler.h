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
#ifndef _WXPROTOCOLHANDLER_H_
#define _WXPROTOCOLHANDLER_H_
#include <wx/wx.h>
#include <acq/acqplugin.h>
#if ! defined(__WXMSW__)
#include <linux/types.h>
#else	/*  */
#include <acq/acqtypes.h>
#endif
#define CHECKSUM_ROM 1

typedef union cksum_t {
	__u64 ckldword;
	__u32 ckdword;
	__u16 ckword;
	__u8 ckbyte;
} CKSUM;
class wxProtocolHandler {
  public:
	wxProtocolHandler();
	~wxProtocolHandler();
	void SetNextState(int state);
	int RegisterCommandHandler(void *FuncCmdHdl);
	int RegisterDataHandler(void *FuncDHdl);
	int CommandHandler(__u8 cmdByte);
	int DataHandler(char *dBuf, int size);
	int GetPresentState();
	void SetState(int State);
	void CreateChecksum(__u64 cksum_start, int type);
	void DecPacketSize();
	void SetPacketSize(__u32);
	void AdjustPacketSize(void *Algo, void *params);
	__u64 GetPacketSize();
	void AddChecksum(__u64 cksum, int type);
	__u64 Checksum();
  private:
	int m_state;
	int (*cmdHandler) (__u8 m_cmdByte);
	int (*dataHandler) (wxWindow * parent, char *dBuf, int size);
	CKSUM cksum;
	__u64 m_pktsize;
	int m_cksumtype;
};

#endif
