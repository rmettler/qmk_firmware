#pragma once

// TAP-HOLD PER KEY CONFIGURATION
// Simplified per key configuration of the QMK tap-hold function.
// The defines as specified by QMK must be defined in the config.h

#include <quantum/quantum.h>
#include <stdint.h>
#include <stdbool.h>

typedef enum
{
    taphold_decision_mode_time_only,
    taphold_decision_mode_other_key_tap,
    taphold_decision_mode_other_key_press
} taphold_decision_mode;

typedef struct {
    uint16_t              tapping_term;
    bool                  repeat_primary;
    taphold_decision_mode decision_mode;
} taphold_config_t;

static taphold_config_t map_taphold_config(uint16_t keycode);

uint16_t get_tapping_term(const uint16_t keycode, keyrecord_t *const record) {
    const taphold_config_t config = map_taphold_config(keycode);
    return config.tapping_term;
}

bool get_tapping_force_hold(const uint16_t keycode, keyrecord_t *const record) {
    const taphold_config_t config = map_taphold_config(keycode);
    dprintf("get_tapping_force_hold %d\n", !config.repeat_primary);
    return !config.repeat_primary;
}

bool get_permissive_hold(const uint16_t keycode, keyrecord_t *const record) {
    const taphold_config_t config = map_taphold_config(keycode);
    dprintf("get_permissive_hold %d\n", config.decision_mode);
    return config.decision_mode == taphold_decision_mode_other_key_tap || config.decision_mode == taphold_decision_mode_other_key_press;
}

bool get_hold_on_other_key_press(const uint16_t keycode, keyrecord_t *const record) {
    const taphold_config_t config = map_taphold_config(keycode);
    dprintf("get_hold_on_other_key_press %d\n", config.decision_mode);
    return config.decision_mode == taphold_decision_mode_other_key_press;
}
