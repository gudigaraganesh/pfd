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
#ifndef WXCOMDEFS_H
#define WXCOMDEFS_H
#define COMERRNO(i)  (-500-(i))
#define COMERRSTR(i)  	CERRSTR#i
#define CERRSTR1     "Device Name Too Big"
#define CERRSTR2     "Device Not Opened"
#define CERRSTR3     "Device Busy"
#define CERRSTR4     "Device Disconnected"
#define CERRSTR4     "Device Not Found"
#define CERRSTR5     "Invalid Settings-not supported"
#define CERRSTR6     "Device Firmware Incorrect"
#define CERRSTR7     "This Feature not supported"
#define CERRSTR8     "No Signal"
#define CERRSTR9     "Not responding"
#define CERRSTR10    "Corrupted Input"
#define CERRSTR11    "Checksum Error"
#define CERRSTR12    "Channel not available"
#define CERRSTR13    "Speed Mismatch"
#define CERRSTR14    "Out of Sync"						#define CERRSTR15    "cannot close"
#define COMOK(i)     (1000+(i))
#define COMOKSTR(i)  COKSTR#i
#define COKSTR1	     "Opened Device"
#define COKSTR2	     "Connected Successfully"
#endif
