
#include "BatteryHealthMonitoring.h"


extern char* WarningMessageToDisplay[RANGE_MAX];
const  char* WarningMessageEN[RANGE_MAX] = {"LOW_SOC_BREACH","LOW_SOC_WARNING","SOC_NORMAL","HIGH_SOC_WARNING","HIGH_SOC_BREACH","SOC_UNDEFINED"};
const  char* WarningMessageDE[RANGE_MAX] = {"LOW_SOC_BREACH","LOW_SOC_WARNUNG","SOC_NORMAL","HIGH_SOC_WARNUNG","HIGH_SOC_BREACH","SOC_UNDEFINED"};
const  char* WarningMessageCN[RANGE_MAX] = {"L_S_BREACHEN","L_S_WARN!!","NORMAL","H_S_WARN!!","H_S_BREACHEN","UNDEFINED"};

void ConvertLanguageIndex (LanguageUsed Language)
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

