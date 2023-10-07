#include "trackpad.h"


#define Trackpad_ADDR 0x3B


#define REG_PID    0x00
#define REG_REV    0x01
#define REG_MOTION 0x02

#define REG_DELTA_X 0x03
#define REG_DELTA_Y 0x04

#define pin_TP_SHUTDOWN GP24
#define pin_TP_MOTION GP22
#define pin_TP_RESET GP16
#define pin_BLK_KBD GP25
#define pin_BLK_TP GP0

#define BIT_MOTION_MOT (1 << 7)

#define trackpad_timeout 100


void pointing_device_init(void) {
    i2c_init();
    wait_ms(10);

    setPinOutput(pin_TP_SHUTDOWN);
    writePinLow(pin_TP_SHUTDOWN);

    setPinInputHigh(pin_TP_MOTION);

    setPinOutput(pin_TP_RESET);
    writePinLow(pin_TP_RESET);
    wait_ms(100);
    writePinHigh(pin_TP_RESET);
}


uint8_t read_register8(uint8_t reg) {
    uint8_t val;
    i2c_writeReg(TRACKPAD_WRITE, reg, NULL, 0, trackpad_timeout);
    i2c_readReg(TRACKPAD_READ, reg, &val, 1, trackpad_timeout);
    return val;
}

bool pointing_device_task(void) {
    const uint8_t ifmotion = read_register8(REG_MOTION);
    
    if ( ifmotion & BIT_MOTION_MOT) {
        int8_t y =  read_register8(REG_DELTA_X);
        int8_t x =  read_register8(REG_DELTA_Y);
        

        x = ((x < 127) ? x : (x - 256)) * 2.0;
        y = ((y < 127) ? y : (y - 256)) * 2.0;

        report_mouse_t currentReport = pointing_device_get_report();
        currentReport.x= x;
        currentReport.y= y;
        pointing_device_set_report(currentReport);
    }
    return pointing_device_send();
}
