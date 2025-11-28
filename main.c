#include <stdio.h>
#include <stdlib.h>

#define LENGTH 10
#define WIDTH 10
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
    int signature;
    int length;
    int width;
    Pixel pixels;
} Pixmap;

//  Define functions
int createImage(Pixmap pixmap);
// TODO à créer !
void tryCatch(){};
void verifyCreationOfImage(){};


int main() {
    printf("Ce fichier est lancé correctement !\n");

    Pixel pixels;
    pixels.r = "112";
    pixels.g = "123";
    pixels.b = "52";

    Pixmap pixmap;
    pixmap.signature = 3;
    pixmap.length = LENGTH;
    pixmap.width = WIDTH;
    pixmap.pixels = pixels;

    int res = createImage(pixmap);
    if(res == 1) printf("Le fichier est crée ! Vas tchéquer ça gros !\n");
    else printf("Le fichier n'est pas crée... C'est toi le problème, pas le code :(\n");

    return 0;
}

int createImage(Pixmap pixmap) {
    FILE *f = fopen(IMG_FILE, "r");
    if(!f) {
        printf("Le fichier est non ouvrable/modifiable !");
        return 0;
    }


    // TODO créer une boucle **for** pour remplir notre fichier IMG_FILE

    return 0;
};