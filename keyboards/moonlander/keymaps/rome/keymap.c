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

#define UML(keycode) LT(0, keycode)

static inline void dprint_keycode_event(const char *const context, const uint16_t keycode, const keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    dprintf("%s: keycode=%04x (c,r)=%d,%d pressed=%d tap.count=%d tap.interrupted=%d time=%d\n", context, keycode, record->event.key.col, record->event.key.row, record->event.pressed,
            record->tap.count, record->tap.interrupted, record->event.time);
#endif
}

// mm: mod morph (given key+modifier are replaced with another key+modifier)
enum custom_keycodes
{
    RGB_SLD = ML_SAFE_RANGE,
    mm_bspace_del,
    mm_lbrackets,
    mm_rbrackets,
    M_QUEST_BANG,
    M_LED_RESET,
    M_ITER_LED
};

enum layers
{
    L_COLEMAK_DH = 0,
    L_QWERTZ,
    L_SYM,
    L_MOUSE,
    L_NAV,
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

// TODO: ctrl+z, win+e, calculator
// TODO: bspace and del together (tap: bspace; hold: del; tap-hold to repeat bspace)
// TODO: find out where to put ¨, or ä, ö, ü, é, è
// TODO: Windows ALT-Codes:
//  Ä    Ö    Ü    «    »    ‹    ›     -> faster way:
//  0196 0214 0220 0171 0187 0139 0155

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [L_COLEMAK_DH] = LAYOUT_moonlander(
    KC_ESCAPE,      KC_1,           KC_2,           KC_3,            KC_4,            KC_5,         XXXXXXX,         /**/  XXXXXXX,        KC_6,           KC_7,            KC_8,            KC_9,           KC_0,           KC_DELETE,
    KC_TAB,         KC_Q,           KC_W,           KC_F,            KC_P,            KC_B,         XXXXXXX,         /**/  XXXXXXX,        KC_J,           KC_L,            UML(KC_U),       CH_Y,           mm_bspace_del,  mm_bspace_del,
    CTL_T(KC_ESC),  UML(KC_A),      KC_R,           LT(L_NAV, KC_S), LT(L_SYM, KC_T), KC_G,         XXXXXXX,         /**/  XXXXXXX,        KC_M,           LT(L_SYM, KC_N), LT(L_NAV, KC_E), KC_I,           UML(KC_O),      CTL_T(KC_ENTER),
    KC_LSFT,        CH_Z,           KC_X,           KC_C,            KC_D,            KC_V,                          /**/                  KC_K,           KC_H,            CH_COMM,         CH_DOT,         CH_MINS,        KC_RSFT,
    KC_LCTL,        XXXXXXX,        XXXXXXX,        KC_LWIN,         KC_LALT,                       RESET,           /**/  DEBUG,                          KC_ALGR,         KC_RWIN,         XXXXXXX,        XXXXXXX,        XXXXXXX,
                                                                     CTL_T(KC_SPACE), ALT_T(KC_TAB), TG(L_SYM),      /**/  TG(L_NAV),      mm_bspace_del,  SFT_T(KC_ENTER)
  ),
  [L_QWERTZ] = LAYOUT_moonlander(
    _______,        _______,        _______,        _______,        _______,        _______,        _______,      /**/  _______,        _______,        _______,        _______,        _______,        _______,        _______,
    _______,        _______,        _______,        KC_E,           KC_R,           KC_T,           _______,      /**/  _______,        CH_Y,           KC_U,           KC_I,           KC_O,           KC_P,           _______,
    _______,        _______,        _______,        _______,        KC_F,           _______,        KC_B,         /**/  _______,        KC_H,           KC_J,           KC_K,           KC_L,           M_QUEST_BANG,   _______,
    _______,        _______,        _______,        _______,        _______,        _______,                      /**/                  KC_N,           KC_M,           _______,        _______,        _______,        _______,
    _______,        _______,        _______,        _______,        _______,        _______,                      /**/                  _______,        _______,        _______,        _______,        _______,        _______,
                                                                    _______,        _______,        _______,      /**/  _______,        _______,        _______
  ),
  [L_SYM] = LAYOUT_moonlander( /* TODO: make dead keys direct, ignore modifiers; switch minus underscore, so that shift isnt needed; disable normal keys */
    _______,        KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_F6,        /**/  KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,         KC_F12,         _______,
    _______,        _______,        CH_PIPE,        CH_AMPR,        CH_CIRC,        CH_TILD,        _______,      /**/  _______,        CH_PERC,        CH_EXLM,        CH_LSBR,        CH_RSBR,        CH_QUES,        _______,
    _______,        CH_PLUS,        CH_MINS,        CH_ASTR,        CH_SLSH,        CH_EQL,         _______,      /**/  _______,        CH_QUOT,        CH_EQL,         mm_lbrackets,   mm_rbrackets,   CH_EXLM,        _______,
    _______,        CH_DLR,         CH_AT,          CH_HASH,        CH_BSLS,        ALGR(CH_E),                   /**/                  CH_GRV,         CH_DQUO,        CH_LABR,        CH_RABR,        CH_UNDS,        _______,
    _______,        _______,        _______,        _______,        _______,        _______,                      /**/                  _______,        _______,        _______,        _______,        _______,        _______,
                                                                    _______,        _______,        _______,      /**/  _______,        _______,        _______
  ),
  [L_NAV] = LAYOUT_moonlander(
    _______,        KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_F6,        /**/  KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,         KC_F12,         _______,
    _______,        KC_7,           KC_6,           KC_5,           KC_4,           KC_8,           _______,      /**/  _______,        XXXXXXX,        KC_INSERT,      KC_UP,          mm_bspace_del,  _______,        _______,
    _______,        KC_3,           KC_2,           KC_1,           KC_0,           KC_9,           _______,      /**/  _______,        XXXXXXX,        KC_LEFT,        KC_DOWN,        KC_RIGHT,       KC_TAB,         _______,
    _______,        CH_LRBR,        CH_RRBR,        CH_DOT,         KC_BSPACE,      KC_DEL,                       /**/                  XXXXXXX,        KC_HOME,        KC_END,         KC_PGUP,        KC_PGDOWN,      _______,
    _______,        _______,        _______,        _______,        _______,        _______,                      /**/                  _______,        _______,        _______,        _______,        _______,        _______,
                                                                    _______,        _______,        _______,      /**/  _______,        _______,        _______
  ),
  [L_MOUSE] = LAYOUT_moonlander(
    RGB_TOG,        RGB_MOD,        RGB_RMOD,       _______,        _______,        _______,        _______,      /**/  _______,        _______,        _______,        _______,        _______,        _______,        _______,
    RGB_HUI,        RGB_SAI,        RGB_VAI,        RGB_SPI,        _______,        _______,        _______,      /**/  _______,        XXXXXXX,        XXXXXXX,        KC_MS_UP,       XXXXXXX,        XXXXXXX,        _______,
    RGB_HUD,        RGB_SAD,        RGB_VAD,        RGB_SPD,        _______,        _______,        _______,      /**/  _______,        XXXXXXX,        KC_MS_LEFT,     KC_MS_DOWN,     KC_MS_RIGHT,    KC_MS_ACCEL0,   _______,
    _______,        _______,        _______,        _______,        _______,        _______,                      /**/                  XXXXXXX,        KC_MS_BTN1,     KC_MS_BTN2,     XXXXXXX,        KC_MS_ACCEL1,   _______,
    RGB_M_P,        RGB_M_B,        RGB_M_R,        RGB_M_SW,       _______,        _______,                      /**/                  _______,        _______,        _______,        _______,        _______,        _______,
                                                                    _______,        _______,        _______,      /**/  _______,        _______,        _______
  ),
  [L_SETTINGS] = LAYOUT_moonlander(
    _______,        _______,        _______,        _______,        _______,        M_LED_RESET,    M_ITER_LED,   /**/  _______,        XXXXXXX,        XXXXXXX,        XXXXXXX,        _______,        _______,        _______,
    KC_MEDIA_STOP,KC_MEDIA_PLAY_PAUSE,KC_MS_BTN1,   KC_MS_UP,       KC_MS_BTN2,     _______,        _______,      /**/  _______,        XXXXXXX,        KC_1,           KC_2,           KC_3,           XXXXXXX,        _______,
    KC_BRIGHTNESS_DOWN,KC_BRIGHTNESS_UP,KC_MS_LEFT, KC_MS_DOWN,     KC_MS_RIGHT,    _______,        _______,      /**/  _______,        XXXXXXX,        KC_4,           KC_5,           KC_6,           XXXXXXX,        _______,
    KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,XXXXXXX,      XXXXXXX,        XXXXXXX,        _______,                      /**/                  KC_CALCULATOR,  KC_7,           KC_8,           KC_9,           XXXXXXX,        _______,
    _______,        _______,        KC_MS_ACCEL0,   KC_MS_ACCEL1,   KC_MS_ACCEL2,   _______,                      /**/                  WEBUSB_PAIR,    KC_0,           _______,        _______,        _______,        _______,
                                                                    _______,        _______,        _______,      /**/  _______,        _______,        _______
  ),
};
// clang-format on

// TODO: custom tapping term for umlaut
static uint16_t map_umlaut(uint16_t keycode) {
    switch (keycode) {
        case UML(KC_A): return CH_ADIA;
        case UML(KC_O): return CH_ODIA;
        case UML(KC_U): return CH_UDIA;
    }
    return 0;
}

static bool process_umlaut(uint16_t keycode, keyrecord_t *record) {
    const uint16_t uml = map_umlaut(keycode);
    if (!uml || !record->event.pressed) {
        return false;
    }
    const uint8_t kc = keycode & 0xFF;
    if (record->tap.count) {
        tap_code(kc);
    } else {
        const uint8_t mods = get_mods();
        if (mods == MOD_BIT(KC_LSHIFT)) {
            unregister_mods(mods);
            tap_code16(CH_DIAE);
            register_mods(mods);
            tap_code(kc);
        } else {
            tap_code16(uml);
        }
    }
    return true;
}

typedef struct {
    uint8_t  mod_mask;
    uint16_t normal;
    uint16_t morphed;
} mod_morph_t;

static mod_morph_t map_mod_morph(uint16_t keycode) {
    switch (keycode) {
        case mm_bspace_del: return (mod_morph_t){MOD_BIT(KC_LSHIFT), KC_BSPACE, KC_DEL};
        case mm_lbrackets: return (mod_morph_t){MOD_BIT(KC_LSHIFT), CH_LRBR, CH_LCBR};
        case mm_rbrackets: return (mod_morph_t){MOD_BIT(KC_LSHIFT), CH_RRBR, CH_RCBR};
    }
    return (mod_morph_t){.mod_mask = 0};
}

// TODO: enable repeating
static bool process_mod_morph(uint16_t keycode, keyrecord_t *record) {
    const mod_morph_t mm   = map_mod_morph(keycode);
    if (!mm.mod_mask || !record->event.pressed) {
        return false;
    }
    //static uint16_t   last = 0;
    const uint8_t mods = get_mods();
    if (mods == mm.mod_mask) {
        unregister_mods(mm.mod_mask);
        tap_code16(mm.morphed);
        register_mods(mm.mod_mask);
    } else {
        tap_code16(mm.normal);
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    dprint_keycode_event("process_record_user", keycode, record);
    if (process_umlaut(keycode, record)) {
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
        case M_QUEST_BANG:
            // case KC_A:
            return true;
        case KC_1 ... KC_3:
        case KC_5 ... KC_6:
        case KC_9 ... KC_0:
        case CH_DOT:
            if (layer_state_is(L_SYM)) return true;
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
        case KC_6: return (autoshift_codes_t){KC_6, CH_LRBR};  // '('
        case KC_5: return (autoshift_codes_t){KC_5, CH_RRBR};  // ')'
        case KC_3: return (autoshift_codes_t){KC_3, CH_PLUS};  // '+'
        case KC_2: return (autoshift_codes_t){KC_2, CH_MINS};  // '-'
        case KC_1: return (autoshift_codes_t){KC_1, CH_ASTR};  // '*'
        case KC_0: return (autoshift_codes_t){KC_0, CH_SLSH};  // '/'
        case KC_9: return (autoshift_codes_t){KC_9, KC_ENTER};
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
    [L_COLEMAK_DH] = {{255, 220, 201}, {141, 255, 233}, {255, 220, 201}, {33, 255, 255},  {14, 255, 255},  {HSV_OFF},       {HSV_OFF},      {HSV_OFF},       {HSV_OFF},
                      {HSV_OFF},       {HSV_OFF},       {HSV_OFF},       {HSV_OFF},       {HSV_OFF},       {HSV_OFF},       {HSV_OFF},      {HSV_OFF},       {HSV_OFF},
                      {HSV_OFF},       {HSV_OFF},       {HSV_OFF},       {HSV_OFF},       {105, 255, 255}, {HSV_OFF},       {33, 255, 255}, {HSV_OFF},       {HSV_OFF},
                      {HSV_OFF},       {HSV_OFF},       {HSV_OFF},       {141, 255, 233}, {141, 255, 233}, {105, 255, 255}, {15, 166, 195}, {105, 255, 255}, {HSV_OFF},
                      {14, 255, 255},  {14, 255, 255},  {14, 255, 255},  {14, 255, 255},  {141, 255, 233}, {HSV_OFF},       {14, 255, 255}, {HSV_OFF},       {14, 255, 255},
                      {141, 255, 233}, {HSV_OFF},       {HSV_OFF},       {HSV_OFF},       {14, 255, 255},  {141, 255, 233}, {HSV_OFF},      {HSV_OFF},       {HSV_OFF},
                      {14, 255, 255},  {HSV_OFF},       {HSV_OFF},       {HSV_OFF},       {105, 255, 255}, {HSV_OFF},       {33, 255, 255}, {HSV_OFF},       {HSV_OFF},
                      {HSV_OFF},       {HSV_OFF},       {HSV_OFF},       {141, 255, 233}, {141, 255, 233}, {105, 255, 255}, {33, 255, 255}, {HSV_OFF},       {HSV_OFF}},

    [L_QWERTZ] = {{0} },

    [L_SYM] = {{0}},

    [L_NAV] = {{0}},

    [L_MOUSE] = {{0}},

    [L_SETTINGS] = {{0}},
};

HSV get_layer_color(int layer) {
    switch (layer) {
        case L_COLEMAK_DH: return (HSV){43, 255, 255};
        case L_QWERTZ: return (HSV){43, 127, 255};
        case L_SYM: return (HSV){23, 255, 255};
        case L_MOUSE: return (HSV){120, 255, 255};
        case L_NAV: return (HSV){43, 255, 127};
    }
    return (HSV){HSV_OFF};
}

void set_layer_color(int layer) {
    for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
        HSV hsv = ledmap[layer][i];
        if (!hsv.h && !hsv.s && !hsv.v) {
            // HSV color = get_layer_color(layer);
            // rgb_matrix_set_color(i, color.h, color.s, color.v);
        } else {
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
