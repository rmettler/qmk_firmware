#include "diahold.h"
#include "taphold_config.h"
#include QMK_KEYBOARD_H

#include <keyboards/planck/ez/ez.h>

#include <quantum/version.h>
#include <quantum/keymap_extras/keymap_german_ch.h>
#include <quantum/keymap_extras/sendstring_german_ch.h>

#define CH_LRBR S(CH_8)
#define CH_RRBR S(CH_9)
#define CH_LSBR ALGR(CH_UDIA)
#define CH_RSBR ALGR(CH_DIAE)
#define CH_LABR CH_LABK
#define CH_RABR CH_RABK

static inline void dprint_keycode_event(const char *const context, const uint16_t keycode, const keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    dprintf("%s: keycode=%04x (c,r)=%d,%d pressed=%d tap.count=%d tap.interrupted=%d time=%d\n", context, keycode, record->event.key.col, record->event.key.row, record->event.pressed,
            record->tap.count, record->tap.interrupted, record->event.time);
#endif
}

// mm: mod morph (given key+modifier are replaced with another key+modifier)'"'"?!
enum custom_keycodes
{
    dh_a_ae = LT(0, KC_A),
    dh_o_oe = LT(0, KC_O),
    dh_u_ue = LT(0, KC_U),
    RGB_SLD = EZ_SAFE_RANGE,
    mm_bspace_del,
    mm_lbrackets,
    mm_rbrackets,
    mm_quest_bang,
    mm_quotes,
    M_QUEST_BANG,
    M_LED_RESET,
    M_ITER_LED
};

enum layers
{
    L_COLEMAK_DH = 0,
    L_SYM,
    L_NUM,
    L_NAV,
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
//  Ä    Ö    Ü    «    »    ‹    ›     -> faster way:
//  0196 0214 0220 0171 0187 0139 0155

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [L_COLEMAK_DH] = LAYOUT_planck_grid(
        TG(L_MOUSE),    KC_Q,           KC_W,           KC_F,            KC_P,               KC_B,       /**/ KC_J,            KC_L,            dh_u_ue,         CH_Y,           CH_MINS,        mm_quotes,
        KC_ESC,         dh_a_ae,        KC_R,         LT(L_MOUSE, KC_S), LT(L_NAV, KC_T),    KC_G,       /**/ KC_M,            LT(L_SYM, KC_N), LT(L_NUM, KC_E), KC_I,           dh_o_oe,        KC_BSPC,
        KC_DEL,         CH_Z,           KC_X,           KC_C,            KC_D,               KC_V,       /**/ KC_K,            KC_H,            CH_COMM,         mm_quest_bang,  CH_DOT,         KC_LALT,
        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,         LT(L_SYM, KC_TAB),  CTL_T(KC_SPACE), CTL_T(KC_SPACE), SFT_T(KC_ENTER), KC_LGUI,         XXXXXXX,        XXXXXXX,        TG(L_SETTINGS)
    ),
    [L_SYM] = LAYOUT_planck_grid(
        XXXXXXX,        CH_DEG,         CH_TILD,        CH_CIRC,         CH_PERC,            XXXXXXX,    /**/ XXXXXXX,         CH_AMPR,         CH_LSBR,         CH_RSBR,        CH_PIPE,        _______,
        _______,        KC_KP_PLUS,     CH_MINS,        CH_ASTR,         CH_SLSH,            CH_HASH,    /**/ CH_QUOT,         CH_EQL,          CH_LRBR,         CH_RRBR,        CH_LCBR,        _______,
        _______,        CH_AT,          CH_EURO,        CH_DLR,          CH_BSLS,            CH_GRV,     /**/ CH_ACUT,         CH_DQUO,         CH_LABR,         CH_RABR,        CH_RCBR,        _______,
        XXXXXXX,        _______,        _______,        TO(L_COLEMAK_DH),_______,            _______,         _______,         _______,         _______,         _______,        _______,        _______
    ),
    // TODO: add key to make layer toggled (TG doesn't work, because already in layer. maybe add another layer)
    [L_NUM] = LAYOUT_planck_grid(
        XXXXXXX,        KC_7,           KC_6,           KC_5,           KC_4,           KC_8,            /**/ XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,        _______,
        _______,        KC_3,           KC_2,           LT(L_NAV, KC_1),KC_0,           KC_9,            /**/ XXXXXXX,        KC_LCTL,        _______,        KC_LSFT,        KC_LALT,        _______,
        _______,        C(CH_Z),        C(KC_X),        C(KC_C),        CH_DOT,         C(KC_V),         /**/ XXXXXXX,        KC_LWIN,        XXXXXXX,        XXXXXXX,        XXXXXXX,        _______,
        _______,        C(CH_Y),        _______,        TO(L_COLEMAK_DH),_______,       _______,         /**/ _______,        _______,        _______,        _______,        XXXXXXX,        XXXXXXX
    ),
    // TODO: add LEDs for num lock and caps lock
    // TODO: add layer toggle to mouse layer
    [L_NAV] = LAYOUT_planck_grid(
        XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX,         XXXXXXX,        XXXXXXX,        /**/  KC_PSCREEN,     KC_INSERT,      KC_UP,          XXXXXXX,        XXXXXXX,        _______,
        KC_ESC,         KC_LALT,        KC_LSHIFT,      _______,         KC_BSPACE,      KC_DEL,         /**/  KC_WWW_BACK,    KC_LEFT,        KC_DOWN,        KC_RIGHT,       KC_WWW_FORWARD, _______,
        _______,        C(CH_Z),        XXXXXXX,        XXXXXXX,         WIN_T(KC_ENTER),XXXXXXX,        /**/  KC_BRK,         KC_HOME,        KC_END,         KC_PGUP,        KC_PGDOWN,      XXXXXXX,
        XXXXXXX,        XXXXXXX,        XXXXXXX,        TO(L_COLEMAK_DH),_______,        _______,        /**/  _______,        _______,        _______,        _______,        XXXXXXX,        _______
    ),
    [L_MOUSE] = LAYOUT_planck_grid(
        _______,        _______,        XXXXXXX,        XXXXXXX,        XXXXXXX,         _______,        /**/  XXXXXXX,        KC_WH_U,        KC_MS_UP,       KC_WH_D,        XXXXXXX,        _______,
        _______,        XXXXXXX,        KC_MS_BTN3,     XXXXXXX,        KC_MS_BTN1,      XXXXXXX,        /**/  XXXXXXX,        KC_MS_LEFT,     KC_MS_DOWN,     KC_MS_RIGHT,    KC_MS_ACCEL0,   _______,
        _______,        _______,        XXXXXXX,        XXXXXXX,        KC_MS_BTN2,      _______,        /**/  KC_CALCULATOR,  XXXXXXX,        XXXXXXX,        XXXXXXX,        KC_MS_ACCEL1,   _______,
        XXXXXXX,        _______,        _______,        TO(L_COLEMAK_DH),_______,        _______,        /**/  _______,        _______,        _______,        _______,        XXXXXXX,        XXXXXXX
    ),
    [L_SETTINGS] = LAYOUT_planck_grid(
        KC_MEDIA_STOP,KC_MEDIA_PLAY_PAUSE,KC_MS_BTN1,   KC_MS_UP,        KC_MS_BTN2,     _______,        /**/  XXXXXXX,        RGB_TOG,        RGB_MOD,        RGB_RMOD,       RGB_M_SW,       RESET,
        KC_BRIGHTNESS_DOWN,KC_BRIGHTNESS_UP,KC_MS_LEFT, KC_MS_DOWN,      KC_MS_RIGHT,    _______,        /**/  XXXXXXX,        RGB_HUI,        RGB_SAI,        RGB_VAI,        RGB_SPI,        _______,
        KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,XXXXXXX,      XXXXXXX,         XXXXXXX,        _______,        /**/  XXXXXXX,        RGB_HUD,        RGB_SAD,        RGB_VAD,        RGB_SPD,        _______,
        XXXXXXX,        _______,          _______,      TO(L_COLEMAK_DH),_______,        _______,        /**/  WEBUSB_PAIR,    RGB_M_P,        RGB_M_B,        RGB_M_R,        _______,        XXXXXXX
    ),
};
// clang-format on

static bool is_diahold(const uint16_t keycode) { return (keycode >= dh_a_ae && keycode <= dh_u_ue); }

static bool is_alpha(const uint16_t keycode) { return (keycode >= KC_A && keycode <= KC_Z); }

static bool is_num(const uint16_t keycode) { return (keycode >= KC_1 && keycode <= KC_0) || (keycode >= KC_KP_1 && keycode <= KC_KP_0); }

static bool is_alphanum(const uint16_t keycode) { return is_alpha(keycode) || is_num(keycode); }

static taphold_config_t map_taphold_config(const uint16_t keycode) {
    if (is_diahold(keycode)) {
        return (taphold_config_t){.tapping_term = 200, .repeat_primary = false, .decision_mode = taphold_decision_mode_time_only};
    }
    const uint16_t primary = keycode & 0xFF;
    if (is_alphanum(primary)) {
        return (taphold_config_t){.tapping_term = 300, .repeat_primary = false, .decision_mode = taphold_decision_mode_other_key_tap};
    }
    if (primary == KC_ENTER) {
        return (taphold_config_t){.tapping_term = 175, .repeat_primary = true, .decision_mode = taphold_decision_mode_other_key_press};
    }
    if (primary == KC_SPACE) {
        return (taphold_config_t){.tapping_term = 175, .repeat_primary = true, .decision_mode = taphold_decision_mode_other_key_tap};
    }
    if (primary == KC_TAB) {
        return (taphold_config_t){.tapping_term = 175, .repeat_primary = false, .decision_mode = taphold_decision_mode_other_key_press};
    }
    return (taphold_config_t){.tapping_term = 500, .repeat_primary = false, .decision_mode = taphold_decision_mode_time_only};
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
        case mm_lbrackets: return (mod_morph_config_t){MOD_BIT(KC_LSHIFT), CH_LRBR, CH_LCBR};
        case mm_rbrackets: return (mod_morph_config_t){MOD_BIT(KC_LSHIFT), CH_RRBR, CH_RCBR};
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
    return true;
}

bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    dprint_keycode_event("get_custom_auto_shifted_key", keycode, record);
    switch (keycode) {
        case M_QUEST_BANG:
            // case KC_A:
            return true;
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
        case M_QUEST_BANG: return (autoshift_codes_t){CH_QUES, CH_EXLM};
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
