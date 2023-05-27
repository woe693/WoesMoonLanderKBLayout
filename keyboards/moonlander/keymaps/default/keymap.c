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
#include "Hotkey.h"
#include "rgb.h"

#define MONAV ACTION_LAYER_MODS(NAV, KC_LEFT_CTRL | KC_LALT | KC_TAB)

LEADER_EXTERNS();

enum custom_keycodes
{
    VRSN = ML_SAFE_RANGE,
    WDNAV,
    COPY,
    PASTE,
    BASELAY,
    WDNAVSELECT,
    ARRW,
    CUT,
    UNDO,
    GAMELAYSWITCH,
};

enum layers
{
    BASE,  // default layer
    NAV,
    GAME,
};

typedef enum{
    NAVCLOSED,
    NAVOPEN,
} Window_Nav_State_t;

Window_Nav_State_t Window_Nav_State = NAVCLOSED;

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_moonlander(
        KC_EQL,     KC_1,            KC_2,           KC_3,        KC_4,     KC_5,    XXXXXXX,                    XXXXXXX,  KC_6,   KC_7,   KC_8,      KC_9,     KC_0,     KC_MINS,
        KC_DEL,     KC_Q,            KC_W,           KC_E,        KC_R,     KC_T,    XXXXXXX,                    XXXXXXX,  KC_Y,   KC_U,   KC_I,      KC_O,     KC_P,     KC_BSLS,
        KC_BSPC,    KC_A,            KC_S,           KC_D,        KC_F,     KC_G,    XXXXXXX,                    XXXXXXX,  KC_H,   KC_J,   KC_K,      KC_L,     KC_SCLN,  KC_QUOT,
        KC_LSFT,    LCTL_T(KC_Z),    KC_X,           KC_C,        KC_V,     KC_B,                                          KC_N,   KC_M,   KC_COMM,   KC_DOT,   KC_SLSH,  KC_RSFT,
        XXXXXXX,    XXXXXXX,         XXXXXXX,        XXXXXXX,     MONAV,             UNDO,                       KC_ESC,           MO(NAV),QK_LEAD,   KC_LBRC,  KC_RBRC,  GAMELAYSWITCH,

                                                                  KC_SPC,   KC_BSPC, KC_LGUI,                    KC_LALT,  KC_TAB,  KC_ENT
    ),

    [NAV] = LAYOUT_moonlander(
        XXXXXXX,    KC_F1,           KC_F2,          KC_F3,       KC_F4,      KC_F5,   KC_F6,                     KC_F7,    KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX,
        XXXXXXX,    KC_TAB,          CUT,            COPY,        PASTE,      XXXXXXX, XXXXXXX,                   XXXXXXX,  XXXXXXX, XXXXXXX, KC_UP,   XXXXXXX, XXXXXXX, KC_AUDIO_VOL_UP,
        XXXXXXX,    KC_LSFT,         XXXXXXX,        XXXXXXX,     XXXXXXX,    XXXXXXX, XXXXXXX,                   XXXXXXX,  XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, BASELAY, KC_AUDIO_VOL_DOWN,
        XXXXXXX,    KC_LCTL,         XXXXXXX,        KC_LEFT_ALT, XXXXXXX,    XXXXXXX,                                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_AUDIO_MUTE,
        XXXXXXX,    XXXXXXX,         XXXXXXX,        XXXXXXX,     WDNAVSELECT,         XXXXXXX,                    _______,          _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                                                     _______, _______, _______,                    _______, _______, _______
    ),

    [GAME] = LAYOUT_moonlander(

        KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   XXXXXXX,                XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,
        KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   XXXXXXX,                XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,
        XXXXXXX,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   XXXXXXX,                XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,
        KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                           XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,
        XXXXXXX,  XXXXXXX, XXXXXXX, KC_LCTL, KC_SPC,          XXXXXXX,                XXXXXXX,              _______,   XXXXXXX,   XXXXXXX,   XXXXXXX,   BASELAY,
                                             XXXXXXX, XXXXXXX, _______,               XXXXXXX, XXXXXXX, WDNAVSELECT
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
            COPYHOTKEY();
            return false;
        break;

        case PASTE:
            PASTEHOTKEY();
            return false;
        break;

        case CUT:
            CUTHOTKEY();
            return false;
        break;

        case UNDO:
            UNDOHOTKEY();
            return false;
        break;

        case GAMELAYSWITCH:
            layer_move(GAME);
            return false;
        break;
        }
    }
    return true;
}

void leader_start_user(void) {
    // Do something when the leader key is pressed
}

void leader_end_user(void) {
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



int keypace = 0;
int timepace = 0;

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case BASE:
            autoshift_disable();
            rgb_matrix_set_color(60, 255, 255, 255);

        break;
        case NAV:
        {
            autoshift_disable();
            NavLayerRGB();
        }
        break;
        case GAME:
        {
            autoshift_disable();
            SetGameLayerLights();
        }
        break;
        default:
            autoshift_disable();
        break;
    }
    return state;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record)
{
    return 300;
}


void colorAKey(int ID, int r, int g, int b)
{
    rgb_matrix_set_color(ID, r, g, b);
}

void colorLeftKeyGrid(int Column, int Row, int r, int g, int b)
{
    int correction = 0;

    if(((Column == 5) && (Row == 4)) || ((Column == 6) && (Row > 2)) || (Column > 6) || (Row > 5))
    {
        return;
    }

    if(Column > 5 && Column < 7)
    {
        correction -= 1;
    }

    Column *= 5;

    int newLinearValue = (Column + Row + correction);

    colorAKey(newLinearValue, r, g, b);
}


void colorRightKeyGrid(int Column, int Row, int r, int g, int b)
{
    int correction = 0;

    if(((Column == 5) && (Row == 4)) || ((Column == 6) && (Row > 2)) || (Column > 6) || (Row > 5))
    {
        return;
    }

    if(Column > 5 && Column < 7)
    {
        correction -= 1;
    }

    Column *= 5;

    int newLinearValue = (Column + Row + correction) + (NumberOfKeys / 2);

    colorAKey(newLinearValue, r, g, b);
}

void NavLayerRGB(void)
{

    //rgb_matrix_set_color(11, 255, 255, 255);
    //rgb_matrix_set_color(10, 255, 255, 255);

    colorLeftKeyGrid(0 ,_1stRow,RED)   ;
    colorLeftKeyGrid(1 ,_1stRow,PURPLE);
    colorLeftKeyGrid(2 ,_1stRow,PURPLE);
    colorLeftKeyGrid(3 ,_1stRow,PURPLE);
    colorLeftKeyGrid(4 ,_1stRow,PURPLE);
    colorLeftKeyGrid(5 ,_1stRow,PURPLE);
    colorLeftKeyGrid(6 ,_1stRow,PURPLE);

    colorLeftKeyGrid(0 ,_2ndRow,BLANK)  ;
    colorLeftKeyGrid(1 ,_2ndRow,GREEN)  ;
    colorLeftKeyGrid(2 ,_2ndRow,BLUE)  ;
    colorLeftKeyGrid(3 ,_2ndRow,BLUE) ;
    colorLeftKeyGrid(4 ,_2ndRow,BLUE) ;
    colorLeftKeyGrid(5 ,_2ndRow,BLANK) ;
    colorLeftKeyGrid(6 ,_2ndRow,BLANK) ;

    colorLeftKeyGrid(0 ,_3rdRow,BLANK) ;
    colorLeftKeyGrid(1 ,_3rdRow,WHITE) ;
    colorLeftKeyGrid(2 ,_3rdRow,BLANK) ;
    colorLeftKeyGrid(3 ,_3rdRow,BLANK) ;
    colorLeftKeyGrid(4 ,_3rdRow,BLANK) ;
    colorLeftKeyGrid(5 ,_3rdRow,BLANK) ;
    colorLeftKeyGrid(6 ,_3rdRow,BLANK) ;

    colorLeftKeyGrid(0 ,_4thRow,BLANK) ;
    colorLeftKeyGrid(1 ,_4thRow,WHITE) ;
    colorLeftKeyGrid(2 ,_4thRow,BLANK) ;
    colorLeftKeyGrid(3 ,_4thRow,WHITE) ;
    colorLeftKeyGrid(4 ,_4thRow,BLANK) ;
    colorLeftKeyGrid(5 ,_4thRow,BLANK) ;

    colorLeftKeyGrid(0 ,_5thRow,BLANK) ;
    colorLeftKeyGrid(1 ,_5thRow,BLANK) ;
    colorLeftKeyGrid(2 ,_5thRow,BLANK) ;
    colorLeftKeyGrid(3 ,_5thRow,BLANK) ;
    colorLeftKeyGrid(4 ,_5thRow,RED)   ;

    colorRightKeyGrid(0,_1stRow,RED)   ;
    colorRightKeyGrid(1,_1stRow,PURPLE);
    colorRightKeyGrid(2,_1stRow,PURPLE);
    colorRightKeyGrid(3,_1stRow,PURPLE);
    colorRightKeyGrid(4,_1stRow,PURPLE);
    colorRightKeyGrid(5,_1stRow,PURPLE);
    colorRightKeyGrid(6,_1stRow,PURPLE);

    colorRightKeyGrid(0,_2ndRow,GREEN) ;
    colorRightKeyGrid(1,_2ndRow,BLANK) ;
    colorRightKeyGrid(2,_2ndRow,BLANK) ;
    colorRightKeyGrid(3,_2ndRow,BLUE)  ;
    colorRightKeyGrid(4,_2ndRow,BLANK) ;
    colorRightKeyGrid(5,_2ndRow,BLANK) ;
    colorRightKeyGrid(6,_2ndRow,BLANK) ;

    colorRightKeyGrid(0,_3rdRow, 255/2,255,255/2) ;
    colorRightKeyGrid(1,_3rdRow,BLANK) ;
    colorRightKeyGrid(2,_3rdRow,BLUE)  ;
    colorRightKeyGrid(3,_3rdRow,BLUE)  ;
    colorRightKeyGrid(4,_3rdRow,BLUE)  ;
    colorRightKeyGrid(5,_3rdRow,BLANK) ;
    colorRightKeyGrid(6,_3rdRow,BLANK) ;

    colorRightKeyGrid(0,_4thRow,BLANK) ;
    colorRightKeyGrid(1,_4thRow,BLANK) ;
    colorRightKeyGrid(2,_4thRow,BLANK) ;
    colorRightKeyGrid(3,_4thRow,BLANK) ;
    colorRightKeyGrid(4,_4thRow,BLANK) ;
    colorRightKeyGrid(5,_4thRow,BLANK) ;

    colorRightKeyGrid(0,_5thRow,BLANK) ;
    colorRightKeyGrid(1,_5thRow,BLANK) ;
    colorRightKeyGrid(2,_5thRow,BLANK) ;
    colorRightKeyGrid(3,_5thRow,BLANK) ;
    colorRightKeyGrid(4,_5thRow,BLANK) ;
}


void SetGameLayerLights(void)
{
    colorRightKeyGrid(0, _1stRow, BLANK);
    colorRightKeyGrid(1, _1stRow, PURPLE);
    colorRightKeyGrid(2, _1stRow, PURPLE);
    colorRightKeyGrid(3, _1stRow, PURPLE);
    colorRightKeyGrid(4, _1stRow, PURPLE);
    colorRightKeyGrid(5, _1stRow, PURPLE);
    colorRightKeyGrid(6, _1stRow, PURPLE);
    colorRightKeyGrid(0, _2ndRow, BLANK);
    colorRightKeyGrid(1, _2ndRow, BLANK);
    colorRightKeyGrid(2, _2ndRow, BLANK);
    colorRightKeyGrid(3, _2ndRow, BLANK);
    colorRightKeyGrid(4, _2ndRow, BLANK);
    colorRightKeyGrid(5, _2ndRow, BLANK);
    colorRightKeyGrid(6, _2ndRow, BLANK);
    colorRightKeyGrid(0, _3rdRow, BLANK);
    colorRightKeyGrid(1, _3rdRow, BLANK);
    colorRightKeyGrid(2, _3rdRow, BLANK);
    colorRightKeyGrid(3, _3rdRow, BLANK);
    colorRightKeyGrid(4, _3rdRow, BLANK);
    colorRightKeyGrid(5, _3rdRow, BLANK);
    colorRightKeyGrid(6, _3rdRow, BLANK);
    colorRightKeyGrid(0, _4thRow, BLANK);
    colorRightKeyGrid(1, _4thRow, BLANK);
    colorRightKeyGrid(2, _4thRow, BLANK);
    colorRightKeyGrid(3, _4thRow, BLANK);
    colorRightKeyGrid(4, _4thRow, BLANK);
    colorRightKeyGrid(5, _4thRow, BLANK);
    colorRightKeyGrid(0, _5thRow, RED);
    colorRightKeyGrid(1, _5thRow, BLANK);
    colorRightKeyGrid(2, _5thRow, BLANK);
    colorRightKeyGrid(3, _5thRow, BLANK);
    colorRightKeyGrid(4, _5thRow, BLANK);
}
