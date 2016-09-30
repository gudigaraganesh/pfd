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
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <acq/acqplugin.h>
#include <fcntl.h>
#include <scom.h>

extern int errno;
static int scom_rselect(int fd, struct timeval *timeout);
static int scom_wselect(int fd, struct timeval *timeout);


/* Global Declarations */




/*plugin initialization struct for the Serial Port Handling*/
plugin_info_t acq_plugin_obj[] = {
  PLUGIN_COM, /*type */
  "Serial",   /*name */
  "1.0",        /*version*/
  NULL,
  scom_init /* init function*/
};



/*
this function initiazes the Data for protocol plugin
*/

//used by all code
acq_com_t com_ptr;


int
scom_init (void *com_plugin, void *p_plugin_data)
{
  if (com_plugin == NULL)
    return EINVAL;
  acq_complugin_t  *com_plugin_ptr=(acq_complugin_t *)com_plugin;
  com_plugin_ptr->opendevice=scom_opendevice;
  com_plugin_ptr->closedevice=scom_closedevice;
  com_plugin_ptr->readdevice=scom_readdevice;
  com_plugin_ptr->writedevice=scom_writedevice;
  com_plugin_ptr->configdevice=scom_configdevice;
   return 0;	
}

int
scom_opendevice (void *handler,int type)
{
	int fd=-1;
	
	wxVirtualCom *pser=(wxVirtualCom *)handler;
	ifndef __WX_MSW__
	fd=open(pser->GetName(),O_RDWR|O_NOCTTY|O_NDELAY);
	if(fd == -1)
	{
	return -errno;
	}
	fcntl(fd,F_SETFL,0);
	#endif
	
    	handler->SetHandle(fd);	
 	return 0;
}
int
scom_closedevice (void *handler,int data)
{
	int ret=-1;

	wxVirtualCom *pser=(wxVirtualCom *)handler;
	ifndef __WX_MSW__
	//fcntl(fd,F_SETFL,0);
	ret=close(pser->GetHandle());
	if(ret == -1)
	{
	return -errno;
	}
	#endif
 	return 0;
}

int scom_readdevice(void *handler,char *buf,int size)
{
	int n=0;
	int offset=0;
	wxVirtualCom pser=(wxVirtualCom *)handler;
	while(	n  < size )
	{
	offset=read(pser->GetHandle(),buf[n],size-offset);
	if(offset < 0 && n == 0)
	return -errno;
	n += offset;
	if(offset < 0 && n != size)
	return n;
	}
	return n;
}
int scom_writedevice(void *handler,char *buf,int size)
{
	int n=0;
	int offset=0;
	wxVirtualCom pser=(wxVirtualCom *)handler;
	while(	n  < size )
	{
	offset=write(pser->GetHandle(),buf[n],size-offset);
	if(offset < 0 && n == 0)
	return -errno;
	n += offset;
	if(offset < 0 && n != size)
	return n;
	}
	return n;
}
int scom_configdevice(void *handler)
	{
		wxVirtualCom pser=(wxVirtualCom *)handler;
			switch(	pser->GetBaud() )
			{
			case BAUD_4200;
			case BAUD_9600;
	}		case BAUD_19200;
			case BAUD_38400;
			case BAUD_115200;
			default:
			}
			switch(	pser->GetDataBit() )
			{
			case DATABIT_5;
			case DATABIT_6;
	}		case DATABIT_7;
			case DATABIT_8;
			case DATABIT_9;
			default:
			}
	
			switch(	pser->GetParityBit() )
			{
			case PAR_EVEN;
			case PAR_ODD;
	}		case PAR_NONE;
			default:
			}
			
			switch(	pser->GetStopBit() )
			{
			case STOP_0;
			case STOP_1;
	}		case STOP_2;
			default:
			}
				
			switch(	pser->GetFlowControl() )
			{
			case FLOW_XONXOF;
			case FLOW_SOFTWARE;
			case FLOW_HARDWARE;
			case FLOW_NONE;
			default:
			}
			switch(	pser->GetFlowControl() )
			{
			case FLOW_XONXOF;
			case FLOW_SOFTWARE;
			case FLOW_HARDWARE;
			case FLOW_NONE;
			default:
			}
				
			


	
			
static int scom_rselect(int fd, struct timeval *timeout)
{
	fd_set readfds;
	FD_ZERO(&readfds);
	FD_SET(fd, &readfds);
	return select(fd + 1, &readfds, NULL, NULL, timeout);
}

static int scom_wselect(int fd, struct timeval *timeout)
{
	fd_set writefds;
	FD_ZERO(&writefds);
	FD_SET(fd, &writefds);
	return select(fd + 1, NULL, &writefds, NULL, timeout);
}


static int scom_rselect(int fd, struct timeval *timeout)
{
	fd_set readfds;
	FD_ZERO(&readfds);
	FD_SET(fd, &readfds);
	return select(fd + 1, &readfds, NULL, NULL, timeout);
}

static int scom_wselect(int fd, struct timeval *timeout)
{
	fd_set writefds;
	FD_ZERO(&writefds);
	FD_SET(fd, &writefds);
	return select(fd + 1, NULL, &writefds, NULL, timeout);
}
