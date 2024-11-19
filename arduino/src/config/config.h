#pragma once
#include "../servo/servo.h"

#define HEAD_ADDRESS 0x40
#define LEFT_HAND_ADDRESS 0x41
#define RIGHT_HAND_ADDRESS 0x42
#define STOM_ADDRESS 0x43

#define SERVO_AMOUNT 29
#define MODULE_AMOUNT 4

#define HEAD_EN_PIN 2
#define LHAND_EN_PIN 27
#define RHAND_EN_PIN 4
#define STOM_EN_PIN 26

extern servo servos[];
extern int moduleEnablePins[];

int getServoIndex(int device_adress, int pin);
servo *getServo(int device_address, int pin);
