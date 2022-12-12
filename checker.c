#include <stdio.h>
#include <assert.h>
#define AreSOCInRange(X) (X<20 || X>80) ? 0 : 1

#define AreChargeRateInRange(X) (X < 0.8 )? 0 : 1

#define AreTemperatureInRange(X) (X < 0 || X > 45) ? 0 : 1


int batteryIsOk(float temperature, float soc, float chargeRate) {
  if(AreTemperatureInRange(temperature) && AreChargeRateInRange(chargeRate) && AreSOCInRange(soc))
  {
    return 0;
  }
  else{ 
return 1;
  }
}

int main() {
  assert(batteryIsOk(25, 70, 0.7));
  assert(!batteryIsOk(50, 85, 0));
}
