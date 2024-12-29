#include "../include/map.h"
#include "../include/elements.h"
#include "../include/utils.h"
#include <stdlib.h>
#include <stdio.h>

// ==============================
// Section: Fonctions de gestion de la carte
// ==============================

// Initialiser la carte : remplissage des cases avec des murs et des espaces vides
void InitializeMap(Map *map) {
    CheckMultiplePointers(map, map->Grille, NULL);
    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Cols; j++) {
            map->Grille[i][j] = (i == 0 || j == 0 || i == Rows - 1 || j == Cols - 1) ? MUR : VIDE;
        }
    }
}

// Reinitialiser la carte : reinitialise la carte en redessinant les murs et espaces vides
void ResetMap(Map *map) {
    CheckMultiplePointers(map, map->Grille, NULL);
    InitializeMap(map); 
}

// ==============================
// Section: Fonctions d'affichage
// ==============================

// Dessiner une ligne derriere le joueur sur la carte
void DrawLineOnMap(Map *map, int id, int x, int y) {
    CheckMultiplePointers(map, map->Grille, NULL);
    map->Grille[x][y] = id * 2;  // Marque la case avec une valeur basee sur l'ID du joueur
}

// Afficher la carte dans la console
void DisplayMap(Map *map) {
    CheckMultiplePointers(map, map->Grille, NULL);
    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Cols; j++) {
            printf("%d ", map->Grille[i][j]);
        }
        printf("\n");
    }
}

// Effacer une ligne sur la carte 
void ClearLineOnMap(Map *map, int x, int y) {
    CheckMultiplePointers(map, map->Grille, NULL);
    map->Grille[x][y] = VIDE;
}


