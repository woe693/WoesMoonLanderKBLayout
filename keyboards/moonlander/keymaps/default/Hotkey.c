#include "Hotkey.h"


void undo( void )
{
SEND_STRING(SS_LCTL("z"));
}

void cut( void )
{
SEND_STRING(SS_LCTL("x"));
}

void copy( void )
{
SEND_STRING(SS_LCTL("c"));
}

void paste( void )
{
SEND_STRING(SS_LCTL("v"));
}

void WindowNav( void )
{
    SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_TAB))));
}

void SwtchToBaseLay( void )
{
    layer_state_set(BASE);
}

void SwtchToGameLay( void )
{
    layer_state_set(GAME);
}
