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
#ifndef _SSPROTO_H_
#define _SSPROTO_H_
#include <wx/wx.h>
#include <sys/types.h>
#include <acq/acqplugin.h>
//SunShine measurements Specific protocol Implementation
//All commands related to SunShine propietery protocol for online dumping
//of data from the serial port
#define SS_CMD_STPKT1      0xA5
#define SS_CMD_STPKT2   0xA4
#define SS_CMD_SHIFTMODE  0x31
#define SS_CMD_ENDPKT     0xff


//states
#define SS_CMD_STATE1 0x00
#define SS_CMD_STATE2 0x01
#define SS_CMD_STATE3 0x02
#define SS_CMD_STATE4 0x03
#define SS_CMD_STATE5 0x04
#define SS_CMD_STATE6 0x04


//definitions of protocol
#define SS_PROTO_STPKT1  165   /*Start the new packet1 */
#define SS_PROTO_STPKT2  164   /*Start the new packet2 */

//size
#define MAXBUFSIZE 200
int ssSerial_init (void *ss_plugin, void *p_plugin_data);
int ssSerial_command (void *handler, __u8 cmdByte);
int ssSerial_processdata(void *phandle,char *buf,int size);
int ssSerial_Packet(acq_data *packet);
int CompareByte (wxProtocolHandler * phandle, __u8 cmdByte);
int ssSerial_processSample(wxProtocolHandler *proto,__u8 *buf,int size);
int ssSerial_processSample(wxProtocolHandler *proto,__u8 *buf,int size);
int ssSerial_processAverage(wxProtocolHandler *proto,__u8 *buf,int size);
#endif
