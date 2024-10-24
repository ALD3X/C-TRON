// game.h

#ifndef GAME_H
#define GAME_H

#include <stdio.h>     // Pour printf, fprintf, etc.
#include <stdlib.h>    // Pour exit, malloc, etc.
#include "game.h"      // Pour les définitions de GameState et des prototypes de fonction
#include "player.h"    // Pour la définition de la structure Player
#include "map.h"       // Pour la définition de la structure Map
#include "utils.h"     // Pour CheckPointer, si nécessaire

// Énumération pour les états du jeu
typedef enum {
    GAME_ONGOING,
    PLAYER1_WON,
    PLAYER2_WON
} GameState;

// Fonction pour vérifier l'état du jeu
GameState CheckGameState(const Player *player1, const Player *player2);

// Fonction pour ajouter un score à un joueur
void AddPlayerScore(Player *player);

// Fonction pour réinitialiser la vie d'un joueur
void ResetPlayerLive(Player *player);

// Fonction pour redémarrer le jeu
void RestartGame(Player *player1, Player *player2, Map *map);

// Fonction pour retourner le score du joueur 
int GetPlayerScore(const Player *player);

#endif // GAME_H
