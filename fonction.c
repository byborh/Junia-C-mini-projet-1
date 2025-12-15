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
    else if (generation == 4) createPalette(pixmap, X1, Y1, X2, Y2);
    
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
    
    printf("\nToutes les images crées !  Utilise cette commande pour créer la vidéo :\n");
    printf("ffmpeg -i im%%d.ppm video.mpg\n");
    
    return 1;
}

color palette(int c) {
    color rgb;

    // On utilise un modulo pour créer un cycle : 
    c = c % 400;

    // Ici, on gère le mélange des couleurs par paliers.
    // On fait varier R, G et B progressivement pour créer un dégradé fluide.
    if (c >= 0 && c <= 255) {
        rgb.red = c;
        rgb.green = 0;
        rgb.blue = 0;
    }
    else if (c >= 256 && c <= 510) {
        rgb.red = 255;
        rgb.green = c - 255;
        rgb.blue = 0;
    }
    else if (c >= 511 && c <= 765) {
        rgb.red = 765 - c;
        rgb.green = 255;
        rgb.blue = 0;
    }
    else if (c >= 766 && c <= 1020) {
        rgb.red = 0;
        rgb.green = 255;
        rgb.blue = c - 765;
    }
    else if (c >= 1021 && c <= 1275) {
        rgb.red = 0;
        rgb.green = 1275 - c;
        rgb.blue = 255;
    }
    else if (c >= 1276 && c <= 1530) {
        rgb.red = c - 1275;
        rgb.green = 0;
        rgb.blue = 255;
    }
    else { 
        rgb.red = 255;
        rgb.green = 0;
        rgb.blue = 1785 - c;
    }

    return rgb;
}

int createPalette(Pixmap pixmap, double x1, double y1, double x2, double y2) {
    // Ouverture du fichier image en mode écriture
    FILE* f = fopen(IMG_FILE, "w");
    if (!f) {
        printf("Le fichier est non ouvrable/modifiable !\n");
        return 0;
    }

    // Écriture de l'en-tête standard pour le format PPM (type P3)
    fprintf(f, "%s\n%d %d\n%d\n", pixmap.signature, pixmap.length, pixmap.height, OPACITY);
    
    // On parcourt chaque pixel de l'image (hauteur x largeur)
    for (int j = 0; j < pixmap.height; j++) {
        for (int i = 0; i < pixmap.length; i++) {
            
            // On convertit la position du pixel (i, j) en coordonnées du plan mathématique (x, y)
            double x = x1 + (x2 - x1) * i / (pixmap.length - 1);
            double y = y1 + (y2 - y1) * j / (pixmap.height - 1);

            // Calcul de la convergence (Mandelbrot ou Julia) pour ce point
            int c = convergence(x, y);

            // On récupère la couleur correspondante (le * 20 resserre les bandes de couleurs)
            color rgb = palette(c * 20);

            // On écrit les valeurs RGB du pixel dans le fichier
            fprintf(f, "%d %d %d ", rgb.red, rgb.green, rgb.blue);
        }
        fprintf(f, "\n");
    }

    fclose(f);
    return 1;
}

mandel_pic new_mandel(int width, int height, double Xmin, double Ymin, double scale) {

    mandel_pic mandel;
    mandel.width = width;
    mandel.height = height;
    mandel.Xmin = Xmin;
    mandel.Ymin = Ymin;
    mandel.scale = scale;
    mandel.Xmax = Xmin + (scale * 3.0);
    mandel.Ymax = Ymin + (scale * 3.0 * ((double)height / (double)width));
    mandel.pixwidth = (scale * 3.0) / (double)width;
    mandel.convrg = (int *)malloc(width * height * sizeof(int));

    if (mandel.convrg == NULL) {
        fprintf(stderr, "Erreur : échece de l'allocation mémoire pour convrg\n");
        exit(1);
    }

    return mandel;
}