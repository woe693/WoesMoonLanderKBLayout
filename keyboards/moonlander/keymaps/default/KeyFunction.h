#pragma once

#include "config.h"
#include "moonlander.h"
#include "raw_hid.h"
#include "process_combo.h"
#include "Hotkey.h"

enum custom_keycodes
{
    VRSN = ML_SAFE_RANGE,
    WDNAV,
    COPY,
    PASTE,
    ARRW,
    CUT,
    UNDO,
    GAMELAYSWITCH,
    STMOVLY
};



typedef enum{
    NAVCLOSED,
    NAVOPEN,
} Window_Nav_State_t;

Window_Nav_State_t Window_Nav_State;
