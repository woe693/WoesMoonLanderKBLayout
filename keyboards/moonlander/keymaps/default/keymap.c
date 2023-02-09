/* Copyright 2020 ZSA Technology Labs, Inc <@zsa>
 * Copyright 2020 Jack Humbert <jack.humb@gmail.com>
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include QMK_KEYBOARD_H
#include "version.h"
#include "config.h"
#include "moonlander.h"
#include "raw_hid.h"
#include "process_combo.h"

//#define QMK_KEYBOARD "Moonlander"
//#define QMK_KEYMAP   "Test"
//#define COMBO_COUNT 1


enum layers {
    BASE,  // default layer
    FUNC,  // Function Keys
    MDIA,  // media keys
    NAV,
    GAME,
};



enum custom_keycodes {
    VRSN = ML_SAFE_RANGE,
    WDNAV,
    COPY,
    PASTE,
    BASELAY,
    WDNAVSELECT,
    ARRW,
    CUT,
};

typedef enum
{
    NAVCLOSED,
    NAVOPEN,
}Window_Nav_states_e;

Window_Nav_states_e Window_Nav_State;



// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_moonlander(
        KC_EQL,     KC_1,            KC_2,           KC_3,        KC_4,     KC_5,    XXXXXXX,                    XXXXXXX,  KC_6,      KC_7,             KC_8,             KC_9,             KC_0,             KC_MINS,
        KC_DEL,     KC_Q,            KC_W,           KC_E,        KC_R,     KC_T,    XXXXXXX,                    XXXXXXX,  KC_Y,      KC_U,             KC_I,             KC_O,             KC_P,             KC_BSLS,
        KC_BSPC,    KC_A,            KC_S,           KC_D,        KC_F,     KC_G,    XXXXXXX,                    XXXXXXX,  KC_H,      KC_J,             KC_K,             KC_L,             KC_SCLN,          KC_QUOT,
        KC_LSFT,    LCTL_T(KC_Z),    KC_X,           KC_C,        KC_V,     KC_B,                                          KC_N,      KC_M,             KC_COMM,          KC_DOT,           KC_SLSH,          KC_RSFT,
        XXXXXXX,    XXXXXXX,         XXXXXXX,        XXXXXXX,     WDNAV,    XXXXXXX,                             KC_ESC,   ARRW,      XXXXXXX,          KC_LBRC,          KC_RBRC,          MO(FUNC),

                                                                  KC_SPC,   KC_BSPC, KC_LGUI,                    KC_LALT,  KC_TAB,  KC_ENT
    ),

    [FUNC] = LAYOUT_moonlander(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,             KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
        _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                             _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,          _______,           _______,          _______, _______, _______, _______, _______,
                                            _______, _______, _______,           _______,_______, _______
    ),

    [MDIA] = LAYOUT_moonlander(
        LED_LEVEL,XXXXXXX,XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
        XXXXXXX, XXXXXXX, XXXXXXX, KC_MS_U, XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MPLY,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                             XXXXXXX, XXXXXXX, KC_MPRV, KC_MNXT, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN1, KC_BTN2,         XXXXXXX,            XXXXXXX,          KC_VOLU, KC_VOLD, KC_MUTE, XXXXXXX, XXXXXXX,
                                            XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX
    ),

    [NAV] = LAYOUT_moonlander(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, KC_TAB,  CUT,     COPY,    PASTE,   XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX, KC_UP,   XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, BASELAY, XXXXXXX,
        XXXXXXX, KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, WDNAVSELECT,         XXXXXXX,        _______, BASELAY, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                            KC_LEFT_ALT, _______, XXXXXXX,           XXXXXXX, XXXXXXX, WDNAVSELECT
    ),

    [GAME] = LAYOUT_moonlander(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                 XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                    XXXXXXX, XXXXXXX, XXXXXXX, KC_UP,   XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, KC_LSFT, KC_A,    KC_S,    KC_D,    XXXXXXX, XXXXXXX,                 XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, BASELAY, XXXXXXX,
        XXXXXXX, KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, WDNAVSELECT,      XXXXXXX,                 _______,          BASELAY, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                            KC_LEFT_ALT, _______, XXXXXXX,           XXXXXXX, XXXXXXX, WDNAVSELECT
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {

        case WDNAV:
            register_code(KC_LEFT_CTRL);
            register_code(KC_LALT);
            register_code(KC_TAB);
            unregister_code(KC_LEFT_CTRL);
            unregister_code(KC_LALT);
            unregister_code(KC_TAB);
            layer_move(NAV);
            Window_Nav_State = NAVOPEN;
           return false;
        break;

        case ARRW:
            layer_move(NAV);

            return false;
        break;

        case BASELAY:
                if(Window_Nav_State == NAVOPEN)
                {
                register_code(KC_ESC);
                unregister_code(KC_ESC);
                Window_Nav_State = NAVCLOSED;
                }

                layer_move(BASE);
            return false;
        break;

        case WDNAVSELECT:
            if(Window_Nav_State == NAVOPEN)
            {
                register_code(KC_ENTER);
                unregister_code(KC_ENTER);
                layer_move(BASE);
                Window_Nav_State = NAVCLOSED;
            }else{
                register_code(KC_LEFT_CTRL);
                register_code(KC_LALT);
                register_code(KC_TAB);
                unregister_code(KC_LEFT_CTRL);
                unregister_code(KC_LALT);
                unregister_code(KC_TAB);
                Window_Nav_State = NAVOPEN;
            }
            return false;
        break;

        case COPY:
        register_code(KC_LEFT_CTRL);
        register_code(KC_C);
        unregister_code(KC_C);
        unregister_code(KC_LEFT_CTRL);
            return false;
        break;

        case PASTE:
        register_code(KC_LEFT_CTRL);
        register_code(KC_V);
        unregister_code(KC_V);
        unregister_code(KC_LEFT_CTRL);
            return false;
        break;

        case CUT:
            register_code(KC_LCTL);
            register_code(KC_X);
            unregister_code(KC_LCTL);
            unregister_code(KC_X);
            return false;
        break;
        }

    }
    return true;
}



