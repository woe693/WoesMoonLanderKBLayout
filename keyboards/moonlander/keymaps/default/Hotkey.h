#pragma once

#define UNDOHOTKEY()\
{\
    register_code(KC_LCTL);\
    register_code(KC_Z);\
    unregister_code(KC_LCTL);\
    unregister_code(KC_Z);\
}\

#define CUTHOTKEY()\
{\
    register_code(KC_LCTL);\
    register_code(KC_X);\
    unregister_code(KC_LCTL);\
    unregister_code(KC_X);\
}\


#define PASTEHOTKEY()\
{\
    register_code(KC_LEFT_CTRL);\
    register_code(KC_V);\
    unregister_code(KC_V);\
    unregister_code(KC_LEFT_CTRL);\
}\

#define COPYHOTKEY(){register_code(KC_LEFT_CTRL); register_code(KC_C); unregister_code(KC_C); unregister_code(KC_LEFT_CTRL);}
