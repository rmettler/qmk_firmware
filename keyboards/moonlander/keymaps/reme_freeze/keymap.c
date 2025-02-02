#include "diahold.h"
//#include "taphold_config.h"

#include <keyboards/moonlander/moonlander.h>

#include <quantum/version.h>
#include <quantum/keymap_extras/keymap_german_ch.h>
#include <quantum/keymap_extras/sendstring_german_ch.h>

#define CH_LRBR S(CH_8)
#define CH_RRBR S(CH_9)
#define CH_LSBR ALGR(CH_UDIA)
#define CH_RSBR ALGR(CH_DIAE)
#define CH_LABR CH_LABK
#define CH_RABR CH_RABK
#define CH_PND  S(CH_DLR)

// mm: mod morph (given key+modifier are replaced with another key+modifier)
enum custom_keycodes
{
    dh_a_ae = LT(0, KC_A),
    dh_o_oe = LT(0, KC_O),
    dh_u_ue = LT(0, KC_U),
    RGB_SLD = ML_SAFE_RANGE,
    mm_bspace_del,
    mm_quotes,
};

enum layers
{
    L_BASE = 0,
    L_QWERTZ,
    L_SYM,
    L_NUMNAV,
    L_FUNC,
    L_MOUSE,
    L_SETTINGS
};

// TODO: home row mods (shift) might work when using: https://docs.qmk.fm/#/tap_hold
// #define TAPPING_FORCE_HOLD_PER_KEY
// bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {}

// also tune it using:
// #define PERMISSIVE_HOLD_PER_KEY
// or
// #define HOLD_ON_OTHER_KEY_PRESS_PER_KEY

// at least tune the timeout per key

// TODO: combo of both thumb keys -> layer with modifier as sticky keys for complex shortcuts e.g. with
// TODO: ctrl+z, win+e, calculator
// TODO: bspace and del together (tap: bspace; hold: del; tap-hold to repeat bspace)
// TODO: find out where to put ¨, or ä, ö, ü, é, è
// TODO: Windows ALT-Codes:
//  Ä    Ö    Ü    «    »    ‹    ›     -> fsaster way:
//  0196 0214 0220 0171 0187 0139 0155

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [L_BASE] = LAYOUT_moonlander(
        RESET,          XXXXXXX,        XXXXXXX,        XXXXXXX,         XXXXXXX,         XXXXXXX,       XXXXXXX,        /**/  XXXXXXX,        XXXXXXX,        XXXXXXX,          XXXXXXX,         XXXXXXX,        XXXXXXX,             XXXXXXX,
        XXXXXXX,        KC_Q,           KC_W,           KC_F,            KC_P,            KC_B,          XXXXXXX,        /**/  XXXXXXX,        KC_J,           KC_L,             dh_u_ue,         CH_Y,           CH_MINS,             XXXXXXX,
        XXXXXXX,        dh_a_ae,        KC_R,           KC_S,            KC_T,            KC_G,          XXXXXXX,        /**/  XXXXXXX,        KC_M,           KC_N,             KC_E,            KC_I,           dh_o_oe,             XXXXXXX,
        XXXXXXX,        ALT_T(CH_Z),    CTL_T(KC_X),    KC_C,            KC_D,            GUI_T(KC_V),                   /**/                  GUI_T(KC_K),    KC_H,             CH_COMM,         CTL_T(CH_DOT),  ALT_T(CH_QUOT),      XXXXXXX,
        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,         OSM(MOD_LSFT),                  XXXXXXX,        /**/  XXXXXXX,                        KC_ENTER,         XXXXXXX,         XXXXXXX,        XXXXXXX,             XXXXXXX,
                                                                         KC_SPC,          KC_ESC,        XXXXXXX,        /**/  XXXXXXX,        KC_BSPC,        TO(L_SYM)
    ),
    // TODO: add modifier (on thumb?) to toggle numbers with f keys
    // TOCO: maybe shift all columns one to the right (wasd on base position)
    [L_QWERTZ] = LAYOUT_moonlander(
        KC_ESC,         KC_H,           KC_1,           KC_2,           KC_3,           KC_4,           KC_ESC,          /**/  XXXXXXX,        KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_DELETE,
        KC_J,           KC_TAB,         KC_E,           KC_P,           KC_Q,           KC_R,           XXXXXXX,         /**/  XXXXXXX,        CH_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_BACKSPACE,
        KC_LCTL,        KC_A,           KC_S,           KC_W,           KC_D,           KC_F,           XXXXXXX,         /**/  XXXXXXX,        KC_H,           KC_J,           KC_K,           KC_L,           CH_ODIA,        KC_ENTER,
        KC_M,           KC_LSFT,        CH_Z,           KC_X,           KC_C,           KC_V,                            /**/                  KC_N,           KC_M,           CH_COMM,        CH_DOT,         CH_MINS,        KC_RSFT,
        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,                        TO(L_BASE),      /**/  _______,                        TO(L_BASE),     XXXXXXX,        XXXXXXX,        XXXXXXX,        KC_RCTL,
                                                                        KC_SPACE,       KC_LALT,        XXXXXXX,         /**/  XXXXXXX,        XXXXXXX,        XXXXXXX
    ),
    // TODO: as non dead key: grave `, circ ^, tild ~
    // TODO: add double angle brackets to shifted version of <, >
    // TODO: realign symbols (right hand seems ok besides % and disabled keys), make dead keys direct, ignore modifiers; switch minus underscore, so that shift isnt needed; disable normal keys
    //       optimize for common bigrams and trigrams:
    //       text: ´e, =>
    //       c++:  !=, <=, >=, +=, -=, *=, /=, ~=, &=, |=, ^=, (), {}, );, };, )};, ->, /*, */, !(, (", "), (', '), "{, }"
    //       scripts: $(, ${, #(, #{
    //       haskell: >>=, >@>, {-, -}
    //       f#:      (*, *), [<, >], @", <>, |>, ||>, |||>, <|, <||, <|||, :>, :?, :?>, .[, [|, |], <-, (|, |), ~-, ~+, and many more...
    [L_SYM] = LAYOUT_moonlander(
        _______,        _______,        _______,        _______,        _______,        _______,        _______,      /**/  _______,        _______,        _______,        _______,        _______,        _______,        _______,
        _______,        CH_TILD,        CH_HASH,        CH_DLR,         CH_PERC,        _______,        _______,      /**/  _______,        _______,        CH_AT,          CH_LSBR,        CH_RSBR,        CH_DEG,         _______,
        _______,        CH_EQL,         CH_LCBR,        CH_RCBR,        CH_SLSH,        CH_AMPR,        _______,      /**/  _______,        _______,        CH_DQUO,        CH_LRBR,        CH_RRBR,        CH_EXLM,        _______,
        _______,        CH_DIAE,        CH_EURO,        CH_CIRC,        CH_BSLS,        CH_GRV,                       /**/                  CH_ACUT,        CH_PIPE,        CH_LABR,        CH_RABR,        TO(L_FUNC),     _______,
        _______,        _______,        _______,        _______,        _______,                        _______,      /**/  _______,                        _______,        _______,        _______,        _______,        _______,
                                                                        TO(L_BASE),     TO(L_MOUSE),    _______,      /**/  _______,        mm_bspace_del,  TO(L_NUMNAV)
    ),
    // TODO: add key to make layer toggled (TG doesn't work, because already in layer. maybe add another layer) 
    [L_NUMNAV] = LAYOUT_moonlander(
        _______,        _______,        _______,        _______,        _______,        _______,        _______,      /**/  _______,        _______,        _______,        _______,        _______,        _______,        _______,
        _______,        KC_7,           KC_6,           KC_5,           KC_4,           KC_9,           _______,      /**/  _______,        _______,        KC_HOME,        KC_PGDOWN,      KC_PGDOWN,      KC_END,         _______,
        _______,        KC_3,           KC_2,           KC_1,           KC_0,           KC_8,           _______,      /**/  _______,        _______,        KC_LEFT,        KC_DOWN,        KC_UP,          KC_RIGHT,       _______,
        _______,        _______,        _______,        C(KC_C),        C(KC_V),        _______,                      /**/                  _______,        KC_TAB,         _______,        _______,        TO(L_FUNC),     _______,
        _______,        _______,        _______,        _______,        _______,                        _______,      /**/  _______,                        _______,        _______,        _______,        _______,        _______,
                                                                        TO(L_BASE),     _______,        _______,      /**/  _______,        mm_bspace_del,  TO(L_SYM)
    ),
    [L_FUNC] = LAYOUT_moonlander(
        _______,        _______,        _______,        _______,        _______,        _______,        _______,      /**/  _______,        _______,        _______,        _______,          _______,      _______,        _______,
        _______,        KC_F7,          KC_F6,          KC_F5,          KC_F4,          KC_F9,          _______,      /**/  _______,        _______,     KC_BRIGHTNESS_DOWN,KC_BRIGHTNESS_UP, KC_VOLD,      KC_VOLU,        _______,
        _______,        KC_F3,          KC_F2,          KC_F1,          KC_F10,         KC_F8,          _______,      /**/  _______,        _______,        KC_MPRV,        KC_MPLY,          KC_MUTE,      KC_MNXT,        _______,
        _______,        _______,        _______,        _______,        KC_F12,         KC_F11,                       /**/                  _______,        KC_PSCREEN,     KC_CALCULATOR,    TO(L_QWERTZ), TO(L_SETTINGS), _______,
        _______,        _______,        _______,        _______,        _______,                        _______,      /**/  _______,                        _______,        _______,          _______,      _______,        _______,
                                                                        TO(L_BASE),     _______,        _______,      /**/  _______,       _______,         _______
    ),
    [L_MOUSE] = LAYOUT_moonlander(
        _______,        _______,        _______,        _______,        _______,        _______,        _______,      /**/  _______,        _______,        _______,        _______,        _______,        _______,        _______,
        _______,        _______,        _______,        _______,        _______,        _______,        _______,      /**/  _______,        _______,        KC_WH_L,        KC_WH_D,        KC_WH_U,        KC_WH_R,        _______,
        _______,        KC_MS_BTN5,     KC_MS_BTN4,     KC_MS_BTN3,     KC_MS_BTN1,     _______,        _______,      /**/  _______,        _______,        KC_MS_LEFT,     KC_MS_DOWN,     KC_MS_UP,       KC_MS_RIGHT,    _______,
        _______,        _______,        _______,        _______,        KC_MS_BTN2,     _______,                      /**/                  _______,        _______,        _______,        _______,        _______,        _______,
        _______,        _______,        _______,        _______,        _______,                        _______,      /**/  _______,                        _______,        _______,        _______,        _______,        _______,
                                                                        TO(L_BASE),     _______,        _______,      /**/  _______,       _______,         _______
    ),
    [L_SETTINGS] = LAYOUT_moonlander(
        _______,        _______,        _______,        _______,        _______,        _______,        _______,      /**/  _______,        _______,        _______,        _______,        _______,        _______,        _______,
        _______,        _______,        _______,        _______,        _______,        _______,        _______,      /**/  _______,        _______,        RGB_TOG,        RGB_MOD,        RGB_RMOD,       _______,        _______,
        _______,        _______,        _______,        _______,        _______,        _______,        _______,      /**/  _______,        _______,        RGB_HUI,        RGB_SAI,        RGB_VAI,        RGB_SPI,        _______,
        _______,        _______,        _______,        _______,        _______,        _______,                      /**/                  _______,        RGB_HUD,        RGB_SAD,        RGB_VAD,        RGB_SPD,        _______,
        _______,        _______,        _______,        _______,        _______,                        _______,      /**/  _______,                        RGB_M_P,        RGB_M_B,        RGB_M_R,        RGB_M_SW,       _______,
                                                                        TO(L_BASE),     _______,        _______,      /**/  _______,        _______,        _______
    ),
};


static diahold_config_t map_diahold(const uint16_t keycode) {
    switch (keycode) {
        case dh_a_ae: return (diahold_config_t){KC_A, CH_DIAE};
        case dh_o_oe: return (diahold_config_t){KC_O, CH_DIAE};
        case dh_u_ue: return (diahold_config_t){KC_U, CH_DIAE};
    }
    return (diahold_config_t){.letter = KC_NO};
}

typedef struct {
    uint8_t  mod_mask;
    uint16_t normal;
    uint16_t morphed;
} mod_morph_config_t;

static mod_morph_config_t map_mod_morph(uint16_t keycode) {
    switch (keycode) {
        case mm_bspace_del: return (mod_morph_config_t){MOD_BIT(KC_LSHIFT), KC_BSPACE, KC_DEL};
        case mm_quotes: return (mod_morph_config_t){MOD_BIT(KC_LSHIFT), CH_QUOT, CH_DQUO};
    }
    return (mod_morph_config_t){.mod_mask = 0};
}

// TODO: maybe enable repeating
// TODO: modifier not working on morphed keys, e.g. ctrl+shift+del does nothing
static bool process_mod_morph(uint16_t keycode, keyrecord_t *record) {
    const mod_morph_config_t mm = map_mod_morph(keycode);
    if (!mm.mod_mask || !record->event.pressed) {
        return false;
    }
    // static uint16_t   last = 0;
    const uint8_t mods = get_mods();
    if (mods & mm.mod_mask) {
        unregister_mods(mods & mm.mod_mask);
        tap_code16(mm.morphed);
        register_mods(mods & mm.mod_mask);
    } else {
        tap_code16(mm.normal);
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (process_diahold(keycode, record)) {
        return false;
    }
    if (process_mod_morph(keycode, record)) {
        return false;
    }
    switch (keycode) {
        case RGB_SLD:
            if (record->event.pressed) {
                rgblight_mode(1);
            }
            return false;
    }
    return true;
}

// Regularly called function, e.g. to check on timers (timer_read(), timer_elapsed()):
// void matrix_scan_user() { }

extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [L_QWERTZ] = { {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255}, {43,255,255} },

    [L_SYM] = { {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255}, {85,255,255} },

    [L_NUMNAV] = { {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255}, {148,255,255} },

    [L_FUNC] = { {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255}, {127,255,255} },

    [L_MOUSE] = { {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255}, {201,255,255} },

    [L_SETTINGS] = { {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255}, {21,255,255} },
};

void set_layer_color(int layer) {
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb( hsv );
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    }
  }
}

void rgb_matrix_indicators_user(void) {
  if (keyboard_config.disable_layer_led) { return; }
  switch (biton32(layer_state)) {
    case L_QWERTZ:
      set_layer_color(L_QWERTZ);
      break;
    case L_SYM:
      set_layer_color(L_SYM);
      break;
    case L_NUMNAV:
      set_layer_color(L_NUMNAV);
      break;
    case L_FUNC:
      set_layer_color(L_FUNC);
      break;
    case L_MOUSE:
      set_layer_color(L_MOUSE);
      break;
    case L_SETTINGS:
      set_layer_color(L_SETTINGS);
      break;
   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
}
