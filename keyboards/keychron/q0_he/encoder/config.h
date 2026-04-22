#pragma once


#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_LED_COUNT 26

#    define SNLED27351_CURRENT_TUNE \
        { 0x9A, 0x9A, 0x9A, 0x9A, 0x9A, 0x9A, 0x9A, 0x9A, 0x9A, 0x9A, 0x9A, 0x9A }

#    define RGB_MATRIX_DRIVER_LOAD_ENABLE
#    define RGB_MATRIX_TIMEOUT RGB_MATRIX_TIMEOUT_INFINITE

#    define NUM_LOCK_INDEX 5
#    define LOW_BAT_IND_INDEX \
        { 24 }

#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#    define PROFILE_LED_MATRIX_LIST \
        { 4, 5, 6 }
#endif
