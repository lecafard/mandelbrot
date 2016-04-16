#include <math.h>

#include "pixelColor.h"

#define MAX_ITERATIONS 256
#define NUM_COLORS 10

unsigned char stepsToRed(int steps) {
    unsigned char intensity;
    if(steps == MAX_ITERATIONS) {
        intensity = 0;
    } else {
        intensity = 3 * 32 * (log(steps) / log(2));
    }

    return intensity;
}

unsigned char stepsToBlue(int steps) {
    unsigned char intensity;
    if(steps == MAX_ITERATIONS) {
        intensity = 0;
    } else {
        intensity = 4 * 32 * (log(steps) / log(2));
    }

    return intensity;   
}

unsigned char stepsToGreen(int steps) {
    unsigned char intensity;
    if(steps == MAX_ITERATIONS) {
        intensity = 0;
    } else {
        intensity = 5 * 32 * (log(steps) / log(2));
    }

    return intensity;
}
