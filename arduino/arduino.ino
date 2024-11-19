#include "src/modbus/modbus.h"
#include "src/command/command.h"
#include "src/servo/servo.h"

TLV *packet = getModbusTlv();

void setup()
{
    Serial.begin(115200);
    Serial3.begin(115200);
    setupServo();
}

void loop()
{
    tickServo();
}

void serialEvent()
{
    while (Serial.available())
    {
        unsigned char c = Serial.read();
        readModbus(c);

        if (isModbusComplete())
        {
            processCommand(packet);
            resetModbus();
        }
    }
}