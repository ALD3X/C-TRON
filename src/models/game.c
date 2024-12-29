#include "../include/game.h"
#include "../include/display.h"
#include "../include/player.h"
#include "../include/map.h"
#include "../include/input.h"
#include "../include/utils.h"
#include "../include/elements.h"
#include <stdio.h>
#include <stdlib.h>

// ==============================
// Section: Fonctions de verification
// ==============================

// Verifie l'etat du jeu en fonction de la vie des joueurs
GameState CheckGameState(const Player *player1, const Player *player2) {
    CheckMultiplePointers((void *)player1, (void *)player2, NULL);

    if (!player1->isAlive) return PLAYER2_WON;
    if (!player2->isAlive) return PLAYER1_WON;
    if(player1->isAlive && player2->isAlive) return GAME_ONGOING;
    return GAME_WAITING;
}

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
    InitializePlayer(player1, JOUEUR_1);
    InitializePlayer(player2, JOUEUR_2);
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
// Section: Gestion du mode de jeu
// ==============================

// Gere le mode de jeu
GameState ModeDeJeu(int mode, Player *player1, Player *player2, Map *map, DisplayContext *display) {

    int nb;
    // Verification du mode de jeu
    if(mode == 0) nb = 2;
    else if(mode == 1) nb = 3;
    else return GAME_WAITING;
    

    // Affichage des controles et du compte a rebours
    if (display->type == DISPLAY_SDL) {
        DisplayControlsSDL(display->renderer);
        DisplayCountdownSDL(display->renderer);
    } else {
        DisplayControlsNcurses();
        DisplayCountdownNcurses();
    }

    // Boucle principale du jeu
    while (GetPlayerScore(player1) < nb && GetPlayerScore(player2) < nb) {
        DrawMap(display, map);

        // Gestion des entrees et des mouvements selon le type d'affichage
        if (display->type == DISPLAY_SDL) {
            HandlePlayerInputSDL(player1, player2, map);
        } else {
            HandlePlayerInputNcurses(player1, player2, map);
        }

        UpdatePlayerMovement(player1, map);
        UpdatePlayerMovement(player2, map);

        // Verification des scores et gestion des eliminations
        for (int i = 0; i < 2; i++) {
            Player *current = (i == 0) ? player1 : player2;
            Player *opponent = (i == 0) ? player2 : player1;

            if (!current->isAlive) {
                // Son du crash
                Mix_Chunk* sound_crash = LoadSound("assets/sounds/sound_crash.wav");
                PlaySound(sound_crash, 3);

                AddPlayerScore(opponent);
                RestartGame(player1, player2, map);

                if (display->type == DISPLAY_SDL) {
                    DisplayScoreSDL(display->renderer, player1, player2);
                    if (GetPlayerScore(player1) == nb) return PLAYER1_WON;
                    if (GetPlayerScore(player2) == nb) return PLAYER2_WON;
                    DisplayCountdownSDL(display->renderer);
                } else {
                    DisplayScoreNcurses(player1, player2);
                    if (GetPlayerScore(player1) == nb) return PLAYER1_WON;
                    if (GetPlayerScore(player2) == nb) return PLAYER2_WON;
                    DisplayCountdownNcurses();
                }
            }
        }

        // Rafraichissement de l'affichage SDL
        if (display->type == DISPLAY_SDL) {
            SDL_RenderPresent(display->renderer);
        }
    }

    return GAME_ONGOING;
}

// ==============================
// Section: Gestion de la boucle de jeu
// ==============================

// Gere la boucle de jeu
void HandleGameLoop(DisplayContext *display, Player *player1, Player *player2, Map *map) {
    int running = 1;
    GameState state = GAME_WAITING;
    int modeDeJeu = -1;

    while (running) {
        int choice = -1;

        // Gestion de l'etat "GAME_WAITING"
        if (state == GAME_WAITING) {
            if (display->type == DISPLAY_SDL) {
                choice = HandleMenuEventsSDL(display->renderer);
            } else {
                choice = HandleMenuEventsNcurses();
            }

            if (choice == 0) {
                EndDisplay(display);
                exit(EXIT_SUCCESS);
            } else {
                state = GAME_ONGOING;
                modeDeJeu = (display->type == DISPLAY_SDL) ? HandleModeDeJeuEventsSDL(display->renderer, display) : HandleModeDeJeuEventsNcurses();
            }
        }

        // Gestion de l'etat "GAME_ONGOING"
        if (modeDeJeu != -1 && state == GAME_ONGOING) {
            state = ModeDeJeu(modeDeJeu, player1, player2, map, display);
        }

        // Gestion de l'ecran de fin
        if (state != GAME_ONGOING && state != GAME_WAITING) {
            if (display->type == DISPLAY_SDL) {
                choice = HandleEndScreenEventsSDL(display->renderer, state, player1, player2, display);
            } else {
                choice = HandleEndScreenEventsNcurses(state, player1, player2);
            }

            if (choice == 1) {
                RestartGame(player1, player2, map);
                ResetScores(player1, player2);
                state = GAME_ONGOING;
            } else {
                RestartGame(player1, player2, map);
                ResetScores(player1, player2);
                state = GAME_WAITING;
                modeDeJeu = -1;
            }
        }
    }
}

