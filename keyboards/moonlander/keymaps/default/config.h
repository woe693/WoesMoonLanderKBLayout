

/*
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

#pragma once

//#define AUTO_SHIFT_TIMEOUT 150
#define TAPPING_TERM 200
#define LEADER_TIMEOUT 350
#define PREVENT_STUCK_MODIFIERS

#define MATRIX_ROWS 12
#define MATRIX_COLS 7

#define LEADER_PER_KEY_TIMING
#define ORYX_CONFIGURATOR

#define numbrrow        KC_ESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,
#define qwert           KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,
#define shasdfg         KC_A,   KC_S,   KC_D,   KC_F,   KC_G,

enum layers
{
    BASE,  // default layer
    NAV,
    WINNAV,
    GAME,
};


