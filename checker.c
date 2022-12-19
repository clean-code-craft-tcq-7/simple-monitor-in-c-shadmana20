#include <stdio.h>
#include <assert.h>
#include "BatteryManagmentSystem.h"

/*Macro to check the minimum and maximum value of given input*/
#define RangeCheck(Input,MinValue,MaxValue) ((Input<=MinValue || Input>=MaxValue)?0:1)

/*Minimum and Maximum Ranges*/
#define TEMPMIN	0
#define TEMPMAX 45
#define SOCMIN 20
#define SOCMAX 80
#define CHARGERATEMAX 0.8

const char* Store_WarningMessage[MESSAGE_MAX];
const char* PreWarningMessageTable[Warning_max] = {"Approaching_discharge","Approaching_charge_peak"};
const char* WarningMessageTable[MAX_LANG][MESSAGE_MAX] = {
		{/*Language : DEFAULT */
			"LOW_SOC_BREACH","LOW_SOC_WARNING","SOC_NORMAL","HIGH_SOC_WARNING","HIGH_SOC_BREACH","SOC_UNDEFINED"},
		{/*Language : ENGLISH */
			"LOW_SOC_BREACH","LOW_SOC_WARNING","SOC_NORMAL","HIGH_SOC_WARNING","HIGH_SOC_BREACH","SOC_UNDEFINED"},
		{/*Language : GERMAN */
			"LOW_SOC_BREACH","LOW_SOC_WARNUNG","SOC_NORMAL","HIGH_SOC_WARNUNG","HIGH_SOC_BREACH","SOC_UNDEFINED"},
		{ /*Language : CHINA */
			"L_S_BREACHEN","L_S_WARN!!","NORMAL","H_S_WARN!!","H_S_BREACHEN","UNDEFINED"}
		
	};


/*Function Delceration for BMS*/
int Check_ChargeRate(float chargeRate);

/*Function Returns True if the Battery is OK else return false*/
int batteryIsOk(float temperature, float soc, float chargeRate)
{
  int batterystate = 1;
  /*Macro returns flase if the Temperature is out of range and true if Temperature is in range*/ 
  batterystate = RangeCheck(temperature,TEMPMIN,TEMPMAX);
  /*Macro returns flase if the SOC is out of range and true if its in range*/
  batterystate *= RangeCheck(soc,SOCMIN,SOCMAX);
  batterystate *= Check_ChargeRate(chargeRate);

  return batterystate;
}
 
/*Function returns flase if the chargeRate is out of range and true if its in range*/ 
int Check_ChargeRate(float chargeRate)
{
   if(chargeRate > CHARGERATEMAX)
   return 0;
   else
   return 1;
}

void SelectLanguageandWarnigMessage(Select_Language Language)
{   
   if(Language < MAX_LANG)
   {
      for(int i =0;i<MESSAGE_MAX;i++)
      {
	Store_WarningMessage[i] = WarningMessageTable[Language][i];
      }
    } 
}

int main()
{
  assert(batteryIsOk(25, 70, 0.7));
  assert(!batteryIsOk(50, 85, 0));
  assert(batteryIsOk(44, 79, 0.7));
  assert(!batteryIsOk(46, 81, 0.8));
  assert(!batteryIsOk(0, 0, 0.7));
  SelectLanguageandWarnigMessage(DEFAULT);
  assert(Store_WarningMessage[(BatteryHelathMonitor(13))] == "LOW_SOC_BREACH");
  SelectLanguageandWarnigMessage(GERMAN);
  assert(Store_WarningMessage[(BatteryHelathMonitor(77))] == "HIGH_SOC_WARNUNG");
  assert(PreWarningMessageTable[PreWarningIndicatorMessage(23,SOCMIN,SOCMAX)] == "Approaching_discharge"); /* 5% of 80 is 4 , [20-24],[76-80] */
  assert(PreWarningMessageTable[PreWarningIndicatorMessage(77,SOCMIN,SOCMAX)] == "Approaching_charge_peak");
  assert(PreWarningMessageTable[PreWarningIndicatorMessage(1,TEMPMIN,TEMPMAX)] == "Approaching_discharge"); /* 5% of 45 is 2 , [0-2],[43-45] */
  assert(PreWarningMessageTable[PreWarningIndicatorMessage(44,TEMPMIN,TEMPMAX)] == "Approaching_charge_peak");

}
