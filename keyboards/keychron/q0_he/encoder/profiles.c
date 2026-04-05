#include QMK_KEYBOARD_H
#include "xinput_keycodes.h"

uint8_t profile_gobal_mode[PROFILE_COUNT] = {
    AKM_REGULAR,
    AKM_RAPID,
    AKM_RAPID,
};

// clang-format off
const uint16_t PROGMEM default_profiles[PROFILE_COUNT][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_numpad_6x5(
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0,    0     ),
    [1] = LAYOUT_numpad_6x5(
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0,    0     ),
    [2] = LAYOUT_numpad_6x5(
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0,    0     ),
};
