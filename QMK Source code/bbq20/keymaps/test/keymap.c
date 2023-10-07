#include QMK_KEYBOARD_H

#define pin_BLK_KBD GP25
#define pin_BLK_TP GP0

enum layer_number {
  _QWERTY = 0,
  _LOWER = 1,
  _RAISE = 2,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)


extern bool isScrollMode;
extern bool isBoostMode;
extern bool isSlowMode;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT(

                 KC_1,                                                        KC_2,   
        KC_CAPS,           KC_4,            KC_BTN1,                KC_5,           KC_6, 
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_BSPC,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_DLR,  KC_ENT,
                 KC_LCTL,          KC_LALT,    KC_SPC,        KC_7,            KC_8
)

};

void board_init(void){
    setPinOutput(pin_BLK_KBD);  
    setPinOutput(pin_BLK_TP);
    writePinHigh(pin_BLK_KBD);
    writePinLow(pin_BLK_TP);
}

bool led_update_user(led_t led_state) {
    if (led_state.caps_lock) {  //if caps lock is on
    writePinHigh(pin_BLK_TP);
    isScrollMode = true;
    } else {                    //if caps lock is off
    writePinLow(pin_BLK_TP);
    isScrollMode = false;
    }
    return true;
}

