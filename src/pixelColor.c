// Ram Kaniyur, quadrupleslap, z5122495
// Mark, UNSW
// 16 April, 2016
// Some nice colors for the Mandelbrot fractal.

#include "pixelColor.h"

#define MAX_ITERATIONS 256
#define NUM_COLORS 5

unsigned char stepsToRed(int steps) {
    // Red component of nth color.
    unsigned char reds[NUM_COLORS] = {0, 0, 255, 232, 255};

    unsigned char intensity = 0;
    if (steps == MAX_ITERATIONS) {
        intensity = 255;
    } else {
        intensity = reds[steps % NUM_COLORS];
    }

    return intensity;
}

unsigned char stepsToGreen(int steps) {
    // Green component of nth color.
    unsigned char greens[NUM_COLORS] = {66, 255, 0, 0, 0};

    unsigned char intensity = 0;
    if (steps == MAX_ITERATIONS) {
        intensity = 255;
    } else {
        intensity = greens[steps % NUM_COLORS];
    }

    return intensity;
}

unsigned char stepsToBlue(int steps) {
    // Blue component of nth color.
    unsigned char blues[NUM_COLORS] = {232, 158, 252, 136, 2};

    unsigned char intensity = 0;
    if (steps == MAX_ITERATIONS) {
        intensity = 255;
    } else {
        intensity = blues[steps % NUM_COLORS];
    }

    return intensity;
}

