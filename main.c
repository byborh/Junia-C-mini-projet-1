#include "fonction.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        printf("│ 4 - Palette (Couleurs dynamiques)    │\n");
        printf("│ 5 - Utilisation de mandel_pic        │\n");
        printf("│ 6 - Zoom Optimisé par Interpolation  │\n");
        printf("│ 7 - Quitter                          │\n");
        printf("└──────────────────────────────────────┘\n");
        printf("Choisissez une option entre 0 et 7 : ");
        
        if (scanf("%d", &choice) != 1) {
            printf("\nErreur de saisie !\n");
            while (getchar() != '\n');
            continue;
        }
        
        while (getchar() != '\n');
        
        Pixel pixels;
        Pixmap pixmap;
        
        switch (choice) {
            case 0: {
                printf("\nCréation d'un CARRÉ (900x600)...\n");
                
                pixels.r = 0; pixels.g = 123; pixels.b = 255;
                strcpy(pixmap.signature, "P3");
                pixmap.length = 10;
                pixmap.height = 10;
                pixmap.pixels = (Pixel*)malloc(pixmap.length * pixmap.height * sizeof(Pixel));
                
                if (!pixmap.pixels) {
                    printf("Erreur allocation mémoire !\n");
                    break;
                }

                for (int i = 0; i < pixmap.length * pixmap.height; i++) {
                    pixmap.pixels[i] = pixels;
                }

                createImage(pixmap, 0, pixmap.length, pixmap.height);
                printf("Fichier créé : image.ppm\n");
                free(pixmap.pixels);
                break;
            }
            
            case 1: {
                printf("\nCréation d'un CERCLE (640x400)...\n");
                
                pixels.r = 0; pixels.g = 123; pixels.b = 255;
                strcpy(pixmap.signature, "P3");
                pixmap.length = 640;
                pixmap.height = 400;
                pixmap.pixels = (Pixel*)malloc(pixmap.length * pixmap.height * sizeof(Pixel));
                
                if (!pixmap.pixels) {
                    printf("Erreur allocation mémoire !\n");
                    break;
                }

                for (int i = 0; i < pixmap.length * pixmap.height; i++) {
                    pixmap.pixels[i] = pixels;
                }

                createImage(pixmap, 1, pixmap.length, pixmap.height);
                printf("Fichier créé : image.ppm\n");
                free(pixmap.pixels);
                break;
            }
            
            case 2: {
                printf("\nCréation du MANDELBROT (900x600)...\n");
                
                pixels.r = 0; pixels.g = 123; pixels.b = 255;
                strcpy(pixmap.signature, "P3");
                pixmap.length = 900;
                pixmap.height = 600;
                pixmap.pixels = (Pixel*)malloc(pixmap.length * pixmap.height * sizeof(Pixel));
                
                if (!pixmap.pixels) {
                    printf("Erreur allocation mémoire !\n");
                    break;
                }

                for (int i = 0; i < pixmap.length * pixmap.height; i++) {
                    pixmap.pixels[i] = pixels;
                }

                createImage(pixmap, 2, pixmap.length, pixmap.height);
                printf("Fichier créé : image.ppm\n");
                free(pixmap.pixels);
                break;
            }
            
            case 3: {
                printf("\nCréation du MANDELBROT ZOOM (900x600, 10 images)...\n");
                
                pixels.r = 0; pixels.g = 123; pixels.b = 255;
                strcpy(pixmap.signature, "P3");
                pixmap.length = 900;
                pixmap.height = 600;
                pixmap.pixels = (Pixel*)malloc(pixmap.length * pixmap.height * sizeof(Pixel));
                
                if (!pixmap.pixels) {
                    printf("Erreur allocation mémoire !\n");
                    break;
                }

                for (int i = 0; i < pixmap.length * pixmap.height; i++) {
                    pixmap.pixels[i] = pixels;
                }

                createImage(pixmap, 3, pixmap.length, pixmap.height);
                printf("Fichiers créés : im0.ppm à im9.ppm\n");
                printf("Pour créer la vidéo :\n");
                printf("ffmpeg -i im%%d.ppm video.mpg\n");
                free(pixmap.pixels);
                break;
            }

            case 4: {
                printf("\nCréation du MANDELBROT (900x600) avec createPalette (coueleurs dynamiques)...\n");
                
                pixels.r = 0; pixels.g = 123; pixels.b = 255;
                strcpy(pixmap.signature, "P3");
                pixmap.length = 900;
                pixmap.height = 600;
                pixmap.pixels = (Pixel*)malloc(pixmap.length * pixmap.height * sizeof(Pixel));
                
                if (!pixmap.pixels) {
                    printf("Erreur allocation mémoire !\n");
                    break;
                }

                for (int i = 0; i < pixmap.length * pixmap.height; i++) {
                    pixmap.pixels[i] = pixels;
                }

                createImage(pixmap, 4, pixmap.length, pixmap.height);
                printf("Fichier créé : image.ppm\n");
                free(pixmap.pixels);
                break;
            }

            case 5: {
                printf("\nTest EXERCICE 2 : Utilisation de mandel_pic...\n");
                
                mandel_pic mp = new_mandel(900, 600, X1, Y2, 1.0);
                
                printf("Structure allouée. Dimensions: %dx%d. Xmin: %f, Ymin: %f\n", 
                       mp.width, mp.height, mp.Xmin, mp.Ymin);
                
                printf("Calcul en cours...\n");
                compute_mandel(&mp);
                
                save_mandel(&mp, "image.ppm");
                
                free_mandel(&mp);
                break;
            }

            case 6: {
                printf("\nTest EXERCICE 3 : Zoom Optimisé par Interpolation...\n");
                
                // Création de l'image de base (Vue large) 
                printf("1. Calcul de l'image de base (référence)...\n");
                mandel_pic base = new_mandel(900, 600, X1, -1.0, 1.0);
                compute_mandel_optimized(&base, NULL); // Pas d'image avant, calcul normal
                save_mandel(&base, "image.ppm");

                // réation d'une image zoomée
                // On zoome un peu (scale plus petit) et on se décale un peu
                // Ancien scale = 1.0. Nouveau scale = 0.5 (Zoom x2)
                printf("2. Calcul de l'image zoomée (avec optimisation)...\n");
                mandel_pic zoom = new_mandel(900, 600, -1.5, -0.5, 0.5);
                
                // C'est ICI que la magie opère : on passe l'adresse de 'base' comme référence
                compute_mandel_optimized(&zoom, &base);
                
                save_mandel(&zoom, "zoom_opti.ppm");
                
                printf("Fini ! Comparez 'image.ppm' et 'zoom_opti.ppm'.\n");

                free_mandel(&base);
                free_mandel(&zoom);
                break;
            }
            
            case 7: {
                printf("\nAu revoir !\n");
                loop = 0;
                break;
            }
            
            default: {
                printf("\nChoix invalide !  Veuillez entrer 0-5.\n");
                break;
            }
        }
        
    } while (loop);

    return 0;
}