// Ram Kaniyur, quadrupleslap, z5122495
// Mark, UNSW
// 16 April, 2016
// Some nice colors for the Mandelbrot fractal.

#include <math.h>

#include "pixelColor.h"

unsigned char stepsToShade(int steps) {
    if (steps == 1) return 0;
    return (steps >> 1) + 128;
}

unsigned char stepsToRed(int steps) {
    if (steps == 256)
        return 255;
    else if (steps % 3 != 2)
        return stepsToShade(steps);
    else
        return 0;
}

unsigned char stepsToGreen(int steps) {
    if (steps == 256)
        return 255;
    else if (steps % 3 != 1)
        return stepsToShade(steps);
    else
        return 0;
}

unsigned char stepsToBlue(int steps) {
    if (steps == 256)
        return 255;
    else if (steps % 3 != 0)
        return stepsToShade(steps);
    else
        return 0;
}
