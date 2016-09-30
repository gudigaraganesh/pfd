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
#include <stdio.h>
#include <errno.h>
#include <acq/acqplugin.h>
#include <ssproto.h>




/* Global Declarations */

__u8 *p_smpdata; /*points to global samples buffer */
__u8  m_smpdata[MAXBUFSIZE]; /* global sample buffer */



/*plugin initialization struct for the Sunshine's protocol */
plugin_info_t acq_plugin_obj[] = {
  PLUGIN_PROTO, /*type */
  "SunShine",   /*name */
  "1.0",        /*version*/
  NULL,
  ssSerial_init /* init function*/
};



/*
this function initiazes the Data for protocol plugin
*/
int
ssSerial_init (void *ss_plugin, void *p_plugin_data)
{
  if (ss_plugin == NULL)
    return EINVAL;
 acq_protoplugin_t  *ss_plugin_ptr=(acq_protoplugin_t *)ss_plugin;
   ss_plugin_ptr->command=ssSerial_command;
   ss_plugin_ptr->processdata=ssSerial_processdata;
   ss_plugin_ptr->get_packet=ssSerial_Packet;

/*Major  Data Initialisation */
   p_smpdata=&m_smpdata[0];
   return 0;	
}

int
ssSerial_command (void *handler, __u8 cmdByte)
{
  wxProtocolHandler *proto = (wxProtocolHandler *) handler;
  return CompareByte (proto, cmdByte);
}

int
CompareByte (wxProtocolHandler * phandle, __u8 cmdByte)
{
  switch (phandle->GetPresentState ())
    {
    case SS_CMD_STATE1:
      if (cmdByte == SS_PROTO_STPKT1)
	phandle->SetState (SS_CMD_STATE2);
      else
	phandle->SetState (SS_CMD_STATE1);
      return ACQ_CMD_MODE;
    case SS_CMD_STATE2:
      if (cmdByte == SS_PROTO_STPKT2)
	phandle->SetState (SS_CMD_STATE3);
      else
	phandle->SetState (SS_CMD_STATE1);
      return ACQ_CMD_MODE;
    case SS_CMD_STATE3:
      phandle->CreateChecksum (cmdByte,CHECKSUM_ROM);
      phandle->SetPacketSize (cmdByte - 1);
      phandle->SetState (SS_CMD_STATE4);
      return ACQ_CMD_MODE;
    case SS_CMD_STATE4:
      if (cmdByte == SS_CMD_SHIFTMODE)
	phandle->SetState (SS_CMD_STATE5);
      else
	phandle->SetState (SS_CMD_STATE6);
	phandle->DecPacketSize();
    return ACQ_DATA_MODE;
default:
      return ACQ_CMD_ERR;
    }

}

int ssSerial_processdata(void *phandle,char *buf,int size)
{
wxProtocolHandler *proto=(wxProtocolHandler *)phandle;
if(proto->GetPresentState()== SS_CMD_STATE5)
return ssSerial_processSample(proto,(__u8 *)buf,size);
else
if(proto->GetPresentState()== SS_CMD_STATE6)
return ssSerial_processAverage(proto,(__u8 *)buf,size);
}

int ssSerial_processSample(wxProtocolHandler *proto,__u8 *buf,int size)
{
if( buf[0] == SS_CMD_ENDPKT)
{
if(proto->GetPacketSize() == 0 && proto->Checksum() == 0)
{

p_smpdata=&m_smpdata[0];
return ACQ_CMD_MODE;
}
}
proto->AddChecksum(buf[0],CHECKSUM_ROM);
int i_fwd=p_smpdata-&m_smpdata[0];
if( (i_fwd+size ) > MAXBUFSIZE   )
{
p_smpdata=&m_smpdata[0];
return ACQ_CMD_MODE;
}
memcpy(p_smpdata,buf,size);
p_smpdata+=size;
return ACQ_DATA_MODE;
}
int 
ssSerial_Packet(acq_data *packet)
{


}
