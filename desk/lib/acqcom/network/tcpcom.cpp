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
#include <ctype.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <acq/acqplugin.h>
#include <fcntl.h>
#include <acq/tcpcom.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>




/* Global Declarations */
extern int errno;

wxTcpCom::wxTcpCom (char *ipAddr, bool bDevOpen)
	:wxVirtualCom(ipAddr,bDevOpen)
{
	if(ipAddr != NULL )
	{
		if(strlen(ipAddr)< MAXDEVNAME)
		{	
		strncpy(devName,ipAddr,MAXDEVNAME);
		}
	}
	
	if(bDevOpen)
	OpenDevice(&devName[0]);
	
}


int wxTcpCom::OpenDevice (char *ipAddr,int port)
{
	int fd=-1;
	struct sockaddr_in sin;
	
	#ifndef __WX_MSW__
	fd=open(this->GetName(),O_RDWR|O_NOCTTY|O_NDELAY);
	if(fd == -1)
	{
	return -errno;
	}
	fcntl(fd,F_SETFL,0);
	#endif
    	this->SetHandle(fd);	
 	return 0;
}
int wxTcpCom::CloseDevice ( )
{
	int ret=-1;

	#ifndef __WX_MSW__
	//fcntl(fd,F_SETFL,0);
	ret=close(this->GetHandle());
	if(ret == -1)
	{
	return -errno;
	}
	#endif
 	return 0;
}

int wxTcpCom::ReadDevice(char *dataBuf,int endMark,int cmd)
{
	int n=0;
	int offset=0;
	while(	n  < endMark )
	{
	offset=read(this->GetHandle(),&dataBuf[n],(endMark-offset));
	if(offset < 0 && n == 0)
	return -errno;
	n += offset;
	if(offset < 0 && n != endMark)
	return n;
	}
	return n;
}
int wxTcpCom::WriteDevice(char *dataBuf,int endMark,bool bFile)
{
	int n=0;
	int offset=0;
	while(	n  < endMark )
	{
	offset=write(this->GetHandle(),&dataBuf[n],(endMark-offset));
	if(offset < 0 && n == 0)
	return -errno;
	n += offset;
	if(offset < 0 && n != endMark)
	return n;
	}
	return n;
}
int wxTcpCom::ConfigureDevice()
	{
	
	}
int wxTcpCom::Rselect(int fd, struct timeval *timeout)
{
	fd_set readfds;
	FD_ZERO(&readfds);
	FD_SET(fd, &readfds);
	return select(fd + 1, &readfds, NULL, NULL, timeout);
}

int wxTcpCom::Wselect(int fd, struct timeval *timeout)
{
	fd_set writefds;
	FD_ZERO(&writefds);
	FD_SET(fd, &writefds);
	return select(fd + 1, NULL, &writefds, NULL, timeout);
}


	__u16 wxTcpCom::GetPort()
	{
	return tcpPort;
	}
	unsigned long wxTcpCom::GetIP()
	{
	return (unsigned long)inet_addr(devName);
	}
	void wxTcpCom::SetPort(__u16 port)
	{
	tcpPort=port;
	}
	void wxTcpCom::SetIP(unsigned long ipAddr)
	{

	}
	void wxTcpCom::SetIP(char *ipAddr)
	{

	}
