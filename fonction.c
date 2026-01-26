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
        fprintf(stderr, "Erreur : échec de l'allocation mémoire pour convrg\n");
        exit(1);
    }

    return mandel;
}

// Fonction pour remplir la structure (calculer Mandelbrot)
void compute_mandel(mandel_pic *mp) {
    for (int j = 0; j < mp->height; j++) {
        for (int i = 0; i < mp->width; i++) {
            // Calcul des coordonnées mathématiques
            // On utilise pixwidth pour avancer pas à pas
            double x = mp->Xmin + i * mp->pixwidth;
            double y = mp->Ymin + j * mp->pixwidth; 
            
            // Calcul de la convergence et stockage dans le tableau
            mp->convrg[j * mp->width + i] = convergence(x, y);
        }
    }
}

int save_mandel(mandel_pic *mp, char *filename) {
    FILE* f = fopen(filename, "w");
    if (!f) {
        printf("Le fichier %s est non ouvrable/modifiable !\n", filename);
        return 0;
    }

    // en tete ppm
    fprintf(f, "P3\n%d %d\n%d\n", mp->width, mp->height, OPACITY);

    for (int j = 0; j < mp->height; j++) {
        for (int i = 0; i < mp->width; i++) {
            // Récupération de la valeur de convergence stockée
            int c = mp->convrg[j * mp->width + i];
            
            // Application de la palette (facteur 20 pour le style)
            color rgb = palette(c * 20);
            
            fprintf(f, "%d %d %d ", rgb.red, rgb.green, rgb.blue);
        }
        fprintf(f, "\n");
    }

    fclose(f);
    printf("Image sauvegardée dans %s\n", filename);
    return 1;
}

void free_mandel(mandel_pic *mp) {
    if (mp->convrg != NULL) {
        free(mp->convrg);
        mp->convrg = NULL;
    }
}

// optimisation functions
int interpolate(mandel_pic *mp, double x, double y) {
    // 1. Petite chance aléatoire de forcer le recalcul (1%)
    if ((rand() % 100) == 0) return -1;

    int i = (int)((x - mp->Xmin) / mp->pixwidth);
    int j = (int)((y - mp->Ymin) / mp->pixwidth);

    // 3. Vérification : est-on DANS l'image précédente ?
    // On retire 1 aux bornes car on va regarder les voisins (i+1, j+1)
    if (i < 0 || i >= mp->width - 1 || j < 0 || j >= mp->height - 1) {
        return -1; // Hors champ, il faut recalculer
    }

    // 4. Test des 4 voisins (le carré autour du point)
    int val = mp->convrg[j * mp->width + i]; // Pixel haut-gauche
    
    // Si le pixel de droite, celui du bas, et celui en bas à droite sont identiques
    if (val == mp->convrg[j * mp->width + (i + 1)] &&
        val == mp->convrg[(j + 1) * mp->width + i] &&
        val == mp->convrg[(j + 1) * mp->width + (i + 1)]) {
        
        return val;
    }

    return -1;
}

void compute_mandel_optimized(mandel_pic *current, mandel_pic *prev) {
    for (int j = 0; j < current->height; j++) {
        for (int i = 0; i < current->width; i++) {
            
            double x = current->Xmin + i * current->pixwidth;
            double y = current->Ymin + j * current->pixwidth;
            
            int val = -1;

            // Si on a une image précédente, on essaie d'interpoler
            if (prev != NULL) {
                val = interpolate(prev, x, y);
            }

            // Si l'interpolation a échoué (renvoi -1), on fait le vrai calcul
            if (val == -1) {
                val = convergence(x, y);
            }

            current->convrg[j * current->width + i] = val;
        }
    }
}


// générer une séquence d'images zoomées
void generate_zoom_sequence(int width, int height, int num_frames) {
    // Point intéressant (Vallée des hippocampes)
    double target_x = -0.743643887037151;
    double target_y = 0.13182590420533;
    
    double scale = 1.0; // Zoom de départ (vue large)
    double zoom_factor = 0.90; // On zoome de 10% à chaque image
    
    // Structure pour garder en mémoire l'image précédente
    mandel_pic prev_img;
    int has_prev = 0; // Booléen pour savoir si c'est la première itération

    printf("Début de la génération de %d images vers (%f, %f)...\n", num_frames, target_x, target_y);

    for (int k = 0; k < num_frames; k++) {
        // 1. Calcul des bornes pour que (target_x, target_y) reste au centre
        // Largeur mathématique totale = scale * 3.0
        double w_math = scale * 3.0;
        double h_math = w_math * ((double)height / width);
        
        double x_min = target_x - (w_math / 2.0);
        double y_min = target_y - (h_math / 2.0);

        // 2. Création de la nouvelle structure
        mandel_pic current = new_mandel(width, height, x_min, y_min, scale);

        // 3. Calcul (Optimisé si on a une image précédente)
        if (has_prev) {
            // On passe l'adresse de prev_img pour l'interpolation
            compute_mandel_optimized(&current, &prev_img);
            
            // On n'a plus besoin des données de l'image d'avant, on libère sa mémoire
            free_mandel(&prev_img); 
        } else {
            // Premier tour : calcul complet
            compute_mandel_optimized(&current, NULL);
        }

        // 4. Sauvegarde du fichier
        char filename[64];
        // %03d permet d'avoir frame001, frame002, etc. (tri facile)
        sprintf(filename, "frame%03d.ppm", k);
        save_mandel(&current, filename);
        
        printf("Image %d/%d générée (scale = %e)\n", k + 1, num_frames, scale);

        // 5. Préparation de l'itération suivante
        // L'image actuelle devient l'image précédente
        prev_img = current; 
        has_prev = 1;
        
        // On réduit l'échelle pour le prochain tour (Zoom In)
        scale *= zoom_factor;
    }

    // Libération de la toute dernière image restée en mémoire
    if (has_prev) {
        free_mandel(&prev_img);
    }
    
    printf("Génération terminée ! Utilisez ffmpeg pour créer la vidéo.\n");
}


// Générer une série d'images à partir de paramètres donnés
void generate_batch(double start_x, double start_y, double start_scale, int count, int start_num) {
    // On retrouve le centre de l'image (la cible du zoom) à partir des coordonnées reçues
    double width_math = start_scale * 3.0;
    double height_math = width_math * ((double)HEIGHT / LENGTH); // On utilise les constantes par défaut
    
    double target_x = start_x + width_math / 2.0;
    double target_y = start_y + height_math / 2.0;
    
    double current_scale = start_scale;
    double zoom_factor = 0.90; // Le même facteur que dans l'exercice 4
    
    mandel_pic prev_img;
    int has_prev = 0;

    printf("[Batch %d] Démarrage : %d images à partir de l'image %d\n", start_num, count, start_num);

    for (int k = 0; k < count; k++) {
        // 1. Calcul des bornes actuelles
        double w = current_scale * 3.0;
        double h = w * ((double)HEIGHT / LENGTH);
        
        double x_min = target_x - (w / 2.0);
        double y_min = target_y - (h / 2.0);

        // 2. Création
        // Note: On utilise les dimensions par défaut LENGTH/HEIGHT (900x600) ou celles de la commande
        // Pour simplifier ici on utilise les defines LENGTH/HEIGHT
        mandel_pic current = new_mandel(LENGTH, HEIGHT, x_min, y_min, current_scale);

        // 3. Calcul (Optimisé)
        if (has_prev) {
            compute_mandel_optimized(&current, &prev_img);
            free_mandel(&prev_img);
        } else {
            // Pour la première image du batch, pas d'interpolation possible (on n'a pas l'image d'avant)
            compute_mandel_optimized(&current, NULL);
        }

        // 4. Sauvegarde
        char filename[64];
        sprintf(filename, "frame%03d.ppm", start_num + k);
        save_mandel(&current, filename);
        
        // 5. Préparation suivante
        prev_img = current;
        has_prev = 1;
        current_scale *= zoom_factor;
    }

    if (has_prev) free_mandel(&prev_img);
    printf("[Batch %d] Terminé !\n", start_num);
}

picture new_pic(int width, int height) {
    // printf("Création d'une image %dx%d\n", width, height);
    picture p;
    p.width = width;
    p.height = height;
    
    // Allocation du tableau de pixels
    p.pixels = (Pixel *)malloc(width * height * sizeof(Pixel));
    
    if (p.pixels == NULL) {
        fprintf(stderr, "Erreur : échec de l'allocation mémoire pour les pixels\n");
        exit(1);
    }
    return p;
}

void clean_pic(picture *p) {
    if(p->pixels != NULL) {
        free(p->pixels);
        p->pixels = NULL;
    }
}

int save_pic(picture *p, char *filename) {
    FILE* f = fopen(filename, "w");
    if (!f) {
        printf("Le fichier %s est non ouvrable/modifiable !\n", filename);
        return 0;
    }

    // en tete ppm
    fprintf(f, "P3\n%d %d\n%d\n", p->width, p->height, OPACITY);

    for (int j = 0; j < p->height; j++) {
        for (int i = 0; i < p->width; i++) {
            // remplir les pixels
            Pixel px = p->pixels[j * p->width + i];

            fprintf(f, "%d %d %d ", px.r, px.g, px.b);
        }
        fprintf(f, "\n");
    };

    fclose(f);
    printf("Image %s sauvegardée.\n", filename);
    return 1;
}

int set_pixel(picture *p, int x, int y, Pixel color) {
    if(x >= 0 && x < p->width && y >= 0 && y < p->height) {
        int index = y * p->width + x;
        p->pixels[index] = color;
    }
};


int draw_line(picture *p, int x0, int y0, int x1, int y1, Pixel color) {
    // nombre de pixels à dessiner
    int n = fmax(abs(x0-x1), abs(y0-y1)) + 1;

    for(int i = 0; i <= n; i++) {
        int x = x0 + i * (x1 - x0) / n;
        int y = y0 + i * (y1 - y0) / n;
        set_pixel(p, x, y, color);
    }
};

int sierpinski(picture *p, double x, double y, double dimension, Pixel color) {
    double hauteur = dimension * sqrt(3.0) / 2.0;

    double top_x = x + dimension / 2.0;
    double top_y = y - hauteur;

    for (int j = (int)top_y; j <= (int)y; j++) {
        // si on sort de l'image en hauteur, on ignore
        if(j<0 || j >= p->height) continue;

        // calcul de la progression 0.0 au sommet et 1.0 à la base -> pour savoir quelle largeur faire face à cette hauteur
        double progress = (j - top_y) / hauteur;

        // la demi-largeyr à cette ligne précise
        double half_span = (dimension / 2.0) * progress;

        // calcul des bornes gauche et droite pour cette ligne
        int start_x = (int)(top_x - half_span);
        int end_x = (int)(top_x + half_span);

        // remplissage horizontal
        for(int i = start_x; i <= end_x; i ++) {
            set_pixel(p, i, j, color);
        }
    }

    return 1;
};


int sierpinski_div(picture *p, double x, double y, double dimension, Pixel color) {
    // je dois prendre 3 triangles et de les crées de plus en plus petits en dessou du précédent !
    // je dois le créer en utilisant la fonction sierpinski

    double demi_taille = dimension / 2.0;

    if(dimension < 300) {
        sierpinski(p, x, y, demi_taille, color);
        return 1;
    }

    sierpinski(p, x, y, demi_taille, color);
    sierpinski(p, x + demi_taille, y, demi_taille, color);
    sierpinski(p, (x + dimension / 4.0), (y - dimension * sqrt(3.0)/4.0), demi_taille, color);

    return 1;
};


int sierpinski_pro_max(picture *p, double x, double y, double dimension, Pixel color) {

    if(dimension >= SEUIL_SIERPINSKI) {
        double demi_taille = dimension / 2.0;
        double offset_h = dimension * sqrt(3.0) / 4.0;

        Pixel dark_color = assombrir(color, 0.7);

        sierpinski_pro_max(p, x, y, demi_taille, dark_color);
        sierpinski_pro_max(p, x + demi_taille, y, demi_taille, dark_color);
        sierpinski_pro_max(p, (x + dimension / 4.0), (y - offset_h), demi_taille, dark_color);

        return 1;
    }

    double hauteur = dimension * sqrt(3.0) / 2.0;
    double top_x = x + dimension / 2.0;
    double top_y = y - hauteur;

    for (int j = (int)top_y; j <= (int)y; j++) {
        // si on sort de l'image en hauteur, on ignore
        if(j<0 || j >= p->height) continue;

        // calcul de la progression 0.0 au sommet et 1.0 à la base -> pour savoir quelle largeur faire face à cette hauteur
        double progress = (j - top_y) / hauteur;

        // la demi-largeyr à cette ligne précise
        double half_span = (dimension / 2.0) * progress;

        // calcul des bornes gauche et droite pour cette ligne
        int start_x = (int)(top_x - half_span);
        int end_x = (int)(top_x + half_span);

        // remplissage horizontal
        for(int i = start_x; i <= end_x; i ++) {
            set_pixel(p, i, j, color);
        }
    }

    return 1;
};

Pixel assombrir(Pixel p, double facteur) {
    Pixel c;
    c.r = (unsigned char)(p.r * facteur);
    c.g = (unsigned char)(p.g * facteur);
    c.b = (unsigned char)(p.b * facteur);
    return c;
}

int reader(picture *p, char *filename, Pixel color) {
    // on lit le fichier ./subject/cat.txt ou ./subject/kang.txt
    FILE *f = fopen(filename, "r");
    if(f == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier %s\n", filename);
        return 0;
    }

    double x1, x2, y1, y2;
    int line_count = 0;

    while(fscanf(f, "%lf %lf %lf %lf", &x1, &x2, &y1, &y2) == 4) {
        draw_line(p, x1, x2, y1, y2, color);
        line_count++;
    }

    fclose(f);
    printf("%d segments ont été tracés depuis %s\n", line_count, filename);

    return 1;    
}

vector* read_vector_file(char *filename) {
    FILE *f = fopen(filename, "r");
    if(f == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier %s\n", filename);
        return NULL;
    }

    vector *head = NULL;
    vector *new_element = NULL;
    double x1, x2, y1, y2;
    int count = 0;

    while(fscanf(f, "%lf %lf %lf %lf", &x1, &x2, &y1, &y2) == 4) {
        new_element = malloc(sizeof(vector));
        
        if(new_element == NULL) break;

        new_element->x1 = x1;
        new_element->x2 = x2;
        new_element->y1 = y1;
        new_element->y2 = y2;

        new_element->next = head;
        head = new_element;

        count++;
    }

    fclose(f);
    printf("%d segments chargés en mémoire depuis %s\n", count, filename);

    return head;
}

void draw_vector(picture *p, vector *v, Pixel color) {
    while(v != NULL) {
        draw_line(p, (int)v->x1, (int)v->x2, (int)v->y1, (int)v->y2, color);
        v = v->next;
    }
}

void scale_vector(vector *v, double scale) {
    v->x1 = v->x1 * scale;
    v->x2 = v->x2 * scale;
    v->y1 = v->y1 * scale;
    v->y2 = v->y2 * scale;
}