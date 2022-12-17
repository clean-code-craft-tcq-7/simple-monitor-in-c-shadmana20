
#include "BatteryHealthMonitoring.h"

#define RangeChecker(X,Y,Z) ( X>=Y && X <=Z) ? 1 : 0


//char* WarningMessageToDisplay[RANGE_MAX];


void MonitorHealthWithTolerance(int tolerance ,int MinThreshold , int MaxThreshold , int *DrainRange , int *PeakRange)
{
    
    int Value = (int)((tolerance*MaxThreshold)/100);
    
    *DrainRange = MinThreshold + Value;
    *PeakRange  = MaxThreshold - Value;
    
}

WarningRanges BatteryHelathMonitor(int soc)
{  
    switch(soc)
    {
    case 0 ... 20:        
    //if(soc>=0 && soc<=20)
    return LOW_SOC_BREACH;
    break;
    //else if(soc>=21 && soc<=24)
    case 21 ...24:
    return LOW_SOC_WARNING;
    break;
    case 25 ... 75:        
   // else if(soc>=25 && soc<=75)
    return SOC_NORMAL; 
    break;
    //else if(soc>=76 && soc<=80)
    case 76 ... 80:        
    return HIGH_SOC_WARNING;
    break;
    //else if(soc>=81 && soc<=100)
    case 81 ... 100:
    return HIGH_SOC_BREACH;
    break;
    //else
    default:
    return SOC_UNDEFINED;
    break;
            
    }
}

