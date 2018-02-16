#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define trigger_time 110

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys
#define CURS 3 // cursor layout

//special keys
#define MY_A   LT(CURS, KC_A)
#define MY_S   MT(MOD_LALT, KC_S)
#define MY_D   MT(MOD_LCTL, KC_D)
#define MY_F   MT(MOD_LSFT, KC_F)
#define MY_J   MT(MOD_RSFT, KC_J)
#define MY_K   MT(MOD_RCTL, KC_K)
#define MY_L   MT(MOD_LALT, KC_L)

//macros
#define T1     M(101)
#define T2     M(102)
#define T3     M(103)
#define T4     M(104)
#define T5     M(105)
#define T6     M(106)
#define T7     M(107)
#define T8     M(108)
#define T9     M(109)
#define T10    M(110)
#define T11    M(111)
#define T12    M(112)

#define MY_WIN M(120)
#define T_ENT  M(121)
#define T_ESC  M(122)

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |  =/F12 | 1/F1 | 2/F2 | 3/F3 | 4/F4 | 5/F5 | LEFT |           | RIGHT| 6/F6 | 7/F7 | 8/F8 | 9/F9 | 0/F10| -/F11  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | TAB    |   Q  |   W  |   E  |   R  |   T  |  L1  |           |  L1  |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | BkSp   |CURS/A| ALT/S|CTRL/D|SHFT/F|   G  |------|           |------|   H  |SHFT/J|CTRL/K| ALT/L|   ;  |  ' "   |
 * |--------+------+------+------+------+------| Hyper|           | Meh  |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |Grv/L1| App  |AltShf| Left | Right|                                       |  Up  | Down |   [  |   ]  | ~L1  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | App  | LGui |       | Alt  |Ctrl/Esc|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | Home |       | PgUp |        |      |
 *                                 | Space|Backsp|------|       |------|  Tab   |Enter |
 *                                 |      |ace   | End  |       | PgDn |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = LAYOUT_ergodox(  // layer 0 : default
        // left hand
        T12,            T1,           T2,             T3,        T4,     T5,     KC_LEFT,
        KC_TAB,         KC_Q,         KC_W,           KC_E,      KC_R,   KC_T,   TG(SYMB),
        KC_BSPC,        MY_A,         MY_S,           MY_D,      MY_F,   KC_G,
        KC_LSFT,        KC_Z,         KC_X,           KC_C,      T_ESC,  KC_B,   ALL_T(KC_NO),
        LT(SYMB,KC_GRV),KC_APP,       LALT(KC_LSFT),  KC_LEFT,   KC_RGHT,

                                              ALT_T(KC_APP),  KC_LGUI,
                                                              KC_HOME,
                                               KC_SPC,KC_BSPC,KC_END,
        // right hand
             KC_RGHT,     T6,     T7,      T8,       T9,       T10,                T11,
             TG(SYMB),    KC_Y,   KC_U,    KC_I,     KC_O,     KC_P,               KC_BSLS,
                          KC_H,   MY_J,    MY_K,     MY_L,     KC_SCLN,            KC_QUOT,
             MEH_T(KC_NO),KC_N,   T_ENT,   KC_COMM,  KC_DOT,   KC_SLSH,            KC_RSFT,
                                  KC_UP,   KC_DOWN,  KC_LBRC,  KC_RBRC,            KC_FN1,

             KC_LALT,        CTL_T(KC_ESC),
             KC_PGUP,
             KC_PGDN,KC_TAB, KC_ENT
    ),
/* Keymap 1: Symbol Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |Version  |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | EPRM  |      |      |      |      |                                       |      |    . |   0  |   =  |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |Animat|      |       |Toggle|Solid |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |Bright|Bright|      |       |      |Hue-  |Hue+  |
 *                                 |ness- |ness+ |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = LAYOUT_ergodox(
       // left hand
       VRSN,   KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_TRNS,
       KC_TRNS,KC_EXLM,KC_AT,  KC_LCBR,KC_RCBR,KC_PIPE,KC_TRNS,
       KC_TRNS,KC_HASH,KC_DLR, KC_LPRN,KC_RPRN,KC_GRV,
       KC_TRNS,KC_PERC,KC_CIRC,KC_LBRC,KC_RBRC,KC_TILD,KC_TRNS,
          EPRM,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       RGB_MOD,KC_TRNS,
                                               KC_TRNS,
                               RGB_VAD,RGB_VAI,KC_TRNS,
       // right hand
       KC_TRNS, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
       KC_TRNS, KC_UP,   KC_7,   KC_8,    KC_9,    KC_ASTR, KC_F12,
                KC_DOWN, KC_4,   KC_5,    KC_6,    KC_PLUS, KC_TRNS,
       KC_TRNS, KC_AMPR, KC_1,   KC_2,    KC_3,    KC_BSLS, KC_TRNS,
                         KC_TRNS,KC_DOT,  KC_0,    KC_EQL,  KC_TRNS,
       RGB_TOG, RGB_SLD,
       KC_TRNS,
       KC_TRNS, RGB_HUD, RGB_HUI
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |      |      |      |      |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      | Lclk | Rclk |                                       |VolUp |VolDn | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 |      |      |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MDIA] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_BTN2,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
                          KC_VOLU, KC_VOLD, KC_MUTE, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_WBAK
),

/* Keymap 3: Cursor layer
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      | Home |  Up  | End  |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------| BkSpc| Left | Down | Right| Del  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      | PgUp |      | PgDn |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// CURSOR
[CURS] = LAYOUT_ergodox(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_HOME, KC_UP,   KC_END,  KC_TRNS, KC_TRNS,
                 KC_BSPC, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL,  KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_PGUP, KC_TRNS, KC_PGDN, KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  switch(id) {
    case 0:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      break;
    case 1:
      if (record->event.pressed) { // For resetting EEPROM
        eeconfig_init();
      }
      break;

		case 101:
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
		case 102:
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
		case 103:
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
		case 104:
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
		case 105:
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
		case 106:
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
		case 107:
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
		case 108:
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
		case 109:
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
		case 110:
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
		case 111:
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
		case 112:
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
    case 120:
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
    case 121:
      if (record->event.pressed) {
				key_timer = timer_read();
			}
			else {
				if (timer_elapsed(key_timer) > trigger_time) {
					return MACRO( T(ENT), END );
				}
				else {
					return MACRO( T(M), END );
				}
			}
      break;
    case 122:
      if (record->event.pressed) {
				key_timer = timer_read();
			}
			else {
				if (timer_elapsed(key_timer) > trigger_time) {
					return MACRO( T(ESC), END );
				}
				else {
					return MACRO( T(V), END );
				}
			}
      break;
  }
  return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
      }
      return false;
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
  rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

};

// Runs whenever there is a layer state change.
uint32_t layer_state_set_user(uint32_t state) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  uint8_t layer = biton32(state);
  switch (layer) {
      case 0:
        #ifdef RGBLIGHT_COLOR_LAYER_0
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
        #else
        #ifdef RGBLIGHT_ENABLE
          rgblight_init();
        #endif
        #endif
        break;
      case 1:
        ergodox_right_led_1_on();
        #ifdef RGBLIGHT_COLOR_LAYER_1
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
        #endif
        break;
      case 2:
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_2
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
        #endif
        break;
      case 3:
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_3
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
        #endif
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_4
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
        #endif
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_5
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
        #endif
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_6
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_7
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      default:
        break;
    }

  return state;
};
