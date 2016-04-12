#!/bin/bash

gcc -O3 -Wall -Werror $PWD/source/*.c -lm -o $PWD/build/mandelbrot
