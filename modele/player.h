// player.h

#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "map.h"
#include "elements.h"

#define MAX_ATTEMPTS 100


typedef struct 
{
    int x;       // Position X du joueur
    int y;       // Position Y du joueur
    int id;      // ID du joueur 
    int score;   // Score du joueur
    int isAlive; // État du joueur (1: vivant, 0: mort)
} Player;

// Enum pour les directions
typedef enum {
    TOP,    
    RIGHT,  
    DOWN,     
    LEFT   
} Direction;

typedef enum {
    GAME_ONGOING,
    PLAYER1_WON,
    PLAYER2_WON,
} GameState;

// Fonctions pour les joueurs
void CheckPointer(void *ptr, const char *errorMessage);
void resetPLayerlive(Player *player);
void InitializePlayer(Player *player, int id);
GameState CheckGameState(const Player *player1, const Player *player2);
int CheckCollision(Map *map, int x, int y);
int IsCoordinateValid(int x, int y);
void AddPlayerScore(Player *player);
int GetPlayerScore(const Player *player);

void MovePlayerInDirection(Player *player, Map *map, Direction direction);
void CalculateNewPosition(Direction direction, int *x, int *y);
void RecordPlayerPath(Map *map, Player *player);
void UpdatePlayerPosition(Player *player, Map *map, int newX, int newY);
void HandlePlayerCollision(Player *player);

int GenerateValidCoordinates(int *x, int *y, Map *map);
void SpawnTwoPlayers(Player *player1, Player *player2, Map *map);



#endif // PLAYER_H
