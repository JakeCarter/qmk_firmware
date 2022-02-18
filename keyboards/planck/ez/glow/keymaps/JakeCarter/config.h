#pragma once

#define NO_MUSIC_MODE
#ifdef AUDIO_ENABLE

// Something is broken with tempo. Using the standard 120 tempo produces songs that play entirely too fast.
// With some trial an error, it seems that the timing is 4x faster than it should be. To get proper 120 bpm,
// We need to use 120 / 4, which is 30.
#ifdef TEMPO_DEFAULT
    #undef TEMPO_DEFAULT
#endif
#define TEMPO_DEFAULT 30

// Scale Notes
#define _SN1 _A3
#define _SN2 _B3
#define _SN3 _CS4
#define _SN4 _D4
#define _SN5 _E4
#define _SN6 _FS4
#define _SN7 _G4
#define _SN8 _A4

#define SCALE_SOUND E__NOTE(_SN1), E__NOTE(_SN2), E__NOTE(_SN3), E__NOTE(_SN4), E__NOTE(_SN5), E__NOTE(_SN6), E__NOTE(_SN7),
#define ERROR_SOUND S__NOTE(_SN1), S__NOTE(_SN1),

#define STARTUP_SONG SONG(NO_SOUND)
#define GOODBYE_SONG SONG(NO_SOUND)
#endif // AUDIO_ENABLE

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

#define LEADER_TIMEOUT 300
#define LEADER_PER_KEY_TIMING
#define LEADER_NO_TIMEOUT
