#pragma once

#define _1stRow 0
#define _2ndRow 1
#define _3rdRow 2
#define _4thRow 3
#define _5thRow 4

#define PURPLE 60, 0, 255
#define BLUE 0, 0, 255
#define BLANK  0, 0, 0
#define RED 255, 0, 0
#define WHITE 255, 255, 255
#define YELLOW 255, 255, 0
#define CYAN 0, 255, 255
#define GREEN 0, 255, 0

#define NumberOfKeys (72)
#define NumberOfThumbClusterKeysOnOneSide (4)

void NavLayerRGB(void);
void WinNavLayerRGB( void );
void SetGameLayerLights(void);
void colorAKey(int ID, int r, int g, int b);

void colorRightKeyGrid(int Column, int Row, int r, int g, int b);
void colorLeftKeyGrid(int Column, int Row, int r, int g, int b);
