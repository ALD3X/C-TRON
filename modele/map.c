//map.c

#include "map.h"

// Initialiser la carte
void InitializeMap(Map *map) {
    if (map == NULL) {
        fprintf(stderr, "Erreur: La carte est nulle, impossible de l'initialiser.\n");
        exit(EXIT_FAILURE); // Quitter en cas d'erreur critique
    }

    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Cols; j++) {
            // Utiliser une condition pour remplir la grille
            map->Grille[i][j] = (i == 0 || j == 0 || i == Rows - 1 || j == Cols - 1) ? MUR : VIDE;
        }
    }
} // InitializeMap

// Réinitialiser la carte
void ResetMap(Map *map) {
    InitializeMap(map); // Reinitialiser en appelant InitializeMap
} // ResetMap

// Creer une ligne derrière le joueur
void DrawLineOnMap(Map *map, int id, int x, int y) {
    if (map != NULL) {
        map->Grille[x][y] = id * 2; // Dessiner la ligne
    } else {
        fprintf(stderr, "Erreur: La carte est nulle, impossible de dessiner la ligne.\n");
        exit(EXIT_FAILURE); // Quitter en cas d'erreur critique
    }
} // DrawLineOnMap

// Dessiner la carte
void DrawMap(Map *map) {
    if (map == NULL) {
        fprintf(stderr, "Erreur: La carte est nulle, impossible de l'afficher.\n");
        return; // Retourner en cas d'erreur
    }

    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Cols; j++) {
            char displayChar = ' '; // Caractere par défaut

            // Déterminer quel caractere afficher
            switch (map->Grille[i][j]) {
                case MUR: displayChar = '#'; break;
                case JOUEUR_1: displayChar = '@'; break;
                case JOUEUR_2: displayChar = '$'; break;
                case LIGNE_JOUEUR_1: displayChar = 'X'; break;
                case LIGNE_JOUEUR_2: displayChar = 'O'; break;
            }

            printf("%c", displayChar); // Afficher le caractere
        }
        printf("\n"); // Nouvelle ligne apres chaque ligne de la carte
    }
} // DrawMap
