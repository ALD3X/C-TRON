#include "../include/game.h"
#include "../include/display.h"
#include "../include/player.h"
#include "../include/map.h"
#include "../include/input.h"
#include "../include/utils.h"
#include <stdio.h>
#include <stdlib.h>


// ==============================
// Section: Fonctions de reinitialisation
// ==============================

// Reinitialise le jeu
void RestartGame(Player *player1, Player *player2, Map *map) {
    CheckMultiplePointers(map, map->Grille, player1, player2, NULL);

    ResetPlayerLive(player1);
    ResetPlayerLive(player2); 
    ResetMap(map); 
    SpawnTwoPlayers(player1, player2, map); 
}

// ==============================
// Section: Fonctions d'initialisation
// ==============================

// Initialise le jeu
void InitializeGame(Player *player1, Player *player2, Map *map) {
    CheckMultiplePointers(map, map->Grille, player1, player2, NULL);

    InitializeMap(map);
    InitializePlayer(player1, 1);
    InitializePlayer(player2, 2);
    SpawnTwoPlayers(player1, player2, map);
    LOG("Jeu initialise.\n");
}

// ==============================
// Section: Fonctions de mise a jour
// ==============================

// Met a jour le jeu a chaque frame
void UpdateGame(Player *player1, Player *player2, Map *map) {
    CheckMultiplePointers(map, map->Grille, player1, player2, NULL);

    UpdatePlayerMovement(player1, map);
    UpdatePlayerMovement(player2, map);
    LOG("Jeu mis a jour.\n");
}

// ==============================
// Section: Fonctions d'affichage
// ==============================

// Affiche l'etat actuel du jeu
void DisplayGameState(const Player *player1, const Player *player2) {
    CheckMultiplePointers((void *)player1, (void *)player2, NULL);

    printf("Score du Joueur 1: %d\n", player1->score);
    printf("Score du Joueur 2: %d\n", player2->score);
    printf("Joueur 1 est %s\n", player1->isAlive ? "vivant" : "mort");
    printf("Joueur 2 est %s\n", player2->isAlive ? "vivant" : "mort");
}

// ==============================
// Section: Fonctions de gestion du mode de jeu
// ==============================

// Gere le mode de jeu
GameState ModeDeJeu(int mode, Player *player1, Player *player2, Map *map, DisplayContext *display) {
    int nb = (mode == 1) ? 2 : 3;
    displayControls(display->renderer);

    while (1) {
        switch (display->type) {
            case DISPLAY_SDL:
                DrawMap(display, map);
                HandlePlayerInputSDL(player1, player2, map);
                UpdatePlayerMovement(player1, map);
                UpdatePlayerMovement(player2, map);
                SDL_RenderPresent(display->renderer);

                if (player1->isAlive == 0) {
                    AddPlayerScore(player2);
                    RestartGame(player1, player2, map);

                    if (GetPlayerScore(player2) >= nb) return PLAYER2_WON;
                   
                    displayScore(display->renderer, player1, player2);
                    displayCountdownSDL(display->renderer);
                } else if (player2->isAlive == 0) {
                    AddPlayerScore(player1);
                    RestartGame(player1, player2, map);

                    if (GetPlayerScore(player1) >= nb) return PLAYER1_WON;

                    displayScore(display->renderer, player1, player2);
                    displayCountdownSDL(display->renderer);
                }

                break;

            case DISPLAY_NCURSES:
                // Implémentation pour NCurses ici
                break;

            default:
                fprintf(stderr, "Type d'affichage inconnu\n");
                exit(EXIT_FAILURE);
        }
    }

    return GAME_ONGOING; // Sécurité
}


// ==============================
// Section: Fonctions de gestion de la boucle de jeu
// ==============================

// Gere la boucle de jeu
void HandleGameLoop(DisplayContext *display, Player *player1, Player *player2, Map *map) {
    int running = 1;
    GameState state = GAME_WAITING;
    int modeDeJeu = -1;

    while (running) {
        int choice = -1;

        switch (display->type) {
            case DISPLAY_NCURSES:
                // Gerer le type d'affichage NCurses
                break;
            case DISPLAY_SDL:
                if (state == GAME_WAITING) {
                    displayMenuSDL(display->renderer);
                    choice = handleMenuEvents(display->renderer);
                    if (choice == 0) {
                        EndSDL(display);
                        exit(EXIT_SUCCESS);
                    } else {
                        state = GAME_ONGOING;
                        displayModeDeJeuSDL(display->renderer);
                        modeDeJeu = handleModeDeJeuEvents(display->renderer);
                        choice = -1;
                    }
                }
                break;
            default:
                fprintf(stderr, "Type d'affichage inconnu\n");
                exit(EXIT_FAILURE);
        }

        if (modeDeJeu != -1 && state == GAME_ONGOING) {
            state = ModeDeJeu(modeDeJeu, player1, player2, map, display);
        }

        if (state != GAME_ONGOING && state != GAME_WAITING) {
            if (display->type == DISPLAY_SDL) {
                displayEndScreen(display->renderer, state, player1, player2);
                choice = handleEndScreenEvents(display->renderer, state, player1, player2);
                if (choice == 1) {
                    ResetScores(player1, player2);
                    RestartGame(player1, player2, map);
                    state = GAME_ONGOING;
                    choice = -1;
                } else {
                    ResetScores(player1, player2);
                    RestartGame(player1, player2, map);
                    state = GAME_WAITING;
                    modeDeJeu = -1;
                    choice = -1;
                }
            } else {
                // Gerer l'ecran de fin NCurses
                break;
            }
        }
    }
}

