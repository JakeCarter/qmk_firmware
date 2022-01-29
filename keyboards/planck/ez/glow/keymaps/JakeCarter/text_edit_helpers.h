#pragma once

#include <stdbool.h>

void te_select_word(bool is_pressed);
void te_select_line(bool is_pressed);

void te_indent(bool is_pressed);
void te_outdent(bool is_pressed);

void te_move_line_down(bool is_pressed);
void te_move_line_up(bool is_pressed);
