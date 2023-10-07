#include "quantum.h"
#include "pointing_device.h"
#include "report.h"
#include "stdio.h"
#include "i2c_master.h"

#ifndef TRACKPAD_ADDRESS
#    define TRACKPAD_ADDRESS 0x3B
#endif
#define TRACKPAD_WRITE ((TRACKPAD_ADDRESS << 1) )
#define TRACKPAD_READ  ((TRACKPAD_ADDRESS << 1) )

uint8_t  read_register8(uint8_t reg);
