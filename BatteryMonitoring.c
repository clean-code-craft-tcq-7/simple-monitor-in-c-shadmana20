
#include "BatteryHealthMonitoring.h"

#define TOLERENCEVALUE 5
#define RangeChecker(X,Y,Z) (X<=Y && X>=Z)?1:0
#define BreachMinThd 21
#define BreachMaxThd 81
#define WarningMinThd 24
#define WarningMaxThd 76
#define WarnBreachBoundary 20

struct 
{
	int DrainRange;
	int PeakRange;
}descharge_range;

/*Function Decleration*/
static WarningRanges ReturnSocBreach(int soc);
static WarningRanges ReturnSocWarning(int soc);
static int SocRangeCheck(int soc, int MinRange, int MaxRange);
static void CalculateDrianPeakThreshold(int MinThreshold , int MaxThreshold);

static int SocRangeCheck(int soc, int MinRange, int MaxRange)
{
	if(soc <= MinRange)
	{
		return 1;
	}
	else if(soc>=MaxRange)
	{
		return 0;
	}
	
}

static void CalculateDrianPeakThreshold(int MinThreshold , int MaxThreshold)
{
    int Value = (int)((TOLERENCEVALUE*MaxThreshold)/100);
    
     descharge_range.DrainRange = MinThreshold + Value;
     descharge_range.PeakRange  = MaxThreshold - Value;
}

WarningWithTolerance PreWarningIndicatorMessage(int input, int MinThreshold , int MaxThreshold )
{   

    CalculateDrianPeakThreshold(MinThreshold , MaxThreshold);
	
    if(input <= descharge_range.DrainRange)	    
    {
        return Approaching_Discharge;
    }
 
    if( input>= descharge_range.PeakRange)
    {
        return Approaching_Peak;
    }
}

WarningRanges BatteryHelathMonitor(int soc)
{  
    if(RangeChecker(soc, BreachMaxThd, BreachMinThd) == 1)
	{
		return ReturnSocWarning(soc);
	}
	else
	{
		return ReturnSocBreach(soc);
	}
}


static WarningRanges ReturnSocBreach(int soc)
{
	 
	if(SocRangeCheck(soc, WarnBreachBoundary, BreachMaxThd) == 1)
	{
		return LOW_SOC_BREACH;
	}
	else
	{
		return HIGH_SOC_BREACH;
	}
	
}

static WarningRanges ReturnSocWarning(int soc)
{
	
	WarningRanges Returnstaus = SOC_NORMAL;
	
	if(SocRangeCheck(soc, WarningMinThd, WarningMaxThd) == 1)
	{
		Returnstaus = LOW_SOC_WARNING;
	}
	else
	{
		Returnstaus = HIGH_SOC_WARNING;
	}
	
	return Returnstaus;
	
}
