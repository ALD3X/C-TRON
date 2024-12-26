#include "../include/input.h"
#include "../include/utils.h"
#include "../include/player.h"
#include "../include/map.h"
#include <ncurses.h>
#include <SDL2/SDL.h>
#include <stdio.h>

// ==============================
// Section: Fonctions de gestion des controles
// ==============================

// Fonction pour gerer les controles du joueur 1 avec les touches z, q, s, d
void HandlePlayer1Controls(Player *player, int input) {
    switch (input) {
        case 'z':    // Haut
            SwitchPlayerDirection(player, TOP);
            break;
        case 's':    // Bas
            SwitchPlayerDirection(player, DOWN);
            break;
        case 'q':    // Gauche
            SwitchPlayerDirection(player, LEFT);
            break;
        case 'd':    // Droite
            SwitchPlayerDirection(player, RIGHT);
            break;
        default:
            break; // Ignorer les autres entrees
    }
}

// Fonction pour gerer les controles du joueur 2 avec les touches flechees pour Ncurses
void HandlePlayer2ControlsNcurses(Player *player, int input) {
    switch (input) {
        case KEY_UP:    // Haut
            SwitchPlayerDirection(player, TOP);
            break;
        case KEY_DOWN:  // Bas
            SwitchPlayerDirection(player, DOWN);
            break;
        case KEY_LEFT:  // Gauche
            SwitchPlayerDirection(player, LEFT);
            break;
        case KEY_RIGHT: // Droite
            SwitchPlayerDirection(player, RIGHT);
            break;
        default:
            break; // Ignorer les autres entrees
    }
}

// Fonction pour gerer les controles du joueur 2 avec les touches flechees pour SDL
void HandlePlayer2ControlsSDL(Player *player, int input) {
    switch (input) {
        case SDLK_UP:    // Haut
            SwitchPlayerDirection(player, TOP);
            break;
        case SDLK_DOWN:  // Bas
            SwitchPlayerDirection(player, DOWN);
            break;
        case SDLK_LEFT:  // Gauche
            SwitchPlayerDirection(player, LEFT);
            break;
        case SDLK_RIGHT: // Droite
            SwitchPlayerDirection(player, RIGHT);
            break;
        default:
            break; // Ignorer les autres entrees
    }
}

// ==============================
// Section: Fonctions de gestion des entrees des joueurs
// ==============================

// Fonction pour gerer les entrees des joueurs avec Ncurses
void HandlePlayerInputNcurses(Player *player1, Player *player2, Map *map) {
    CheckMultiplePointers(map, map->Grille, player1, player2, NULL);
    int input = getch(); 

    // Gestion des entrees pour le joueur 1
    HandlePlayer1Controls(player1, input);

    // Gestion des entrees pour le joueur 2
    HandlePlayer2ControlsNcurses(player2, input);

    // Quitter le jeu
    if (input == 'e') {
        endwin();
        exit(0);
    }
}

// Fonction pour gerer les entrees des joueurs avec SDL
void HandlePlayerInputSDL(Player *player1, Player *player2, Map *map) {
    CheckMultiplePointers(map, map->Grille, player1, player2, NULL);

    SDL_Event event;

    // Gestion des evenements SDL
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            printf("Jeu quitte.\n");
            exit(0); // Sortie du programme
        }

        // Verifier si une touche est pressee
        if (event.type == SDL_KEYDOWN) {
            int input = event.key.keysym.sym;

            // Gestion des entrees pour le joueur 1
            HandlePlayer1Controls(player1, input);

            // Gestion des entrees pour le joueur 2
            HandlePlayer2ControlsSDL(player2, input);

            // Quitter le jeu
            if (input == SDLK_e) {
                printf("Jeu quitte.\n");
                exit(0); // Sortie du programme
            }
        }
    }
}
