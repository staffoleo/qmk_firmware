#include "tada68.h"

#define BASE 0
#define FUNL 1 //function keys

#define _______ KC_TRNS

// special keys
#define MY_F MT(MOD_LSFT, KC_F)
#define MY_J MT(MOD_RSFT, KC_J)
#define MY_D MT(MOD_LCTL, KC_D)
#define MY_K MT(MOD_RCTL, KC_K)
#define MY_S MT(MOD_LALT, KC_S)
#define MY_L MT(MOD_RALT, KC_L)
#define MY_E MT(MOD_LGUI, KC_E)
#define MY_I MT(MOD_RGUI, KC_I)
#define MY_SPC LT(FUNL, KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Layer BASE: (Base Layer) Default Layer
   * ,----------------------------------------------------------------------------------------------.
   * |Esc   |   1|    2|    3|    4|    5|    6|    7|    8|    9|    0|    -|    =|  Backsp |  ~ ` |
   * |----------------------------------------------------------------------------------------------|
   * |Tab    |    Q|    W|E/GUI|    R|    T|    Y|    U|I/GUI|    O|    P|    [|    ]|    \  |  Del |
   * |----------------------------------------------------------------------------------------------|
   * |Esc      |    A|S/ALT|D/CTL|F/SFT|    G|    H|J/SFT|K/CTL|L/ALT|    ;|    '|  Return   |  PgUp|
   * |----------------------------------------------------------------------------------------------|
   * |BackSpace |    Z|    X|    C|    V|    B|    N|    M|    ,|    .|    /|  Delete  |   Up|  PgDn|
   * |----------------------------------------------------------------------------------------------|
   * |      |      |      |       Space / Function layer       | CAPS|     |     |  Lef|  Dow|  Rig |
   * `----------------------------------------------------------------------------------------------'
   */
[BASE] = KEYMAP_ANSI(
  KC_ESC ,  KC_1  ,   KC_2 ,   KC_3 ,   KC_4 ,   KC_5 ,   KC_6 ,   KC_7 ,   KC_8 ,   KC_9 ,   KC_0 , KC_MINS, KC_EQL , KC_BSPC,  KC_GRV, \
  KC_TAB ,  KC_Q  ,   KC_W ,   MY_E ,   KC_R ,   KC_T ,   KC_Y ,   KC_U ,   MY_I ,   KC_O ,   KC_P , KC_LBRC, KC_RBRC, KC_BSLS,  KC_DEL, \
  KC_ESC,  KC_A  ,   MY_S ,   MY_D ,   MY_F ,   KC_G ,   KC_H ,   MY_J ,   MY_K ,   MY_L  , KC_SCLN, KC_QUOT,           KC_ENT, KC_PGUP, \
  KC_BSPC,            KC_Z ,   KC_X ,   KC_C ,   KC_V ,   KC_B ,   KC_N ,   KC_M , KC_COMM, KC_DOT , KC_SLSH, KC_DEL ,   KC_UP, KC_PGDN, \
  _______, _______, _______,                MY_SPC                               , KC_CAPS, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT),
  
    /* Layer FUNL: Function Layer
     * ,--------------------------------------------------------------------------------------------.
     * |     | F1  | F2  | F3  | F4  | F5  | F6  | F7  | F8  | F9  | F10 | F11 | F12 |         |    |   
     * |--------------------------------------------------------------------------------------------|
     * |       |     |     |     |     |     |     |     |     |     |     |     |     |       |    |
     * |--------------------------------------------------------------------------------------------|
     * |         |     |     |     |     |     |     |     |     |     |     |     |           |    |
     * |--------------------------------------------------------------------------------------------|
     * |           |     |     |     |     |     |     |      |    |      |    |          |    |    |
     * |--------------------------------------------------------------------------------------------|
     * |      |      |      |                                     |     |     |    |     |     |    |
     * `--------------------------------------------------------------------------------------------'
     */
    [FLAY] = KEYMAP(
  _______,  KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4 ,  KC_F5 ,  KC_F6 ,  KC_F7 ,  KC_F8 ,  KC_F9 , KC_F10 , KC_F11 , KC_F12 , _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
  _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______,                        _______,                       _______, _______, _______, _______, _______, _______),
  };
