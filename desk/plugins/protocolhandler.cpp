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
#include <acq/protocolhandler.h>


	wxProtocolHandler::wxProtocolHandler()
	{
	m_state=0;
	}
	
	wxProtocolHandler::~wxProtocolHandler()
	{


	}

	void wxProtocolHandler::SetNextState(int state)
	{

	}

	int wxProtocolHandler::RegisterCommandHandler(void *FuncCmdHdl)
	{
	return 0;
	}
	int wxProtocolHandler::RegisterDataHandler(void *FuncDHdl)
	{
	return 0;
	}

	int wxProtocolHandler::CommandHandler(__u8 cmdByte)
	{
	return 0;
	}
	int wxProtocolHandler::DataHandler(char *dBuf,int size)
	{
	return 0;
	}
	int wxProtocolHandler::GetPresentState( )
	{
	return m_state;
	}
	void wxProtocolHandler::SetState(int state)
	{
	m_state=state;
	}
	void wxProtocolHandler::CreateChecksum(__u64 cksum_start,int type)
	{
	switch(type)
	{
	case CHECKSUM_ROM:
	default:
		cksum.ckbyte=(__u8)cksum_start;
	}
	m_cksumtype=type;
	}
	void wxProtocolHandler::DecPacketSize()
	{
	m_pktsize--;
	}
	void wxProtocolHandler::SetPacketSize(__u32 pktsize)
	{
	m_pktsize=pktsize;
	}
	void wxProtocolHandler::AdjustPacketSize(void *Algo,void *params)
	{
	
	}
	__u64  wxProtocolHandler::GetPacketSize()
	{
	return m_pktsize;
	}

	void wxProtocolHandler::AddChecksum(__u64 cksum_add,int type)
	{
	switch(type)
	{
	case CHECKSUM_ROM:
	default:
		cksum.ckbyte+=(__u8)cksum_add;
	}
		
	}
	__u64 wxProtocolHandler::Checksum()
	{
	switch(m_cksumtype)
	{
	case CHECKSUM_ROM:
	default:
		return cksum.ckbyte;
	}
	}
