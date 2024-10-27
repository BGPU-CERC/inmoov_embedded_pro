#pragma once

#define MODBUS_STATE_TAG 11
#define MODBUS_STATE_LEN 12
#define MODBUS_STATE_VAL 13
#define MODBUS_STATE_COMPLETE 14

#define TLV_LEN_MAX 64

struct TLV
{
  unsigned char tag;
  unsigned char len;
  unsigned char val[TLV_LEN_MAX];
};

char readModbus(unsigned char data);
bool isModbusComplete();
void resetModbus();
TLV *getModbusTlv();
