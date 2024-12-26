#ifndef GAME_H
#define GAME_H

typedef enum {
    GAME_ONGOING,
    PLAYER1_WON,
    PLAYER2_WON,
    GAME_WAITING
} GameState;

#include "display.h"   
#include "player.h"    
#include "input.h"   

// ====================================================
//                    FONCTIONS
// ====================================================

// Redemarre le jeu
void RestartGame(Player *player1, Player *player2, Map *map);

// Initialise le jeu
void InitializeGame(Player *player1, Player *player2, Map *map);

// Met a jour le jeu
void UpdateGame(Player *player1, Player *player2, Map *map);

// Affiche l'etat du jeu
void DisplayGameState(const Player *player1, const Player *player2);

// Gere la boucle principale du jeu
void HandleGameLoop(DisplayContext *display, Player *player1, Player *player2, Map *map);

// Definie le mode de jeu
GameState ModeDeJeu(int mode, Player *player1, Player *player2, Map *map, DisplayContext *display);

#endif // GAME_H
