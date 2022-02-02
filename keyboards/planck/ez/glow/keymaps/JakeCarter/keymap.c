#include QMK_KEYBOARD_H
#ifdef AUDIO_ENABLE
#include "muse.h"
#endif
#include "eeprom.h"
#include "g/keymap_combo.h"


// enum planck_keycodes {
//     MY_NEW_KEYCODE = EZ_SAFE_RANGE,
// };

enum planck_layers {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST,
    _HYPER,
};

#define JC_SS_HYPER(_string_) SS_RGUI(SS_RALT(SS_RCTL(SS_RSFT(_string_))))

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

#define HYPER_ESC LT(_HYPER, KC_ESCAPE)
#define HYPER_SPELL RALT(RGUI(RCTL(RSFT(KC_S))))
#define HYPER_CLPBRD RALT(RGUI(RCTL(RSFT(KC_V))))
#define HYPER_ALFRED RALT(RGUI(RCTL(RSFT(KC_SPACE))))

#define RETURN_SHIFT MT(MOD_RSFT, KC_ENTER)

#define LOCK RGUI(RCTL(KC_Q))

// Same as `ko_make_basic()` but doesn't suppress the trigger_mods
#define jc_ko_make_basic(trigger_mods_, trigger_key, replacement_key) \
((const key_override_t){                                              \
    .trigger_mods                           = (trigger_mods_),        \
    .layers                                 = (~0),                   \
    .suppressed_mods                        = (0),                    \
    .options                                = (ko_options_default),   \
    .negative_mod_mask                      = (0),                    \
    .custom_action                          = NULL,                   \
    .context                                = NULL,                   \
    .trigger                                = (trigger_key),          \
    .replacement                            = (replacement_key),      \
    .enabled                                = NULL                    \
})

//
// Replace HYPER_ESC with Shift+Tab if GUI is held down, resulting in CMD+Shift+Tab; Previous App in App Switcher
//
// Using CMD+Shift+Tab instead of CMD+` because CMD+` only works after App Switcher has been activated.
// CMD+Shift+Tab can activate the App Switcher and move to the previous app in one key combo.
const key_override_t key_override_hyper_esc = jc_ko_make_basic(MOD_MASK_GUI, HYPER_ESC, RSFT(KC_TAB));

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &key_override_hyper_esc,
    NULL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_planck_grid(
        KC_TAB,          KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_BSPACE,
        HYPER_ESC,       KC_A,           KC_S,           KC_D,           KC_F,           KC_G,           KC_H,           KC_J,           KC_K,           KC_L,           KC_SCOLON,      KC_QUOTE,
        KC_LSHIFT,       KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,           KC_N,           KC_M,           KC_COMMA,       KC_DOT,         KC_UP,          RETURN_SHIFT,
        KC_SLASH,        KC_LCTRL,       KC_LALT,        KC_LGUI,        LOWER,          KC_SPACE,       KC_NO,          RAISE,          KC_LEAD,       KC_LEFT,        KC_DOWN,         KC_RIGHT
  ),

    [_LOWER] = LAYOUT_planck_grid(
        KC_TRANSPARENT,  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_LPRN,        KC_RPRN,        KC_7,           KC_8,           KC_9,
        KC_TRANSPARENT,  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_BSLASH,      KC_LBRACKET,    KC_RBRACKET,    KC_4,           KC_5,           KC_6,
        KC_TRANSPARENT,  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_GRAVE,       KC_MINUS,       KC_EQUAL,       KC_1,           KC_2,           KC_3,
        DYN_MACRO_PLAY1, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_NO,          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_0,           KC_DOT
    ),

    [_RAISE] = LAYOUT_planck_grid(
        LOCK,           KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK, KC_AUDIO_MUTE,  KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP,
        KC_TRANSPARENT, KC_EXLM,        KC_AT,          KC_HASH,        KC_DLR,         KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,      KC_TRANSPARENT,      KC_TRANSPARENT, KC_TRANSPARENT,    KC_TRANSPARENT,
        KC_TRANSPARENT, KC_PERC,        KC_CIRC,        KC_AMPR,        KC_ASTR,        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,      KC_TRANSPARENT,      KC_TRANSPARENT, KC_TRANSPARENT,    KC_TRANSPARENT,
        DYN_REC_START1, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_NO,          KC_TRANSPARENT,      KC_TRANSPARENT,      KC_TRANSPARENT, KC_TRANSPARENT,    KC_TRANSPARENT
    ),

    [_ADJUST] = LAYOUT_planck_grid(
        KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,         KC_F12,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, RGB_TOG,        RGB_VAI,        RGB_VAD,        KC_TRANSPARENT, RESET,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, RGB_MOD,        RGB_HUI,        RGB_HUD,        KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_NO,          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
    ),

    [_HYPER] = LAYOUT_planck_grid(
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, HYPER_SPELL,    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, HYPER_CLPBRD,   KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, HYPER_ALFRED,   KC_NO,          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
    ),

};

extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [_BASE] = {
        {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000},
        {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000},
        {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000},
        {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000},        {000,000,000},         {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000} },

    [_LOWER] = {
        {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {112,218,204}, {112,218,204}, {139,217,213}, {139,217,213}, {139,217,213},
        {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {042,217,230}, {214,218,204}, {214,218,204}, {139,217,213}, {139,217,213}, {139,217,213},
        {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {042,217,230}, {127,201,219}, {127,201,219}, {139,220,213}, {139,217,213}, {139,217,213},
        {026,245,180}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000},        {000,000,000},         {000,000,000}, {000,000,000}, {000,000,000}, {139,217,213}, {139,217,213} },

    [_RAISE] = {
        {025,255,255}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,255}, {000,000,255}, {000,000,255}, {000,000,255}, {000,000,255},
        {000,000,000}, {112,218,204}, {112,218,204}, {112,218,204}, {112,218,204}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000},
        {000,000,000}, {112,218,204}, {112,218,204}, {112,218,204}, {112,218,204}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000},
        {026,245,242}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000},        {000,000,000},         {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000} },

    [_ADJUST] = {
        {000,000,255}, {000,000,255}, {000,000,255}, {000,000,255}, {000,000,255}, {000,000,255}, {000,000,255}, {000,000,255}, {000,000,255}, {000,000,255}, {000,000,255}, {000,000,255},
        {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {044,143,255}, {044,143,255}, {044,143,255}, {000,000,000}, {026,255,255},
        {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {044,143,255}, {044,143,255}, {044,143,255}, {000,000,000}, {000,000,000},
        {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000},        {000,000,000},         {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000} },

    [_HYPER] = {
        {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000},
        {000,000,000}, {000,000,000}, {188,255,255}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000},
        {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {188,255,255}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000},
        {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000},        {188,255,255},         {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000} },
};

void set_layer_color(int layer) {
    for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
        HSV hsv = {
          .h = pgm_read_byte(&ledmap[layer][i][0]),
          .s = pgm_read_byte(&ledmap[layer][i][1]),
          .v = pgm_read_byte(&ledmap[layer][i][2]),
        };
        if (!hsv.h && !hsv.s && !hsv.v) {
            rgb_matrix_set_color( i, 0, 0, 0 );
        } else {
            RGB rgb = hsv_to_rgb( hsv );
            float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
            rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
        }
    }
}

void rgb_matrix_indicators_user(void) {
    if (keyboard_config.disable_layer_led) { return; }
    uint8_t enabled_layer = biton32(layer_state);
    switch (enabled_layer) {
        case _LOWER:
        case _RAISE:
        case _ADJUST:
        case _HYPER:
            set_layer_color(enabled_layer);
            break;

        case _BASE:
        default:
            if (rgb_matrix_get_flags() == LED_FLAG_NONE) {
                rgb_matrix_set_color_all(0, 0, 0);
            }
            break;
    }
}

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//     switch (keycode) {
//         case MY_NEW_KEYCODE:
//             if (record->event.pressed) {
//                 // Handle Key Down
//             } else {
//                 // Handle Key Up
//             }
//             break;
//     }
//     return true;
// }

#ifdef AUDIO_ENABLE
bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;
#endif

LEADER_EXTERNS();

void matrix_scan_user(void) {

LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    // Alfred
    SEQ_ONE_KEY(KC_A) {
        // Open Alfred
        // CMD+ALT+CTRL+Shift+Space
        SEND_STRING(JC_SS_HYPER(SS_TAP(X_SPACE)));
    }
    SEQ_TWO_KEYS(KC_A, KC_S) {
        // Open Alfred in Spell mode
        // CMD+ALT+CTRL+Shift+S
        SEND_STRING(JC_SS_HYPER("s"));
    }
    SEQ_TWO_KEYS(KC_A, KC_C) {
        // Open Alfred in Clipboard mode
        // CMD+ALT+CTRL+Shift+V
        SEND_STRING(JC_SS_HYPER("v"));
    }

    // Text Editing
    SEQ_TWO_KEYS(KC_S, KC_A) {
        // Select All
        // CMD+A
        SEND_STRING(SS_RGUI("a"));
    }
    SEQ_THREE_KEYS(KC_S, KC_A, KC_A) {
        // Select All; Copy
        // CMD+A CMD+C
        SEND_STRING(SS_RGUI("a") SS_RGUI("c"));
    }
    SEQ_TWO_KEYS(KC_S, KC_W) {
        // Select Word
        // ALT+Right ALT+Shift+Left
        SEND_STRING(SS_LALT(SS_TAP(X_RIGHT) SS_LSFT(SS_TAP(X_LEFT))));
    }
    SEQ_THREE_KEYS(KC_S, KC_W, KC_W) {
        // Select Word; Copy
        // ALT+Right ALT+Shift+Left CMD+C
        SEND_STRING(SS_LALT(SS_TAP(X_RIGHT) SS_LSFT(SS_TAP(X_LEFT))) SS_RGUI("c"));
    }
    SEQ_TWO_KEYS(KC_S, KC_L) {
        // Select Line
        // CMD+Right CMD+Shift+Left
        SEND_STRING(SS_LGUI(SS_TAP(X_RIGHT) SS_LSFT(SS_TAP(X_LEFT))));
    }
    SEQ_THREE_KEYS(KC_S, KC_L, KC_L) {
        // Select Line; Copy
        // CMD+Right CMD+Shift+Left CMD+C
        SEND_STRING(SS_LGUI(SS_TAP(X_RIGHT) SS_LSFT(SS_TAP(X_LEFT))) SS_RGUI("c"));
    }
  }

#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    }
#endif
}

#ifdef AUDIO_ENABLE
bool music_mask_user(uint16_t keycode) {
    switch (keycode) {
        case RAISE:
        case LOWER:
            return false;
        default:
            return true;
    }
}
#endif

uint32_t layer_state_set_user(uint32_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}


