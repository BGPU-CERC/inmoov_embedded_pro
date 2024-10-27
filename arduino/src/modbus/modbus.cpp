
#include "modbus.h"
#include <Arduino.h>

struct TLV tlv;

char modbusState = MODBUS_STATE_TAG;
char modbusIndexVal = 0;

void checkModbusTag(unsigned char data)
{
  tlv.tag = data;
  modbusState = MODBUS_STATE_LEN;
}

void checkModbusLen(unsigned char data)
{
  tlv.len = data;

  switch (data)
  {
  case 0:
    modbusState = MODBUS_STATE_COMPLETE;
    break;
  default:
    modbusState = MODBUS_STATE_VAL;
    break;
  }
}

void checkModbusVal(unsigned char data)
{
  tlv.val[modbusIndexVal++] = data;

  if (modbusIndexVal >= tlv.len)
  {
    modbusState = MODBUS_STATE_COMPLETE;
  }
}

char readModbus(unsigned char data)
{
  switch (modbusState)
  {
  case MODBUS_STATE_TAG:
    checkModbusTag(data);
    break;
  case MODBUS_STATE_LEN:
    checkModbusLen(data);
    break;
  case MODBUS_STATE_VAL:
    checkModbusVal(data);
    break;
  default:
    break;
  }

  return modbusState;
}

bool isModbusComplete()
{
  return modbusState == MODBUS_STATE_COMPLETE;
}

void resetModbus()
{
  modbusState = MODBUS_STATE_TAG;
  modbusIndexVal = 0;
}

TLV *getModbusTlv()
{
  return &tlv;
}
