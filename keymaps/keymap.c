#include QMK_KEYBOARD_H
#include "version.h"

#define BASE 0 // default layer (colemak layout)
#define QWER 1 // qwerty layout
#define FUNC 2 // function layer
#define STEN 3 // stenography
#define EMOJ 4 // emoji

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

enum custom_keycodes {
#ifdef ORYX_CONFIGURATOR
  EPRM = EZ_SAFE_RANGE,
#else
  EPRM = SAFE_RANGE,
#endif
  VRSN,
  PTPASTE = SAFE_RANGE,
  ALT_TAB = SAFE_RANGE,
  RGB_SLD
};

enum unicode_names {
  HRTEYES,
  WINK,
  BEG,
  BLUSH,
  SMIRK,
  ROLLEYES,
  MONOC,
  CRYING,
  UGH,
  HMM,
  SWEAT,
  NAILS,
  FIRE,
  HEART,
  SHRUG
  UPSDOWN,
  PRAY,
  WAVE,
  THUP,
  EYES
};

const uint32_t PROGMEM unicode_map[] = {
  [HRTEYES] = 0x1F60D,
  [WINK] = 0x1F609,
  [BEG] = 0x1F97A,
  [BLUSH] = 0x1F633,
  [SMIRK] = 0x1F60F,
  [ROLLEYES] = 0x1F644,
  [MONOC] = 0x1F9D0,
  [CRYING] = 0x1F62D,
  [UGH] = 0x1F612,
  [HMM] = 0x1F914,
  [SWEAT] = 0x1F605,
  [NAILS] = 0x1F485,
  [FIRE] = 0x1F525,
  [HEART] = 0xFE0F,
  [SHRUG] = 0x1F937
  [UPSDOWN] = 0x1F643,
  [PRAY] = 0x1F64F,
  [WAVE] = 0x1F44B,
  [THUP] = 0x1F44D,
  [EYES] = 0x1F440
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Default layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Esc/Fn |   1  |   2  |   3  |   4  |   5  |  6   |           |  Fn  |   7  |   8  |   9  |   0  |   -  |  LOCK  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   F  |   P  |   G  |  {   |           |  }   |   J  |   L  |   U  |   Y  |  :/; |  "  '  |
 * |--------+------+------+------+------+------|  [   |           |  ]   |------+------+------+------+------+--------|
 * | Cmd    |   A  |   R  |   S  |   T  |   D  |------|           |------|   H  |   N  |   E  |   I  |   O  |  ?  /  |
 * |--------+------+------+------+------+------|  (   |           |  )   |------+------+------+------+------+--------|
 * | Steno  |   Z  |   X  |   C  |   V  |   B  |      |           |      |   K  |   M  |   ,  |   .  |  Up  | ` Shft |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | <Tab | >Tab |QWERTY| Ctrl | Optn |                                       | | \  | + =  | Left | Down | Right|
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        | Emoji| 1P   |       | Mac1 | Macro2 |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |PTPast|       |AltTab|        |      |
 *                                 | Shift|Enter |------|       |------|Backspce| Space|
 *                                 |      |      |PMenu |       |Locale|        |      |
 *                                 `--------------------'       `----------------------'
 */
[BASE] = LAYOUT_ergodox(
  // left hand
  LT(FUNC, KC_ESC),    KC_1,             KC_2,         KC_3,        KC_4,         KC_5,         KC_6,
  KC_TAB,              KC_Q,             KC_W,         KC_F,        KC_P,         KC_G,         KC_LBRACKET,
  KC_LCMD,             KC_A,             KC_R,         KC_S,        KC_T,         KC_D,
  TG(STEN),            KC_Z,             KC_X,         KC_C,        KC_V,         KC_B,         KC_LEFT_PAREN,
  LCMD(KC_LBRC),       LCMD(KC_RBRC),    TG(QWER),     KC_LCTRL,    KC_LOPT,
                                                                                  MO(EMOJ),     LCMD(KC_BSLASH),
                                                                                                PTPASTE,
                                                                    KC_LSHIFT,    KC_ENTER,     LCMD(LOPT(KC_V)),
  // right hand
  TG(FUNC),            KC_7,             KC_8,         KC_9,        KC_0,         KC_MINUS,     LCMD(LCTL(KC_Q)),
  KC_RBRACKET,         KC_J,             KC_L,         KC_U,        KC_Y,         KC_SCOLON,    KC_QUOTE,
                       KC_H,             KC_N,         KC_E,        KC_I,         KC_O,         KC_SLASH,
  KC_RIGHT_PAREN,      KC_K,             KC_M,         KC_COMM,     KC_DOT,       KC_UP,        RSFT_T(KC_GRAVE),
                                         KC_BSLASH,    KC_EQUAL,    KC_LEFT,      KC_DOWN,      KC_RIGHT,
  DYN_MACRO_PLAY1,     DYN_MACRO_PLAY2,
  ALT_TAB,
  LCMD(KC_SLASH),      KC_BSPACE,        KC_SPACE
),
/* Keymap 1: QWERTY Layer
*
* ,--------------------------------------------------.           ,--------------------------------------------------.
* |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
* |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
* |        |   Q  |   W  |   E  |   R  |   T  |      |           |      |   Y  |   U  |   I  |   O  |  P   |        |
* |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
* |        |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  | :  ; |        |
* |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
* |  Shift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  | ?  / | Shift  |
* `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
*   |      |      |QWERTY|      |      |                                       |      |      |      |      |      |
*   `----------------------------------'                                       `----------------------------------'
*                                        ,-------------.       ,---------------.
*                                        |      |      |       |      |        |
*                                 ,------|------|------|       |------+--------+------.
*                                 |      |      |      |       |      |        |      |
*                                 |      |      |------|       |------|        |      |
*                                 |      |      |      |       |      |        |      |
*                                 `--------------------'       `----------------------'
 */
[QWER] = LAYOUT_ergodox(
  // left hand
  KC_TRNS,      KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,      KC_TRNS,
  KC_TRNS,      KC_Q,       KC_W,       KC_E,       KC_R,       KC_T,         KC_TRNS,
  KC_TRNS,      KC_A,       KC_S,       KC_D,       KC_F,       KC_G,
  KC_LSHIFT,    KC_Z,       KC_X,       KC_C,       KC_V,       KC_B,         KC_TRNS,
  KC_TRNS,      KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                                                                KC_TRNS,      KC_TRNS,
                                                                              KC_TRNS,
                                                    KC_TRNS,    KC_TRNS,      KC_TRNS,
  // right hand
  KC_TRNS,      KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,      KC_TRNS,
  KC_TRNS,      KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,         KC_TRNS,
                KC_H,       KC_J,       KC_K,       KC_L,       KC_SCOLON,    KC_TRNS,
  KC_TRNS,      KC_N,       KC_M,       KC_COMM,    KC_DOT,     KC_SLASH,     KC_RSHIFT,
                            KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,      KC_TRNS,
  KC_TRNS,      KC_TRNS,
  KC_TRNS,
  KC_TRNS,      KC_TRNS,    KC_TRNS
),
/* Keymap 2: Function keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | Esc/Fn | Brt- | Brt+ |Expose|KBrt- |KBrt+ | Mute |           |  Fn  | Vol- | Vol+ | Prev | Play | Next |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
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
[FUNC] = LAYOUT_ergodox(
  // left hand
  KC_TRNS,     KC_BRID,        KC_BRIU,      C(KC_UP),    KC_BRMD,    KC_BRMU,     KC__MUTE,
  KC_TRNS,     KC_TRNS,        KC_TRNS,      KC_TRNS,     KC_TRNS,    KC_TRNS,     KC_TRNS,
  KC_TRNS,     KC_TRNS,        KC_TRNS,      KC_TRNS,     KC_TRNS,    KC_TRNS,
  KC_TRNS,     KC_TRNS,        KC_TRNS,      KC_TRNS,     KC_TRNS,    KC_TRNS,     KC_TRNS,
  KC_TRNS,     KC_TRNS,        KC_TRNS,      KC_TRNS,     KC_TRNS,
                                                                      KC_TRNS,     KC_TRNS,
                                                                                   KC_TRNS,
                                                          KC_TRNS,    KC_TRNS,     KC_TRNS,
  // right hand
  KC_TRNS,     KC__VOLDOWN,    KC__VOLUP,    KC_MRWD,     KC_MPLY,    KC_MFFD,     KC_TRNS,
  KC_TRNS,     KC_TRNS,        KC_TRNS,      KC_TRNS,     KC_TRNS,    KC_TRNS,     KC_TRNS,
               KC_TRNS,        KC_TRNS,      KC_TRNS,     KC_TRNS,    KC_TRNS,     KC_TRNS,
  KC_TRNS,     KC_TRNS,        KC_TRNS,      KC_TRNS,     KC_TRNS,    KC_TRNS,     KC_TRNS,
                               KC_TRNS,      KC_TRNS,     KC_TRNS,    KC_TRNS,     KC_TRNS,
  KC_TRNS,     KC_TRNS,
  KC_TRNS,
  KC_TRNS,     KC_TRNS,        KC_TRNS
),
/* Keymap 3: Stenography
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |  #   |  #   |  #   |  #   |  *   |           |  *   |  #   |  #   |  #   |  #   |  #   |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |  S   |  T   |  P   |  H   |------|           |------|  F   |  P   |  L   |  T   |  D   |        |
 * |--------+------+------+------+------+------|  *   |           |  *   |------+------+------+------+------+--------|
 * | Steno  |      |  S   |  K   |  W   |  R   |      |           |      |  R   |  B   |  G   |  S   |  Z   |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |  A   |  O   |------|       |------|  E   |  U   |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[STEN] = LAYOUT_ergodox(
  // left hand
  KC_TRNS,      KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,     KC_TRNS,
  KC_TRNS,      KC_TRNS,    STN_N1,     STN_N2,     STN_N3,     STN_N4,      STN_ST1,
  KC_TRNS,      KC_TRNS,    STN_S1,     STN_TL,     STN_PL,     STN_HL,
  KC_TRNS,      KC_TRNS,    STN_S2,     STN_KL,     STN_WL,     STN_RL,      STN_ST2,
  KC_TRNS,      KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                                                                KC_TRNS,     KC_TRNS,
                                                                             KC_TRNS,
                                                    STN_A,      STN_O,       KC_TRNS,
  // right hand
  KC_TRNS,      KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,     KC_TRNS,
  STN_ST3,      STN_N5,     STN_N6,     STN_N7,     STN_N8,     STN_N9,      KC_TRNS,
                SFN_FR,     STN_PR,     STN_LR,     STN_TR,     STN_DR,      KC_TRNS,
  STN_ST4,      STN_RR,     STN_BR,     STN_GR,     STN_SR,     STN_ZR,      KC_TRNS,
                            KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,     KC_TRNS,
  KC_TRNS,      KC_TRNS,
  KC_TRNS,
  KC_TRNS,      STN_E,      STN_U
),
/* Keymap 4: Emoji
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |  😍  |  😉  |  🥺  |  😳 |  😏  |------|           |------|  😅  |  💅  |  🔥  | ❤️  |  🤷🏻‍  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |  🙄  |  🧐  |  😭  |  😒  |  🤔 |      |           |      |  🙃  |  🙏  |  👋  |  👍 |  👀  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |Emoji |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[EMOJ] = LAYOUT_ergodox(
  // left hand
  KC_TRNS,     KC_TRNS,        KC_TRNS,      KC_TRNS,     KC_TRNS,    KC_TRNS,     KC_TRNS,
  KC_TRNS,     KC_TRNS,        KC_TRNS,      KC_TRNS,     KC_TRNS,    KC_TRNS,     KC_TRNS,
  KC_TRNS,     X(HRTEYES),     X(WINK),      X(BEG),      X(BLUSH),   X(SMIRK),
  KC_TRNS,     X(ROLLEYES),    X(MONOC),     X(CRYING),   X(UGH),     X(HMM),      KC_TRNS,
  KC_TRNS,     KC_TRNS,        KC_TRNS,      KC_TRNS,     KC_TRNS,
                                                                      KC_TRNS,     KC_TRNS,
                                                                                   KC_TRNS,
                                                          KC_TRNS,    KC_TRNS,     KC_TRNS,
  // right hand
  KC_TRNS,     KC_TRNS,        KC_TRNS,      KC_TRNS,     KC_TRNS,    KC_TRNS,     KC_TRNS,
  KC_TRNS,     KC_TRNS,        KC_TRNS,      KC_TRNS,     KC_TRNS,    KC_TRNS,     KC_TRNS,
               X(SWEAT),       X(NAILS),     X(FIRE),     X(HEART),   X(SHRUG),    KC_TRNS,
  KC_TRNS,     X(UPSDOWN),     X(PRAY),      X(WAVE),     X(THUP),    X(EYES),     KC_TRNS,
                               KC_TRNS,      KC_TRNS,     KC_TRNS,    KC_TRNS,     KC_TRNS,
  KC_TRNS,     KC_TRNS,
  KC_TRNS,
  KC_TRNS,     KC_TRNS,        KC_TRNS
),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
      case PTPASTE:
        SEND_STRING (",.");
        return false;
      case EPRM:
        eeconfig_init();
        return false;
      case VRSN:
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        return false;
      #ifdef RGBLIGHT_ENABLE
      case RGB_SLD:
        rgblight_mode(1);
        return false;
      #endif
    }
  }
  return true;
}

// Super alt-tab
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
  }
  return true;
}
void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
  rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

// Runs whenever there is a layer state change.
layer_state_t layer_state_set_user(layer_state_t state) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  uint8_t layer = get_highest_layer(state);
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
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_7);
        #endif
        break;
      default:
        break;
    }

  return state;
};
