#include <keyboards/moonlander/moonlander.h>

#include <quantum/version.h>
#include <quantum/keymap_extras/keymap_german_ch.h>
#include <quantum/keymap_extras/sendstring_german_ch.h>

enum custom_keycodes
{
    RGB_SLD = ML_SAFE_RANGE,
    ST_MACRO_0,
    M_QUEST_BANG,
    M_LED_RESET,
    M_ITER_LED
};

enum layers
{
    L_COLEMAK_DH = 0,
    L_QWERTZ,
    L_SYMBOLS,
    L_MOUSE,
    L_NAV
};
// TODO: ctrl+z, win+e, calculator
// TODO: bspace and del together (tap: bspace; hold: del; tap-hold to repeat bspace)
// TODO: find out where to put ¨, or ä, ö, ü, é, è
// TODO: maybe mod_tap on space with layer shift for äöü€ (maybe $ on (qwertz s), @ on s (qwertz d), % on t (qwertz f), # ond d (qwertz c), &?, |?, =?)
// TODO: Windows ALT-Codes:
//  Ä    Ö    Ü    «    »    ‹    ›     -> faster way:
//  0196 0214 0220 0171 0187 0139 0155

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [L_COLEMAK_DH] = LAYOUT_moonlander(
    KC_ESCAPE,      KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_F6,        /**/  KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,         KC_F12,         KC_DELETE,
    KC_TAB,         KC_Q,           KC_W,           KC_F,           KC_P,           KC_B,           XXXXXXX,      /**/  XXXXXXX,        KC_J,           KC_L,           KC_U,           CH_Y,           M_QUEST_BANG,   KC_BSPACE,
    CTL_T(KC_ESC),  KC_A,           KC_R,           KC_S,           KC_T,           KC_G,           XXXXXXX,      /**/  XXXXXXX,        KC_M,           KC_N,           KC_E,           KC_I,           KC_O,           CTL_T(KC_ENTER),
    KC_LSFT,        CH_Z,           KC_X,           KC_C,           KC_D,           KC_V,                         /**/                  KC_K,           KC_H,           CH_COMM,        CH_DOT,         CH_MINS,        KC_RSFT,
    KC_LCTL,        XXXXXXX,        XXXXXXX,        KC_LWIN,        KC_LALT,                        RESET,        /**/  DEBUG,                          XXXXXXX,        KC_RWIN,        XXXXXXX,        XXXXXXX,        XXXXXXX,
                                                                    SFT_T(KC_SPACE),TT(L_SYMBOLS),  TG(L_NAV),    /**/  TG(L_QWERTZ),   TT(L_MOUSE),    XXXXXXX /*KC_ENTER*/
  ),
  [L_QWERTZ] = LAYOUT_moonlander(
    _______,        _______,        _______,        _______,        _______,        _______,        _______,      /**/  _______,        _______,        _______,        _______,        _______,        _______,        _______,
    _______,        _______,        _______,        KC_E,           KC_R,           KC_T,           _______,      /**/  _______,        CH_Y,           KC_U,           KC_I,           KC_O,           KC_P,           _______,
    _______,        _______,        _______,        _______,        KC_F,           _______,        KC_B,         /**/  _______,        KC_H,           KC_J,           KC_K,           KC_L,           M_QUEST_BANG,   _______,
    _______,        _______,        _______,        _______,        _______,        _______,                      /**/                  KC_N,           KC_M,           _______,        _______,        _______,        _______,
    _______,        _______,        _______,        _______,        _______,        _______,                      /**/                  _______,        _______,        _______,        _______,        _______,        _______,
                                                                    _______,        _______,        _______,      /**/  _______,        _______,        _______
  ),
  [L_SYMBOLS] = LAYOUT_moonlander(
    _______,        _______,        _______,        _______,        _______,        _______,        _______,      /**/   _______,        _______,        _______,        _______,        _______,        _______,        _______,
    _______,        KC_7,           KC_6,           KC_5,           KC_4,           KC_8,           _______,      /**/   _______,        XXXXXXX,        KC_INSERT,      KC_UP,          KC_DEL,         XXXXXXX,        _______,
    _______,        KC_3,           KC_2,           KC_1,           KC_0,           KC_9,           _______,      /**/   _______,        XXXXXXX,        KC_LEFT,        KC_DOWN,        KC_RIGHT,       KC_PGUP,        _______,
    _______,        XXXXXXX,        XXXXXXX,        XXXXXXX,        CH_DOT,         KC_BSPACE,                    /**/                   XXXXXXX,        KC_HOME,        KC_END,         XXXXXXX,        KC_PGDOWN,      _______,
    _______,        _______,        _______,        _______,        _______,        _______,                      /**/                   _______,        _______,        _______,        _______,        _______,        _______,
                                                                    _______,        _______,        _______,      /**/   _______,        _______,        _______
  ),
  [L_MOUSE] = LAYOUT_moonlander(
    RGB_TOG,        RGB_MOD,        RGB_RMOD,       _______,        _______,        _______,        _______,      /**/   _______,        _______,        _______,        _______,        _______,        _______,        _______,
    RGB_HUI,        RGB_SAI,        RGB_VAI,        RGB_SPI,        _______,        _______,        _______,      /**/   _______,        XXXXXXX,        XXXXXXX,        KC_MS_UP,       XXXXXXX,        XXXXXXX,        _______,
    RGB_HUD,        RGB_SAD,        RGB_VAD,        RGB_SPD,        _______,        _______,        _______,      /**/   _______,        XXXXXXX,        KC_MS_LEFT,     KC_MS_DOWN,     KC_MS_RIGHT,    KC_MS_ACCEL0,   _______,
    _______,        _______,        _______,        _______,        _______,        _______,                      /**/                   XXXXXXX,        KC_MS_BTN1,     KC_MS_BTN2,     XXXXXXX,        KC_MS_ACCEL1,   _______,
    RGB_M_P,        RGB_M_B,        RGB_M_R,        RGB_M_SW,       _______,        _______,                      /**/                   _______,        _______,        _______,        _______,        _______,        _______,
                                                                    _______,        _______,        _______,      /**/   _______,        _______,        _______
  ),
  [L_NAV] = LAYOUT_moonlander(
    _______,        _______,        _______,        _______,        _______,        M_LED_RESET,    M_ITER_LED,   /**/  TO(3),          XXXXXXX,        XXXXXXX,        XXXXXXX,        ST_MACRO_0,     _______,        _______,
    KC_MEDIA_STOP,KC_MEDIA_PLAY_PAUSE,KC_MS_BTN1,   KC_MS_UP,       KC_MS_BTN2,     _______,        _______,      /**/  _______,        XXXXXXX,        KC_1,           KC_2,           KC_3,           XXXXXXX,        _______,
    KC_BRIGHTNESS_DOWN,KC_BRIGHTNESS_UP,KC_MS_LEFT, KC_MS_DOWN,     KC_MS_RIGHT,    _______,        _______,      /**/  XXXXXXX,        XXXXXXX,        KC_4,           KC_5,           KC_6,           XXXXXXX,        _______,
    KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,XXXXXXX,      XXXXXXX,        XXXXXXX,        _______,                      /**/                  KC_CALCULATOR,  KC_7,           KC_8,           KC_9,           XXXXXXX,        _______,
    _______,        _______,        KC_MS_ACCEL0,   KC_MS_ACCEL1,   KC_MS_ACCEL2,   _______,                      /**/                  WEBUSB_PAIR,    KC_0,           _______,        _______,        _______,        _______,
                                                                    _______,        _______,        _______,      /**/  _______,        _______,        _______
  ),
};
// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    dprintf("process_record_user: keycode=%08x pressed=%d tap.count=%d tap.interrupted=%d time=%d\n", keycode, record->event.pressed, record->tap.count, record->tap.interrupted, record->event.time);
    switch (keycode) {
        case CTL_T(CH_DQUO):
            // Workaround because mod-tap does not work with shifted keys
            if (record->tap.count && record->event.pressed) {
                tap_code16(CH_DQUO);
                return false;
            }
            return true;
        case ST_MACRO_0:
            if (record->event.pressed) {
                SEND_STRING(SS_LGUI(SS_TAP(X_X)) SS_DELAY(100) SS_TAP(X_U) SS_DELAY(100) SS_TAP(X_S));
            }
            return true;
        case RGB_SLD:
            if (record->event.pressed) {
                rgblight_mode(1);
            }
            return false;
    }
    return true;
}

bool get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record) {
    dprintf("get_custom_auto_shifted_key: keycode=%08x pressed=%d tap.count=%d tap.interrupted=%d\n", keycode, record->event.pressed, record->tap.count, record->tap.interrupted);
    switch (keycode) {
        // case KC_BSPACE:
        case M_QUEST_BANG:
        case KC_4 ... KC_7: return true;
    }
    return false;
}

// uint16_t get_autoshift_timeout(uint16_t keycode, keyrecord_t *record) {
//     switch (keycode) {
//         case AUTO_SHIFT_NUMERIC:
//         case AUTO_SHIFT_SPECIAL:
//         case AUTO_SHIFT_ALPHA:
//         default:
//             return get_generic_autoshift_timeout();
//     }
// }

typedef struct {
    uint16_t normal;
    uint16_t shifted;
    bool     unhandeled;
} autoshift_codes_t;

autoshift_codes_t map_autshift_codes(const uint16_t keycode) {
    switch (keycode) {
        // case KC_BSPACE: return (autoshift_codes_t){KC_BSPACE, KC_DELETE};
        case M_QUEST_BANG: return (autoshift_codes_t){CH_QUES, CH_EXLM};
        case KC_7: return (autoshift_codes_t){KC_7, CH_SLSH};  // '/'
        case KC_6: return (autoshift_codes_t){KC_6, CH_ASTR};  // '*'
        case KC_5: return (autoshift_codes_t){KC_5, CH_MINS};  // '-'
        case KC_4: return (autoshift_codes_t){KC_4, CH_PLUS};  // '+'
    };
    return (autoshift_codes_t){.unhandeled = true};
}

void autoshift_press_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
    dprintf("autoshift_press_user: keycode=%08x pressed=%d tap.count=%d tap.interrupted=%d\n", keycode, record->event.pressed, record->tap.count, record->tap.interrupted);
    const autoshift_codes_t codes = map_autshift_codes(keycode);
    dprintf("  codes: handeled=%d\n", !codes.unhandeled);
    if (codes.unhandeled) {
        if (shifted) {
            add_weak_mods(MOD_BIT(KC_LSFT));
        }
        // & 0xFF gets the Tap key for Tap Holds, required when using Retro Shift
        // register_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode); COMPILE ERROR
        register_code16(keycode);
    } else {
        dprintf("  codes: normal=%08x shifted=%08x\n", codes.normal, codes.shifted);
        register_code16((!shifted) ? codes.normal : codes.shifted);
    }
}

void autoshift_release_user(uint16_t keycode, bool shifted, keyrecord_t *record) {
    dprintf("autoshift_release_user: keycode=%08x pressed=%d tap.count=%d tap.interrupted=%d\n", keycode, record->event.pressed, record->tap.count, record->tap.interrupted);
    const autoshift_codes_t codes = map_autshift_codes(keycode);
    if (codes.unhandeled) {
        // & 0xFF gets the Tap key for Tap Holds, required when using Retro Shift
        // The IS_RETRO check isn't really necessary here, always using
        // keycode & 0xFF would be fine.
        // unregister_code16((IS_RETRO(keycode)) ? keycode & 0xFF : keycode); COMPILE ERROR
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

    [L_QWERTZ] = {{255, 220, 201}, {141, 255, 233}, {255, 220, 201}, {33, 255, 255},  {14, 255, 255},  {105, 255, 255}, {105, 255, 255}, {105, 255, 255}, {105, 255, 255},
                  {14, 255, 255},  {105, 255, 255}, {105, 255, 255}, {105, 255, 255}, {105, 255, 255}, {33, 255, 255},  {105, 255, 255}, {105, 255, 255}, {105, 255, 255},
                  {105, 255, 255}, {33, 255, 255},  {105, 255, 255}, {105, 255, 255}, {0, 0, 255},     {105, 255, 255}, {33, 255, 255},  {105, 255, 255}, {105, 255, 255},
                  {105, 255, 255}, {105, 255, 255}, {255, 220, 201}, {141, 255, 233}, {141, 255, 233}, {105, 255, 255}, {15, 166, 195},  {105, 255, 255}, {HSV_OFF},
                  {14, 255, 255},  {14, 255, 255},  {14, 255, 255},  {141, 255, 233}, {141, 255, 233}, {105, 255, 255}, {105, 255, 255}, {14, 255, 255},  {14, 255, 255},
                  {141, 255, 233}, {105, 255, 255}, {105, 255, 255}, {105, 255, 255}, {14, 255, 255},  {141, 255, 233}, {105, 255, 255}, {105, 255, 255}, {105, 255, 255},
                  {14, 255, 255},  {14, 255, 255},  {105, 255, 255}, {105, 255, 255}, {0, 0, 255},     {105, 255, 255}, {33, 255, 255},  {105, 255, 255}, {105, 255, 255},
                  {105, 255, 255}, {105, 255, 255}, {15, 166, 195},  {141, 255, 233}, {141, 255, 233}, {105, 255, 255}, {33, 255, 255},  {33, 255, 255},  {255, 220, 201}},

    [L_SYMBOLS] = {{HSV_OFF},      {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},      {HSV_OFF},      {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},      {HSV_OFF},
                   {HSV_OFF},      {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},      {HSV_OFF},      {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},      {HSV_OFF},
                   {HSV_OFF},      {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},      {HSV_OFF},      {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},      {HSV_OFF},
                   {HSV_OFF},      {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},      {HSV_OFF},      {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},      {HSV_OFF},
                   {15, 166, 195}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {15, 166, 195}, {15, 166, 195}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {15, 166, 195}, {HSV_OFF},
                   {HSV_OFF},      {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},      {HSV_OFF},      {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF}, {HSV_OFF},      {HSV_OFF}},

    [L_MOUSE] = {{0}},

    [L_NAV] = {{HSV_OFF},       {255, 220, 201}, {33, 255, 255},  {141, 255, 233}, {HSV_OFF},       {HSV_OFF},       {255, 220, 201}, {33, 255, 255},  {141, 255, 233}, {HSV_OFF},      {HSV_OFF},
               {HSV_OFF},       {105, 255, 255}, {HSV_OFF},       {105, 255, 255}, {HSV_OFF},       {105, 255, 255}, {105, 255, 255}, {HSV_OFF},       {33, 255, 255},  {HSV_OFF},      {HSV_OFF},
               {105, 255, 255}, {HSV_OFF},       {255, 220, 201}, {HSV_OFF},       {HSV_OFF},       {HSV_OFF},       {HSV_OFF},       {HSV_OFF},       {HSV_OFF},       {HSV_OFF},      {HSV_OFF},
               {HSV_OFF},       {HSV_OFF},       {HSV_OFF},       {HSV_OFF},       {HSV_OFF},       {HSV_OFF},       {HSV_OFF},       {105, 255, 255}, {33, 255, 255},  {HSV_OFF},      {HSV_OFF},
               {HSV_OFF},       {105, 255, 255}, {105, 255, 255}, {141, 255, 233}, {141, 255, 233}, {141, 255, 233}, {105, 255, 255}, {HSV_OFF},       {141, 255, 233}, {HSV_OFF},      {141, 255, 233},
               {105, 255, 255}, {HSV_OFF},       {141, 255, 233}, {141, 255, 233}, {141, 255, 233}, {141, 255, 233}, {HSV_OFF},       {HSV_OFF},       {HSV_OFF},       {33, 255, 255}, {15, 166, 195},
               {HSV_OFF},       {HSV_OFF},       {105, 255, 255}, {HSV_OFF},       {HSV_OFF},       {255, 220, 201}},

};

HSV get_layer_color(int layer) {
    switch (layer) {
        case L_COLEMAK_DH: return (HSV){43, 255, 255};
        case L_QWERTZ: return (HSV){43, 127, 255};
        case L_SYMBOLS: return (HSV){23, 255, 255};
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
            //hsv.v   = (uint32_t)hsv.v * rgb_matrix_get_val() / 255U;  // TODO only do this with a global dim level so that it can be adjusted seperately
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
        default:
            break;
    }
}
