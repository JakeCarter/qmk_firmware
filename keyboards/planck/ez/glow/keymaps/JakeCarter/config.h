#pragma once

#ifdef AUDIO_ENABLE
#define STARTUP_SONG SONG(PLANCK_SOUND)
#endif

#define MIDI_BASIC

#define ENCODER_RESOLUTION 4

/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/
#define ORYX_CONFIGURATOR
#undef TAPPING_TERM
#define TAPPING_TERM 110

#define USB_SUSPEND_WAKEUP_DELAY 0

#define RGB_MATRIX_STARTUP_SPD 60 // Animation Speed
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_REACTIVE_NEXUS

#define RGB_MATRIX_STARTUP_HUE 100
#define RGB_MATRIX_STARTUP_SAT 255
#define RGB_MATRIX_STARTUP_VAL 200

#define KEY_OVERRIDE_ENABLE 1
