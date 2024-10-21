// map.h 

#ifndef MAP_H
#define MAP_H

#include <stdlib.h> // Ajoute ceci en haut de map.c
#include <stdio.h>
#include "elements.h"


// Declaration de la taille de la carte 
#define Rows 25
#define Cols 25

typedef struct{
    int Grille[Rows][Cols];
} Map;

void InitializeMap(Map *map);
void ResetMap(Map *map);
void DrawMap(Map *map);
void DrawLineOnMap(Map *map, int id ,int x, int y);


#endif // MAP_H