#include "BateryMonitoring.h"

void CopyLanguageIndex(LanguageUsed Language)
{
    for(int i =0;i<RANGE_MAX;i++)
        {
            if( Language <GERMAN){
            WarningMessageToDisplay[i] = WarningMessageEN[i];
            }
            else if (Language == GERMAN)
            {
            WarningMessageToDisplay[i] = WarningMessageDE[i];   
            }
            else
            WarningMessageToDisplay[i] = WarningMessageCN[i];
        }
    
    
}


void MonitorHealthWithTolerance(int tolerance ,int MinThreshold , int MaxThreshold , int *DrainRange , int *PeakRange)
{
    
    int Value = (int)((tolerance*MaxThreshold)/100);
    
    *DrainRange = MinThreshold + Value;
    *PeakRange  = MaxThreshold - Value;
    
}

WarningRanges BatteryHelathMonitor(int soc)
{  
    
    if(soc>=0 && soc<=20)
    return LOW_SOC_BREACH;
    else if(soc>=21 && soc<=24)
    return LOW_SOC_WARNING;
    else if(soc>=25 && soc<=75)
    return SOC_NORMAL; 
    else if(soc>=76 && soc<=80)
    return HIGH_SOC_WARNING;
    else if(soc>=81 && soc<=100)
    return HIGH_SOC_BREACH;
    else
    return SOC_UNDEFINED;
}
