#!/bin/bash

gcc -O2 -Wall -Werror $PWD/source/*.c -lm -o $PWD/build/mandelbrot
