#include <stdio.h>
#include <assert.h>
#include "BatteryHealthMonitoring.h"

const char* WarningMessageEN[RANGE_MAX] = {"LOW_SOC_BREACH","LOW_SOC_WARNING","SOC_NORMAL","HIGH_SOC_WARNING","HIGH_SOC_BREACH","SOC_UNDEFINED"};
const char* WarningMessageDE[RANGE_MAX] = {"LOW_SOC_BREACH","LOW_SOC_WARNUNG","SOC_NORMAL","HIGH_SOC_WARNUNG","HIGH_SOC_BREACH","SOC_UNDEFINED"};
const char* WarningMessageCN[RANGE_MAX] = {"L_S_BREACHEN","L_S_WARN!!","NORMAL","H_S_WARN!!","H_S_BREACHEN","UNDEFINED"};

#define RangeCheck(X,Y,Z) (X<=Y || X>=Z)?0:1
#define MinRangeTemperature 0
#define MaxRangeTemperature 45
#define MinRangeSOC 20
#define MaxRangeSOC 80
#define ChargeRateThreshold 0.8

int Check_ChargeRate(float chargeRate);

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

}


