#include "fonction.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char *argv[]) {
    if (argc >= 6) {
        double x = atof(argv[1]);
        double y = atof(argv[2]);
        double s = atof(argv[3]);
        int count = atoi(argv[4]);
        int start = atoi(argv[5]);
        
        generate_batch(x, y, s, count, start);
        return 0;
    }

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
        printf("│ 7 - Génération de séquence vidéo     │\n");
        printf("│ 8 - Multitâche                       │\n");
        printf("│ 9 - Structures de données de base    │\n");
        printf("│ 10 - Dessiner les lignes             │\n");
        printf("│ 99 - Quitter                         │\n");
        printf("└──────────────────────────────────────┘\n");
        printf("Choisissez une option entre 0 et 10 : ");
        
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
                
                pixels.r = 0; pixels.g = 123; pixels.b = MAX_HEX;
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
                
                pixels.r = 0; pixels.g = 123; pixels.b = MAX_HEX;
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
                
                pixels.r = 0; pixels.g = 123; pixels.b = MAX_HEX;
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
                
                pixels.r = 0; pixels.g = 123; pixels.b = MAX_HEX;
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
                
                pixels.r = 0; pixels.g = 123; pixels.b = MAX_HEX;
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
                
                mandel_pic mp = new_mandel(LENGTH, HEIGHT, X1, Y2, Y1);
                
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
                
                printf("1. Calcul de l'image de base (référence)...\n");
                mandel_pic base = new_mandel(900, 600, X1, -1.0, 1.0);
                compute_mandel_optimized(&base, NULL); // Pas d'image avant, calcul normal
                save_mandel(&base, "image.ppm");

                printf("2. Calcul de l'image zoomée (avec optimisation)...\n");
                mandel_pic zoom = new_mandel(900, 600, -1.5, -0.5, 0.5);
                
                compute_mandel_optimized(&zoom, &base);
                
                save_mandel(&zoom, "zoom_opti.ppm");
                
                printf("Fini ! Comparez 'image.ppm' et 'zoom_opti.ppm'.\n");

                free_mandel(&base);
                free_mandel(&zoom);
                break;
            }

            case 7: {
                printf("\nTest EXERCICE 4 : Génération de séquence vidéo...\n");
                printf("Attention : Cela va créer 50 fichiers frameXXX.ppm dans le dossier.\n");
                
                generate_zoom_sequence(320, 240, 100);
                
                break;
            }

            case 8: {
                printf("\n=== LANCEMENT MULTITÂCHE ===\n");
                printf("On va générer 40 images au total, réparties sur 4 processus.\n");
                
                // Paramètres de la cible (Vallée des hippocampes)
                double tx = -0.743643887037151;
                double ty = 0.13182590420533;
                double start_scale = 1.0;
                double zoom_factor = 0.90;
                
                // On divise le travail en 4 parties de 10 images
                int total_images = 40;
                int split = 4;
                int imgs_per_proc = total_images / split;

                for (int p = 0; p < split; p++) {
                    int start_frame = p * imgs_per_proc;
                    
                    // Calcul de l'échelle au début de ce batch
                    // scale_p = start_scale * (0.9 ^ start_frame)
                    double current_scale = start_scale * pow(zoom_factor, start_frame);
                    
                    // Calcul des Xmin/Ymin pour ce batch
                    double w = current_scale * 3.0;
                    double h = w * ((double)HEIGHT / LENGTH); // Ratio 900x600
                    double xm = tx - w/2.0;
                    double ym = ty - h/2.0;

                    // Création de la commande système
                    // ./test Xmin Ymin Scale Count StartNum &
                    char command[256];
                    
                    // Note: le '&' à la fin dit à Linux de lancer en arrière-plan et de rendre la main tout de suite
                    sprintf(command, "./test %f %f %f %d %d &", xm, ym, current_scale, imgs_per_proc, start_frame);
                    
                    printf("Lancement processus %d : %s\n", p+1, command);
                    system(command);
                }
                
                printf("\nLes 4 processus travaillent en parallèle !\n");
                printf("Regardez votre gestionnaire de tâches ou attendez quelques secondes.\n");
                break;
            }

            case 9: {
                printf("\n--- Test Structure Picture ---\n");
                
                int w = 10;
                int h = 10;
                
                // Création de l'image
                picture p = new_pic(w, h);
                
                // Définition des couleurs
                Pixel black = {0, 0, 0};
                Pixel red   = {255, 0, 0};

                // Initialisation tout en NOIR
                for (int y = 0; y < h; y++) {
                    for (int x = 0; x < w; x++) {
                        set_pixel(&p, x, y, black);
                    }
                }

                // Coloriage des 4 coins
                // (0,0) est en haut à gauche
                set_pixel(&p, 0, 0, red);
                set_pixel(&p, w - 1, 0, red);
                set_pixel(&p, 0, h - 1, red);
                set_pixel(&p, w - 1, h - 1, red);
                
                // Sauvegarde
                save_pic(&p, IMG_FILE);
                
                // Nettoyage mémoire
                clean_pic(&p);
                
                printf("Test fini ! Oouvrez %s (tout petit carré noir avec points rouges).\n", IMG_FILE);
                break;
            }
            
            case 10: {
                printf("\nDraw line\n");
                
                picture p = new_pic(10, 10);
                
                Pixel white = {255, 255, 255};
                Pixel red = {255, 0, 0};
                Pixel blue = {0, 0, 255};
                Pixel green = {0, 255, 0};
                Pixel magenta = {255, 0, 255};

                draw_line(&p, 0, 0, 9, 9, white);
                draw_line(&p, 2, 2, 7, 7, red);
                draw_line(&p, 2, 7, 7, 2, blue);
                draw_line(&p, 1, 2, 1, 7, green);
                draw_line(&p, 8, 2, 8, 7, green);
                draw_line(&p, 2, 1, 7, 1, magenta);
                draw_line(&p, 2, 8, 7, 8, magenta);

                save_pic(&p, IMG_FILE);

                clean_pic(&p);

                printf("Test fini ! Oouvrez %s (lignes de différentes couleurs).\n", IMG_FILE);
                break;
            }

            case 99: {
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