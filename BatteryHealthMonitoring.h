#include <stdio.h>


typedef enum {
    LOW_SOC_BREACH,
    LOW_SOC_WARNING,
    SOC_NORMAL,
    HIGH_SOC_WARNING,
    HIGH_SOC_BREACH,
    SOC_UNDEFINED,
    MESSAGE_MAX
} WarningRanges;


typedef enum {
    DEFAULT,
    ENGLISH,
    GERMAN,
    CHINA,
	MAX_LANG
}Select_Language;


typedef enum {
    Approaching_Discharge,
    Approaching_Peak,
    Warning_max
} WarningWithTolerance;

void SelectLanguageandWarnigMessage(Select_Language Language);
WarningRanges BatteryHelathMonitor(int soc);
