// map.h 

#ifndef MAP_H
#define MAP_H

#include <stdlib.h> 
#include <stdio.h>
#include "elements.h"
#include "utils.h"


// Declaration de la taille de la carte 
#define Rows 50
#define Cols 50

typedef struct{
    int Grille[Rows][Cols];
} Map;

void InitializeMap(Map *map);
void ResetMap(Map *map);
void DrawLineOnMap(Map *map, int id ,int x, int y);


#endif // MAP_H