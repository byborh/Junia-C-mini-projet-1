#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 10
#define HEIGHT 10
#define OPACITY 255
#define IMG_FILE "image.ppm"

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
// TODO à créer !
void tryCatch(){};
void verifyCreationOfImage(){};


int main() {
    printf("Ce fichier est lancé correctement !\n");

    Pixel pixels;
    pixels.r = 112;
    pixels.g = 123;
    pixels.b = 52;

    Pixmap pixmap;
    // pixmap.signature = "P6";
    strcpy(pixmap.signature, "P3");
    pixmap.length = LENGTH;
    pixmap.height = HEIGHT;
    pixmap.pixels = pixels;

    int res = createImage(pixmap, 0);
    if(res == 1) printf("Le fichier est crée ! Vas tchéquer ça gros !\n");
    else printf("Le fichier n'est pas crée... C'est toi le problème, pas le code :(\n");

    return 0;
}

int createImage(Pixmap pixmap, int generation) {
    
    if(generation == 0) {
        createSquare(pixmap);
    } else if (generation == 1)
    {
        createCircle(pixmap);
    }
    
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
    
}