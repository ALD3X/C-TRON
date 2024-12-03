// input.h

#ifndef INPUT_H
#define INPUT_H

#include <ncurses.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include "player.h"
#include "map.h"
#include "utils.h"
#include <ncurses.h>

// Fonction pour gérer les entrées du joueur
void HandlePlayerInputNcurses(Player *player1, Player *player2, Map *map);
void HandlePlayerInputSDL(Player *player1, Player *player2, Map *map);


#endif // INPUT_H
