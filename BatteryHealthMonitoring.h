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

const char* WarningMessageToDisplay[RANGE_MAX] = {};
const char* WarningMessageEN[RANGE_MAX] = {"LOW_SOC_BREACH","LOW_SOC_WARNING","SOC_NORMAL","HIGH_SOC_WARNING","HIGH_SOC_BREACH","SOC_UNDEFINED"};
const char* WarningMessageDE[RANGE_MAX] = {"LOW_SOC_BREACH","LOW_SOC_WARNUNG","SOC_NORMAL","HIGH_SOC_WARNUNG","HIGH_SOC_BREACH","SOC_UNDEFINED"};
const char* WarningMessageCN[RANGE_MAX] = {"L_S_BREACHEN","L_S_WARN!!","NORMAL","H_S_WARN!!","H_S_BREACHEN","UNDEFINED"};


void MonitorHealthWithTolerance(int tolerance , int MinThreshold, int MaxThrshold , int* DrainRange , int* PeakRange);
void ConvertLanguageIndex (LanguageUsed Language);
WarningRanges BatteryHelathMonitor(int soc);







