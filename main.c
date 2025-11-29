#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <complexe.h>

// TODO: make it dinamic !
#define LENGTH 900 // 10 - 600 - 900
#define HEIGHT 400 // 10 - 600 - 600
#define RAYON 100
#define OPACITY 255
#define IMG_FILE "image.ppm"
#define ZERO 0
#define MANDELBROT = 1

// Define all Structures
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
    Pixel pixels;
} Pixmap;

//  Define functions
int createImage(Pixmap pixmap, int generation);
int createSquare(Pixmap pixmap);
int createCircle(Pixmap pixmap);
int createMandelbrot(Pixmap pixmap);
// TODO à créer !
void tryCatch(){};
void verifyCreationOfImage(){};


int main() {
    printf("Ce fichier est lancé correctement !\n");

    Pixel pixels;
    pixels.r = 0;
    pixels.g = 123;
    pixels.b = 255;

    Pixmap pixmap;
    // pixmap.signature = "P6";
    strcpy(pixmap.signature, "P3");
    pixmap.length = LENGTH;
    pixmap.height = HEIGHT;
    pixmap.pixels = pixels;

    int res = createImage(pixmap, 1);
    if(res == 1) printf("Le fichier est crée ! Vas tchéquer ça gros !\n");
    else printf("Le fichier n'est pas crée... C'est toi le problème, pas le code :(\n");

    return 0;
}


/*
    You need to send a generation number to create a different type of image.
    Exemples :
        0 - Create a square with a uni color
        1 - Create a sqaure with a circle in the middle
        2 - 

*/
int createImage(Pixmap pixmap, int generation) {
    
    if(generation == 0) createSquare(pixmap);
    else if (generation == 1) createCircle(pixmap);
    else if(generation == 3) createMandelbrot(pixmap);
    
    printf("Allez vérifier si j'ai pu crée le fichier ou pas, normalement, si ! sinon, c TOI le problème BHAHAHAHAHAH\n");

    return 1;
};

int createSquare(Pixmap pixmap) {
    FILE* f = fopen(IMG_FILE, "w");
    if(!f) {
        printf("Le fichier est non ouvrable/modifiable !\n");
        return 0;
    }


    fprintf(f, "%s\n%d %d\n%d\n", pixmap.signature, pixmap.length, pixmap.height, OPACITY);
    for(int j = 0; j < HEIGHT; j++) {
        for(int i = 0; i < LENGTH; i++) {
            fprintf(f, "%d %d %d ", pixmap.pixels.r, pixmap.pixels.g, pixmap.pixels.b);
            printf(" %d %d %d ", pixmap.pixels.r, pixmap.pixels.g, pixmap.pixels.b);
        }
        fprintf(f, "\n");
        printf("\n");
    }



    fclose(f);
}

int createCircle(Pixmap pixmap) {
    int cx = HEIGHT/2;
    int cy = LENGTH/2;

    int radius = RAYON * RAYON;

    FILE* f = fopen(IMG_FILE, "w");
    if(!f) {
        printf("Le fichier est non ouvrable/modifiable !\n");
        return 0;
    }

    fprintf(f, "%s\n%d %d\n%d\n", pixmap.signature, pixmap.length, pixmap.height, OPACITY);
    for(int x = 0; x < HEIGHT; x++) {
        for(int y = 0; y < LENGTH; y++) {
            int dx =  x - cx;
            int dy =  y - cy;
            if((dx*dx) + (dy*dy) <= radius) {
                fprintf(f, "%d %d %d ", pixmap.pixels.r, pixmap.pixels.g, pixmap.pixels.b);
            } else {
                fprintf(f, "%d %d %d ", ZERO, ZERO, ZERO);
            }
        }
        fprintf(f, "\n");
    }
    

    fclose(f);
}

int createMandelbrot(Pixmap pixmap) {
    FILE* f = fopen(IMG_FILE, "w");
    if(!f) {
        printf("Le fichier est non ouvrable/modifiable !\n");
        return 0;
    }

    fprintf(f, "%s\n%d %d\n%d\n", pixmap.signature, pixmap.length, pixmap.height, OPACITY);
    for(int j = 0; j < HEIGHT; j++) {
        for(int i = 0; i < LENGTH; i++) {
            fprintf(f, "%d %d %d ", pixmap.pixels.r, pixmap.pixels.g, pixmap.pixels.b);
        }
        fprintf(f, "\n");
    }

    fclose(f);
}

int convergence(double x, double y) {
    double complex z = x + y * I;
    double complex u = z;
    int max_iterations = 85;
    
    for (int n = 0; n < max_iterations; n++) {
        if (cabs(u) >= 2. 0) {
            return n + 1;
        }
        
        u = u * u + z;
    }
    
    return 0;
}