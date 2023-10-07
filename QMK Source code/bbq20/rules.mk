OLED_ENABLE = yes                     # start using i2c 
POINTING_DEVICE_ENABLE = yes          # Mouse keys
POINTING_DEVICE_DRIVER = custom       # customer driver for trackpad on the BB9900 keyboard


OPT_DEFS += -DHAL_USE_I2C=TRUE
# Add support for the BB9900 trackpad
SRC += trackpad.c