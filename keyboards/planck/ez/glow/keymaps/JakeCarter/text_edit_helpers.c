#include "text_edit_helpers.h"

#include QMK_KEYBOARD_H

void te_select_word(bool is_pressed) {
    if (is_pressed) {
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
}

void te_select_line(bool is_pressed) {
    if (is_pressed) {
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
}

void te_indent(bool is_pressed) {
    if (is_pressed) {
        register_code(KC_LGUI);
        SEND_STRING("]");
        unregister_code(KC_LGUI);
    }
}

void te_outdent(bool is_pressed) {
    if (is_pressed) {
        register_code(KC_LGUI);
        SEND_STRING("[");
        unregister_code(KC_LGUI);
    }
}

void te_move_line_down(bool is_pressed) {
    if (is_pressed) {
        register_code(KC_LGUI);
        register_code(KC_LALT);
        SEND_STRING("]");
        unregister_code(KC_LALT);
        unregister_code(KC_LGUI);
    }
}

void te_move_line_up(bool is_pressed) {
    if (is_pressed) {
        register_code(KC_LGUI);
        register_code(KC_LALT);
        SEND_STRING("[");
        unregister_code(KC_LALT);
        unregister_code(KC_LGUI);
    }
}
