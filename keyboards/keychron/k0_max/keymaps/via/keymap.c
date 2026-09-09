/* Copyright 2025 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "keychron_common.h"

enum layers {
    BASE,
    CUSTOM,
    NAV,
    FN,
};

// ============================================================
// Custom chord layout
// ============================================================
//
// Upper: C(M2) L(7)  R(8)  N(9)
// Home:  A(M3) O(4)  I(5)  E(6)
// Lower: D(M4) T(1)  H(2)  S(3)
//
// CmbMod (numpad enter) = KC_SPC on CUSTOM layer
//   alone → Space | with letter → uppercase | with symbol → shifted
//
// True modifiers:
//   + → Shift | - → Alt | . → Ctrl | 0 → Super

#define CMB_MOD KC_SPC

// ── Single-press letters ──
#define FOR_EACH_SINGLE(X) \
    X(c, KC_C) X(l, KC_L) X(r, KC_R) X(n, KC_N) \
    X(a, KC_A) X(o, KC_O) X(i, KC_I) X(e, KC_E) \
    X(d, KC_D) X(t, KC_T) X(h, KC_H) X(s, KC_S)

// ── Chord letters ──
#define FOR_EACH_CHORD(X) \
    X(u, KC_U, KC_I, KC_E) \
    X(m, KC_M, KC_O, KC_I) \
    X(f, KC_F, KC_A, KC_E) \
    X(g, KC_G, KC_O, KC_E) \
    X(p, KC_P, KC_D, KC_T) \
    X(y, KC_Y, KC_R, KC_N) \
    X(w, KC_W, KC_H, KC_S) \
    X(b, KC_B, KC_L, KC_N) \
    X(v, KC_V, KC_A, KC_O) \
    X(k, KC_K, KC_L, KC_R) \
    X(j, KC_J, KC_T, KC_S) \
    X(x, KC_X, KC_T, KC_H) \
    X(q, KC_Q, KC_C, KC_N) \
    X(z, KC_Z, KC_D, KC_S)

// ── Alt chords ──
#define FOR_EACH_ALT_CHORD(X) \
    X(p, KC_P, KC_C, KC_R) \
    X(c, KC_C, KC_D, KC_H) \
    X(y, KC_Y, KC_A, KC_I)

// ── Brackets (open = combo, close = combo + CmbMod) ──
// X(name, open_kc, close_kc, key1, key2)
#define FOR_EACH_BRACKET(X) \
    X(paren, S(KC_9),    S(KC_0),    KC_A, KC_N)  \
    X(brace, S(KC_LBRC), S(KC_RBRC), KC_C, KC_E)  \
    X(angle, S(KC_COMM), S(KC_DOT),  KC_D, KC_E)  \
    X(brack, KC_LBRC,    KC_RBRC,    KC_A, KC_S)

// ── Symbol pairs (base / shifted via CmbMod) ──
#define FOR_EACH_SYMBOL_PAIR(X) \
    X(minus_under,  KC_MINS,     S(KC_MINS), KC_L, KC_E)  \
    X(comma_semi,   KC_COMM,     KC_SCLN,    KC_R, KC_E)  \
    X(pipe_amp,     S(KC_BSLS),  S(KC_7),    KC_N, KC_O)  \
    X(dot_colon,    KC_DOT,      S(KC_SCLN), KC_I, KC_S)  \
    X(apos_dquot,   KC_QUOT,     S(KC_QUOT), KC_O, KC_S)  \
    X(equal_plus,   KC_EQL,      S(KC_EQL),  KC_N, KC_I)  \
    X(ques_excl,    S(KC_SLSH),  S(KC_1),    KC_R, KC_O)  \
    X(slash_bsls,   KC_SLSH,     KC_BSLS,    KC_E, KC_T)  \
    X(grave_tilde,  KC_GRV,      S(KC_GRV),  KC_I, KC_T)  \
    X(doll_pct,     S(KC_4),     S(KC_5),    KC_E, KC_H)  \
    X(hash_at,      S(KC_3),     S(KC_2),    KC_L, KC_I)  \
    X(star_caret,   S(KC_8),     S(KC_6),    KC_O, KC_H)

// ============================================================
// Combo arrays
// ============================================================

#define X(name, kc, k1, k2) \
    const uint16_t PROGMEM chord_##name[] = {k1, k2, COMBO_END};
FOR_EACH_CHORD(X)
#undef X

#define X(name, kc, k1, k2) \
    const uint16_t PROGMEM ac_##name[] = {k1, k2, COMBO_END};
FOR_EACH_ALT_CHORD(X)
#undef X

// Bracket open (2-key)
#define X(name, open_kc, close_kc, k1, k2) \
    const uint16_t PROGMEM sym_##name##_open[] = {k1, k2, COMBO_END};
FOR_EACH_BRACKET(X)
#undef X

// Bracket close (3-key: combo + CmbMod)
#define X(name, open_kc, close_kc, k1, k2) \
    const uint16_t PROGMEM sym_##name##_close[] = {k1, k2, CMB_MOD, COMBO_END};
FOR_EACH_BRACKET(X)
#undef X

#define X(name, base_kc, shift_kc, k1, k2) \
    const uint16_t PROGMEM sym_##name[] = {k1, k2, COMBO_END};
FOR_EACH_SYMBOL_PAIR(X)
#undef X

#define X(name, base_kc, shift_kc, k1, k2) \
    const uint16_t PROGMEM sym_shift_##name[] = {k1, k2, CMB_MOD, COMBO_END};
FOR_EACH_SYMBOL_PAIR(X)
#undef X

#define X(name, kc) \
    const uint16_t PROGMEM cap_##name[] = {kc, CMB_MOD, COMBO_END};
FOR_EACH_SINGLE(X)
#undef X

#define X(name, kc, k1, k2) \
    const uint16_t PROGMEM cap_##name[] = {k1, k2, CMB_MOD, COMBO_END};
FOR_EACH_CHORD(X)
#undef X

#define X(name, kc, k1, k2) \
    const uint16_t PROGMEM ac_cap_##name[] = {k1, k2, CMB_MOD, COMBO_END};
FOR_EACH_ALT_CHORD(X)
#undef X

const uint16_t PROGMEM combo_bspc[] = {KC_LSFT, KC_N, COMBO_END};
const uint16_t PROGMEM combo_del[]  = {KC_LSFT, KC_E, COMBO_END};
const uint16_t PROGMEM global_tab[] = {KC_C, KC_L, COMBO_END};

// ============================================================
// Combo registration (longer combos first for priority)
// ============================================================

combo_t key_combos[] = {
    // 2-key with Shift (Backspace/Delete) — highest priority
    COMBO(combo_bspc, KC_BSPC),
    COMBO(combo_del, KC_DEL),

    // 3-key: uppercase singles
    #define X(name, kc) COMBO(cap_##name, S(kc)),
    FOR_EACH_SINGLE(X)
    #undef X

    // 3-key: uppercase chords
    #define X(name, kc, k1, k2) COMBO(cap_##name, S(kc)),
    FOR_EACH_CHORD(X)
    #undef X

    // 3-key: uppercase alt chords
    #define X(name, kc, k1, k2) COMBO(ac_cap_##name, S(kc)),
    FOR_EACH_ALT_CHORD(X)
    #undef X

    // 3-key: bracket close
    #define X(name, open_kc, close_kc, k1, k2) COMBO(sym_##name##_close, close_kc),
    FOR_EACH_BRACKET(X)
    #undef X

    // 3-key: shifted symbols
    #define X(name, base_kc, shift_kc, k1, k2) COMBO(sym_shift_##name, shift_kc),
    FOR_EACH_SYMBOL_PAIR(X)
    #undef X

    // 2-key: letter chords
    #define X(name, kc, k1, k2) COMBO(chord_##name, kc),
    FOR_EACH_CHORD(X)
    #undef X

    // 2-key: alt chords
    #define X(name, kc, k1, k2) COMBO(ac_##name, kc),
    FOR_EACH_ALT_CHORD(X)
    #undef X

    // 2-key: bracket open
    #define X(name, open_kc, close_kc, k1, k2) COMBO(sym_##name##_open, open_kc),
    FOR_EACH_BRACKET(X)
    #undef X

    // 2-key: symbol pairs (base)
    #define X(name, base_kc, shift_kc, k1, k2) COMBO(sym_##name, base_kc),
    FOR_EACH_SYMBOL_PAIR(X)
    #undef X

    // Global — MUST be last
    COMBO(global_tab, KC_TAB),
};

#define COMBO_COUNT (sizeof(key_combos) / sizeof(key_combos[0]))
#define GLOBAL_TAB_IDX (COMBO_COUNT - 1)
#define BSPC_IDX 0
#define DEL_IDX 1

// ============================================================
// Layer switching
// ============================================================

static bool m1_held = false;
static bool m1_combo_used = false;
static bool m1_other_pressed = false;
static layer_state_t m1_saved_layers = 0;
static bool numlock_held = false;
static bool numlock_other_pressed = false;
static layer_state_t numlock_saved_layers = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Track other keys while NumLock held (exclude M1 and NumLock itself)
    if (numlock_held && record->event.pressed &&
        !(record->event.key.row == 1 && record->event.key.col == 1) &&
        !(record->event.key.row == 1 && record->event.key.col == 0)) {
        numlock_other_pressed = true;
    }

    // Track other keys while M1 held (exclude M1 and NumLock itself)
    if (m1_held && record->event.pressed &&
        !(record->event.key.row == 1 && record->event.key.col == 0) &&
        !(record->event.key.row == 1 && record->event.key.col == 1)) {
        m1_other_pressed = true;
    }

    // M1 (row 1, col 0)
    if (record->event.key.row == 1 && record->event.key.col == 0) {
        if (record->event.pressed) {
            m1_held = true;
            m1_combo_used = false;
            m1_other_pressed = false;
            if (numlock_held) {
                layer_move(NAV);
                m1_combo_used = true;
                numlock_held = false;
            } else {
                m1_saved_layers = layer_state;
                layer_move(CUSTOM);
            }
        } else {
            if (!m1_combo_used && m1_other_pressed) {
                layer_state_set(m1_saved_layers);
            }
            m1_held = false;
        }
        return false;
    }

    // NumLock (row 1, col 1)
    if (record->event.key.row == 1 && record->event.key.col == 1) {
        if (record->event.pressed) {
            if (m1_held) {
                layer_move(NAV);
                m1_combo_used = true;
            } else {
                numlock_held = true;
                numlock_other_pressed = false;
                numlock_saved_layers = layer_state;
                layer_clear();
            }
        } else {
            if (numlock_held) {
                if (numlock_other_pressed) {
                    layer_state_set(numlock_saved_layers);
                }
                numlock_held = false;
            }
        }
        return false;
    }

    if (!process_record_keychron_common(keycode, record)) {
        return false;
    }
    return true;
}

bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    if (combo_index == GLOBAL_TAB_IDX) return true;
    if (combo_index == BSPC_IDX || combo_index == DEL_IDX) return true;
    return layer_state_is(CUSTOM);
}

// ============================================================
// Keymaps
// ============================================================

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_tenkey_27(
        KC_MUTE, KC_ESC,  KC_DEL,  KC_TAB,  KC_BSPC,
        TO(CUSTOM), KC_NUM,  KC_SLSH, S(KC_8), KC_MINS,
        _______,    KC_7,    KC_8,    KC_9,    S(KC_EQL),
        _______,    KC_4,    KC_5,    KC_6,
        _______,    KC_1,    KC_2,    KC_3,
        MO(FN),  KC_0,             KC_DOT,  KC_SPC ),

    [CUSTOM] = LAYOUT_tenkey_27(
        _______,        _______, _______, _______,        _______,
        _______,        _______, XXXXXXX, XXXXXXX,        KC_LALT,
        KC_C,           KC_L,    KC_R,    KC_N,            KC_LSFT,
        KC_A,           KC_O,    KC_I,    KC_E,
        KC_D,           KC_T,    KC_H,    KC_S,
        MO(FN),         KC_LGUI,          KC_LCTL,        CMB_MOD ),

    [NAV] = LAYOUT_tenkey_27(
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, KC_HOME, KC_UP,   KC_PGUP, _______,
        _______, KC_LEFT, KC_DOWN, KC_RGHT,
        _______, KC_END,  XXXXXXX, KC_PGDN,
        _______, KC_INS,           KC_DEL,  _______ ),

    [FN] = LAYOUT_tenkey_27(
        UG_TOGG, BT_HST1, BT_HST2, BT_HST3, P2P4G,
        _______, _______, _______, _______, _______,
        _______, KC_HOME, KC_UP,   KC_PGUP, KC_LSFT,
        _______, KC_LEFT, KC_DOWN, KC_RGHT,
        _______, KC_END,  XXXXXXX, KC_PGDN,
        _______, KC_INS,           KC_DEL,  KC_ENT ),
};
// clang-format on

// ============================================================
// LED indicators
// ============================================================
//
// No RGB effects — only white layer indicators on M1 and NumLock:
//   BASE → NumLock    CUSTOM → M1    NAV → both
//
// Overrides Keychron's rgb_matrix_indicators_keychron() (weak, in
// keychron/common/keychron_task.c), whose default would draw host NumLock
// state on LED 5 plus the BT/2.4G and backlit indicators. Done here in the
// keymap so upstream's k0_max.c stays untouched.

#define M1_LED_INDEX 4
#define NUMLOCK_LED_INDEX 5

static void set_layer_indicators(layer_state_t state) {
    rgb_matrix_set_color_all(0, 0, 0);
    if (layer_state_cmp(state, NAV)) {
        rgb_matrix_set_color(M1_LED_INDEX, 255, 255, 255);
        rgb_matrix_set_color(NUMLOCK_LED_INDEX, 255, 255, 255);
    } else if (layer_state_cmp(state, CUSTOM)) {
        rgb_matrix_set_color(M1_LED_INDEX, 255, 255, 255);
    } else {
        rgb_matrix_set_color(NUMLOCK_LED_INDEX, 255, 255, 255);
    }
}

/* Every frame while RGB is enabled. */
bool rgb_matrix_indicators_keychron(void) {
    set_layer_indicators(layer_state);
    return true;
}

/* On layer change while RGB is disabled: wake the driver, draw, flush, and
 * let it shut down again — the same pattern Keychron's led_update_kb uses for
 * lock LEDs. The state is passed in because the global layer_state is not
 * assigned until after the layer_state_set_* chain returns
 * (quantum/action_layer.c). */
layer_state_t layer_state_set_user(layer_state_t state) {
    if (!rgb_matrix_is_enabled()) {
        rgb_matrix_driver_exit_shutdown();
        set_layer_indicators(state);
        rgb_matrix_driver.flush();
        if (rgb_matrix_driver_allow_shutdown()) {
            rgb_matrix_driver_shutdown();
        }
    }
    return state;
}

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [BASE]   = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [CUSTOM] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [NAV]    = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [FN]     = {ENCODER_CCW_CW(UG_VALD, UG_VALU)},
};
#endif
