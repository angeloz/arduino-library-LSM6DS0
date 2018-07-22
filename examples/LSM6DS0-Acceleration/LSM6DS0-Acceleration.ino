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
  SerialUSB.print(acc.acc_getAxesX());
  SerialUSB.print(" - Y:");
  SerialUSB.print(acc.acc_getAxesY());
  SerialUSB.print(" - Z:");
  SerialUSB.println(acc.acc_getAxesZ());
  delay(100);
}
