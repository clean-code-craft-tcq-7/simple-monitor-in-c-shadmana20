#include <stdio.h>
#include <assert.h>

#define AreTemperatureInRange(X) (X < 0 || X > 45) ? 0 : 1

//#define AreSOCInRange(X) (X<20 || X>80) ? 0 : 1

//#define AreChargeRateInRange(X) (X > 0.8 )? 0 : 1

#define AreChargeRateAndSOCInRange(X,Y) (((X<20 || X>80) && (Y > 0.8 )) ? 0 : 1)

int batteryIsOk(float temperature, float soc, float chargeRate) {
  if(AreTemperatureInRange(temperature) && AreChargeRateAndSOCInRange(soc,chargeRate))
  {
    return 0;
  }
 return 1;
  
}

int main() {
  assert(batteryIsOk(25, 70, 0.7));
  assert(!batteryIsOk(50, 85, 0));
}
