#include "config.h"

servo servos[SERVO_AMOUNT] = {
    {HEAD_ADDRESS, 0, 65, 115, 500, 2500, ServoDriverSmooth(HEAD_ADDRESS)}, // jaw
    {HEAD_ADDRESS, 1, 50, 140, 500, 2500, ServoDriverSmooth(HEAD_ADDRESS)}, // neck
    {HEAD_ADDRESS, 2, 50, 130, 500, 2500, ServoDriverSmooth(HEAD_ADDRESS)}, // rollneck l
    {HEAD_ADDRESS, 3, 50, 130, 500, 2500, ServoDriverSmooth(HEAD_ADDRESS)}, // rollneck r
    {HEAD_ADDRESS, 4, 40, 130, 500, 2500, ServoDriverSmooth(HEAD_ADDRESS)}, // rothead
    {HEAD_ADDRESS, 5, 40, 120, 500, 2500, ServoDriverSmooth(HEAD_ADDRESS)}, // eyeX
    {HEAD_ADDRESS, 6, 70, 110, 500, 2500, ServoDriverSmooth(HEAD_ADDRESS)}, // eyeY

    {LEFT_HAND_ADDRESS, 0, 0, 90, 500, 2500, ServoDriverSmooth(LEFT_HAND_ADDRESS)},   // thumb
    {LEFT_HAND_ADDRESS, 1, 0, 160, 500, 2500, ServoDriverSmooth(LEFT_HAND_ADDRESS)},  // index
    {LEFT_HAND_ADDRESS, 2, 0, 160, 500, 2500, ServoDriverSmooth(LEFT_HAND_ADDRESS)},  // majeure
    {LEFT_HAND_ADDRESS, 3, 0, 160, 500, 2500, ServoDriverSmooth(LEFT_HAND_ADDRESS)},  // ringFinger
    {LEFT_HAND_ADDRESS, 4, 0, 160, 500, 2500, ServoDriverSmooth(LEFT_HAND_ADDRESS)},  // pinky
    {LEFT_HAND_ADDRESS, 5, 0, 180, 500, 2500, ServoDriverSmooth(LEFT_HAND_ADDRESS)},  // wrist
    {LEFT_HAND_ADDRESS, 6, 20, 95, 500, 2500, ServoDriverSmooth(LEFT_HAND_ADDRESS)},  // bicep
    {LEFT_HAND_ADDRESS, 7, 40, 160, 500, 2500, ServoDriverSmooth(LEFT_HAND_ADDRESS)}, // rotate
    {LEFT_HAND_ADDRESS, 8, 30, 170, 500, 2500, ServoDriverSmooth(LEFT_HAND_ADDRESS)}, // shoulder
    {LEFT_HAND_ADDRESS, 9, 18, 65, 500, 2500, ServoDriverSmooth(LEFT_HAND_ADDRESS)},  // omoplate

    {RIGHT_HAND_ADDRESS, 0, 0, 90, 500, 2500, ServoDriverSmooth(RIGHT_HAND_ADDRESS)},   // thumb
    {RIGHT_HAND_ADDRESS, 1, 0, 160, 500, 2500, ServoDriverSmooth(RIGHT_HAND_ADDRESS)},  // index
    {RIGHT_HAND_ADDRESS, 2, 0, 160, 500, 2500, ServoDriverSmooth(RIGHT_HAND_ADDRESS)},  // majeure
    {RIGHT_HAND_ADDRESS, 3, 0, 160, 500, 2500, ServoDriverSmooth(RIGHT_HAND_ADDRESS)},  // ringFinger
    {RIGHT_HAND_ADDRESS, 4, 0, 160, 500, 2500, ServoDriverSmooth(RIGHT_HAND_ADDRESS)},  // pinky
    {RIGHT_HAND_ADDRESS, 5, 0, 180, 500, 2500, ServoDriverSmooth(RIGHT_HAND_ADDRESS)},  // wrist
    {RIGHT_HAND_ADDRESS, 6, 20, 95, 500, 2500, ServoDriverSmooth(RIGHT_HAND_ADDRESS)},  // bicep
    {RIGHT_HAND_ADDRESS, 7, 40, 160, 500, 2500, ServoDriverSmooth(RIGHT_HAND_ADDRESS)}, // rotate
    {RIGHT_HAND_ADDRESS, 8, 30, 170, 500, 2500, ServoDriverSmooth(RIGHT_HAND_ADDRESS)}, // shoulder
    {RIGHT_HAND_ADDRESS, 9, 18, 65, 500, 2500, ServoDriverSmooth(RIGHT_HAND_ADDRESS)},  // omoplate

    {STOM_ADDRESS, 0, 50, 90, 500, 2500, ServoDriverSmooth(STOM_ADDRESS)},  // midstom
    {STOM_ADDRESS, 1, 60, 120, 500, 2500, ServoDriverSmooth(STOM_ADDRESS)}, // topstom
};

int moduleEnablePins[MODULE_AMOUNT] = {
    HEAD_EN_PIN,
    LHAND_EN_PIN,
    RHAND_EN_PIN,
    STOM_EN_PIN,
};

int getServoIndex(int deviceAddress, int pin)
{
    for (int i = 0; i < SERVO_AMOUNT; i++)
    {
        if (servos[i].deviceAddress == deviceAddress && servos[i].pin == pin)
        {
            return i;
        }
    }
    return -1;
}

servo *getServo(int deviceAddress, int pin)
{
    int index = getServoIndex(deviceAddress, pin);
    if (index != -1)
    {
        return &servos[index];
    }
    return nullptr;
}
