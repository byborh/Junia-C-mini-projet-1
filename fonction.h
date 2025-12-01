#ifndef FONCTION_H
#define FONCTION_H

#include <complex.h>
#include <stdio.h>

#define LENGTH 900
#define HEIGHT 600
#define RAYON 100
#define OPACITY 255
#define IMG_FILE "image.ppm"
#define ZERO 0
#define X1 -2.0
#define Y1 1.0
#define X2 1.0
#define Y2 -1.0
#define TARGET_X -0.99
#define TARGET_Y 0.3
#define ZOOM_ITERATIONS 10

typedef struct 
{
    unsigned int r;
    unsigned int g;
    unsigned int b;
} Pixel;

typedef struct
{
    char signature[3];
    int length;
    int height;
    Pixel* pixels;
} Pixmap;

int createImage(Pixmap pixmap, int generation, int length, int height);
int createSquare(Pixmap pixmap);
int createCircle(Pixmap pixmap);
int createMandelbrot(Pixmap pixmap, double x1, double y1, double x2, double y2);
int createMandelbrotZoom(Pixmap pixmap);
int convergence(double x, double y);

#endif