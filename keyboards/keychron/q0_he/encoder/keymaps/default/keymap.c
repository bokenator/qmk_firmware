#include QMK_KEYBOARD_H

enum layers { BASE, FUNC };

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_numpad_6x5(
        KC_MUTE, MO(FUNC), KC_ESC,  KC_BSPC,  KC_TAB,
        _______, KC_NUM,   KC_PSLS, KC_PAST,  KC_PMNS,
        _______, KC_P7,    KC_P8,   KC_P9,    KC_PPLS,
        _______, KC_P4,    KC_P5,   KC_P6,
        _______, KC_P1,    KC_P2,   KC_P3,    KC_PENT,
        _______, KC_P0,             KC_PDOT),
    [FUNC] = LAYOUT_numpad_6x5(
        UG_TOGG, _______,  KC_MUTE, KC_VOLD,  KC_VOLU,
        _______, UG_NEXT,  UG_VALU, UG_HUEU,  KC_DEL,
        _______, UG_PREV,  UG_VALD, UG_HUED,  _______,
        _______, UG_SATU,  UG_SPDU, KC_MPRV,
        _______, UG_SATD,  UG_SPDD, KC_MPLY,  _______,
        _______, UG_TOGG,           KC_MNXT),
};
// clang-format on

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [FUNC] = {ENCODER_CCW_CW(UG_VALD, UG_VALU)},
};
#endif
