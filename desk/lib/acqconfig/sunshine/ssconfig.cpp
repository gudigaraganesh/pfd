#include "acqconfig.h"
#ifdef OLDTEST 
struct channels_profile defchannels[DEFAULTANACHAN+DEFAULTDIGCHAN];
void InitChannels()
{
int counter=0;
defchannels[counter].channelname.Printf("AIR-TEMPERATURE");
defchannels[counter+1].channelname.Printf("WT");
defchannels[counter+2].channelname.Printf("SOIL-TEMPERATURE");
defchannels[counter+3].channelname.Printf("WIND-DIRECTION");
defchannels[counter+4].channelname.Printf("EVAPORATION");
defchannels[counter+5].channelname.Printf("DPT");
defchannels[counter+6].channelname.Printf("SOLAR-RADIATION");
defchannels[counter+7].channelname.Printf("DSR");
defchannels[counter+8].channelname.Printf("PSR");
defchannels[counter+9].channelname.Printf("SM");
defchannels[counter+10].channelname.Printf("PRESSURE");
defchannels[counter+11].channelname.Printf("VOLTAGE");
defchannels[counter+12].channelname.Printf("SRI");
defchannels[counter+13].channelname.Printf("SRO");
defchannels[counter+14].channelname.Printf("SRN");
defchannels[counter+15].channelname.Printf("TSP");
defchannels[counter+16].channelname.Printf("TRS");
defchannels[counter+17].channelname.Printf("WCU");
defchannels[counter+18].channelname.Printf("WCV");
defchannels[counter+19].channelname.Printf("INV");
defchannels[counter+20].channelname.Printf("INV");
defchannels[counter+21].channelname.Printf("INV");
defchannels[counter+22].channelname.Printf("WIND-SPEED");
defchannels[counter+23].channelname.Printf("RAIN-FALL");
defchannels[counter+24].channelname.Printf("RELATIVE-HUMIDITY");

defchannels[counter].channelunit.Printf("Deg.C");
defchannels[counter+1].channelunit.Printf("Deg.C");
defchannels[counter+2].channelunit.Printf("Deg.C");
defchannels[counter+3].channelunit.Printf("Deg");
defchannels[counter+4].channelunit.Printf("mm");
defchannels[counter+5].channelunit.Printf("Deg.C");
defchannels[counter+6].channelunit.Printf("mW/SqCm");
defchannels[counter+7].channelunit.Printf("mV");
defchannels[counter+8].channelunit.Printf("mW/SqCm");
defchannels[counter+9].channelunit.Printf("mW/SqCm");
defchannels[counter+10].channelunit.Printf("mW/SqCm");
defchannels[counter+11].channelunit.Printf("mV");
defchannels[counter+12].channelunit.Printf("ppm");
defchannels[counter+13].channelunit.Printf("ppm");
defchannels[counter+14].channelunit.Printf("ppm");
defchannels[counter+15].channelunit.Printf("ppm");
defchannels[counter+16].channelunit.Printf("COH");
defchannels[counter+17].channelunit.Printf("ppb");
defchannels[counter+18].channelunit.Printf("m/s");
defchannels[counter+19].channelunit.Printf("m/s");
defchannels[counter+20].channelunit.Printf("mm");
defchannels[counter+21].channelunit.Printf("%");
defchannels[counter+22].channelunit.Printf("m/s");
for(int ind=0;ind<DEFAULTANACHAN+DEFAULTDIGCHAN;ind++)
{
if(ind >=DEFAULTDIGCHAN)
defchannels[ind].channeltype=1;   //0 indicates analog
else
defchannels[ind].channeltype=0;   //0 indicates analog
defchannels[ind].bAvg=false;   
defchannels[ind].bHex=false;
defchannels[ind].samplemin=defchannels[ind].calibmin=0;
defchannels[ind].samplemax=defchannels[ind].calibmax=2048;
}

}
#endif
