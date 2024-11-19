#include "command.h"
#include "../servo/servo.h"
#include <Arduino.h>
#include <HardwareSerial.h>
#include "../config/config.h"

constexpr uint8_t ROLLNECK_PIN_VALUE = 77;
constexpr uint8_t LEFT_ROLLNECK_PIN = 2;
constexpr uint8_t RIGHT_ROLLNECK_PIN = 3;

void executeSetServoAngle(TLV *tlv)
{
    uint8_t deviceAddress = tlv->val[0];
    int pin = tlv->val[1];
    int angle = *(uint16_t *)&tlv->val[2];
    int speed = *(uint16_t *)&tlv->val[4];

    unsigned int key = (deviceAddress << 8) | pin;

    switch (key)
    {
    case (HEAD_ADDRESS << 8) | ROLLNECK_PIN_VALUE:
        setServoTarget(deviceAddress, LEFT_ROLLNECK_PIN, angle, speed);
        setServoTarget(deviceAddress, RIGHT_ROLLNECK_PIN, angle, speed);
        break;

    default:
        setServoTarget(deviceAddress, pin, angle, speed);
    }

    Serial.print("CMD_SERVO_SET_ANGLE:");
    Serial.print(" pin: ");
    Serial.print(pin, DEC);
    Serial.print(" angle: ");
    Serial.print(angle, DEC);
    Serial.print(" speed: ");
    Serial.print(speed, DEC);
    Serial.print("\n");
}

void executeServoAttach(TLV *tlv)
{
    uint8_t deviceAddress = tlv->val[0];
    int pin = tlv->val[1];
    int angle = *(uint16_t *)&tlv->val[2];
    int speed = *(uint16_t *)&tlv->val[4];

    unsigned int key = (deviceAddress << 8) | pin;

    switch (key)
    {
    case (HEAD_ADDRESS << 8) | ROLLNECK_PIN_VALUE:
        attachServo(deviceAddress, LEFT_ROLLNECK_PIN, angle, speed);
        attachServo(deviceAddress, RIGHT_ROLLNECK_PIN, angle, speed);
        break;

    default:
        attachServo(deviceAddress, pin, angle, speed);
    }

    Serial.print("CMD_SERVO_ATTACH:");
    Serial.print(" pin: ");
    Serial.print(pin, DEC);
    Serial.print(" angle: ");
    Serial.print(angle, DEC);
    Serial.print(" speed: ");
    Serial.print(speed, DEC);
    Serial.print("\n");
}

void executeServoDetach(TLV *tlv)
{
    uint8_t deviceAddress = tlv->val[0];
    int pin = tlv->val[1];

    detachServo(deviceAddress, pin);

    Serial.print("CMD_SERVO_DETACH:");
    Serial.print(" pin: ");
    Serial.print(pin, DEC);
    Serial.print("\n");
}

void executeServoPower(TLV *tlv)
{
    int state = tlv->val[0];

    setServoPower(state);

    Serial.print("CMD_SERVO_POWER:");
    Serial.print(" state: ");
    Serial.print(state, DEC);
    Serial.print("\n");
}

void executeStopAllServo(TLV *tlv)
{
    stopTickServo();
    setServoPower(true);
}

void executeLedStateChange(TLV *tlv)
{
    byte state = tlv->val[0];

    Serial3.write(state);

    Serial.print("CMD_LED_SET_STATE:");
    Serial.print(" state: ");
    Serial.print(state, DEC);
    Serial.print("\n");
}

void handleUnknownCommand(TLV *tlv)
{
    Serial.print("CMD_UNKNOWN:");
    Serial.print(" tag: ");
    Serial.print(tlv->tag, HEX);
    Serial.print(" len: ");
    Serial.print(tlv->len, HEX);
    Serial.print(" val: ");

    for (char i = 0; i < tlv->len; i++)
    {
        Serial.print(tlv->val[i], HEX);
    }

    Serial.print("\n");
}

void processCommand(TLV *tlv)
{
    switch (tlv->tag)
    {
    case CMD_SERVO_SET_ANGLE:
        executeSetServoAngle(tlv);
        break;
    case CMD_SERVO_STOP_ALL:
        executeStopAllServo(tlv);
        break;
    case CMD_SERVO_ATTACH:
        executeServoAttach(tlv);
        break;
    case CMD_SERVO_DETACH:
        executeServoDetach(tlv);
        break;
    case CMD_SERVO_POWER:
        executeServoPower(tlv);
        break;
    case CMD_LED_SET_STATE:
        executeLedStateChange(tlv);
        break;
    default:
        handleUnknownCommand(tlv);
        break;
    }
}
