#include "servo.h"
#include "../config/config.h"

constexpr uint8_t SERVO_TICK_INTERVAL_MS = 20;

uint32_t throttle = 0;
boolean ticking = false,
        powerState = true;

void setupServo()
{
  setServoPower(powerState);

  for (int i = 0; i < SERVO_AMOUNT; i++)
  {
    servos[i].handle.setAutoDetach(false);
    servos[i].handle.setAccel(0);
  }
}

void tickServo()
{
  // тик каждые 20 мс (как в библиотеке)
  if (millis() - throttle >= SERVO_TICK_INTERVAL_MS)
  {
    throttle += SERVO_TICK_INTERVAL_MS;

    if (!ticking)
    {
      return;
    }

    // двигаем все сервы. Такой вариант эффективнее отдельных тиков
    for (int i = 0; i < SERVO_AMOUNT; i++)
    {
      servos[i].handle.tickManual();
    }
  }
}

void stopTickServo()
{
  ticking = false;
}

void setServoPower(bool mode)
{
  for (int i = 0; i < MODULE_AMOUNT; i++)
  {
    digitalWrite(moduleEnablePins[i], mode);
  }
}

void setServoTarget(int deviceAdress, int pin, int angle, int speed)
{
  servo *s = getServo(deviceAdress, pin);

  if (s != nullptr)
  {
    s->handle.setTargetDeg(angle);
    s->handle.setSpeed(speed);
    ticking = true;
  }
}

void attachServo(int deviceAdress, int pin, int angle, int speed)
{
  servo *s = getServo(deviceAdress, pin);

  if (s != nullptr)
  {
    s->handle.attach(pin, s->minAngle, s->maxAngle, s->minPwm, s->maxPwm, angle);
    setServoTarget(deviceAdress, pin, angle, speed);
  }
}

void detachServo(int deviceAdress, int pin)
{
  servo *s = getServo(deviceAdress, pin);

  if (s != nullptr)
  {
    s->handle.detach();
  }
}
