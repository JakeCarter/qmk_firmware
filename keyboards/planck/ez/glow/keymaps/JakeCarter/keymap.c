#include QMK_KEYBOARD_H
#include "eeprom.h"
#include "g/keymap_combo.h"
#include "features/leader.h"
#include "qmk-vim/src/vim.h"

enum planck_keycodes {
    TMP_SCALE_SONG = EZ_SAFE_RANGE,
    TMP_SONG_ERROR,
    JC_LEADER,
};

enum planck_layers {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST,
};

#define JC_SS_HYPER(_string_) SS_RGUI(SS_RALT(SS_RCTL(SS_RSFT(_string_))))

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

#define RETURN_SHIFT MT(MOD_RSFT, KC_ENTER)

#define LOCK RGUI(RCTL(KC_Q))

#ifdef AUDIO_ENABLE
float song_scale[][2] = SONG(SCALE_SOUND);
float song_error[][2] = SONG(ERROR_SOUND);
#endif

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
// Replace KC_ESCAPE with `KC_GRAVE` if GUI is held down, resulting in CMD+`; In App Switch: Previous App, otherwise Next Window
//
const key_override_t key_override_escape = jc_ko_make_basic(MOD_MASK_GUI, KC_ESCAPE, KC_GRAVE);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &key_override_escape,
    NULL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_planck_grid(
        KC_ESCAPE,       KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_BSPACE,
        KC_TAB,          KC_A,           KC_S,           KC_D,           KC_F,           KC_G,           KC_H,           KC_J,           KC_K,           KC_L,           KC_SCOLON,      KC_QUOTE,
        KC_LSHIFT,       KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,           KC_N,           KC_M,           KC_COMMA,       KC_DOT,         KC_SLASH,       RETURN_SHIFT,
        JC_LEADER,       KC_LCTRL,       KC_LALT,        KC_LGUI,        LOWER,          KC_SPACE,       KC_NO,          RAISE,          KC_UP,          KC_LEFT,        KC_DOWN,        KC_RIGHT
  ),

    [_LOWER] = LAYOUT_planck_grid(
        KC_TRANSPARENT,  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_LPRN,        KC_RPRN,        KC_7,           KC_8,           KC_9,
        KC_TRANSPARENT,  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_BSLASH,      KC_LBRACKET,    KC_RBRACKET,    KC_4,           KC_5,           KC_6,
        KC_TRANSPARENT,  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_GRAVE,       KC_LT,          KC_GT,          KC_1,           KC_2,           KC_3,
        DYN_MACRO_PLAY1, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_NO,          KC_TRANSPARENT, KC_MINUS,       KC_EQUAL,       KC_0,           KC_DOT
    ),

    [_RAISE] = LAYOUT_planck_grid(
        LOCK,           KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK, KC_AUDIO_MUTE,  KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP,
        KC_TRANSPARENT, KC_EXLM,        KC_AT,          KC_HASH,        KC_DLR,         KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,      KC_TRANSPARENT,      KC_TRANSPARENT, KC_TRANSPARENT,    KC_TRANSPARENT,
        KC_TRANSPARENT, KC_PERC,        KC_CIRC,        KC_AMPR,        KC_ASTR,        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,      KC_TRANSPARENT,      KC_TRANSPARENT, KC_TRANSPARENT,    KC_TRANSPARENT,
        DYN_REC_START1, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_NO,          KC_TRANSPARENT,      KC_TRANSPARENT,      KC_TRANSPARENT, KC_TRANSPARENT,    KC_TRANSPARENT
    ),

    [_ADJUST] = LAYOUT_planck_grid(
        KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,         KC_F12,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, AU_TOG,         KC_TRANSPARENT, KC_TRANSPARENT, RGB_TOG,        RGB_VAI,        RGB_VAD,        KC_TRANSPARENT, RESET,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, TMP_SONG_ERROR, TMP_SCALE_SONG, KC_TRANSPARENT, KC_TRANSPARENT, RGB_MOD,        RGB_HUI,        RGB_HUD,        KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_NO,          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
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
        {026,245,180}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000},        {000,000,000},         {000,000,000}, {042,217,230}, {042,217,230}, {139,217,213}, {139,217,213} },

    [_RAISE] = {
        {025,255,255}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,255}, {000,000,255}, {000,000,255}, {000,000,255}, {000,000,255},
        {000,000,000}, {112,218,204}, {112,218,204}, {112,218,204}, {112,218,204}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000},
        {000,000,000}, {112,218,204}, {112,218,204}, {112,218,204}, {112,218,204}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000},
        {026,245,242}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000},        {000,000,000},         {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000} },

    [_ADJUST] = {
        {000,000,255}, {000,000,255}, {000,000,255}, {000,000,255}, {000,000,255}, {000,000,255}, {000,000,255}, {000,000,255}, {000,000,255}, {000,000,255}, {000,000,255}, {000,000,255},
        {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {044,143,255}, {000,000,000}, {000,000,000}, {044,143,255}, {044,143,255}, {044,143,255}, {000,000,000}, {026,255,255},
        {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {044,143,255}, {044,143,255}, {044,143,255}, {000,000,000}, {000,000,000},
        {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000},        {000,000,000},         {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000} },
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_leader(keycode, record)) {
        return false;
    }

    if (!process_vim_mode(keycode, record)) {
        return false;
    }

    switch (keycode) {
#ifdef AUDIO_ENABLE
        case TMP_SCALE_SONG:
            if (record->event.pressed) {
                // Handle Key Down
                PLAY_SONG(song_scale);
            } else {
                // Handle Key Up
            }
            break;
        case TMP_SONG_ERROR:
            if (record->event.pressed) {
                PLAY_SONG(song_error);
            }
#endif
        case JC_LEADER:
            if (record->event.pressed) {
                start_leading();
            }
            return false;
            break;
        default:
            break;
    }
    return true;
}

uint32_t layer_state_set_user(uint32_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

void *leader_select_all_func(uint16_t keycode) {
    switch (keycode) {
        case KC_C:
            // Select All; Copy
            // CMD+A CMD+C
            SEND_STRING(SS_RGUI("a") SS_RGUI("c"));
            return NULL;

        case KC_ENTER: // Accept
            // Select All
            // CMD+A
            SEND_STRING(SS_RGUI("a"));
            return NULL;

        default:
            return NULL;
    }
}

void *leader_select_word_func(uint16_t keycode) {
    switch (keycode) {
        case KC_C:
            // Select Word; Copy
            // ALT+Right ALT+Shift+Left CMD+C
            SEND_STRING(SS_LALT(SS_TAP(X_RIGHT) SS_LSFT(SS_TAP(X_LEFT))) SS_RGUI("c"));
            return NULL;
        case KC_ENTER: // Accept
            // Select Word
            // ALT+Right ALT+Shift+Left
            SEND_STRING(SS_LALT(SS_TAP(X_RIGHT) SS_LSFT(SS_TAP(X_LEFT))));
            return NULL;
        default:
            return NULL;
    }
}

void *leader_select_line_func(uint16_t keycode) {
    switch (keycode) {
        case KC_C:
            // Select Line; Copy
            // CMD+Right CMD+Shift+Left CMD+C
            SEND_STRING(SS_RGUI(SS_TAP(X_RIGHT) SS_LSFT(SS_TAP(X_LEFT))) SS_RGUI("c"));
            return NULL;
        case KC_ENTER: // Accept
            // Select Line
            // CMD+Right CMD+Shift+Left
            SEND_STRING(SS_RGUI(SS_TAP(X_RIGHT) SS_LSFT(SS_TAP(X_LEFT))));
            return NULL;
        default:
            return NULL;
    }
}

void *leader_s_func(uint16_t keycode) {
    switch (keycode) {
        case KC_A:
            return leader_select_all_func;
        case KC_P:
            // Open Alfred in Spell mode
            // CMD+ALT+CTRL+Shift+S
            SEND_STRING(JC_SS_HYPER("s"));
            return NULL;
        case KC_W:
            return leader_select_word_func;
        case KC_L:
            return leader_select_line_func;
        default:
            return NULL;
    }
}

void *leader_c_func(uint16_t keycode) {
    switch (keycode) {
        case KC_L:
            // Open Alfred in Clipboard mode
            // CMD+ALT+CTRL+Shift+V
            SEND_STRING(JC_SS_HYPER("v"));
            return NULL;
        default:
            return NULL;
    }
}

void *leader_d_func(uint16_t keycode) {
    switch (keycode) {
        case KC_D:
            // Open Alfred to Derived Data
            // CMD+ALT+CTRL+Shift+V
            SEND_STRING(JC_SS_HYPER("d"));
            return NULL;
        default:
            return NULL;
    }
}

void *leader_start_func(uint16_t keycode) {
    switch (keycode) {
        case KC_S:
            return leader_s_func;
        case KC_A:
            // Open Alfred
            // CMD+ALT+CTRL+Shift+Space
            SEND_STRING(JC_SS_HYPER(SS_TAP(X_SPACE)));
            return NULL;
        case KC_C:
            return leader_c_func;
        case KC_D:
            return leader_d_func;
        case KC_V:
            toggle_vim_mode();
            return NULL;
        default:
            return NULL;
    }
}
