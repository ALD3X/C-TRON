#ifndef INPUT_H
#define INPUT_H

#include "player.h"
#include "map.h"
#include <ncurses.h>
#include <SDL2/SDL.h>

// ====================================================
//                    FONCTIONS
// ====================================================

// Gere les controles du joueur 1
void HandlePlayer1Controls(Player *player, int input);

// Gere les controles du joueur 2 avec ncurses
void HandlePlayer2ControlsNcurses(Player *player, int input);

// Gere les controles du joueur 2 avec SDL
void HandlePlayer2ControlsSDL(Player *player, int input);

// Gere les entrees des joueurs avec ncurses
void HandlePlayerInputNcurses(Player *player1, Player *player2, Map *map);

// Gere les entrees des joueurs avec SDL
void HandlePlayerInputSDL(Player *player1, Player *player2, Map *map);

#endif // INPUT_H
