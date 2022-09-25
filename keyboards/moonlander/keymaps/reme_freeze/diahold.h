
#pragma once

#include <quantum/action.h>
#include <quantum/action_util.h>
#include <quantum/quantum.h>
#include <quantum/logging/debug.h>
#include <stdint.h>
#include <stdbool.h>

// DIACRITIC HOLD
//   on tap:  taps given letter, modifiers are retained
// adds a given diacritic to a the given letter on on hold action, modifiers are retained

// TODO: fix repeat behavior for when repeat is enabled
typedef struct {
    uint8_t  letter;
    uint16_t diacritic;
} diahold_config_t;

// needs to be implemented in keymap.c
static diahold_config_t map_diahold(uint16_t keycode);

static bool process_diahold(const uint16_t keycode, const keyrecord_t* const record) {
    const diahold_config_t config = map_diahold(keycode);
    if (config.letter == KC_NO) {
        return false;
    }
    if (!record->event.pressed) {
        return true;
    }
    const uint8_t mods                  = get_mods();
    const bool    hold_action           = record->tap.count == 0;
    const bool    non_shift_mods_active = mods & (~MOD_MASK_SHIFT);
    if (hold_action && !non_shift_mods_active) {
        if (mods) {
            unregister_mods(mods);
            tap_code16(config.diacritic);
            register_mods(mods);
        } else {
            tap_code16(config.diacritic);
        }
    }
    tap_code(config.letter);
    return true;
}
