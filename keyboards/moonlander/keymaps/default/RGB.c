#include "config.h"
#include "moonlander.h"
#include "raw_hid.h"
#include "process_combo.h"
#include "RGB.h"

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

void WinNavLayerRGB(void)
{

    //rgb_matrix_set_color(11, 255, 255, 255);
    //rgb_matrix_set_color(10, 255, 255, 255);

    colorLeftKeyGrid(0 ,_1stRow,RED)   ;
    colorLeftKeyGrid(1 ,_1stRow,BLANK);
    colorLeftKeyGrid(2 ,_1stRow,BLANK);
    colorLeftKeyGrid(3 ,_1stRow,BLANK);
    colorLeftKeyGrid(4 ,_1stRow,BLANK);
    colorLeftKeyGrid(5 ,_1stRow,BLANK);
    colorLeftKeyGrid(6 ,_1stRow,BLANK);

    colorLeftKeyGrid(0 ,_2ndRow,BLANK)  ;
    colorLeftKeyGrid(1 ,_2ndRow,BLANK)  ;
    colorLeftKeyGrid(2 ,_2ndRow,BLUE)  ;
    colorLeftKeyGrid(3 ,_2ndRow,BLANK) ;
    colorLeftKeyGrid(4 ,_2ndRow,BLANK) ;
    colorLeftKeyGrid(5 ,_2ndRow,BLANK) ;
    colorLeftKeyGrid(6 ,_2ndRow,BLANK) ;

    colorLeftKeyGrid(0 ,_3rdRow,BLANK) ;
    colorLeftKeyGrid(1 ,_3rdRow,BLANK) ;
    colorLeftKeyGrid(2 ,_3rdRow,BLANK) ;
    colorLeftKeyGrid(3 ,_3rdRow,BLANK) ;
    colorLeftKeyGrid(4 ,_3rdRow,BLANK) ;
    colorLeftKeyGrid(5 ,_3rdRow,BLANK) ;
    colorLeftKeyGrid(6 ,_3rdRow,BLANK) ;

    colorLeftKeyGrid(0 ,_4thRow,BLANK) ;
    colorLeftKeyGrid(1 ,_4thRow,BLANK) ;
    colorLeftKeyGrid(2 ,_4thRow,BLANK) ;
    colorLeftKeyGrid(3 ,_4thRow,BLANK) ;
    colorLeftKeyGrid(4 ,_4thRow,BLANK) ;
    colorLeftKeyGrid(5 ,_4thRow,BLANK) ;

    colorLeftKeyGrid(0 ,_5thRow,BLANK) ;
    colorLeftKeyGrid(1 ,_5thRow,BLANK) ;
    colorLeftKeyGrid(2 ,_5thRow,BLANK) ;
    colorLeftKeyGrid(3 ,_5thRow,BLANK) ;
    colorLeftKeyGrid(4 ,_5thRow,RED)   ;

    colorRightKeyGrid(0,_1stRow,BLANK)   ;
    colorRightKeyGrid(1,_1stRow,BLANK);
    colorRightKeyGrid(2,_1stRow,BLANK);
    colorRightKeyGrid(3,_1stRow,BLANK);
    colorRightKeyGrid(4,_1stRow,BLANK);
    colorRightKeyGrid(5,_1stRow,BLANK);
    colorRightKeyGrid(6,_1stRow,BLANK);

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

