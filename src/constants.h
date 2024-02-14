#include "stdint.h"

// display constants

const uint16_t RED     = 0xF800;
const uint16_t GREEN   = 0x07E0;
const uint16_t BLUE    = 0x001F;
const uint16_t CYAN    = 0x07FF;
const uint16_t MAGENTA = 0xF81F;
const uint16_t YELLOW  = 0xFFE0;
const uint16_t WHITE   = 0xFFFF;
const uint16_t GRAY    = 0x520A;
const uint16_t BLACK   = 0x0000;

const uint16_t DISPLAY_WIDTH   = 320;
const uint16_t DISPLAY_HEIGHT  = 480;

// touch constants

const uint16_t PRESSURE_LEFT = 10;
const uint16_t PRESSURE_RIGHT = 1200;

const int XP = 8;
const int XM = A2;
const int YP = A3;
const int YM = 9;

//  UNO R3
// const int XBEGIN = 129;
// const int XEND = 902;
// const int YBEGIN = 94;
// const int YEND = 961;

//  UNO R4 MINIMA
const int XBEGIN = 177;
const int XEND = 863;
const int YBEGIN = 121;
const int YEND = 950;

// application constants

const uint16_t PAINT_WIDTH = 4;

const uint16_t CANVAS_X = 10;
const uint16_t CANVAS_Y = 10;

const uint16_t CANVAS_W = DISPLAY_WIDTH - (2 * CANVAS_X);
const uint16_t CANVAS_H = (DISPLAY_HEIGHT/4) * 3 - (2 * CANVAS_Y);

const uint16_t PAINT_RADIUS = 12;
const uint16_t PAINT_OFFSET_X = 40;
const uint16_t PAINT_OFFSET_Y = CANVAS_Y + CANVAS_H + 30;
const uint16_t PAINT_COORS[][3] = {
    {0, 0, RED},    {35, 0, GREEN},     {70, 0, BLUE},
    {0, 35, CYAN},  {35, 35, MAGENTA},  {70, 35, YELLOW},
    {0, 70, WHITE}, {35, 70, GRAY},     {70, 70, BLACK}
};

const uint16_t THICKNESS_OPTIONS[] = {3, 5, 7, 9};
const uint16_t THICKNESS_OPTION_COORS[][2] = {{160, PAINT_OFFSET_Y}, {195, PAINT_OFFSET_Y}, {230, PAINT_OFFSET_Y}, {265, PAINT_OFFSET_Y}};
