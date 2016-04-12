#include <math.h>

#include "pixelColor.h"

#define MAX_ITERATIONS 255

unsigned char stepsToRed(int steps) {
    double deg = (360.0 / 255.0) * 64 * (log(steps) / log(4));
    unsigned char red;

    if (deg < 60) {
        red = 255;
    } else if (deg < 120) {
        red = 510 - (255 / 60) * deg;
    } else if (deg < 240) {
        red = 0;
    } else if (deg < 300) {
        red = (255 / 60) * deg - 1020;
    } else if (deg < 360) {
        red = 255;
    } else {
        red = 0;
    }

    return red;
}

unsigned char stepsToBlue(int steps) {
    double deg = (360.0 / 255.0) * 64 * (log(steps) / log(4));
    unsigned char blue;

    if (deg < 120) {
        blue = 0;
    } else if (deg < 180) {
        blue = (255 / 60) * deg - 510;
    } else if (deg < 300) {
        blue = 255;
    } else if (deg < 360) {
        blue = 1530 - (255 / 60) * deg;
    } else {
        blue = 0;
    }

    return blue;
}

unsigned char stepsToGreen(int steps) {
    double deg = (360.0 / 255.0) * 64 * (log(steps) / log(4));
    unsigned char green;

    if (deg < 60) {
        green = (255 / 60) * deg;
    } else if (deg < 180) {
        green = 255;
    } else if (deg < 240) {
        green = 1020 - (255 / 60) * deg;
    } else {
        green = 0;
    }

    return green;
}
