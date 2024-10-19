// player.h

#ifndef PLAYER_H
#define PLAYER_H

#include "map.h"

typedef struct 
{
    int x ; // Position X du joueur
    int y ; // Position Y du joueur
    int id ; // id du joueur 
    int isAlive ; // Etat du joueur (1: vivant, 0: mort)
}Player;

// Enum pour les directions
typedef enum {
    TOP,    
    RIGHT,  
    DOWN,     
    LEFT   
} Direction;


void InitPlayer(Player *player, Map *map,int x, int y, int id);
void MovePlayer(Player *player, Map *map, Direction direction);
int CrashTest(Map *map, int x, int y);
int IsCoordValide(int x, int y);
void CreateLigne(Map *map, Player *player, int x, int y);
void SpawnPlayers(Player *player1, Player *player2, Map *map);

#endif // PLAYER_H