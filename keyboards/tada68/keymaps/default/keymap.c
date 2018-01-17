#include "tada68.h"
#include "process_unicode_common.h"
#include "process_unicode.h"
#include "quantum.h"
#include "quantum_keycodes.h"
#include "process_tap_dance.h"


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BL 0
#define _FL 1

enum emoticons {
	LED_UP = SAFE_RANGE,
	LED_DOWN
};

enum
{
  TD_H_BSPC = 0
};

#define TD_H TD(TD_H_BSPC)

#define trigger_time 200

#define T1 M(1)
#define T2 M(2)
#define T3 M(3)
#define T4 M(4)
#define T5 M(5)
#define T6 M(6)
#define T7 M(7)
#define T8 M(8)
#define T9 M(9)
#define T10 M(10)
#define T11 M(11)
#define T12 M(12)
#define END_HOME M(0)
#define MY_WIN M(20)

#define _______ KC_TRNS

#define LSHIFT OSM(MOD_LSFT)

#define FN_APP LT(_FL, KC_APP)

#define MY_TAB MT(MOD_LCTL | MOD_LSFT, KC_TAB)
#define MY_CAP MT(MOD_LCTL, KC_CAPS)
#define MY_ESC LT(_FL, KC_ESC)
#define MY_F   MT(MOD_LSFT, KC_F)
#define MY_J   MT(MOD_RSFT, KC_J)

static uint16_t key_timer;

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_H_BSPC] = ACTION_TAP_DANCE_DOUBLE(KC_H, KC_BSPC)};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap _BL: (Base Layer) Default Layer
   * ,----------------------------------------------------------------.
   * |MYES |F1|F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|  -|  =|Backsp |~ ` |
   * |----------------------------------------------------------------|
   * |C+S,Ta| Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |Del |
   * |----------------------------------------------------------------|
   * |CT,CAPS|  A|  S|  D|F_S|  G|  H|J_S|  K|  L|  ;|  '|Return |PgUp|
   * |----------------------------------------------------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift | Up|PgDn|
   * |----------------------------------------------------------------|
   * |Ctrl| WIN |Alt |        Space         |Alt| FN|Ctrl|Lef|Dow|Rig |
   * `----------------------------------------------------------------'
   */

    //		| 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|
    //		KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,

    //		| F1 | F2 | F3 | F4 | F5 | F6 | F7 | F8 | F9 | F10
    //		KC_F1 ,KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,
    [_BL] = KEYMAP_ANSI(
        MY_ESC, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, T12, KC_BSPC, KC_GRV,
        MY_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,
        MY_CAP, KC_A, KC_S, KC_D, MY_F, KC_G, TD_H, MY_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, KC_PGUP,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP, KC_PGDN,
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, FN_APP, KC_RCTRL, KC_LEFT, KC_DOWN, KC_RGHT),

    /* Keymap _FL: Function Layer
   * ,----------------------------------------------------------------.
   * |   |  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|F11|F12|Del    |Ins |
   * |----------------------------------------------------------------|
   * |     |VU-|MUT|VU+|   |   |   |McL|MsU|McR|   |   |   |     |Hme |
   * |----------------------------------------------------------------|
   * |      |Bl-|BL |BL+|   |   |   |MsL|MsD|MsR|   |   |        |End |
   * |----------------------------------------------------------------|
   * |        |   |   |	  |   |   |   |   |   |   |   |   |  |PGUP|HOM|
   * |----------------------------------------------------------------|
   * |    |    |    |                       |   |   |App|HOME|PGDN|END|
   * `----------------------------------------------------------------'
   *
   * App stands for windows context menu
   */
    [_FL] = KEYMAP_ANSI(
        _______, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_F11, KC_F12, KC_DEL, KC_INS,
        _______, KC_VOLD, KC_MUTE, KC_VOLU, _______, _______, _______, _______, KC_BTN1, KC_MS_U, KC_BTN2, _______, _______, _______, KC_HOME,
        _______, BL_DEC, BL_TOGG, BL_INC, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______, KC_END,
        LED_UP, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PGUP, KC_HOME,
        LED_DOWN, _______, _______, _______, _______, _______, KC_APP, KC_HOME, KC_PGDN, KC_END),
};

void led_set_user(uint8_t usb_led) {
	if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        // Turn capslock on
        PORTB |= (1<<6);
    } else {
        // Turn capslock off
        PORTB &= ~(1<<6);
    }
}



int led_status = 0;

void tap(uint16_t keycode)
{
  register_code(keycode);
  unregister_code(keycode);
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case LED_UP:
			if(record->event.pressed){
        PORTB |= (1<<6);
      }
      return false;
			break;
    case LED_DOWN:
      if (record->event.pressed)
      {
        PORTB &= ~(1 << 6);
      }
      return false;
      break;
  }
	return true;
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    switch (id) {
		case 0:
			if (record->event.pressed) {
				key_timer = timer_read();
			}
			else {
				if (timer_elapsed(key_timer) > trigger_time) {
					return MACRO( T(END), END );
				}
				else {
					return MACRO( T(HOME), END );
				}
			}
			break;
		case 1:
			if (record->event.pressed) {
				key_timer = timer_read();
			}
			else {
				if (timer_elapsed(key_timer) > trigger_time) {
					return MACRO( T(F1), END );
				}
				else {
					return MACRO( T(1), END );
				}
			}
			break;
		case 2:
			if (record->event.pressed) {
				key_timer = timer_read();
			}
			else {
				if (timer_elapsed(key_timer) > trigger_time) {
					return MACRO( T(F2), END );
				}
				else {
					return MACRO( T(2), END );
				}
			}
			break;
		case 3:
			if (record->event.pressed) {
				key_timer = timer_read();
			}
			else {
				if (timer_elapsed(key_timer) > trigger_time) {
					return MACRO( T(F3), END );
				}
				else {
					return MACRO( T(3), END );
				}
			}
			break;
		case 4:
			if (record->event.pressed) {
				key_timer = timer_read();
			}
			else {
				if (timer_elapsed(key_timer) > trigger_time) {
					return MACRO( T(F4), END );
				}
				else {
					return MACRO( T(4), END );
				}
			}
			break;
		case 5:
			if (record->event.pressed) {
				key_timer = timer_read();
			}
			else {
				if (timer_elapsed(key_timer) > trigger_time) {
					return MACRO( T(F5), END );
				}
				else {
					return MACRO( T(5), END );
				}
			}
			break;
		case 6:
			if (record->event.pressed) {
				key_timer = timer_read();
			}
			else {
				if (timer_elapsed(key_timer) > trigger_time) {
					return MACRO( T(F6), END );
				}
				else {
					return MACRO( T(6), END );
				}
			}
			break;
		case 7:
			if (record->event.pressed) {
				key_timer = timer_read();
			}
			else {
				if (timer_elapsed(key_timer) > trigger_time) {
					return MACRO( T(F7), END );
				}
				else {
					return MACRO( T(7), END );
				}
			}
			break;
		case 8:
			if (record->event.pressed) {
				key_timer = timer_read();
			}
			else {
				if (timer_elapsed(key_timer) > trigger_time) {
					return MACRO( T(F8), END );
				}
				else {
					return MACRO( T(8), END );
				}
			}
			break;
		case 9:
			if (record->event.pressed) {
				key_timer = timer_read();
			}
			else {
				if (timer_elapsed(key_timer) > trigger_time) {
					return MACRO( T(F9), END );
				}
				else {
					return MACRO( T(9), END );
				}
			}
			break;
		case 10:
			if (record->event.pressed) {
				key_timer = timer_read();
			}
			else {
				if (timer_elapsed(key_timer) > trigger_time) {
					return MACRO( T(F10), END );
				}
				else {
					return MACRO( T(0), END );
				}
			}
			break;
		case 11:
			if (record->event.pressed) {
				key_timer = timer_read();
			}
			else {
				if (timer_elapsed(key_timer) > trigger_time) {
					return MACRO( T(F11), END );
				}
				else {
					return MACRO( T(MINS), END );
				}
			}
			break;
		case 12:
			if (record->event.pressed) {
				key_timer = timer_read();
			}
			else {
				if (timer_elapsed(key_timer) > trigger_time) {
					return MACRO( T(F12), END );
				}
				else {
					return MACRO( T(EQL), END );
				}
			}
			break;
    case 20:
     if (record ->event.pressed)
     {
       key_timer = timer_read();
       layer_on(_FL);
     }
     else
     {
       layer_off(_FL);
       if (timer_elapsed(key_timer) < trigger_time)
       {
         register_code(KC_LGUI);
         unregister_code(KC_LGUI);
         // MACRO( T(KC_LGUI), END );
       }
     }
     break;
  }
  return MACRO_NONE;
};
