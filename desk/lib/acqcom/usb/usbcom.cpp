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
#include <stdio.h>
#include <acq/acqplugin.h>
#include <fcntl.h>
#include <acq/usbcom.h>
#if !defined(__WXMSW__)
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#endif


/* Global Declarations */
extern int errno;

wxUSBCom::wxUSBCom(char *serDev, bool bDevOpen)
:wxVirtualCom(serDev, bDevOpen)
{
	if (serDev != NULL) {
		if (strlen(serDev) < MAXDEVNAME) {
			strncpy(devName, serDev, MAXDEVNAME);
		}
	}

	if (bDevOpen)
		OpenDevice(&devName[0]);

}


int wxUSBCom::OpenDevice(char *serDev, int mode)
{
	int fd = -1;
	printf("I reached here for trying to read");
#if !defined(__WX_MSW__)
	fd = open(this->GetName(), O_RDWR | O_NOCTTY | O_NDELAY);
	if (fd == -1) {
		return -errno;
	}
	fcntl(fd, F_SETFL, 0);
	this->SetHandle(fd);
#else
	HANDLE tempFD;
	COMMTIMEOUTS CommTimeOuts;

	if ((tempFD = CreateFile(serDev, GENERIC_READ | GENERIC_WRITE, 0,	/* exclusive access */
							 NULL,	/* no security attrs */
							 OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,	/* overlapped I/O */
							 NULL)) == (HANDLE) - 1)
		return -1;
	else {
		/* get any early notifications */
		SetCommMask(tempFD, EV_RXCHAR);
		/* setup device buffers */
		SetupComm(tempFD, 4096, 4096);
		/* purge any information in the buffer */
		PurgeComm(tempFD, PURGE_TXABORT | PURGE_RXABORT |
				  PURGE_TXCLEAR | PURGE_RXCLEAR);
		/* set up for overlapped I/O */
		CommTimeOuts.ReadIntervalTimeout = 0xFFFFFFFF;
		CommTimeOuts.ReadTotalTimeoutMultiplier = 0;
		CommTimeOuts.ReadTotalTimeoutConstant = 1000;
		CommTimeOuts.WriteTotalTimeoutMultiplier = 10;
		CommTimeOuts.WriteTotalTimeoutConstant = 0;
		SetCommTimeouts(tempFD, &CommTimeOuts);
		this->SetHandle(tempFD);
	}
#endif
	return 0;
}

int wxUSBCom::CloseDevice()
{
	int ret = -1;

#if !defined(__WX_MSW__)
	ret = close(this->GetHandle());
	if (ret == -1) {
		return -errno;
	}
#else
	SetCommMask(h_Dev, 0);
	/* drop DTR */
	EscapeCommFunction(h_Dev, CLRDTR);

	/* purge any outstanding reads/writes and close device handle */
	PurgeComm(h_Dev, PURGE_TXABORT | PURGE_RXABORT |
			  PURGE_TXCLEAR | PURGE_RXCLEAR);

	CloseHandle(h_Dev);
#endif
	return 0;
}

int wxUSBCom::ReadDevice(char *serBuf, int endMark, int cmd)
{
#if !defined(__WXMSW__)
	int n = 0;
	int offset = 0;

	while (n < endMark) {
		offset = read(this->GetHandle(), &serBuf[n], (endMark - offset));
		if (offset < 0 && n == 0)
			return -errno;
		n += offset;
		if (offset < 0 && n != endMark)
			return n;
	}
	return n;
#else
	BOOL fReadStat;
	COMSTAT ComStat;
	DWORD dwErrorFlags;
	DWORD dwLength = 0;
	DWORD dwError;

	ClearCommError(h_Dev, &dwErrorFlags, &ComStat);
	dwLength = min((DWORD) endMark, ComStat.cbInQue);

	if (dwLength > 0) {
		fReadStat = ReadFile(h_Dev, serBuf, dwLength, &dwLength, &oRead);
		if (!fReadStat) {
			if (GetLastError() == ERROR_IO_PENDING) {
				fprintf(stderr, "\n\rIO Pending");
				/* We have to wait for read to complete.
				 * This function will timeout according to the
				 * CommTimeOuts.ReadTotalTimeoutConstant variable
				 * Every time it times out, check for port errors
				 */
				while (!GetOverlappedResult(h_Dev, &oRead, &dwLength, TRUE)) {
					dwError = GetLastError();
					if (dwError == ERROR_IO_INCOMPLETE) {
						/* normal result if not finished */
						continue;
					} else {
						/* an error occurred, try to recover */
						ClearCommError(h_Dev, &dwErrorFlags, &ComStat);
						break;
					}
				}
			} else {
				/* some other error occurred */
				dwLength = 0;
				ClearCommError(h_Dev, &dwErrorFlags, &ComStat);
			}
		}
	}
	return dwLength;
#endif
}

int wxUSBCom::WriteDevice(char *serBuf, int endMark, bool bFile)
{
#if !defined(__WXMSW__)
	int n = 0;
	int offset = 0;

	while (n < endMark) {
		offset = write(this->GetHandle(), &serBuf[n], (endMark - offset));
		if (offset < 0 && n == 0)
			return -errno;
		n += offset;
		if (offset < 0 && n != endMark)
			return n;
	}
	return n;
#else
	BOOL fWriteStat;
	DWORD dwBytesWritten;
	DWORD dwErrorFlags;
	DWORD dwError;
	DWORD dwBytesSent = 0;
	COMSTAT ComStat;

	fWriteStat = WriteFile(h_Dev, serBuf, endMark, &dwBytesWritten, &oWrite);
	/* Note that normally the code will not execute the following
	 * because the driver caches write operations. Small I/O requests
	 * (up to several thousand bytes) will normally be accepted
	 * immediately and WriteFile will return true even though an
	 * overlapped operation was specified
	 */

	if (!fWriteStat) {
		if (GetLastError() == ERROR_IO_PENDING) {
			/* We should wait for the completion of the write operation
			 * so we know if it worked or not
			 *
			 * This is only one way to do this. It might be beneficial to
			 * place the write operation in a separate thread
			 * so that blocking on completion will not negatively
			 * affect the responsiveness of the UI
			 *
			 * If the write takes too long to complete, this
			 * function will timeout according to the
			 * CommTimeOuts.WriteTotalTimeoutMultiplier variable.
			 * This code logs the timeout but does not retry
			 * the write.
			 */
			while (!GetOverlappedResult
				   (h_Dev, &oWrite, &dwBytesWritten, TRUE)) {
				dwError = GetLastError();
				if (dwError == ERROR_IO_INCOMPLETE) {
					/* normal result if not finished */
					dwBytesSent += dwBytesWritten;
					continue;
				} else {
					/* an error occurred, try to recover */
					ClearCommError(h_Dev, &dwErrorFlags, &ComStat);
					break;
				}
			}
			dwBytesSent += dwBytesWritten;
		} else {
			/* some other error occurred */
			ClearCommError(hPhone, &dwErrorFlags, &ComStat);
			return 0;
		}
	}
	return endMark;
#endif
}

int wxUSBCom::ConfigureDevice()
{
	unsigned long baudR;

#if	!defined(__WXMSW__)
	struct termios wxcom_termios;

	tcgetattr(this->GetHandle(), &wxcom_termios);
#else
	DCB dcb;

	dcb.DCBlength = sizeof(DCB);
	GetCommState(h_Dev, &dcb);
	dcb.fOutxDsrFlow = 0;
#endif
	SetSerialSpeed(GetHandle(), GetBaudRate());
	SetSerialDataBit(GetHandle(), GetDataBit());
	SetSerialParityBit(GetHandle(), GetParityBit());
	SetSerialStopBit(GetHandle(), GetStopBit());
	SetSerialFlowControl(GetHandle(), GetFlowControl());
}
int wxUSBCom::Rselect(int fd, struct timeval *timeout)
{
#if !defined(__WXMSW__)
	fd_set readfds;

	FD_ZERO(&readfds);
	FD_SET(fd, &readfds);
	return select(fd + 1, &readfds, NULL, NULL, timeout);
#else
	usleep(timeout->tv_sec * 60 + timeout->tv_usec);
	return 1;
#endif
}

int wxUSBCom::Wselect(int fd, struct timeval *timeout)
{
#if !defined(__WXMSW__)
	fd_set writefds;

	FD_ZERO(&writefds);
	FD_SET(fd, &writefds);
	return select(fd + 1, NULL, &writefds, NULL, timeout);
#else
	usleep(timeout->tv_sec * 60 + timeout->tv_usec);
	return 1;
#endif
}


__u8 wxUSBCom::GetDataBit()
{
	return dataBit;
}

__u8 wxUSBCom::GetStopBit()
{
	return stopBit;
}

__u8 wxUSBCom::GetParityBit()
{
	return parityBit;
}

__u8 wxUSBCom::GetFlowControl()
{
	return flowControl;
}

__u64 wxUSBCom::GetBaudRate()
{
	return baudRate;
}

void wxUSBCom::SetDataBit(__u8 dataB)
{
	dataBit = dataB;
}

void wxUSBCom::SetParityBit(__u8 parityB)
{
	parityBit = parityB;
}

void wxUSBCom::SetStopBit(__u8 stopB)
{
	stopBit = stopB;
}

void wxUSBCom::SetFlowControl(__u8 flowC)
{
	flowControl = flowC;
}

void wxUSBCom::SetBaudRate(__u64 baudB)
{
	baudRate = baudB;
}

#ifdef __WXMSW__
HANDLE wxUSBCom::GetDevHandle()
{
	return h_Dev;
}

void wxUSBCom::SetHandle(Handle hnd)
{
	h_Dev = hnd;
}
#endif
int wxUSBCom::SetSerialSpeed(int fd, int speed)
{
#ifdef __WXMSW__
	BOOL fRetVal;
	DCB dcb;

	dcb.DCBlength = sizeof(DCB);
	GetCommState(h_Dev, &dcb);
	dcb.BaudRate = MapSpeed(speed);
	fRetVal = SetCommState(h_Dev, &dcb);
	return fRetVal;
#else
	termios wxcom_termios;

	tcgetattr(fd, &wxcom_termios);
	cfsetispeed(&wxcom_termios, MapSpeed(speed));
	cfsetospeed(&wxcom_termios, MapSpeed(speed));
	tcsetattr(fd, TCSANOW, &wxcom_termios);
#endif
}
int wxUSBCom::SetSerialDataBit(int fd, int databits)
{
#ifdef __WXMSW__
	BOOL fRetVal;
	DCB dcb;

	dcb.DCBlength = sizeof(DCB);
	GetCommState(h_Dev, &dcb);
	dcb.ByteSize = MapDataBit(databits);
	fRetVal = SetCommState(h_Dev, &dcb);
	return fRetVal;
#else
	termios wxcom_termios;

	tcgetattr(fd, &wxcom_termios);
	wxcom_termios.c_cflag &= ~CSIZE;
	wxcom_termios.c_cflag |= MapDataBit(databits);
	tcsetattr(fd, TCSANOW, &wxcom_termios);
#endif
}


int wxUSBCom::SetSerialParityBit(int fd, int paritybits)
{
#ifdef __WXMSW__
	BOOL fRetVal;
	DCB dcb;

	dcb.DCBlength = sizeof(DCB);
	GetCommState(h_Dev, &dcb);
	dcb.Parity = MapParityBit(paritybits);
	fRetVal = SetCommState(h_Dev, &dcb);
	return fRetVal;
#else
	termios wxcom_termios;
	int parity = MapParityBit(paritybits);

	tcgetattr(fd, &wxcom_termios);
	if (parity == PAR_NONE)
		wxcom_termios.c_cflag &= ~PARENB;
	else if (parity == PAR_EVEN) {	//even
		wxcom_termios.c_cflag |= PARENB;
		wxcom_termios.c_cflag &= ~PARODD;
	} else if (parity == PAR_ODD) {	//odd
		wxcom_termios.c_cflag |= PARENB;
		wxcom_termios.c_cflag |= PARODD;
	}
	tcsetattr(fd, TCSANOW, &wxcom_termios);
#endif
}

int wxUSBCom::SetSerialStopBit(int fd, int stopbits)
{
#ifdef __WXMSW__
	BOOL fRetVal;
	DCB dcb;

	dcb.DCBlength = sizeof(DCB);
	GetCommState(h_Dev, &dcb);
	dcb.StopBits = MapStopBit(stopbits);
	fRetVal = SetCommState(h_Dev, &dcb);
	return fRetVal;
#else
	termios wxcom_termios;
	int stopbs = MapStopBit(stopbits);

	tcgetattr(fd, &wxcom_termios);
	if (stopbs == STOP_1)
		wxcom_termios.c_cflag &= ~CSTOPB;
	else if (stopbs == STOP_2) {	//2
		wxcom_termios.c_cflag |= CSTOPB;
	}
	tcsetattr(fd, TCSANOW, &wxcom_termios);
#endif
}

int wxUSBCom::SetSerialFlowControl(int fd, int flowctl)
{
#ifdef __WXMSW__
	BOOL fRetVal;
	DCB dcb;

	dcb.DCBlength = sizeof(DCB);
	GetCommState(h_Dev, &dcb);
	dcb.fOutxDsrFlow = 0;
	if (flowctl == FLOW_HARDWARE) {
		dcb.fOutxCtsFlow = TRUE;
		dcb.fRtsControl = RTS_CONTROL_HANDSHAKE;
	} else if (flowctl == FLOW_SOFTWARE) {
		dcb.fOutxCtsFlow = FALSE;
		dcb.fRtsControl = RTS_CONTROL_ENABLE;
		fInX = fOutX = 1;
	} else if (flowctl == FLOW_XONXOFF) {
		dcb.fOutxCtsFlow = FALSE;
		dcb.fRtsControl = RTS_CONTROL_DISABLE;
		fInX = fOutX = 1;
	} else {
		dcb.fOutxCtsFlow = FALSE;
		dcb.fRtsControl = RTS_CONTROL_DISABLE;
		fInX = fOutX = 0;
	}
	fRetVal = SetCommState(h_Dev, &dcb);
	return fRetVal;
#else
	termios wxcom_termios;

	tcgetattr(fd, &wxcom_termios);
	if (flowctl == FLOW_HARDWARE) {
		wxcom_termios.c_iflag &= ~(IXON | IXOFF | IXANY);
		wxcom_termios.c_cflag |= CRTSCTS;
	} else if (flowctl == FLOW_SOFTWARE) {
		wxcom_termios.c_cflag &= ~CRTSCTS;
		wxcom_termios.c_iflag |= (IXON | IXOFF | IXANY);
	} else if (flowctl == FLOW_XONXOF) {
		wxcom_termios.c_cflag &= ~CRTSCTS;
		wxcom_termios.c_iflag |= (IXON | IXOFF | IXANY);
	} else {
		wxcom_termios.c_cflag &= ~CRTSCTS;
		wxcom_termios.c_iflag &= ~(IXON | IXOFF | IXANY);
	}
	tcsetattr(fd, TCSANOW, &wxcom_termios);
#endif
}

int wxUSBCom::SetSerialDTRRTS(int fd, bool rts, bool dtr)
{
#ifdef __WXMSW__
	BOOL fRetVal;
	DCB dcb;

	dcb.DCBlength = sizeof(DCB);
	GetCommState(h_Dev, &dcb);
	dcb.fOutxDsrFlow = 0;
	if (dtr)
		dcb.fDtrControl = DTR_CONTROL_ENABLE;
	else
		dcb.fDtrControl = DTR_CONTROL_DISABLE;

	dcb.fOutxCtsFlow = 0;
	if (rts)
		dcb.fRtsControl = RTS_CONTROL_ENABLE;
	else
		dcb.fRtsControl = RTS_CONTROL_DISABLE;

	dcb.fOutxDsrFlow = 0;
	fInX = fOutX = 0;
	fRetVal = SetCommState(h_Dev, &dcb);
	return fRetVal;
#else
	unsigned int flags;

	flags = TIOCM_DTR;
	if (dtr)
		ioctl(fd, TIOCMBIS, &flags);
	else
		ioctl(fd, TIOCMBIC, &flags);

	flags = TIOCM_RTS;
	if (rts)
		ioctl(fd, TIOCMBIS, &flags);
#endif
}


int wxUSBCom::MapSpeed(int speed)
{
#if !defined(__WXMSW__)
	switch (speed) {
	case BAUD_4800:
		return B4800;
		break;
	case BAUD_9600:
		return B4800;
		break;
	case BAUD_19200:
		return B19200;
		break;
	case BAUD_38400:
		return B38400;
		break;
	case BAUD_115200:
		return B115200;
		break;
	default:
		return B9600;
		break;
	}
#else
	return speed;
#endif
}
int wxUSBCom::MapDataBit(int databits)
{
#if !defined(__WXMSW__)
	switch (databits) {
	case DATABIT_5:
		return CS5;
	case DATABIT_6:
		return CS6;
	case DATABIT_7:
		return CS7;
	case DATABIT_8:
		return CS8;
	default:
		return CS8;
		break;
	}
#else
	return databits;
#endif
}

int wxUSBCom::MapParityBit(int paritybits)
{
#ifdef __WXMSW__
	switch (paritybits) {
	case PAR_EVEN:
		return EVENPARITY;
	case PAR_ODD:
		return ODDPARITY;
	case PAR_NONE:
		return NOPARITY;
	default:
		return MOPARITY;
		break;
	}
#else
	return paritybits;
#endif
}
int wxUSBCom::MapStopBit(int stopbits)
{
#ifdef __WXMSW__
	switch (stopbits) {
	case STOP_1:
		return ONESTOPBIT;
	case STOP_2:
		return TWOSTOPBITS;
	default:
		return ONESTOPBIT;
		break;
	}
#else
	return stopbits;
#endif
}
