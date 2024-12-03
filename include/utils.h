#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"

// Macro pour vérifier les joueurs et la carte
#define CheckALL(count, map, ...) CheckPlayerAndMap((void*[]){__VA_ARGS__}, count, map)

// Fonction utilitaire pour vérifier les pointeurs et gérer les erreurs
void CheckPointer(void *ptr, const char *errorMessage);
void CheckMap(void *map);
void CheckPlayers(void **players, int player_count);   // Players devient un tableau de void*
void CheckPlayerAndMap(void **players, int nbPlayer, void *map);   // Players et map sont des void*
  
#endif // UTILS_H
