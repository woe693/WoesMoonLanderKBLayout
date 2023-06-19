#include "Layer.h"
#include "RGB.h"




layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case BASE:
            rgb_matrix_set_color(60, 255, 255, 255);
            rgb_matrix_set_color(24, 255, 255, 255);
            autoshift_enable();
        break;
        case NAV:
        {
            NavLayerRGB();
            autoshift_disable();
        }
        break;
        case GAME:
        {
            SetGameLayerLights();
            autoshift_disable();
        }
        break;
        case WINNAV:
        {
            WinNavLayerRGB();
            autoshift_disable();
        }
        break;

        default:
        break;
    }
    return state;
}
