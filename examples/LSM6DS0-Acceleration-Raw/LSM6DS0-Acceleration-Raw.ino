#include <LSM6DS0.h>
#include <Wire.h>

LSM6DS0 acc;

void setup() {
  SerialUSB.begin();
  Wire.begin();
  while (!SerialUSB);
  acc.init();
}

void loop() {
  SerialUSB.print("X:");
  SerialUSB.print(acc.acc_getAxesXRaw());
  SerialUSB.print(" - Y:");
  SerialUSB.print(acc.acc_getAxesYRaw());
  SerialUSB.print(" - Z:");
  SerialUSB.println(acc.acc_getAxesZRaw());
  delay(100);
}
