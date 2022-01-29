SRC += muse.c
# Set any rules.mk overrides for your specific keymap here.
# See rules at https://docs.qmk.fm/#/config_options?id=the-rulesmk-file

SRC += text_edit_helpers.c

CONSOLE_ENABLE = no
COMMAND_ENABLE = no
AUDIO_ENABLE = no
MOUSEKEY_ENABLE = no
DYNAMIC_MACRO_ENABLE = yes
