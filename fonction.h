#ifndef FONCTION_H
#define FONCTION_H

#include <complex.h>
#include <stdio.h>
#include <stdlib.h>

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
#define MAX_HEX 255

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

typedef struct {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} color;

typedef struct {
    int width;
    int height;
    
    double Xmin;
    double Ymin;
    
    double Xmax;
    double Ymax;
    
    double scale;
    double pixwidth;
    
    int *convrg;
} mandel_pic;

typedef struct {
    int width;
    int height;
    Pixel* pixels;
} picture;


int createImage(Pixmap pixmap, int generation, int length, int height);
int createSquare(Pixmap pixmap);
int createCircle(Pixmap pixmap);
int createMandelbrot(Pixmap pixmap, double x1, double y1, double x2, double y2);
int createMandelbrotZoom(Pixmap pixmap);
int convergence(double x, double y);
int createPalette(Pixmap pixmap, double x1, double y1, double x2, double y2);
color palette(int c);

mandel_pic new_mandel(int width, int height, double Xmin, double Ymin, double scale);
void compute_mandel(mandel_pic *mp);
int save_mandel(mandel_pic *mp, char *filename);
void free_mandel(mandel_pic *mp);

int interpolate(mandel_pic *mp, double x, double y); // Estime la valeur à partir de l'image précédente
void compute_mandel_optimized(mandel_pic *current, mandel_pic *prev); // Calcule l'image actuelle en utilisant (si possible) l'image précédente 'prev'
void generate_zoom_sequence(int width, int height, int num_frames);
void generate_batch(double start_x, double start_y, double start_scale, int count, int start_num); // Génère une série d'images à partir de paramètres précis (pour le multitâche)

picture new_pic(int width, int height);
void clean_pic(picture *p);
int save_pic(picture *p, char *filename);
int set_pixel(picture *p, int x, int y, Pixel color);

int draw_line(picture *p, int x0, int y0, int x1, int y1, Pixel color);
int sierpinski(picture *p, double x, double y, double dimension, Pixel color);

int sierpinski_div(picture *p, double x, double y, double dimension, Pixel color);
#endif