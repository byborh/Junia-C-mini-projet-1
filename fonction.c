#include "fonction.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "fonction.h"

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

int createImage(Pixmap pixmap, int generation, int length, int height) {
    if (generation == 0) createSquare(pixmap);
    else if (generation == 1) createCircle(pixmap);
    else if (generation == 2) createMandelbrot(pixmap, X1, Y1, X2, Y2);
    else if (generation == 3) createMandelbrotZoom(pixmap);
    
    printf("Allez vérifier si j'ai pu crée le fichier ou pas, normalement, si !  sinon, c TOI le problème BHAHAHAHAHAH\n");

    return 1;
}

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
            fprintf(f, "%d %d %d ", pixmap.pixels[index].r, pixmap.pixels[index].g, pixmap.pixels[index].b);
        }
        fprintf(f, "\n");
    }

    fclose(f);
    return 1;
}

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

int createMandelbrot(Pixmap pixmap, double x1, double y1, double x2, double y2) {
    FILE* f = fopen(IMG_FILE, "w");
    if (! f) {
        printf("Le fichier est non ouvrable/modifiable !\n");
        return 0;
    }

    fprintf(f, "%s\n%d %d\n%d\n", pixmap.signature, pixmap.length, pixmap.height, OPACITY);
    for (int j = 0; j < pixmap.height; j++) {
        for (int i = 0; i < pixmap.length; i++) {
            double x = x1 + (x2 - x1) * i / (pixmap.length - 1);
            double y = y1 + (y2 - y1) * j / (pixmap.height - 1);

            int c = convergence(x, y);

            unsigned char g = (3 * c > 255) ? 255 : 3 * c;
            fprintf(f, "%d %d %d ", 0, g, 255);
        }
        fprintf(f, "\n");
    }

    fclose(f);
    return 1;
}

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
    printf("ffmpeg -i im%%d.ppm video.mpg\n");
    
    return 1;
}