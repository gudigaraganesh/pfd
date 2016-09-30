#include "serialcon.h"
struct Portconf databstr[]={{"8",CS8},
			{"7",CS7},
			{"6",CS6},	
			{"5",CS5}
			};	
struct Portconf stopbstr[]={{"1",1},
			{"2",2},	
			{"0",0},	
			};	
struct Portconf parbstr[]={{"NONE",NONE},
			{"EVEN",EVEN},	
			{"ODD",ODD}	
			};	
struct Portconf flowbstr[]={{"NONE",NONE},
			{"SOFTWARE",SOFTWARE},	
			{"HARDWARE",HARDWARE}	
			};	

struct Portconf baudbstr[]={{"9600",B9600},
			{"19200",B19200},	
			{"38400",B38400},	
			{"115200",B115200}	
			};	
char *Com[PORTMAX]={
		      "/dev/ttyS0",	
		      "/dev/ttyS1",	
		      "/dev/ttyS2",	
		      "/dev/ttyS3",	
		      "/dev/ttyS4",	
		      "/dev/ttyS5",	
		      "/dev/ttyS6",	
		      "/dev/ttyS7",	
		      "/dev/ttyS8",	
		      "/dev/ttyS9",	
		      "/dev/ttyS10",	
		      "/dev/ttyS11",	
		      "/dev/ttyS12",	
		      "/dev/ttyS13",	
		      "/dev/ttyS14"	
		        };	
CSerialCon::CSerialCon(char *name)
{
if(name!=NULL)
    setdefaults(name,B9600,8,1,NONE,NONE);
else
setdefaults(Com[0],B9600,8,1,NONE,NONE);
sbuf=NULL;
}

CSerialCon::~CSerialCon()
{
if(sbuf!=NULL)
delete sbuf;
}

int CSerialCon::OpenSerial(void)
{
if(shandle!=-1)
{
CloseSerial();	
}
shandle = open(port, O_RDWR |O_NOCTTY | O_NDELAY);
DP("%s %d",port,shandle);
	if (shandle  == -1)
	{
       	return -1;	
	}
	fcntl(shandle,F_SETFL,0);
	tcgetattr(shandle,&options);
    	cfsetispeed(&options,BaudRate);
	DP("portafter cfseti=%s\n",port);
    	cfsetospeed(&options,BaudRate);
	DP("portafter cfseto=%s\n",port);
    	options.c_cflag |= (CLOCAL | CREAD);
	if(FlowControl == NONE)
	{
	DP("NONE");
options.c_cflag &= ~CRTSCTS;
options.c_iflag &= ~(IXON | IXOFF | IXANY);
	}
	else	if(FlowControl == SOFTWARE)
		{
		DP("SOFTWARE");
		options.c_cflag &= ~CRTSCTS;
		options.c_iflag |= (IXON | IXOFF | IXANY);
		}
		else	if(FlowControl == HARDWARE)
			{
			DP("HARDWARE");
			options.c_iflag &= ~(IXON | IXOFF | IXANY);
			options.c_cflag |= CRTSCTS;
			}


	//data bits
		options.c_cflag &= ~CSIZE;
		options.c_cflag |= DataBit;

	//1 stop bits
	 		if(StopBit == 1)
			options.c_cflag &= ~CSTOPB;
			else   //2 stopbits
			options.c_cflag |=CSTOPB;	

	//No parity (8N1):
			if(ParityBit == NONE)
			{
			options.c_cflag &= ~PARENB;
			}   			
			else if(ParityBit == EVEN)
			{	//even
			DP("EVEN");
			options.c_cflag |= PARENB ;
			options.c_cflag &= ~PARODD ;
			}
   			else 	if(ParityBit == ODD)
				{	//odd
				DP("ODD");
				options.c_cflag |= PARENB;
				options.c_cflag |= PARODD;
				}
				else 	if(ParityBit == SPACE)
					{        		//space
					DP("SPACE");
					options.c_cflag &= ~PARENB;
					}
					else 	if(ParityBit == MARK)
						{
						DP("MARK");
						}

 tcsetattr(shandle , TCSANOW, &options);
		DP("End of Open%d%s",sprint.shandle,sprint.port);
		return 0;
}

void CSerialCon::CloseSerial(void)
{

		if(shandle!=-1)
		{
		if(sbuf!=NULL)
		delete sbuf;
		sbuf=NULL;	
		::close(shandle); 
		shandle =-1;
		}

}



int CSerialCon::SendDataToSerial(char *buf,int Len)
{
	int ret = 0;
	if(shandle==-1)
	return -1;
	ret = write(shandle,buf,Len);
	//DP("Returned%d\n",ret);
    	//returning number of bytes that is written
	return ret;
}

int CSerialCon::CheckSerial()
{
int status=1;
if(shandle==-1)
return 0;

 ioctl(shandle, TIOCMGET, &status);


           //The port status should be one of the following
	    if ( ((status & TIOCM_CTS) != TIOCM_CTS) &&
	   ((status & TIOCM_DSR) != TIOCM_DSR)  &&
	   ((status & TIOCM_RNG) != TIOCM_RNG) &&
	  ((status & TIOCM_CAR) != TIOCM_CAR) )
	   return 0;
	   return 1;
}

int CSerialCon::SerialData(char *serial_buf)
{
int i=0,lens=strlen(serial_buf),klen=0,len=0;	
OpenSerial();
	if (CheckSerial())
	{
	DP("Tell%d\n",lens);	
	while( len < lens )
	{
	klen=SendDataToSerial(serial_buf+len,lens-len);
	if(klen>=0)
	{
	if(klen!=0)			
	DP("Here%d\n",klen);	
	len+=klen;
	klen=0;
	}
	else
	{
	klen=-4;
	break;
	}
	}
	}
CloseSerial();
return klen;
}

int CSerialCon::SerialPage(char *name)
{
FILE *fp;
int klen=0,len=0;
fp=fopen(name,"rb");
sbuf=new char[length+1];
OpenSerial();
while(!feof(fp))
{
fread(sbuf,1,length,fp);
		if (CheckSerial())
		{
	DP("Tell%d\n",length);	
	while( len < length)
	{
	klen=SendDataToSerial(sbuf+len,length-len);
		if(klen>=0)
		{
		if(klen!=0)			
		DP("Here%d\n",klen);	
		len+=klen;
		klen=0;
		}
		else
			{
		klen=-4;
		break;
			}
	}
		}
		else
			{
			klen=-1;
			}		
			if(klen<0) break;
}
fclose(fp);
CloseSerial();
}

void CSerialCon::ParseSerialArgs(char **args)
{
	int i=0;
	length=MAXBUFSIZE;
	DP(args[0]);
setdefaults(Com[0],B9600,8,1,NONE,NONE);
	if(args[0]==NULL)
	{
setdefaults(Com[0],B9600,8,1,NONE,NONE);
	}
	else
	{
	setvalues(args);
	}
	DP("Entered the Data\n");
}

void CSerialCon::setdefaults(char *ports,uint32 baud,uint8 datab,uint8 stopb,uint8 parityb,uint8 flwctl)  
{
strcpy(port,ports);
BaudRate=baud;
DataBit=datab;
StopBit=stopb;
ParityBit=parityb;
FlowControl=flwctl;
}


void CSerialCon::setvalues(char **args)
{
	bool bcom=false;
	int j=0;
	int i=1,ilen=MAXBUFSIZE;
	char *forwd;
	DP("called the");
	char *backwd;		
	while(args[i]!=NULL)
	{
		backwd=strchr(args[i],'=');
		DP("back data\n");
		DP("%s\n%d\n",args[i],i);
		DP(backwd);
		forwd=((strlen(backwd)<=1)?NULL:backwd+1);	
		DP("Serialing %s",forwd);
		*backwd=0;
		DP("\nBACK %s\n",backwd);
	if(!strcasecmp(args[i],"Port"))
	{
			for(j=0;j<PORTMAX;j++)
			{
				if(!strcasecmp(forwd,Com[j]))
				{
				strcpy(port,Com[j]);
				bcom=true;
				break;
				}
			}
				if(bcom==false)
				{
				strcpy(port,Com[0]);
				}
	}
	if(!strcasecmp(args[i],"Baud"))
	{
			if(!strcasecmp(forwd,"9600"))
			BaudRate=B9600;
			else
			if(!strcasecmp(forwd,"115200"))
			BaudRate=B115200;
			else
			if(!strcasecmp(forwd,"19200"))
			BaudRate=B19200;
			else
			if(!strcasecmp(forwd,"38400"))
			BaudRate=B38400;
	}
			if(!strcasecmp(args[i],"Data"))
			{
				if(!strcasecmp(forwd,"7"))
				DataBit=CS7;
				else	
				if(!strcasecmp(forwd,"8"))
				DataBit=CS8;
				else
				if(!strcasecmp(forwd,"5"))
				DataBit=CS5;
				else
				if(!strcasecmp(forwd,"6"))
				DataBit=CS6;
			}
			if(!strcasecmp(args[i],"Stop"))
			{
				if(!strcasecmp(forwd,"1"))
				StopBit=1;
				else	
				if(!strcasecmp(forwd,"2"))
				StopBit=2;
			}
			if(!strcasecmp(args[i],"FlowControl"))
			{
				if(!strcasecmp(forwd,"NONE"))
				FlowControl=NONE;
				else
				if(!strcasecmp(forwd,"SOFTWARE"))
				FlowControl=SOFTWARE;
				else
				if(!strcasecmp(forwd,"HARDWARE"))
				FlowControl=HARDWARE;
			}
			if(!strcasecmp(args[i],"Parity"))
			{
				if(!strcasecmp(forwd,"NONE"))
				ParityBit=NONE;
				else
				if(!strcasecmp(forwd,"ODD"))
				ParityBit=ODD;
				else
				if(!strcasecmp(forwd,"EVEN"))
				ParityBit=EVEN;
			}
			if(!strcasecmp(args[i],"Size"))
			{
			ilen=atoi(forwd);
			if(ilen<MAXBUFSIZE)
			ilen=MAXBUFSIZE;
			length=ilen;
			}
		i++;
	DP("[End of the book%d]\n",i);
} //end	of while
DP("Exited");
}

#ifdef DEBUG
void EchoSym(void)
{
//system("clear");
printf("****************************************");
printf("****************************************");
printf("\nPORT        = %s\n",sprint.port);
printf("Handle      = %d\n",sprint.shandle);
printf("BAUD          = %d\n",sprint.BaudRate);
printf("DATA          = %d\n",sprint.DataBit);
printf("STOP          = %d\n",sprint.StopBit);
printf("Parity        = %d\n",sprint.ParityBit);
printf("FlowControl   = %d\n",sprint.FlowControl);
printf("Size   	      = %d\n",sprint.length);
printf("****************************************");
printf("****************************************\n");
}
#else
void EchoSym( )
{

}
#endif

char *CSerialCon::getPort()
{
return port;
}



int CSerialCon::recvData(char *serial_buf,int buflen)
{
int i=0,klen=0,len=0;	
      memset(serial_buf,0,buflen);	
	if (CheckSerial())
	{
		while( len < buflen)
		{
		klen=::read(shandle,serial_buf+len,buflen-len);
		if(klen>0)
		{
		len+=klen;
		klen=0;
		}
		else
		{
		break;
		}
		}
	}
	return len;
	}
