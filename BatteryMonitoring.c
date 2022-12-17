
#include "BatteryHealthMonitoring.h"

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
    return LOW_SOC_BREACH;
    break;
    case 21 ...24:
    return LOW_SOC_WARNING;
    break;
    case 25 ... 75:        
    return SOC_NORMAL; 
    break;
    case 76 ... 80:        
    return HIGH_SOC_WARNING;
    break;
    case 81 ... 100:
    return HIGH_SOC_BREACH;
    break;
    default:
    return SOC_UNDEFINED;
    break;
            
    }
}

