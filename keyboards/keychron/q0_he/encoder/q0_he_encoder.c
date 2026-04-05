#include "quantum.h"

// Analog matrix mask: 1 = key present, 0 = no key
// Q0 HE: 6 rows x 5 cols
const matrix_row_t analog_matrix_mask[] = {
    0b11111,  // row 0: knob, ESC, DEL, TAB, BSPC
    0b11111,  // row 1: M1, NUM, /, *, -
    0b11111,  // row 2: M2, 7, 8, 9, +
    0b01111,  // row 3: M3, 4, 5, 6 (no col 4)
    0b11111,  // row 4: M4, 1, 2, 3, Enter
    0b01011,  // row 5: FN, 0(wide), [skip col2], period (no col 4)
};
