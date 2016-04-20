#include <math.h>

#include "pixelColor.h"

#define MAX_ITERATIONS 256
#define NUM_COLORS 5

unsigned char stepsToRed(int steps) {
    unsigned char intensity = 0;
    unsigned char colors[5] = {0, 0, 255, 232, 255};
    if(steps == MAX_ITERATIONS) {
        intensity = 255;
    } else {
        unsigned char mod = steps % NUM_COLORS;
        intensity = colors[mod];
    }


    return intensity;
}

unsigned char stepsToGreen(int steps) {
    unsigned char intensity = 0;
    unsigned char colors[5] = {232, 158, 252, 136, 2};
    if(steps == MAX_ITERATIONS) {
        intensity = 255;
    } else {
        unsigned char mod = steps % NUM_COLORS;
        intensity = colors[mod];
    }

    return intensity;   
}

unsigned char stepsToBlue(int steps) {
    unsigned char intensity = 0;
    unsigned char colors[5] = {66, 255, 0, 0, 0};
    if(steps == MAX_ITERATIONS) {
        intensity = 255;
    } else {
        unsigned char mod = steps % NUM_COLORS;
        intensity = colors[mod];
    }

    return intensity;
}
