#include QMK_KEYBOARD_H
#ifdef AUDIO_ENABLE
#include "muse.h"
#endif
#include "eeprom.h"

enum planck_keycodes {
    RGB_SLD = EZ_SAFE_RANGE,

    // CMD+Tab Replacements
    WIN_NAV_NEXT,
    WIN_NAV_PREV,

    // Text Editing Macros
    TE_SEL_WORD,
    TE_SEL_LINE,
};

enum planck_layers {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST,
    _HYPER,
    _TEXT_EDIT,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define HYPER_ESC LT(_HYPER, KC_ESCAPE)

#define LOCK RGUI(RCTL(KC_Q))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_planck_grid(
        KC_TAB,         KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_BSPACE,
        HYPER_ESC,      KC_A,           KC_S,           KC_D,           KC_F,           KC_G,           KC_H,           KC_J,           KC_K,           KC_L,           KC_SCOLON,      KC_QUOTE,
        KC_LSHIFT,      KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,           KC_N,           KC_M,           KC_COMMA,       KC_DOT,         KC_UP,          MT(MOD_RSFT, KC_ENTER),
        MO(_TEXT_EDIT), KC_LCTRL,       KC_LALT,        KC_LGUI,        LOWER,          KC_SPACE,       KC_NO,          RAISE,          KC_SLASH,       KC_LEFT,        KC_DOWN,        KC_RIGHT
  ),

    [_LOWER] = LAYOUT_planck_grid(
        WIN_NAV_NEXT,    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_LPRN,        KC_RPRN,        KC_7,           KC_8,           KC_9,
        WIN_NAV_PREV,    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_BSLASH,      KC_LBRACKET,    KC_RBRACKET,    KC_4,           KC_5,           KC_6,
        KC_TRANSPARENT,  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_GRAVE,       KC_MINUS,       KC_EQUAL,       KC_1,           KC_2,           KC_3,
        DYN_MACRO_PLAY1,  KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_NO,          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_0,           KC_DOT
    ),

    [_RAISE] = LAYOUT_planck_grid(
        LOCK, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_MEDIA_PLAY_PAUSE,KC_MEDIA_NEXT_TRACK,KC_AUDIO_MUTE,  KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,
        KC_TRANSPARENT, KC_EXLM,        KC_AT,          KC_HASH,        KC_DLR,         KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_PERC,        KC_CIRC,        KC_AMPR,        KC_ASTR,        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        DYN_REC_START1, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_NO,          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
    ),

    [_ADJUST] = LAYOUT_planck_grid(
        KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,         KC_F12,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, RGB_TOG,        RGB_VAI,        RGB_VAD,        KC_TRANSPARENT, RESET,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, RGB_MOD,        RGB_HUI,        RGB_HUD,        KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_NO,          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
    ),

    [_HYPER] = LAYOUT_planck_grid(
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, RALT(RGUI(RCTL(RSFT(KC_S)))),KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, RALT(RGUI(RCTL(RSFT(KC_V)))),KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, RALT(RGUI(RCTL(RSFT(KC_SPACE)))),KC_NO,          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
    ),

    [_TEXT_EDIT] = LAYOUT_planck_grid(
        KC_TRANSPARENT, KC_TRANSPARENT, TE_SEL_WORD,    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, TE_SEL_LINE,    KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_NO,          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
    ),

};

extern bool g_suspend_state;
extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [_BASE] =           {   {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000},
                            {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000},
                            {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000},
                            {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000},        {000,000,000},         {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000} },

    [_LOWER] =          {   {230,218,204}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {112,218,204}, {112,218,204}, {139,217,213}, {139,217,213}, {139,217,213},
                            {230,218,204}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {042,217,230}, {214,218,204}, {214,218,204}, {139,217,213}, {139,217,213}, {139,217,213},
                            {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {042,217,230}, {127,201,219}, {127,201,219}, {139,220,213}, {139,217,213}, {139,217,213},
                            {026,200,242}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000},        {000,000,000},         {000,000,000}, {000,000,000}, {000,000,000}, {139,217,213}, {139,217,213} },

    [_RAISE] =          {   {025,255,255}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,255}, {000,000,255}, {000,000,255}, {000,000,255}, {000,000,255},
                            {000,000,000}, {112,218,204}, {112,218,204}, {112,218,204}, {112,218,204}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000},
                            {000,000,000}, {112,218,204}, {112,218,204}, {112,218,204}, {112,218,204}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000},
                            {026,245,242}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000},        {000,000,000},         {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000} },

    [_ADJUST] =         {   {000,000,255}, {000,000,255}, {000,000,255}, {000,000,255}, {000,000,255}, {000,000,255}, {000,000,255}, {000,000,255}, {000,000,255}, {000,000,255}, {000,000,255}, {000,000,255},
                            {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {044,143,255}, {044,143,255}, {044,143,255}, {000,000,000}, {026,255,255},
                            {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {044,143,255}, {044,143,255}, {044,143,255}, {000,000,000}, {000,000,000},
                            {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000},        {000,000,000},         {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000} },

    [_HYPER] =          {   {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000},
                            {000,000,000}, {000,000,000}, {188,255,255}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000},
                            {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {188,255,255}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000},
                            {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000},        {188,255,255},         {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000} },

    [_TEXT_EDIT] =      {   {000,000,000}, {000,000,000}, {000,000,255}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000},
                            {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,255}, {000,000,000}, {000,000,000},
                            {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000}, {000,000,000},
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
    if (g_suspend_state || keyboard_config.disable_layer_led) { return; }
    uint8_t enabled_layer = biton32(layer_state);
    switch (enabled_layer) {
        case _BASE:
        case _LOWER:
        case _RAISE:
        case _ADJUST:
        case _HYPER:
        case _TEXT_EDIT:
            set_layer_color(enabled_layer);
            break;
        default:
            if (rgb_matrix_get_flags() == LED_FLAG_NONE) {
                rgb_matrix_set_color_all(0, 0, 0);
            }
            break;
    }
}

bool is_window_nav_active = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RGB_SLD:
            if (record->event.pressed) {
                rgblight_mode(1);
            }
            return false;

        case LOWER:
            if (!record->event.pressed && is_window_nav_active) {
                unregister_code(KC_LGUI); // CMD key-up
                is_window_nav_active = false;
            }
            break;

        case WIN_NAV_NEXT:
            if (record->event.pressed) {
                if (!is_window_nav_active) {
                    is_window_nav_active = true;
                    register_code(KC_LGUI); // CMD key-down; Key-up happens during `LOWER` key-up
                }
                register_code(KC_TAB); // Tab key-down
            } else {
                unregister_code(KC_TAB); // Tab key-up
            }
            break;

        case WIN_NAV_PREV:
            if (record->event.pressed) {
                if (!is_window_nav_active) {
                    is_window_nav_active = true;
                    register_code(KC_LGUI); // CMD key-down; Key-up happens during `LOWER` key-up
                }
                register_code16(S(KC_TAB)); // Shift+Tab key-down
            } else {
                unregister_code16(S(KC_TAB)); // Shift+Tab key-up
            }
            break;

        case TE_SEL_WORD:
            if (record->event.pressed) {
                // Move cursor to end of word
                register_code(KC_LALT);
                register_code(KC_RIGHT);
                unregister_code(KC_RIGHT);

                // Select to start of word
                register_code(KC_LSHIFT);
                register_code(KC_LEFT);
                unregister_code(KC_LEFT);
                unregister_code(KC_LSHIFT);
                unregister_code(KC_LALT);
            }
            break;

        case TE_SEL_LINE:
            if (record->event.pressed) {
                // Move cursor to end of line
                register_code(KC_LGUI);
                register_code(KC_RIGHT);
                unregister_code(KC_RIGHT);

                // Select to start of word
                register_code(KC_LSHIFT);
                register_code(KC_LEFT);
                unregister_code(KC_LEFT);
                unregister_code(KC_LSHIFT);
                unregister_code(KC_LGUI);
            }
            break;

    }
    return true;
}

#ifdef AUDIO_ENABLE
bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;
#endif

void matrix_scan_user(void) {
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


