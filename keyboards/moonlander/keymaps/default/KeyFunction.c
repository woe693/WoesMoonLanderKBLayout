#include "KeyFunction.h"

Window_Nav_State_t Window_Nav_State = NAVCLOSED;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode)
        {

        case MO(WINNAV):
            WindowNav();
            return true;
        break;

        case COPY:
            copy();
            return false;
        break;

        case PASTE:
            paste();
            return false;
        break;

        case CUT:
            cut();
            return false;
        break;

        case UNDO:
            undo();
            return false;
        break;

        case GAMELAYSWITCH:
            layer_move(GAME);
            return false;
        break;

        case TG(GAME):
        {
            if(!layer_state_is(GAME))
            {
                SwtchToGameLay();
            }
            return false;
        }

        case TG(BASE):
        {
            if(!layer_state_is(BASE))
            {
                SwtchToBaseLay();
            }
            return false;
        }
        break;
        }
    }
    return true;
}


void post_process_record_user(uint16_t keycode, keyrecord_t *record)
{
    switch (keycode)
    {
    case MO(WINNAV):
        tap_code(KC_ENT);
        break;

    default:
        break;
    }
}
