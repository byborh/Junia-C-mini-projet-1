#include "fonction.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.h"

int main() {
    printf("╔════════════════════════════════════════════╗\n");
    printf("║     Générateur d'Images Fractales          ║\n");
    printf("╚════════════════════════════════════════════╝\n\n");

    int choice = 0;
    int loop = 1;
    
    do {
        printf("\n┌──────────────────────────────────────┐\n");
        printf("│         MENU PRINCIPAL                │\n");
        printf("├──────────────────────────────────────┤\n");
        printf("│ 0 - Carré (couleur unique)           │\n");
        printf("│ 1 - Cercle au centre                 │\n");
        printf("│ 2 - Mandelbrot (image simple)        │\n");
        printf("│ 3 - Mandelbrot avec zoom (10 images) │\n");
        printf("│ 4 - Quitter                          │\n");
        printf("└──────────────────────────────────────┘\n");
        printf("Choisissez une option (0-4) : ");
        
        if (scanf("%d", &choice) != 1) {
            printf("\n✗ Erreur de saisie !\n");
            while (getchar() != '\n');
            continue;
        }
        
        while (getchar() != '\n');
        
        Pixel pixels;
        Pixmap pixmap;
        
        switch (choice) {
            case 0: {
                printf("\n► Création d'un CARRÉ (900x600)...\n");
                
                pixels.r = 0; pixels.g = 123; pixels.b = 255;
                strcpy(pixmap.signature, "P3");
                pixmap.length = 10;
                pixmap.height = 10;
                pixmap.pixels = (Pixel*)malloc(pixmap.length * pixmap.height * sizeof(Pixel));
                
                if (!pixmap.pixels) {
                    printf("✗ Erreur allocation mémoire !\n");
                    break;
                }

                for (int i = 0; i < pixmap.length * pixmap.height; i++) {
                    pixmap.pixels[i] = pixels;
                }

                createImage(pixmap, 0, pixmap.length, pixmap.height);
                printf("✓ Fichier créé : image.ppm\n");
                free(pixmap.pixels);
                break;
            }
            
            case 1: {
                printf("\n► Création d'un CERCLE (640x400)...\n");
                
                pixels.r = 0; pixels.g = 123; pixels.b = 255;
                strcpy(pixmap.signature, "P3");
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
                
                pixels.r = 0; pixels.g = 123; pixels.b = 255;
                strcpy(pixmap.signature, "P3");
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
                
                pixels.r = 0; pixels.g = 123; pixels.b = 255;
                strcpy(pixmap.signature, "P3");
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

                createImage(pixmap, 3, pixmap.length, pixmap.height);
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