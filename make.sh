#!/bin/bash

gcc -O2 -Wall -Werror $PWD/src/*.c -lm -o $PWD/mandelbrot
