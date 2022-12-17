#include <stdio.h>
#include <assert.h>
#include "BatteryHealthMonitoring.h"




#define RangeCheck(X,Y,Z) (X<=Y || X>=Z)?0:1
#define MinRangeTemperature 0
#define MaxRangeTemperature 45
#define MinRangeSOC 20
#define MaxRangeSOC 80
#define ChargeRateThreshold 0.8

int Check_ChargeRate(float chargeRate);
extern char* WarningMessageToDisplay[RANGE_MAX];

int batteryIsOk(float temperature, float soc, float chargeRate)
{
  int batterystate = 1;
  batterystate =  RangeCheck(temperature,MinRangeTemperature , MaxRangeTemperature);
  batterystate *= RangeCheck(soc,MinRangeSOC,MaxRangeSOC);
  batterystate *= Check_ChargeRate(chargeRate);
  return batterystate;
}

int Check_ChargeRate(float chargeRate)
{
   if(chargeRate>ChargeRateThreshold)
   return 0;
   else
   return 1;
}


int main()
{
 
  assert(batteryIsOk(25, 70, 0.7));
  assert(!batteryIsOk(50, 85, 0));
  assert(!batteryIsOk(46, 81, 0.8));
  assert(batteryIsOk(44, 79, 0.7));
  assert(!batteryIsOk(0, 0, 0.7));
  ConvertLanguageIndex(DEFAULT);
  assert(WarningMessageToDisplay[(BatteryHelathMonitor(13))] == "LOW_SOC_WARNING");
  ConvertLanguageIndex(GERMAN);
  assert(WarningMessageToDisplay[(BatteryHelathMonitor(77))] == "HIGH_SOC_WARNUNG");

}



