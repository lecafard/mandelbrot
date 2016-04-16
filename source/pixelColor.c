#include <math.h>

#include "pixelColor.h"

#define MAX_ITERATIONS 256
#define NUM_COLORS 5

unsigned char stepsToRed(int steps) {
    unsigned char intensity = 0;
    if(steps == MAX_ITERATIONS) {
        intensity = 255;
    } else {
        unsigned char mod = steps % NUM_COLORS;
        if(mod == 0) {
            intensity = 0;
        } else if (mod == 1) {
            intensity = 0;
        } else if (mod == 2) {
            intensity = 255;
        } else if (mod == 3) {
            intensity = 232;
        } else if (mod == 4) {
            intensity = 255;
        }
    }

    return intensity;
}

unsigned char stepsToBlue(int steps) {
    unsigned char intensity = 0;
    if(steps == MAX_ITERATIONS) {
        intensity = 255;
    } else {
        unsigned char mod = steps % NUM_COLORS;
        if(mod == 0) {
            intensity = 232;
        } else if (mod == 1) {
            intensity = 158;
        } else if (mod == 2) {
            intensity = 252;
        } else if (mod == 3) {
            intensity = 136;
        } else if (mod == 4) {
            intensity = 2;
        }
    }

    return intensity;   
}

unsigned char stepsToGreen(int steps) {
    unsigned char intensity = 0;
    if(steps == MAX_ITERATIONS) {
        intensity = 255;
    } else {
        unsigned char mod = steps % NUM_COLORS;
        if(mod == 0) {
            intensity = 66;
        } else if (mod == 1) {
            intensity = 255;
        } else if (mod == 2) {
            intensity = 0;
        } else if (mod == 3) {
            intensity = 0;
        } else if (mod == 4) {
            intensity = 0;
        }
    }

    return intensity;
}
