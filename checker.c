#include <stdio.h>
#include <assert.h>
#include "BatteryHealthMonitoring.h"




#define RangeCheck(X,Y,Z) (X<=Y || X>=Z)?0:1
#define Tolerance 5
#define MinRangeTemperature 0
#define MaxRangeTemperature 45
#define MinRangeSOC 20
#define MaxRangeSOC 80
#define ChargeRateThreshold 0.8

char* WarningMessageToDisplay[RANGE_MAX];
const  char* WarningMessageEN[RANGE_MAX] = {"LOW_SOC_BREACH","LOW_SOC_WARNING","SOC_NORMAL","HIGH_SOC_WARNING","HIGH_SOC_BREACH","SOC_UNDEFINED"};
const  char* WarningMessageDE[RANGE_MAX] = {"LOW_SOC_BREACH","LOW_SOC_WARNUNG","SOC_NORMAL","HIGH_SOC_WARNUNG","HIGH_SOC_BREACH","SOC_UNDEFINED"};
const  char* WarningMessageCN[RANGE_MAX] = {"L_S_BREACHEN","L_S_WARN!!","NORMAL","H_S_WARN!!","H_S_BREACHEN","UNDEFINED"};
const  char* WarningMessageWithTolerance[Warning_max] = {"Approaching_discharge"," Approaching_charge_peak"};

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
            else{
            WarningMessageToDisplay[i] = WarningMessageCN[i];
            }
        
         
        }
    
    
}

WarningWithTolerance CreateWarning(int input , int tolerance ,int MinThreshold , int MaxThreshold , int *DrainRange , int *PeakRange)
{    int a =0,b=0;
     MonitorHealthWithTolerance(Tolerance ,MinThreshold , MaxThreshold , &a ,&b);
    if(input>= MinThreshold && input <=a)
    {
        return Approaching_Discharge;
    }
 
    if( input>= b && input <=MaxThreshold)
    {
        return Approaching_Peak;
    }
}

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
    int* a,b,c,d,e,f,g,h;
    
 
  assert(batteryIsOk(25, 70, 0.7));
  assert(!batteryIsOk(50, 85, 0));
  assert(!batteryIsOk(46, 81, 0.8));
  assert(batteryIsOk(44, 79, 0.7));
  assert(!batteryIsOk(0, 0, 0.7));
  ConvertLanguageIndex(DEFAULT);
  assert(WarningMessageToDisplay[(BatteryHelathMonitor(13))] == "LOW_SOC_BREACH");
  ConvertLanguageIndex(GERMAN);
  assert(WarningMessageToDisplay[(BatteryHelathMonitor(77))] == "HIGH_SOC_WARNUNG");
  //assert(WarningMessageWithTolerance[CreateWarning(23,Tolerance,MinRangeSOC,MaxRangeSOC,a,b)] == "Approaching_discharge"); 
    printf("%s --> " , WarningMessageWithTolerance[CreateWarning(23,Tolerance,MinRangeSOC,MaxRangeSOC,a,b)]);
  //assert(WarningMessageWithTolerance[CreateWarning(77,Tolerance,MinRangeSOC,MaxRangeSOC,c,d)] == "Approaching_charge_peak");
    printf("%s --> " , WarningMessageWithTolerance[CreateWarning(77,Tolerance,MinRangeSOC,MaxRangeSOC,c,d)]);
  //assert(WarningMessageWithTolerance[CreateWarning(1,Tolerance,MinRangeTemperature,MaxRangeTemperature,e,f)] == "Approaching_discharge");  /* 5% of 45 is 2 , [0-2],[43-45] */
     printf("%s --> " , WarningMessageWithTolerance[CreateWarning(1,Tolerance,MinRangeTemperature,MaxRangeTemperature,c,d)]);
  //assert(WarningMessageWithTolerance[CreateWarning(44,Tolerance,MinRangeTemperature,MaxRangeTemperature,g,h)] == "Approaching_charge_peak");

}



