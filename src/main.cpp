#include "Arduino.h"

#include "Adafruit_GFX.h"
#include "MCUFRIEND_kbv.h"
#include "TouchScreen.h"

#include "constants.h"

MCUFRIEND_kbv tft;

TouchScreen ts(XP, YP, XM, YM, 300);

uint16_t pen_color = WHITE;
uint16_t thickness_id = 1;

// ----- begin helper math functions -----

bool in_range(uint16_t value, uint16_t lo, uint16_t hi) {
    return (lo <= value) && (value <= hi);
}

uint32_t distance(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1) {

    uint32_t i = (x0 > x1) ? (x0 - x1) : (x1 - x0);
    uint32_t j = (y0 > y1) ? (y0 - y1) : (y1 - y0);

    return sqrt(i*i + j*j);
}

// ----- begin functions to handle touch input -----

void to_display_mode() {

    pinMode(XM, OUTPUT);
    pinMode(XP, OUTPUT);
    pinMode(YM, OUTPUT);
    pinMode(YP, OUTPUT);
}

void convert_touch_coors(uint16_t tx, uint16_t ty, uint16_t *xptr, uint16_t *yptr) {

    tx = constrain(tx, XBEGIN, XEND);
    ty = constrain(ty, YBEGIN, YEND);

    tx = map(tx, XBEGIN, XEND, 0, 319);
    ty = map(ty, YBEGIN, YEND, 479, 0);

    *xptr = tx;
    *yptr = ty;
}

void get_touch_coors(uint16_t *xptr, uint16_t *yptr) {

    TSPoint p;

    for (;;) {

        p = ts.getPoint();
        if (in_range(p.z, PRESSURE_LEFT, PRESSURE_RIGHT)) {
            break;
        }
    }
    convert_touch_coors(p.x, p.y, xptr, yptr);
    to_display_mode();
}

// ----- begin functions to draw widgets -----

void draw_canvas() {
    tft.drawRect(CANVAS_X, CANVAS_Y, CANVAS_W, CANVAS_H, WHITE);
}

void draw_color_selector() {

    uint16_t x, y, c;

    // Draw color selection spots
    for (uint16_t i = 0; i < 9; ++i) {

        x = PAINT_COORS[i][0] + PAINT_OFFSET_X;
        y = PAINT_COORS[i][1] + PAINT_OFFSET_Y;
        c = PAINT_COORS[i][2];

        tft.fillCircle(x, y, PAINT_RADIUS, c);
        tft.drawCircle(x, y, PAINT_RADIUS + 3, WHITE);
    }
}

void draw_size_selector() {

    uint16_t x, y, t;

    for (uint16_t i = 0; i < 4; ++i) {

        x = THICKNESS_OPTION_COORS[i][0];
        y = THICKNESS_OPTION_COORS[i][1];
        t = THICKNESS_OPTIONS[i];

        // create a circle with the appropriate width
        tft.fillCircle(x, y, t, pen_color);

        // if the color has been changed
        (i == thickness_id)
        ? tft.drawCircle(x, y, t + 3, WHITE)
        : tft.drawCircle(x, y, t + 3, BLACK);
    }
}

// ----- begin functions to update widgets -----

void update_canvas(uint16_t x, uint16_t y) {

    uint16_t t = THICKNESS_OPTIONS[thickness_id];

    // if the pen is within the canvas (along with some additional internal padding)
    // the internal padding is added to ensure the ink does not cross the border
    if (in_range(x, CANVAS_X + t + 2, CANVAS_X + CANVAS_W - t - 2)
            && in_range(y, CANVAS_Y + t + 2, CANVAS_Y + CANVAS_H - t - 2)) {

        tft.fillCircle(x, y, t, pen_color);
    }
}

void update_color_selection(uint16_t x, uint16_t y) {

    uint32_t x0, y0, d;

    for (uint16_t i = 0; i < 9; ++i) {

        x0 = PAINT_COORS[i][0] + PAINT_OFFSET_X;
        y0 = PAINT_COORS[i][1] + PAINT_OFFSET_Y;
        d = distance(x0, y0, x, y);

        // the pen is in this color if the distance between its centre
        // and the pen is less than the radius of the paint
        if (d <= PAINT_RADIUS) {

            pen_color = tft.readPixel(x, y);
            draw_size_selector();
            break;
        }
    }
}

void update_size_selection(uint16_t x, uint16_t y) {

    uint32_t x0, y0, d;

    for (uint16_t i = 0; i < 4; ++i) {

        x0 = THICKNESS_OPTION_COORS[i][0];
        y0 = THICKNESS_OPTION_COORS[i][1];
        d = distance(x0, y0, x, y);

        // the pen is in this color if the distance between its centre
        // and the pen is less than the radius of the paint
        if (d <= THICKNESS_OPTIONS[i]) {

            thickness_id = i;
            draw_size_selector();
            break;
        }
    }
}


void setup(void) {

    // Use Serial Monitor for debugging
    Serial.begin(115200);
    tft.begin(0x9486);

    // Fill the screen black for a fresh start
    tft.fillScreen(BLACK);

    // draw widgets
    draw_canvas();
    draw_color_selector();
    draw_size_selector();
}

void loop(void) {

    uint16_t x, y;
    get_touch_coors(&x, &y);

    // update each widget
    update_canvas(x, y);
    update_color_selection(x, y);
    update_size_selection(x, y);

    delay(5);
}