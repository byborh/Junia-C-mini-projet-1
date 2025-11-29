#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <complex.h>
#include <math.h>

// Constantes
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

// Structures
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

// Déclarations des fonctions
int createImage(Pixmap pixmap, int generation, int length, int height);
int createSquare(Pixmap pixmap);
int createCircle(Pixmap pixmap);
int createMandelbrot(Pixmap pixmap, double x1, double y1, double x2, double y2);
int createMandelbrotZoom(Pixmap pixmap);
int convergence(double x, double y);

int main() {
        printf("╔════════════════════════════════════════════╗\n");
    printf("║     Générateur d'Images Fractales          ║\n");
    printf("╚════════════════════════════════════════════╝\n\n");

    int choice = 0;
    int loop = 1;
    
    do {
        printf("\n┌──────────────────────────────────────┐\n");
        printf("│         MENU PRINCIPAL               │\n");
        printf("├──────────────────────────────────────┤\n");
        printf("│ 0 - Carré (couleur unique)           │\n");
        printf("│ 1 - Cercle au centre                 │\n");
        printf("│ 2 - Mandelbrot (image simple)        │\n");
        printf("│ 3 - Mandelbrot avec zoom (10 images) │\n");
        printf("│ 4 - Quitter                          │\n");
        printf("└──────────────────────────────────────┘\n");
        printf("Choisissez une option (0-4) : ");
        
        scanf("%d", &choice);
        
        // Vider le buffer stdin
        while (getchar() != '\n');
        
        switch (choice) {
            case 0: {
                printf("\n► Création d'un CARRÉ (900x600)...\n");
                
                Pixel pixels;
                pixels.r = 0;
                pixels.g = 123;
                pixels.b = 255;

                Pixmap pixmap;
                strcpy(pixmap.signature, "P3");
                pixmap.length = 10;
                pixmap.height = 10;
                pixmap.pixels = (Pixel*)malloc(pixmap.length * pixmap.height * sizeof(Pixel));
                
                if (! pixmap.pixels) {
                    printf("✗ Erreur allocation mémoire !\n");
                    break;
                }

                for (int i = 0; i < pixmap.length * pixmap.height; i++) {
                    pixmap.pixels[i] = pixels;
                }

                createImage(pixmap, 0, pixmap.length, pixmap.height);
                printf("✓ Fichier créé : image. ppm\n");
                free(pixmap.pixels);
                break;
            }
            
            case 1: {
                printf("\n► Création d'un CERCLE (640x400)...\n");
                
                Pixel pixels;
                pixels.r = 0;
                pixels.g = 123;
                pixels.b = 255;

                Pixmap pixmap;
                strcpy(pixmap. signature, "P3");
                pixmap.length = 640;
                pixmap.height = 400;
                pixmap.pixels = (Pixel*)malloc(pixmap.length * pixmap.height * sizeof(Pixel));
                
                if (!pixmap.pixels) {
                    printf("✗ Erreur allocation mémoire !\n");
                    break;
                }

                for (int i = 0; i < pixmap.length * pixmap.height; i++) {
                    pixmap.pixels[i] = pixels;
                }

                createImage(pixmap, 1, pixmap.length, pixmap.height);
                printf("✓ Fichier créé : image.ppm\n");
                free(pixmap.pixels);
                break;
            }
            
            case 2: {
                printf("\n► Création du MANDELBROT (900x600)...\n");
                
                Pixel pixels;
                pixels.r = 0;
                pixels.g = 123;
                pixels.b = 255;

                Pixmap pixmap;
                strcpy(pixmap. signature, "P3");
                pixmap.length = 900;
                pixmap.height = 600;
                pixmap.pixels = (Pixel*)malloc(pixmap.length * pixmap.height * sizeof(Pixel));
                
                if (!pixmap.pixels) {
                    printf("✗ Erreur allocation mémoire !\n");
                    break;
                }

                for (int i = 0; i < pixmap.length * pixmap.height; i++) {
                    pixmap.pixels[i] = pixels;
                }

                createImage(pixmap, 2, pixmap.length, pixmap.height);
                printf("✓ Fichier créé : image.ppm\n");
                free(pixmap.pixels);
                break;
            }
            
            case 3: {
                printf("\n► Création du MANDELBROT ZOOM (900x600, 10 images)...\n");
                
                Pixel pixels;
                pixels.r = 0;
                pixels.g = 123;
                pixels.b = 255;

                Pixmap pixmap;
                strcpy(pixmap.signature, "P3");
                pixmap.length = 900;
                pixmap.height = 600;
                pixmap.pixels = (Pixel*)malloc(pixmap.length * pixmap.height * sizeof(Pixel));
                
                if (! pixmap.pixels) {
                    printf("✗ Erreur allocation mémoire !\n");
                    break;
                }

                for (int i = 0; i < pixmap. length * pixmap.height; i++) {
                    pixmap. pixels[i] = pixels;
                }

                createImage(pixmap, 3, pixmap. length, pixmap.height);
                printf("✓ Fichiers créés : im0.ppm à im9.ppm\n");
                printf("Pour créer la vidéo :\n");
                printf("ffmpeg -i im%%d.ppm video.mpg\n");
                free(pixmap.pixels);
                break;
            }
            
            case 4: {
                printf("\n✓ Au revoir !\n");
                loop = 0;
                break;
            }
            
            default: {
                printf("\n✗ Choix invalide !  Veuillez entrer 0-4.\n");
                break;
            }
        }
        
    } while (loop);

    return 0;
}

/*
    0 - Create a square with a uni color
    1 - Create a square with a circle in the middle
    3 - Create Mandelbrot set
    4 - Create Mandelbrot set with zoom (10 images)
*/
int createImage(Pixmap pixmap, int generation, int length, int height) {
    
    if (generation == 0) createSquare(pixmap);
    else if (generation == 1) createCircle(pixmap);
    else if (generation == 2) createMandelbrot(pixmap, X1, Y1, X2, Y2);
    else if (generation == 3) createMandelbrotZoom(pixmap);
    
    printf("Allez vérifier si j'ai pu crée le fichier ou pas, normalement, si !  sinon, c TOI le problème BHAHAHAHAHAH\n");

    return 1;
}

/*
    Create a square with a uni color
*/
int createSquare(Pixmap pixmap) {
    FILE* f = fopen(IMG_FILE, "w");
    if (!f) {
        printf("Le fichier est non ouvrable/modifiable !\n");
        return 0;
    }

    fprintf(f, "%s\n%d %d\n%d\n", pixmap.signature, pixmap.length, pixmap.height, 255);
    for (int j = 0; j < pixmap.height; j++) {
        for (int i = 0; i < pixmap.length; i++) {
            int index = j * pixmap.length + i;
            fprintf(f, "%d %d %d ", pixmap.pixels[index].r, pixmap.pixels[index].g, pixmap.pixels[index]. b);
        }
        fprintf(f, "\n");
    }

    fclose(f);
    return 1;
}

/*
    Create a square with a circle in the middle
*/
int createCircle(Pixmap pixmap) {
    int cx = pixmap.length / 2;
    int cy = pixmap.height / 2;
    int radius = RAYON * RAYON;

    FILE* f = fopen(IMG_FILE, "w");
    if (!f) {
        printf("Le fichier est non ouvrable/modifiable !\n");
        return 0;
    }

    fprintf(f, "%s\n%d %d\n%d\n", pixmap.signature, pixmap.length, pixmap.height, OPACITY);
    for (int y = 0; y < pixmap.height; y++) {
        for (int x = 0; x < pixmap.length; x++) {
            int dx = x - cx;
            int dy = y - cy;
            int index = y * pixmap.length + x;
            
            if ((dx * dx) + (dy * dy) <= radius) {
                fprintf(f, "%d %d %d ", pixmap.pixels[index].r, pixmap.pixels[index].g, pixmap.pixels[index].b);
            } else {
                fprintf(f, "%d %d %d ", ZERO, ZERO, ZERO);
            }
        }
        fprintf(f, "\n");
    }
    
    fclose(f);
    return 1;
}

/*
    Create Mandelbrot set
*/
int createMandelbrot(Pixmap pixmap, double x1, double y1, double x2, double y2) {
    FILE* f = fopen(IMG_FILE, "w");
    if (! f) {
        printf("Le fichier est non ouvrable/modifiable !\n");
        return 0;
    }

    fprintf(f, "%s\n%d %d\n%d\n", pixmap.signature, pixmap.length, pixmap.height, OPACITY);
    for (int j = 0; j < pixmap.height; j++) {
        for (int i = 0; i < pixmap.length; i++) {
            double x = X1 + (X2 - X1) * i / (pixmap.length - 1);
            double y = Y1 + (Y2 - Y1) * j / (pixmap.height - 1);

            int c = convergence(x, y);

            unsigned char g = (3 * c > 255) ? 255 : 3 * c;
            fprintf(f, "%d %d %d ", 0, g, 255);
        }
        fprintf(f, "\n");
    }

    fclose(f);
    return 1;
}

/*
    Create Mandelbrot set with zoom (10 images)
*/
int createMandelbrotZoom(Pixmap pixmap) {
    double current_x1 = X1;
    double current_y1 = Y1;
    double current_x2 = X2;
    double current_y2 = Y2;
    
    double zoom_factor = 0.1;
    
    for (int iteration = 0; iteration < ZOOM_ITERATIONS; iteration++) {
        printf("Création de l'image %d.. .\n", iteration);
        
        char filename[20];
        sprintf(filename, "im%d.ppm", iteration);
        
        FILE* f = fopen(filename, "w");
        if (!f) {
            printf("Le fichier %s est non ouvrable/modifiable !\n", filename);
            return 0;
        }

        fprintf(f, "%s\n%d %d\n%d\n", pixmap.signature, pixmap.length, pixmap.height, OPACITY);
        for (int j = 0; j < pixmap.height; j++) {
            for (int i = 0; i < pixmap.length; i++) {
                double x = current_x1 + (current_x2 - current_x1) * i / (pixmap.length - 1);
                double y = current_y1 + (current_y2 - current_y1) * j / (pixmap.height - 1);

                int c = convergence(x, y);

                unsigned char g = (3 * c > 255) ? 255 : 3 * c;
                fprintf(f, "%d %d %d ", 0, g, 255);
            }
            fprintf(f, "\n");
        }

        fclose(f);
        
        double mid_x = (current_x1 + current_x2) / 2.0;
        double mid_y = (current_y1 + current_y2) / 2.0;
        
        double width = current_x2 - current_x1;
        double height = current_y2 - current_y1;
        
        mid_x = mid_x + (TARGET_X - mid_x) * zoom_factor;
        mid_y = mid_y + (TARGET_Y - mid_y) * zoom_factor;
        
        width *= 0.8;
        height *= 0.8;
        
        current_x1 = mid_x - width / 2.0;
        current_x2 = mid_x + width / 2.0;
        current_y1 = mid_y + height / 2.0;
        current_y2 = mid_y - height / 2.0;
        
        printf("Image %d crée : %s\n", iteration, filename);
    }
    
    printf("\nToutes les images créés !  Utilise cette commande pour créer la vidéo :\n");
    printf("ffmpeg -i im%%d.ppm video. mpg\n");
    
    return 1;
}


int convergence(double x, double y) {
    double complex z = x + y * I;
    double complex u = z;
    int max_iterations = 85;
    
    for (int n = 0; n < max_iterations; n++) {
        if (cabs(u) >= 2.0) return n + 1;
        u = u * u + z;
    }
    
    return 0;
}