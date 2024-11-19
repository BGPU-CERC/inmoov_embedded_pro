#pragma once
#include "ServoDriverSmooth.h"

struct servo
{
  uint8_t deviceAddress;
  int pin;
  int minAngle;
  int maxAngle;
  int minPwm;
  int maxPwm;
  ServoDriverSmooth handle;
};

void setupServo();

void tickServo();

void stopTickServo();

void setServoPower(bool mode);

void setServoTarget(int deviceAdress, int pin, int angle, int speed);

void attachServo(int deviceAdress, int pin, int angle, int speed);

void detachServo(int deviceAdress, int pin);
