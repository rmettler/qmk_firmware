#include "diahold.h"
#include "taphold_config.h"

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


static inline void dprint_keycode_event(const char *const context, const uint16_t keycode, const keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    dprintf("%s: keycode=%04x (c,r)=%d,%d pressed=%d tap.count=%d tap.interrupted=%d time=%d\n", context, keycode, record->event.key.col, record->event.key.row, record->event.pressed,
            record->tap.count, record->tap.interrupted, record->event.time);
#endif
}

// mm: mod morph (given key+modifier are replaced with another key+modifier)
enum custom_keycodes
{
    dh_a_ae = LT(0, KC_A),
    dh_o_oe = LT(0, KC_O),
    dh_u_ue = LT(0, KC_U),
    RGB_SLD = ML_SAFE_RANGE,
    mm_bspace_del,
    mm_lbrackets,
    mm_rbrackets,
    mm_quest_bang,
    mm_quotes
};

enum layers
{
    L_COLEMAK_DH = 0,
    L_QWERTZ,
    L_SYM_L,
    L_SYM_R,
    L_NUM,
    L_NAV,
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
    [L_COLEMAK_DH] = LAYOUT_moonlander(
        RESET,          XXXXXXX,        XXXXXXX,        XXXXXXX,         XXXXXXX,         XXXXXXX,       XXXXXXX,        /**/  XXXXXXX,        XXXXXXX,        XXXXXXX,          XXXXXXX,         XXXXXXX,        XXXXXXX,             XXXXXXX,
        XXXXXXX,        KC_Q,           KC_W,           KC_F,            KC_P,            KC_B,          XXXXXXX,        /**/  XXXXXXX,        KC_J,           KC_L,             dh_u_ue,         CH_Y,           CH_MINS,             XXXXXXX,
        XXXXXXX,        dh_a_ae,        KC_R,           KC_S,            KC_T,            KC_G,          XXXXXXX,        /**/  XXXXXXX,        KC_M,           KC_N,             KC_E,            KC_I,           dh_o_oe,             XXXXXXX,
        XXXXXXX,        SFT_T(CH_Z),    CTL_T(KC_X),    ALT_T(KC_C),     KC_D,            GUI_T(KC_V),                   /**/                  GUI_T(KC_K),    KC_H,             ALT_T(CH_COMM),  CTL_T(CH_DOT),  SFT_T(CH_QUES),      XXXXXXX,
        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,         LT(L_NAV,KC_ESC),               TG(L_QWERTZ),   /**/  TG(L_SETTINGS),                 LT(L_NUM,KC_DEL), XXXXXXX,         XXXXXXX,        XXXXXXX,             XXXXXXX,
                                                                         LT(L_SYM_R,KC_SPC), LT(L_MOUSE, KC_TAB),XXXXXXX,/**/  XXXXXXX,     LT(L_FUNC,KC_BSPC),LT(L_SYM_L,KC_ENTER)
    ),
    // TODO: add modifier (on thumb?) to toggle numbers with f keys
    // TOCO: maybe shift all columns one to the right (wasd on base position)
    [L_QWERTZ] = LAYOUT_moonlander(
        KC_ESC,         KC_H,           KC_1,           KC_2,           KC_3,           KC_4,           KC_ESC,          /**/  XXXXXXX,        KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_DELETE,
        KC_J,           KC_TAB,         KC_E,           KC_P,           KC_Q,           KC_R,           XXXXXXX,         /**/  XXXXXXX,        CH_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_BACKSPACE,
        KC_LCTL,        KC_A,           KC_S,           KC_W,           KC_D,           KC_F,           XXXXXXX,         /**/  XXXXXXX,        KC_H,           KC_J,           KC_K,           KC_L,           CH_ODIA,        KC_ENTER,
        KC_M,           KC_LSFT,        CH_Z,           KC_X,           KC_C,           KC_V,                            /**/                  KC_N,           KC_M,           CH_COMM,        CH_DOT,         CH_MINS,        KC_RSFT,
        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,                        XXXXXXX,         /**/  XXXXXXX,                        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,        KC_RCTL,
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
    [L_SYM_L] = LAYOUT_moonlander(
        _______,        _______,        _______,        _______,        _______,        _______,        _______,      /**/  _______,        _______,        _______,        _______,        _______,        _______,        _______,
        _______,        CH_DEG,         CH_TILD,        CH_CIRC,        CH_PERC,        KC_GRV,         _______,      /**/  _______,        _______,        _______,        _______,        _______,        _______,        _______,
        _______,        KC_KP_PLUS,     CH_MINS,        CH_ASTR,        CH_SLSH,        CH_HASH,        _______,      /**/  _______,        _______,        _______,        _______,        _______,        _______,        _______,
        _______,        CH_DIAE,        CH_EURO,        CH_DLR,         CH_BSLS,        CH_GRV,                       /**/                  _______,        _______,        _______,        _______,        _______,        _______,
        _______,        _______,        _______,        _______,        _______,                        _______,      /**/  _______,                        _______,        _______,        _______,        _______,        _______,
                                                                        _______,        _______,        _______,      /**/  _______,       _______,         _______
    ),
    [L_SYM_R] = LAYOUT_moonlander(
        _______,        _______,        _______,        _______,        _______,        _______,        _______,      /**/  _______,        _______,        _______,        _______,        _______,        _______,        _______,
        _______,        _______,        _______,        _______,        _______,        _______,        _______,      /**/  _______,        CH_EQL,         CH_AMPR,        CH_LSBR,        CH_RSBR,        CH_EXLM,        _______,
        _______,        _______,        _______,        _______,        _______,        _______,        _______,      /**/  _______,        CH_PIPE,        mm_quotes,      CH_LRBR,        CH_RRBR,        CH_LCBR,        _______,
        _______,        _______,        _______,        _______,        _______,        _______,                      /**/                  CH_ACUT,        CH_AT,          CH_LABR,        CH_RABR,        CH_RCBR,        _______,
        _______,        _______,        _______,        _______,        _______,                        _______,      /**/  _______,                        _______,        _______,        _______,        _______,        _______,
                                                                        _______,        _______,        _______,      /**/  _______,       _______,        _______
    ),
    // TODO: add key to make layer toggled (TG doesn't work, because already in layer. maybe add another layer)
    [L_NUM] = LAYOUT_moonlander(
        _______,        _______,        _______,        _______,        _______,        _______,        _______,      /**/  _______,        _______,        _______,        _______,        _______,        _______,        _______,
        _______,        KC_7,           KC_6,           KC_5,           KC_4,           KC_9,           _______,      /**/  _______,        _______,        _______,        _______,        _______,        _______,        _______,
        _______,        KC_3,           KC_2,           KC_1,           KC_0,           KC_8,           _______,      /**/  _______,        _______,        KC_LEFT,        KC_DOWN,        KC_UP,          KC_RIGHT,       _______,
        _______,        C(CH_Z),        C(KC_X),        C(KC_C),        CH_DOT,         C(KC_V),                      /**/                  _______,        _______,        _______,        _______,        _______,        _______,
        _______,        _______,        _______,        _______,        _______,                        _______,      /**/  _______,                        _______,        _______,        _______,        _______,        _______,
                                                                        _______,        _______,        _______,      /**/  _______,       _______,      _______
    ),
    // TODO: add LEDs for num lock and caps lock
    // TODO: add layer toggle to mouse layer
    [L_NAV] = LAYOUT_moonlander(
        _______,        _______,        _______,        _______,        _______,        _______,        _______,      /**/  _______,        _______,        _______,        _______,        _______,        _______,        _______,
        _______,        _______,        _______,        _______,        _______,        _______,        _______,      /**/  _______,        _______,        KC_HOME,        KC_PGDOWN,      KC_PGUP,        KC_END,         _______,
        _______,        _______,        _______,        _______,        _______,        _______,        _______,      /**/  _______,        _______,        KC_LEFT,        KC_DOWN,        KC_UP,          KC_RIGHT,       _______,
        _______,        _______,        _______,        _______,        _______,        _______,                      /**/                  _______,        _______,        _______,        _______,        _______,        _______,
        _______,        _______,        _______,        _______,        _______,                        _______,      /**/  _______,                        _______,        _______,        _______,        _______,        _______,
                                                                        _______,        _______,        _______,      /**/  _______,       _______,        _______
    ),
    [L_FUNC] = LAYOUT_moonlander(
        _______,        _______,        _______,        _______,        _______,        _______,        _______,      /**/  _______,        _______,        _______,        _______,          _______,      _______,        _______,
        _______,        KC_F7,          KC_F6,          KC_F5,          KC_F4,          KC_F9,          _______,      /**/  _______,        KC_PSCREEN,  KC_BRIGHTNESS_DOWN,KC_BRIGHTNESS_UP, _______,      _______,        _______,
        _______,        KC_F3,          KC_F2,          KC_F1,          KC_F10,         KC_F8,          _______,      /**/  _______,        KC_CALCULATOR,  _______,        _______,          _______,      _______,        _______,
        _______,        _______,        _______,        _______,        KC_F12,         KC_F11,                       /**/                  _______,        _______,        _______,          _______,      _______,        _______,
        _______,        _______,        _______,        _______,        _______,                        _______,      /**/  _______,                        _______,        _______,          _______,      _______,        _______,
                                                                        _______,        _______,        _______,      /**/  _______,       _______,         _______
    ),
    [L_MOUSE] = LAYOUT_moonlander(
        _______,        _______,        _______,        _______,        _______,        _______,        _______,      /**/  _______,        _______,        _______,        _______,        _______,        _______,        _______,
        _______,        KC_MPRV,        KC_MPLY,        KC_MUTE,        KC_MNXT,        KC_VOLU,        _______,      /**/  _______,        _______,        KC_WH_L,        KC_WH_D,        KC_WH_U,        KC_WH_R,        _______,
        _______,        KC_MS_BTN5,     KC_MS_BTN4,     KC_MS_BTN3,     KC_MS_BTN1,     KC_VOLD,        _______,      /**/  _______,        _______,        KC_MS_LEFT,     KC_MS_DOWN,     KC_MS_UP,       KC_MS_RIGHT,    _______,
        _______,        _______,        _______,        _______,        KC_MS_BTN2,     _______,                      /**/                  _______,        _______,        _______,        _______,        _______,        _______,
        _______,        _______,        _______,        _______,        _______,                        _______,      /**/  _______,                        _______,        _______,        _______,        _______,        _______,
                                                                        _______,        _______,        _______,      /**/  _______,       _______,        _______
    ),
    [L_SETTINGS] = LAYOUT_moonlander(
        _______,        _______,        _______,        _______,        _______,        _______,        _______,      /**/  _______,        _______,        _______,        _______,        _______,        _______,        _______,
        _______,        _______,        _______,        _______,        _______,        _______,        _______,      /**/  _______,        _______,        RGB_TOG,        RGB_MOD,        RGB_RMOD,       _______,        _______,
        _______,        _______,        _______,        _______,        _______,        _______,        _______,      /**/  _______,        _______,        RGB_HUI,        RGB_SAI,        RGB_VAI,        RGB_SPI,        _______,
        _______,        _______,        _______,        _______,        _______,        _______,                      /**/                  _______,        RGB_HUD,        RGB_SAD,        RGB_VAD,        RGB_SPD,        _______,
        _______,        _______,        _______,        _______,        _______,                        _______,      /**/  _______,                        RGB_M_P,        RGB_M_B,        RGB_M_R,        RGB_M_SW,       _______,
                                                                        _______,        _______,        _______,      /**/  _______,        _______,       _______
    ),
};
// clang-format on
// clang-format on

static bool is_diahold(const uint16_t keycode) { return (keycode >= dh_a_ae && keycode <= dh_u_ue); }

static bool is_alpha(const uint16_t keycode) { return (keycode >= KC_A && keycode <= KC_Z); }

static bool is_num(const uint16_t keycode) { return (keycode >= KC_1 && keycode <= KC_0) || (keycode >= KC_KP_1 && keycode <= KC_KP_0); }

static bool is_alphanum(const uint16_t keycode) { return is_alpha(keycode) || is_num(keycode); }

static taphold_config_t map_taphold_config(const uint16_t keycode) {
    if (is_diahold(keycode)) {
        return (taphold_config_t){.tapping_term = 150, .repeat_primary = false, .decision_mode = taphold_decision_mode_time_only};
    }
    const uint16_t primary = keycode & 0xFF;
    if (is_alphanum(primary)) {
        return (taphold_config_t){.tapping_term = 150, .repeat_primary = false, .decision_mode = taphold_decision_mode_other_key_tap};
    }
    if (primary == KC_ENTER) {
        return (taphold_config_t){.tapping_term = 150, .repeat_primary = true, .decision_mode = taphold_decision_mode_other_key_press};
    }
    if (primary == KC_SPACE) {
        return (taphold_config_t){.tapping_term = 150, .repeat_primary = true, .decision_mode = taphold_decision_mode_other_key_tap};
    }
    if (primary == KC_TAB) {
        return (taphold_config_t){.tapping_term = 150, .repeat_primary = false, .decision_mode = taphold_decision_mode_other_key_press};
    }
    return (taphold_config_t){.tapping_term = 150, .repeat_primary = false, .decision_mode = taphold_decision_mode_time_only};
}

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
        case mm_bspace_del: return (mod_morph_config_t){MOD_BIT(KC_LALT), KC_BSPACE, KC_DEL};
        case mm_quotes: return (mod_morph_config_t){MOD_BIT(KC_LSHIFT), CH_QUOT, CH_DQUO};
        case mm_quest_bang: return (mod_morph_config_t){MOD_BIT(KC_LSHIFT), CH_QUES, CH_EXLM};
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
    dprint_keycode_event("process_record_user", keycode, record);
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

bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    dprint_keycode_event("get_custom_auto_shifted_key", keycode, record);
    switch (keycode) {
        case KC_2 ... KC_3:
        case KC_5 ... KC_6:
        case KC_9 ... KC_0:
        case CH_DOT:
            if (layer_state_is(L_NUM)) return true;
    }
    return false;
}

typedef struct {
    uint16_t normal;
    uint16_t shifted;
    bool     unhandeled;
} autoshift_codes_t;

autoshift_codes_t map_autshift_codes(const uint16_t keycode) {
    switch (keycode) {
        case KC_6: return (autoshift_codes_t){KC_6, CH_LRBR};      // '('
        case KC_5: return (autoshift_codes_t){KC_5, CH_RRBR};      // ')'
        case KC_3: return (autoshift_codes_t){KC_3, CH_PLUS};      // '+'
        case KC_2: return (autoshift_codes_t){KC_2, CH_MINS};      // '-'
        case KC_0: return (autoshift_codes_t){KC_0, CH_ASTR};      // '*'
        case KC_9: return (autoshift_codes_t){KC_9, CH_SLSH};      // '/'
        case CH_DOT: return (autoshift_codes_t){CH_DOT, CH_COLN};  // ':'
    };
    return (autoshift_codes_t){.unhandeled = true};
}

void autoshift_press_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
    dprint_keycode_event("autoshift_press_user", keycode, record);
    const autoshift_codes_t codes = map_autshift_codes(keycode);
    dprintf("  codes: handeled=%d\n", !codes.unhandeled);
    if (codes.unhandeled) {
        if (shifted) {
            add_weak_mods(MOD_BIT(KC_LSFT));
        }
        register_code16(keycode);
    } else {
        dprintf("  codes: normal=%08x shifted=%08x\n", codes.normal, codes.shifted);
        register_code16((!shifted) ? codes.normal : codes.shifted);
    }
}

void autoshift_release_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
    dprint_keycode_event("autoshift_release_user", keycode, record);
    const autoshift_codes_t codes = map_autshift_codes(keycode);
    if (codes.unhandeled) {
        unregister_code16(keycode);
    } else {
        unregister_code16((!shifted) ? codes.normal : codes.shifted);
    }
}

// Regularly called function, e.g. to check on timers (timer_read(), timer_elapsed()):
// void matrix_scan_user() { }

void keyboard_post_init_user(void) {
    rgb_matrix_enable();
    // debug_enable   = true;
    // debug_keyboard = true;
}

static const HSV PROGMEM ledmap[][DRIVER_LED_TOTAL] = {
    [L_COLEMAK_DH] = {{0}},

    [L_QWERTZ] = {{0}},

    [L_SYM_L] = {{0}},

    [L_SYM_R] = {{0}},

    [L_NAV] = {{0}},

    [L_FUNC] = {{0}},

    [L_NUM] = {{0}},

    [L_MOUSE] = {{0}},

    [L_SETTINGS] = {{0}},
};

static bool hsv_eq(const HSV l, const HSV r) { return l.h == r.h && l.s == r.s && l.v == r.v; }

void set_layer_color(int layer) {
    for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
        HSV hsv = ledmap[1][i];
        if (!hsv_eq(hsv, (HSV){HSV_OFF})) {
            // hsv.v   = (uint32_t)hsv.v * rgb_matrix_get_val() / 255U;  // TODO only do this with a global dim level so that it can be adjusted seperately
            RGB rgb = hsv_to_rgb(hsv);
            // float f   = (float)rgb_matrix_get_val() / 255.f;  TODO
            // rgb_matrix_set_color(i, f * rgb.r, f * rgb.g, f * rgb.b);  TODO
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
}

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (rgb_matrix_get_suspend_state() || keyboard_config.disable_layer_led) {
        return;
    }
    const uint8_t layer = get_highest_layer(layer_state);
    switch (layer) {
        case L_COLEMAK_DH ... L_NAV: set_layer_color(layer); break;  // TODO
        default: break;
    }
}
