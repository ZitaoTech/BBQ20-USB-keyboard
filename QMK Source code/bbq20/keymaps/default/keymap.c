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

                 KC_BTN1,                                                        KC_BTN2,    
        KC_CAPS,          KC_WSCH,             KC_BTN1,                KC_ESC,           KC_WHOM, 
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_BSPC,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_DLR,  KC_ENT,
                 KC_LCTL,          KC_LALT,    KC_SPC,        LOWER,            RAISE
),

[_LOWER] = LAYOUT(

                 KC_PGUP,                                                       KC_PGDN,    
        KC_TAB,           KC_CALC,            KC_BTN2,               KC_BRIU,          KC_BRID, 
        KC_HASH, KC_1,    KC_2,    KC_3,    KC_LPRN, KC_RPRN, KC_UNDS, KC_MINS, KC_PLUS, KC_AT,
        KC_ASTR, KC_4,    KC_5,    KC_6,    KC_SLSH, KC_COLN, KC_SCLN, KC_QUOT, KC_DQT,  KC_DEL,
        KC_LSFT, KC_7,    KC_8,    KC_9,    KC_QUES, KC_EXLM, KC_COMM, KC_DOT,  KC_MUTE, KC_ENT,
                 KC_LGUI, 	       KC_0,      KC_END,       LOWER,            RAISE
),

[_RAISE] = LAYOUT(

                 KC_VOLU,                                                        KC_VOLD,    
        KC_F1,            KC_F5,                KC_BTN3,               KC_F12,           KC_SLEP, 
        KC_NO,   KC_UP,   KC_NO,   KC_NO,   KC_LBRC, KC_RBRC, KC_LABK, KC_RABK, KC_PIPE, KC_EQL,
        KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,   KC_BSLS, KC_AMPR, KC_LCBR, KC_RCBR, KC_CIRC, KC_NO,
        KC_LSFT, KC_NO,   KC_NO,   KC_NO,   KC_PERC, BL_TOGG, KC_GRV,  KC_NO,   KC_NO,   KC_NO,
                 KC_NO,            KC_TILD,     KC_NO,        LOWER,             RAISE
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    /*case KC_LSFT:
      if (record->event.pressed) {
        isScrollMode = true;
        tap_code(KC_LSFT);
      }
      else {
        isScrollMode = false;
      }
      return false;   */
    case KC_LCTL:
      if (record->event.pressed) {
        isBoostMode  = true;
        register_code(KC_LCTL);
      }
      else {
        isBoostMode = false;
        unregister_code(KC_LCTL);
      }
      return false;
    case KC_LALT:
      if (record->event.pressed) {
        isSlowMode = true;
        register_code(KC_LALT);
      }
      else {
        isSlowMode = false;
        unregister_code(KC_LALT);
      }
      return false;
  }
  return true;
}
