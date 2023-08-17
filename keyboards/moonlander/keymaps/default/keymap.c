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

#include "config.h"
#include "moonlander.h"
#include "raw_hid.h"
#include "process_combo.h"

#include "Hotkey.h"
#include "RGB.h"
#include "KeyFunction.h"

#include QMK_KEYBOARD_H
#include "version.h"

#define MONAV LT(NAV, KC_LCTL  | KC_LALT | KC_TAB)

LEADER_EXTERNS();

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_moonlander(
        KC_EQL,     KC_1,            KC_2,           KC_3,        KC_4,             KC_5,    KC_GRAVE,                   XXXXXXX,  KC_6,   KC_7,            KC_8,      KC_9,     KC_0,     KC_MINS,
        KC_DEL,     KC_Q,            KC_W,           KC_E,        KC_R,             KC_T,    XXXXXXX,                    XXXXXXX,  KC_Y,   KC_U,            KC_I,      KC_O,     KC_P,     KC_BSLS,
        KC_BSPC,    KC_A,            KC_S,           KC_D,        LSFT_T(KC_F),     KC_G,    KC_GRAVE,                   XXXXXXX,  KC_H,   RSFT_T(KC_J),    KC_K,      KC_L,     KC_SCLN,  KC_QUOT,
        XXXXXXX,    LCTL_T(KC_Z),    KC_X,           KC_C,        KC_V,             KC_B,                                          KC_N,   KC_M,            KC_COMM,   KC_DOT,   KC_SLSH,  XXXXXXX,
        XXXXXXX,    XXXXXXX,         XXXXXXX,        XXXXXXX,     MO(WINNAV),                UNDO,                       KC_ESC,           MO(NAV),         QK_LEADER, KC_LBRC,  KC_RBRC,  TG(GAME),

                                                                  KC_SPC,           KC_BSPC, KC_LGUI,                    KC_LALT,  KC_TAB,  KC_ENT
    ),

    [NAV] = LAYOUT_moonlander(
        XXXXXXX,    KC_F1,           KC_F2,          KC_F3,       KC_F4,      KC_F5,   KC_F6,                     KC_F7,        KC_F8,      KC_F9,          KC_F10,     KC_F11,         KC_F12,  XXXXXXX,
        XXXXXXX,    KC_TAB,          CUT,            COPY,        PASTE,      XXXXXXX, XXXXXXX,                   XXXXXXX,      XXXXXXX,    KC_PAGE_DOWN,   KC_UP,      KC_PAGE_UP,     XXXXXXX, KC_AUDIO_VOL_UP,
        XXXXXXX,    KC_LSFT,         XXXXXXX,        XXXXXXX,     XXXXXXX,    XXXXXXX, XXXXXXX,                   XXXXXXX,      XXXXXXX,    KC_LEFT,        KC_DOWN,    KC_RGHT,        XXXXXXX, KC_AUDIO_VOL_DOWN,
        XXXXXXX,    KC_LCTL,         XXXXXXX,        KC_LEFT_ALT, XXXXXXX,    XXXXXXX,                                          XXXXXXX,    XXXXXXX,        XXXXXXX,    XXXXXXX,        XXXXXXX, KC_AUDIO_MUTE,
        XXXXXXX,    XXXXXXX,         XXXXXXX,        XXXXXXX,     XXXXXXX,             XXXXXXX,                    _______,                 _______,        XXXXXXX,    XXXXXXX,        XXXXXXX, XXXXXXX,
                                                                     _______, _______, _______,                    _______,     _______,    _______
    ),

    [WINNAV] = LAYOUT_moonlander(
        XXXXXXX,    KC_F1,           KC_F2,          KC_F3,       KC_F4,      KC_F5,   KC_F6,                     KC_F7,    KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX,
        XXXXXXX,    XXXXXXX,          XXXXXXX,       XXXXXXX,     XXXXXXX,    XXXXXXX, XXXXXXX,                   XXXXXXX,  XXXXXXX, XXXXXXX, KC_UP,   XXXXXXX, XXXXXXX, KC_AUDIO_VOL_UP,
        XXXXXXX,    XXXXXXX,         XXXXXXX,        XXXXXXX,     XXXXXXX,    XXXXXXX, XXXXXXX,                   XXXXXXX,  XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, KC_AUDIO_VOL_DOWN,
        XXXXXXX,    XXXXXXX,         XXXXXXX,        XXXXXXX,     XXXXXXX,    XXXXXXX,                                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_AUDIO_MUTE,
        XXXXXXX,    XXXXXXX,         XXXXXXX,        XXXXXXX,     XXXXXXX,             XXXXXXX,                    _______,          _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                                                     _______, _______, _______,                    _______, _______, _______
    ),

    [GAME] = LAYOUT_moonlander(


        KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   XXXXXXX,                XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,
        KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   XXXXXXX,                XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,
        KC_LSFT,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   XXXXXXX,                XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,
        KC_LSFT,  KC_Z,    KC_X,    KC_C,    XXXXXXX, KC_B,                           XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,
        KC_LCTL,  XXXXXXX, XXXXXXX, KC_C,    KC_SPC,          XXXXXXX,                XXXXXXX,              _______,   XXXXXXX,   XXXXXXX,   XXXXXXX,   TG(BASE),
                                             XXXXXXX, STMOVLY, _______,               XXXXXXX, XXXXXXX, _______
    ),
};

float leader_start_song[][2] = SONG(ONE_UP_SOUND);
float leader_succeed_song[][2] = SONG(ALL_STAR);
float leader_fail_song[][2] = SONG(RICK_ROLL);

void leader_start(void)
{
    // Do something when the leader key is pressed
    PLAY_SONG(leader_start_song);
}

void leader_end(void)
{
    SEQ_ONE_KEY(KC_F)
    {
        // Leader, f => Types the below string
        SEND_STRING("QMK is awesome.");
    }
    else SEQ_TWO_KEYS(KC_D, KC_D)
    {
        // Leader, d, d => Ctrl+A, Ctrl+C
        SEND_STRING(SS_LCTL("a") SS_LCTL("c"));
    }
    else SEQ_THREE_KEYS(KC_D, KC_D, KC_S)
    {
        // Leader, d, d, s => Types the below string
        SEND_STRING("https://start.duckduckgo.com\n");
    }
    else SEQ_TWO_KEYS(KC_A, KC_S)
    {
        // Leader, a, s => GUI+S
        tap_code16(LGUI(KC_S));
    }
}
