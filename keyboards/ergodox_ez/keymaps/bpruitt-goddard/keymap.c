// An Ergodox EZ keymap mostly following the programmer's dvorak layout.
//
// See the README.md file for an image of this keymap.

#include QMK_KEYBOARD_H

// The layers that we are defining for this keyboards.
enum board_layers {
  _BASE,
  _RAISE,
  _LOWER,
  _ADJUST,
};

typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7
};

// The Tap Dance identifiers, used in the TD keycode and tap_dance_actions array.
enum {
  TAP_MACRO = 0,
  TAP_LSHIFT,
  TAP_RSHIFT,
};

int cur_dance (qk_tap_dance_state_t *state);

// SAFE_RANGE must be used to tag the first element of the enum.
// DYNAMIC_MACRO_RANGE must always be the last element of the enum if other
// values are added (as its value is used to create a couple of other keycodes
// after it).
enum custom_keycodes {
    MC_ARROW = SAFE_RANGE,
    DYNAMIC_MACRO_RANGE
};

// A 'transparent' key code (that falls back to the layers below it).
#define ___ KC_TRANSPARENT

// A 'blocking' key code. Does nothing but prevent falling back to another layer.
#define XXX KC_NO

// Some combined keys (one normal keycode when tapped and one modifier or layer
// toggle when held).
#define SPC_RALT  MT(MOD_RALT, KC_SPC)  // SPACE key and right alt modifier.
#define SCOMMA_RAISE LT(RAISE, KC_COMMA) // Comma key and momentary num layer
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

// The most portable copy/paste keys (windows (mostly), linux, and some terminal emulators).
#define MK_CUT    LSFT(KC_DEL)  // shift + delete
#define MK_COPY   LCTL(KC_INS)  // ctrl + insert
#define MK_PASTE  LSFT(KC_INS)  // shift + insert
//Move mac desktop spaces
#define MAC_L     LGUI(LSFT(KC_UP)) // cmd + shift + up
#define MAC_R     LGUI(LSFT(KC_DOWN)) // cmd + shift + down

// This file must be included after DYNAMIC_MACRO_RANGE is defined...
#include "dynamic_macro.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Layer 0: basic keys.
  [_BASE] = LAYOUT_ergodox_pretty(
    KC_DLR,           KC_AMPR,    KC_LBRC,      ___,            ___,     ___,     KC_CIRC,           KC_F4,        KC_EQUAL,KC_ASTR, KC_BSLASH, KC_PLUS,  KC_RBRACKET, KC_EXLM,
    KC_BSLASH,        KC_SCOLON,  SCOMMA_RAISE, LCTL_T(KC_DOT), KC_P,    KC_Y,    KC_PERC,           KC_DELETE,    KC_F,    KC_G,    KC_C,      KC_R,     KC_L,        KC_SLASH,
    KC_QUOTE,         KC_A,       KC_O,         KC_E,           KC_U,    KC_I,                                     KC_D,    KC_H,    KC_T,      KC_N,     KC_S,        GUI_T(KC_MINUS),
    TD(TAP_LSHIFT),   KC_AT,      GUI_T(KC_Q),  KC_J,           KC_K,    KC_X,    KC_LALT,           TD(TAP_MACRO),KC_B,    KC_M,    KC_W,      KC_V,     CTL_T(KC_Z), TD(TAP_RSHIFT),
    KC_ESCAPE,        KC_HASH,    KC_GRAVE,     KC_LEFT,        KC_RIGHT,                                                   KC_UP,   KC_DOWN,   KC_HOME,  KC_END,      MEH_T(KC_NO),
                                                      ALT_T(KC_APPLICATION), ALL_T(KC_NO),           ___, KC_LGUI,
                                                                                KC_BSLASH,           ___,
                                        LT(LOWER, KC_ENTER), KC_TAB, LT(LOWER, KC_ESCAPE),           LT(RAISE, KC_ESCAPE), KC_BSPACE,  LT(RAISE, KC_SPACE)),

  [_RAISE] = LAYOUT_ergodox_pretty(
    ___,  ___,  ___,    ___,    ___,    ___,    ___,         ___, ___,    ___,            ___,      ___,            ___,  ___,
    ___,  ___,  KC_F9,  KC_F10, KC_F11, KC_F12, ___,         ___, ___,    LALT(KC_LEFT),  KC_UP,    LALT(KC_RIGHT), ___,  ___,
    ___,  ___,  KC_F5,  KC_F6,  KC_F7,  KC_F8,                    ___,    KC_LEFT,        KC_DOWN,  KC_RIGHT,       ___,  ___,
    ___,  ___,  KC_F1,  KC_F2,  KC_F3,  KC_F4,  ___,         ___, KC_F1,  KC_F2,          KC_F3,    KC_F4,          ___,  ___,
    ___,  ___,  ___,    ___,    ___,                                      ___,            ___,      ___,            ___,  ___,
                                        ___,    ___,         ___,  ___,
                                                ___,         ___,
                                    ___,  ___,  ___,         ___,  ___,  ___),

  [_LOWER] = LAYOUT_ergodox_pretty(
    ___,  ___,  ___,  ___,  ___,  ___,  ___,         ___, ___,      ___,      ___,        ___,        ___,          ___,
    ___,  ___,  KC_7, KC_8, KC_9, ___,  ___,         ___, KC_COMMA, KC_DOT,   KC_MS_BTN1, KC_MS_BTN2, KC_ASTR,      KC_F12,
    ___,  ___,  KC_4, KC_5, KC_6, ___,                    KC_LCBR,  KC_RCBR,  MC_ARROW,   KC_GRAVE,   KC_PLUS,      KC_UNDS,
    ___,  ___,  KC_1, KC_2, KC_3, KC_0, ___,         ___, KC_CIRC,  KC_HASH,  KC_DLR,     ___,        ___,          ___,
    ___,  ___,  ___,  ___,  ___,                                    ___,      ___,        ___,        ___,          ___,
                                ___,    ___,         KC_KP_ASTERISK, KC_KP_SLASH,
                                    KC_LCTL,         ___,
           KC_KP_PLUS,  KC_KP_MINUS, KC_DLR,         ___,  ___,  ___),

  [_ADJUST] = LAYOUT_ergodox_pretty(
    ___,  ___,  ___,  ___,              ___,          ___,  ___,         ___, ___,  ___,  ___,  ___,  ___,  ___,
    ___,  ___,  ___,  LALT(KC_BSPACE),  LALT(KC_DEL), ___,  ___,         ___, ___,  ___,  ___,  ___,  ___,  ___,
    ___,  ___,  ___,  ___,              ___,          ___,                    ___,  ___,  ___,  ___,  ___,  ___,
    ___,  ___,  ___,  ___,              ___,          ___,  ___,         ___, ___,  ___,  ___,  ___,  ___,  ___,
    ___,  ___,  ___,  ___,              ___,                                        ___,  ___,  ___,  ___,  ___,
                                                    ___,    ___,         ___,  ___,
                                                            ___,         ___,
                                                ___,  ___,  ___,         ___,  ___,  ___),


};

// Whether the macro 1 is currently being recorded.
static bool is_macro1_recording = false;

// The current set of active layers (as a bitmask).
// There is a global 'layer_state' variable but it is set after the call
// to layer_state_set_user().
static uint32_t current_layer_state = 0;
uint32_t layer_state_set_user(uint32_t state);

// Method called at the end of the tap dance on the TAP_MACRO key. That key is
// used to start recording a macro (double tap or more), to stop recording (any
// number of tap), or to play the recorded macro (1 tap).
void macro_tapdance_fn(qk_tap_dance_state_t *state, void *user_data) {
  uint16_t keycode;
  keyrecord_t record;
  dprintf("macro_tap_dance_fn %d\n", state->count);
  if (is_macro1_recording) {
    keycode = DYN_REC_STOP;
    is_macro1_recording = false;
    layer_state_set_user(current_layer_state);
  } else if (state->count == 1) {
    keycode = DYN_MACRO_PLAY1;
  } else {
    keycode = DYN_REC_START1;
    is_macro1_recording = true;
    layer_state_set_user(current_layer_state);
  }

  record.event.pressed = true;
  process_record_dynamic_macro(keycode, &record);
  record.event.pressed = false;
  process_record_dynamic_macro(keycode, &record);
}

// Return an integer that corresponds to what kind of tap dance should be executed.
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (!state->pressed)  return SINGLE_TAP;
    //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  //Assumes no one is trying to type the same letter three times (at least not quickly).
  if (state->count == 3) {
    if (!state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8; //magic number. At some point this method will expand to work for more presses
}

//instantiate an instance of 'tap' for the 'x' tap dance.
static tap xtap_state = {
  .is_press_action = true,
  .state = 0
};

void lshift_finished (qk_tap_dance_state_t *state, void *user_data) {
  xtap_state.state = cur_dance(state);
  switch (xtap_state.state) {
    case SINGLE_TAP: register_code16(KC_LPRN); break;
    case SINGLE_HOLD: register_code(KC_LSHIFT); break;
    case DOUBLE_TAP: register_code(KC_CAPS); break;
    case DOUBLE_HOLD: register_code(KC_LSHIFT); break;
  }
}

void lshift_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (xtap_state.state) {
    case SINGLE_TAP: unregister_code16(KC_LPRN); break;
    case SINGLE_HOLD: unregister_code(KC_LSHIFT); break;
    // Don't unregister caps because then it disables caps lock
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: unregister_code(KC_LSHIFT);
  }
  xtap_state.state = 0;
}

void rshift_finished (qk_tap_dance_state_t *state, void *user_data) {
  xtap_state.state = cur_dance(state);
  switch (xtap_state.state) {
    case SINGLE_TAP: register_code16(KC_RPRN); break;
    case SINGLE_HOLD: register_code(KC_RSHIFT); break;
    case DOUBLE_TAP: register_code(KC_CAPS); break;
    case DOUBLE_HOLD: register_code(KC_RSHIFT); break;
  }
}

void rshift_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (xtap_state.state) {
    case SINGLE_TAP: unregister_code16(KC_RPRN); break;
    case SINGLE_HOLD: unregister_code(KC_RSHIFT); break;
    // Don't unregister caps because then it disables caps lock
    case DOUBLE_TAP: break;
    case DOUBLE_HOLD: unregister_code(KC_RSHIFT);
  }
  xtap_state.state = 0;
}

// The definition of the tap dance actions:
qk_tap_dance_action_t tap_dance_actions[] = {
  // This Tap dance plays the macro 1 on TAP and records it on double tap.
  [TAP_MACRO] = ACTION_TAP_DANCE_FN(macro_tapdance_fn),
  [TAP_LSHIFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lshift_finished, lshift_reset),
  [TAP_RSHIFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rshift_finished, rshift_reset)
};

// Runs for each key down or up event.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (keycode != TD(TAP_MACRO)) {
    // That key is processed by the macro_tapdance_fn. Not ignoring it here is
    // mostly a no-op except that it is recorded in the macros (and uses space).
    // We can't just return false when the key is a tap dance, because
    // process_record_user, is called before the tap dance processing (and
    // returning false would eat the tap dance).
    if (!process_record_dynamic_macro(keycode, record)) {
      return false;
    }

    if(record->event.pressed) {
      switch(keycode) {
        case MC_ARROW:
          SEND_STRING("=>");
          return false;
          break;
      }
    }
  }

  return true; // Let QMK send the enter press/release events
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

};

// Value to use to switch LEDs on. The default value of 255 is far too bright.
static const uint8_t max_led_value = 20;

// Whether the given layer (one of the constant defined at the top) is active.
#define LAYER_ON(layer) (current_layer_state & (1<<layer))

void led_1_on(void) {
  ergodox_right_led_1_on();
  ergodox_right_led_1_set(max_led_value);
}

void led_2_on(void) {
  ergodox_right_led_2_on();
  ergodox_right_led_2_set(max_led_value);
}

void led_3_on(void) {
  ergodox_right_led_3_on();
  ergodox_right_led_3_set(max_led_value);
}

void led_1_off(void) {
  ergodox_right_led_1_off();
}

void led_2_off(void) {
  ergodox_right_led_2_off();
}

void led_3_off(void) {
  ergodox_right_led_3_off();
}

void layer_state_set_rgb(uint32_t state) {
  current_layer_state = state;

  if (is_macro1_recording) {
    led_1_on();
    led_2_on();
    led_3_on();
    return;
  }

  if (LAYER_ON(_LOWER)) {
    led_1_on();
  } else {
    led_1_off();
  }

  if (LAYER_ON(_RAISE)) {
    led_2_on();
  } else {
    led_2_off();
  }
};

// Changes to adjust layer when raise and lower are held
layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
  layer_state_set_rgb(state);
  return state;
}
