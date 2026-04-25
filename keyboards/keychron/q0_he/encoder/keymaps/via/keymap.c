#include QMK_KEYBOARD_H
#include "keychron_common.h"

enum layers { BASE, CUSTOM, NAV, FN };

#define CMB_MOD KC_SPC

#define FOR_EACH_SINGLE(X) \
    X(p, KC_P) X(l, KC_L) X(r, KC_R) X(n, KC_N) \
    X(a, KC_A) X(o, KC_O) X(i, KC_I) X(e, KC_E) \
    X(d, KC_D) X(t, KC_T) X(h, KC_H) X(s, KC_S)

#define FOR_EACH_CHORD(X) \
    X(u, KC_U, KC_I, KC_E) X(m, KC_M, KC_O, KC_I) \
    X(f, KC_F, KC_A, KC_E) X(g, KC_G, KC_O, KC_E) \
    X(c, KC_C, KC_D, KC_T) X(y, KC_Y, KC_R, KC_N) \
    X(w, KC_W, KC_H, KC_S) X(b, KC_B, KC_L, KC_N) \
    X(v, KC_V, KC_A, KC_O) X(k, KC_K, KC_L, KC_R) \
    X(j, KC_J, KC_T, KC_S) X(x, KC_X, KC_T, KC_H) \
    X(z, KC_Q, KC_P, KC_N) X(q, KC_Z, KC_D, KC_S)

#define FOR_EACH_ALT_CHORD(X) \
    X(s, KC_S, KC_P, KC_R) X(p, KC_P, KC_D, KC_H) X(e, KC_E, KC_A, KC_I)

#define FOR_EACH_BRACKET(X) \
    X(paren, S(KC_9),    S(KC_0),    KC_A, KC_N) \
    X(brace, S(KC_LBRC), S(KC_RBRC), KC_P, KC_E) \
    X(angle, S(KC_COMM), S(KC_DOT),  KC_D, KC_E) \
    X(brack, KC_LBRC,    KC_RBRC,    KC_A, KC_S)

#define FOR_EACH_SYMBOL_PAIR(X) \
    X(minus_under,  KC_MINS,    S(KC_MINS), KC_L, KC_E) \
    X(comma_semi,   KC_COMM,    KC_SCLN,    KC_R, KC_E) \
    X(pipe_amp,     S(KC_BSLS), S(KC_7),    KC_N, KC_O) \
    X(dot_colon,    KC_DOT,     S(KC_SCLN), KC_I, KC_S) \
    X(apos_dquot,   KC_QUOT,    S(KC_QUOT), KC_O, KC_S) \
    X(equal_plus,   KC_EQL,     S(KC_EQL),  KC_N, KC_I) \
    X(ques_excl,    S(KC_SLSH), S(KC_1),    KC_R, KC_O) \
    X(slash_bsls,   KC_SLSH,    KC_BSLS,    KC_E, KC_T) \
    X(grave_tilde,  KC_GRV,     S(KC_GRV),  KC_I, KC_T) \
    X(doll_pct,     S(KC_4),    S(KC_5),    KC_E, KC_H) \
    X(hash_at,      S(KC_3),    S(KC_2),    KC_L, KC_I) \
    X(star_caret,   S(KC_8),    S(KC_6),    KC_O, KC_H)

// Combo arrays
#define X(name, kc, k1, k2) const uint16_t PROGMEM chord_##name[] = {k1, k2, COMBO_END};
FOR_EACH_CHORD(X)
#undef X
#define X(name, kc, k1, k2) const uint16_t PROGMEM ac_##name[] = {k1, k2, COMBO_END};
FOR_EACH_ALT_CHORD(X)
#undef X
#define X(name, o, c, k1, k2) const uint16_t PROGMEM sym_##name##_open[] = {k1, k2, COMBO_END};
FOR_EACH_BRACKET(X)
#undef X
#define X(name, o, c, k1, k2) const uint16_t PROGMEM sym_##name##_close[] = {k1, k2, CMB_MOD, COMBO_END};
FOR_EACH_BRACKET(X)
#undef X
#define X(name, b, s, k1, k2) const uint16_t PROGMEM sym_##name[] = {k1, k2, COMBO_END};
FOR_EACH_SYMBOL_PAIR(X)
#undef X
#define X(name, b, s, k1, k2) const uint16_t PROGMEM sym_shift_##name[] = {k1, k2, CMB_MOD, COMBO_END};
FOR_EACH_SYMBOL_PAIR(X)
#undef X
#define X(name, kc) const uint16_t PROGMEM cap_##name[] = {kc, CMB_MOD, COMBO_END};
FOR_EACH_SINGLE(X)
#undef X
#define X(name, kc, k1, k2) const uint16_t PROGMEM cap_##name[] = {k1, k2, CMB_MOD, COMBO_END};
FOR_EACH_CHORD(X)
#undef X
#define X(name, kc, k1, k2) const uint16_t PROGMEM ac_cap_##name[] = {k1, k2, CMB_MOD, COMBO_END};
FOR_EACH_ALT_CHORD(X)
#undef X

const uint16_t PROGMEM combo_bspc[] = {KC_LSFT, KC_N, COMBO_END};
const uint16_t PROGMEM combo_del[]  = {KC_LSFT, KC_E, COMBO_END};
const uint16_t PROGMEM global_tab[] = {KC_P, KC_L, COMBO_END};

combo_t key_combos[] = {
    COMBO(combo_bspc, KC_BSPC), COMBO(combo_del, KC_DEL),
    #define X(name, kc) COMBO(cap_##name, S(kc)),
    FOR_EACH_SINGLE(X)
    #undef X
    #define X(name, kc, k1, k2) COMBO(cap_##name, S(kc)),
    FOR_EACH_CHORD(X)
    #undef X
    #define X(name, kc, k1, k2) COMBO(ac_cap_##name, S(kc)),
    FOR_EACH_ALT_CHORD(X)
    #undef X
    #define X(name, o, c, k1, k2) COMBO(sym_##name##_close, c),
    FOR_EACH_BRACKET(X)
    #undef X
    #define X(name, b, s, k1, k2) COMBO(sym_shift_##name, s),
    FOR_EACH_SYMBOL_PAIR(X)
    #undef X
    #define X(name, kc, k1, k2) COMBO(chord_##name, kc),
    FOR_EACH_CHORD(X)
    #undef X
    #define X(name, kc, k1, k2) COMBO(ac_##name, kc),
    FOR_EACH_ALT_CHORD(X)
    #undef X
    #define X(name, o, c, k1, k2) COMBO(sym_##name##_open, o),
    FOR_EACH_BRACKET(X)
    #undef X
    #define X(name, b, s, k1, k2) COMBO(sym_##name, b),
    FOR_EACH_SYMBOL_PAIR(X)
    #undef X
    COMBO(global_tab, KC_TAB),
};

#define COMBO_COUNT (sizeof(key_combos) / sizeof(key_combos[0]))
#define GLOBAL_TAB_IDX (COMBO_COUNT - 1)

static bool m1_held = false;
static bool m1_combo_used = false;
static bool numlock_held = false;
static bool numlock_other_pressed = false;
static layer_state_t numlock_saved_layers = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (numlock_held && record->event.pressed &&
        !(record->event.key.row == 1 && record->event.key.col == 1) &&
        !(record->event.key.row == 1 && record->event.key.col == 0))
        numlock_other_pressed = true;

    if (record->event.key.row == 1 && record->event.key.col == 0) {
        if (record->event.pressed) {
            m1_held = true; m1_combo_used = false;
            if (numlock_held) {
                layer_move(NAV);
                m1_combo_used = true;
                numlock_held = false;
            }
        } else { if (!m1_combo_used) layer_move(CUSTOM); m1_held = false; }
        return false;
    }
    if (record->event.key.row == 1 && record->event.key.col == 1) {
        if (record->event.pressed) {
            if (m1_held) { layer_move(NAV); m1_combo_used = true; }
            else { numlock_held = true; numlock_other_pressed = false;
                   numlock_saved_layers = layer_state; layer_clear(); }
        } else {
            if (numlock_held) {
                if (numlock_other_pressed) layer_state_set(numlock_saved_layers);
                numlock_held = false;
            }
        }
        return false;
    }
    if (!process_record_keychron_common(keycode, record)) return false;
    return true;
}

bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    if (combo_index == GLOBAL_TAB_IDX) return true;
    return layer_state_is(CUSTOM);
}

// Q0 Plus: Enter(tall) at [4,4], period at [5,3], no [5,4]
// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_numpad_6x5(
        KC_MUTE, KC_ESC,  KC_DEL,  KC_TAB,  KC_BSPC,
        TO(CUSTOM), KC_NUM, KC_SLSH, S(KC_8), KC_MINS,
        _______,    KC_7,   KC_8,    KC_9,    S(KC_EQL),
        _______,    KC_4,   KC_5,    KC_6,
        _______,    KC_1,   KC_2,    KC_3,    KC_ENT,
        MO(FN),  KC_0,              KC_DOT          ),

    [CUSTOM] = LAYOUT_numpad_6x5(
        _______,     _______, _______, _______,  _______,
        _______,     _______, XXXXXXX, XXXXXXX,  KC_LALT,
        KC_P,        KC_L,    KC_R,    KC_N,     KC_LSFT,
        KC_A,        KC_O,    KC_I,    KC_E,
        KC_D,        KC_T,    KC_H,    KC_S,     CMB_MOD,
        MO(FN),      KC_LGUI,          KC_LCTL          ),

    [NAV] = LAYOUT_numpad_6x5(
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, KC_HOME, KC_UP,   KC_PGUP, _______,
        _______, KC_LEFT, KC_DOWN, KC_RGHT,
        _______, KC_END,  XXXXXXX, KC_PGDN, _______,
        _______, KC_INS,           KC_DEL          ),

    [FN] = LAYOUT_numpad_6x5(
        UG_TOGG, BT_HST1, BT_HST2, BT_HST3, P2P4G,
        _______, _______, _______, _______, _______,
        _______, KC_HOME, KC_UP,   KC_PGUP, KC_LSFT,
        _______, KC_LEFT, KC_DOWN, KC_RGHT,
        _______, KC_END,  XXXXXXX, KC_PGDN, KC_ENT,
        _______, KC_INS,           KC_DEL          ),
};
// clang-format on



#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [BASE]   = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [CUSTOM] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [NAV]    = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [FN]     = {ENCODER_CCW_CW(UG_VALD, UG_VALU)},
};
#endif
