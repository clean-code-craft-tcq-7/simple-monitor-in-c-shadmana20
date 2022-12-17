
#include <stdio.h>


typedef enum {
    LOW_SOC_BREACH,
    LOW_SOC_WARNING,
    SOC_NORMAL,
    HIGH_SOC_WARNING,
    HIGH_SOC_BREACH,
    SOC_UNDEFINED,
    RANGE_MAX
} WarningRanges;


typedef enum {
    DEFAULT,
    ENGLISH,
    GERMAN,
    CHINA
}LanguageUsed;


typedef enum {
    Approaching_Discharge,
    Approaching_Peak
} WarningWithTolerance;




void MonitorHealthWithTolerance(int tolerance , int MinThreshold, int MaxThrshold , int* DrainRange , int* PeakRange);
void ConvertLanguageIndex (LanguageUsed Language);
WarningRanges BatteryHelathMonitor(int soc);







