#include "../include/game.h"
#include "../include/display.h"
#include "../include/elements.h"
#include "../include/utils.h"


#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include <stdio.h>

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 800;

// ==============================
// Section: Initialisation et terminaison de SDL
// ==============================


// Fonction pour initialiser SDL
bool InitSDL(DisplayContext *display) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        CheckSDLError(__LINE__);
    }

    display->window = SDL_CreateWindow(
        "Tron Game", 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        WINDOW_WIDTH, 
        WINDOW_HEIGHT, 
        SDL_WINDOW_SHOWN
    );

    if (display->window == NULL) {
        CheckSDLError(__LINE__);
    }

    display->renderer = SDL_CreateRenderer(display->window, -1, SDL_RENDERER_ACCELERATED);
    if (display->renderer == NULL) {
        CheckSDLError(__LINE__);
    }

    if (TTF_Init() == -1) {
        CheckTTFError(__LINE__);
    }

    return true;
}

// Fonction pour terminer SDL
void EndSDL(DisplayContext *display) {
    if (display->renderer) {
        SDL_DestroyRenderer(display->renderer);
        display->renderer = NULL;
    }

    if (display->window) {
        SDL_DestroyWindow(display->window);
        display->window = NULL;
    }

    TTF_Quit();
    SDL_Quit();
}

// ==============================
// Section: Fonctions d'affichage de texte
// ==============================

// Fonction pour afficher du texte avec SDL_ttf
void renderText(SDL_Renderer *renderer, const char* text, int x, int y) {
    TTF_Font *font = TTF_OpenFont("assets/Fonts/Monas-BLBW8.ttf", 72);
    if (font == NULL) {
        CheckTTFError(__LINE__);
    }

    SDL_Color color = {255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    if (surface == NULL) {
        CheckTTFError(__LINE__);
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) {
        CheckSDLError(__LINE__);
    }

    SDL_Rect rect = {x - surface->w / 2, y - surface->h / 2, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}

// ==============================
// Section: Fonctions d'affichage de compte a rebours et de score
// ==============================

// Fonction pour afficher un compte a rebours
void displayCountdownSDL(SDL_Renderer *renderer) {
    char countdown[3];

    for (int i = 3; i > 0; i--) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        sprintf(countdown, "%d", i);
        renderText(renderer, countdown, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
        SDL_RenderPresent(renderer);
        SDL_Delay(1000);
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    renderText(renderer, "C'est parti !", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    SDL_RenderPresent(renderer);
    SDL_Delay(1000);
}

// Fonction pour afficher le score
void displayScore(SDL_Renderer *renderer, Player *player1, Player *player2) {
    char scoreText[50];
    sprintf(scoreText, "Joueur 1 [ %d ] - [ %d ] Joueur 2", GetPlayerScore(player1), GetPlayerScore(player2));

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    renderText(renderer, "Score des Joueurs", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 200);
    renderText(renderer, scoreText, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    SDL_RenderPresent(renderer);
    SDL_Delay(2500);
}

// ==============================
// Section: Fonctions de dessin de la carte
// ==============================

// Fonction pour dessiner une cellule
void DrawCell(SDL_Renderer* renderer, int i, int j, int cellWidth, int cellHeight, int cellType) {
    SDL_Color color = GetCellColor(cellType);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    SDL_Rect rect = { j * cellWidth, i * cellHeight, cellWidth, cellHeight };
    SDL_RenderFillRect(renderer, &rect);
}

// Fonction pour obtenir la couleur d'une cellule
SDL_Color GetCellColor(int cellType) {
    switch (cellType) {
        case VIDE: return (SDL_Color){255, 255, 255, 255}; // Blanc
        case MUR: return (SDL_Color){0, 0, 0, 255}; // Noir
        case JOUEUR_1: return (SDL_Color){0, 0, 255, 255}; // Bleu pour Joueur 1
        case JOUEUR_2: return (SDL_Color){255, 0, 0, 255}; // Rouge pour Joueur 2
        case LIGNE_JOUEUR_1: return (SDL_Color){0, 255, 255, 255}; // Cyan pour la ligne du Joueur 1
        case LIGNE_JOUEUR_2: return (SDL_Color){255, 255, 0, 255}; // Jaune pour la ligne du Joueur 2
        default: return (SDL_Color){128, 128, 128, 255}; // Gris par défaut
    }
}

// Fonction pour afficher la carte
void DrawSDL(SDL_Renderer* renderer, Map *map, int rows, int cols) {
    int cellWidth = WINDOW_WIDTH / cols;
    int cellHeight = WINDOW_HEIGHT / rows;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            DrawCell(renderer, i, j, cellWidth, cellHeight, map->Grille[i][j]);
        }
    }
}

// ==============================
// Section: Affichage et gestion de l'ecran de fin
// ==============================

// Fonction pour afficher l'ecran de fin
void displayEndScreen(SDL_Renderer *renderer, GameState gameState, Player *player1, Player *player2) {
    const char* winnerText;
    if (gameState == PLAYER1_WON) winnerText = "Joueur 1 a gagne !";
    if (gameState == PLAYER2_WON) winnerText = "Joueur 2 a gagne !";

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    char scoreText[50];
    sprintf(scoreText, "Joueur 1 [ %d ] - [ %d ] Joueur 2", GetPlayerScore(player1), GetPlayerScore(player2));
    renderText(renderer, scoreText, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 300);

    renderText(renderer, winnerText, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 200);
    renderText(renderer, "Rejouer", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    renderText(renderer, "Retour au Menu", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 100);

    SDL_RenderPresent(renderer);
}

// Fonction pour gerer les evenements de l'ecran de fin
int handleEndScreenEvents(SDL_Renderer *renderer, GameState gameState, Player *player1, Player *player2) {
    SDL_Event event;
    int choice = 1;
    int quit = 0;
    int selectedOption = 0;

    while (!quit) {
        SDL_WaitEvent(&event);

        if (event.type == SDL_QUIT) {
            choice = 1;
            quit = 1;
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                case SDLK_DOWN:
                    selectedOption = !selectedOption;
                    displayEndScreen(renderer, gameState, player1, player2);
                    if (selectedOption == 1) {
                        renderText(renderer, "> Rejouer <", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
                        renderText(renderer, "Retour au Menu", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 100);
                    } else {
                        renderText(renderer, "Rejouer", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
                        renderText(renderer, "> Retour au Menu <", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 100);
                    }
                    SDL_RenderPresent(renderer);
                    break;
                case SDLK_RETURN:
                    choice = selectedOption;
                    quit = 1;
                    break;
            }
        }
    }

    return choice;
}

// ==============================
// Section: Affichage et gestion du menu
// ==============================

// Fonction pour afficher le menu
void displayMenuSDL(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    renderText(renderer, "Tron Game", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 200);
    renderText(renderer, "Jouer", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    renderText(renderer, "Quitter", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 100);

    SDL_RenderPresent(renderer);
}

// Fonction pour gerer les evenements du menu
int handleMenuEvents(SDL_Renderer *renderer) {
    SDL_Event event;
    int choice = 1;
    int quit = 0;
    int selectedOption = 0;

    while (!quit) {
        SDL_WaitEvent(&event);

        if (event.type == SDL_QUIT) {
            choice = 0;
            quit = 1;
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                case SDLK_DOWN:
                    selectedOption = !selectedOption;
                    displayMenuSDL(renderer);
                    if (selectedOption == 1) {
                        renderText(renderer, "> Jouer <", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
                        renderText(renderer, "Quitter", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 100);
                    } else {
                        renderText(renderer, "Jouer", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
                        renderText(renderer, "> Quitter <", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 100);
                    }
                    SDL_RenderPresent(renderer);
                    break;
                case SDLK_RETURN:
                    choice = selectedOption;
                    quit = 1;
                    break;
            }
        }
    }

    return choice;
}

// ==============================
// Section: Affichage et gestion de la selection du mode de jeu 
// ==============================

// Fonction pour afficher la selection du mode de jeu
void displayModeDeJeuSDL(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    renderText(renderer, "Selection du mode de jeu", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 200);
    renderText(renderer, "Bo3", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    renderText(renderer, "Bo5", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 100);

    SDL_RenderPresent(renderer);
}

// Fonction pour gerer les evenements de la selection du mode de jeu
int handleModeDeJeuEvents(SDL_Renderer *renderer) {
    SDL_Event event;
    int choice = 1;
    int quit = 0;
    int selectedOption = 0;

    while (!quit) {
        SDL_WaitEvent(&event);

        if (event.type == SDL_QUIT) {
            choice = 0;
            quit = 1;
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                case SDLK_DOWN:
                    selectedOption = !selectedOption;
                    displayModeDeJeuSDL(renderer);
                    if (selectedOption == 1) {
                        renderText(renderer, "> Bo3 <", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
                        renderText(renderer, "Bo5", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 100);
                        renderText(renderer, "Le premier a 2 points gagne", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 300);
                    } else {
                        renderText(renderer, "Bo3", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
                        renderText(renderer, "> Bo5 <", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 100);
                        renderText(renderer, "Le premier a 3 points gagne", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 300);
                    }
                    SDL_RenderPresent(renderer);
                    break;
                case SDLK_RETURN:
                    choice = selectedOption;
                    quit = 1;
                    break;
            }
        }
    }

    return choice;
}

// ==============================
// Autres fonctions
// ==============================


// Fonction pour afficher les touches des joueurs
void displayControls(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Affichage des touches pour le joueur 1
    SDL_Color blue = {0, 0, 255, 255};
    renderTextWithColor(renderer, "Joueur 1", WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2 - 170, blue);
    renderText(renderer, "Z", WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2 - 80);
    renderText(renderer, "Q", WINDOW_WIDTH / 4 - 60, WINDOW_HEIGHT / 2);
    renderText(renderer, "S", WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2);
    renderText(renderer, "D", WINDOW_WIDTH / 4 + 60, WINDOW_HEIGHT / 2);

    // Affichage des touches pour le joueur 2
    SDL_Color red = {255, 0, 0, 255};
    renderTextWithColor(renderer, "Joueur 2", 3 * WINDOW_WIDTH / 4 - 20, WINDOW_HEIGHT / 2 - 170, red);
    renderText(renderer, "\u2191", 3 * WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2 - 100);
    renderText(renderer, "\u2190", 3 * WINDOW_WIDTH / 4 - 60, WINDOW_HEIGHT / 2);
    renderText(renderer, "\u2193", 3 * WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2);
    renderText(renderer, "\u2192", 3 * WINDOW_WIDTH / 4 + 60, WINDOW_HEIGHT / 2);

    SDL_RenderPresent(renderer);
    SDL_Delay(5000);
}

// Fonction pour afficher du texte avec SDL_ttf et couleur
void renderTextWithColor(SDL_Renderer *renderer, const char* text, int x, int y, SDL_Color color) {
    TTF_Font *font = TTF_OpenFont("assets/Fonts/Monas-BLBW8.ttf", 72);
    if (font == NULL) {
        CheckTTFError(__LINE__);
    }

    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    if (surface == NULL) {
        CheckTTFError(__LINE__);
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) {
        CheckSDLError(__LINE__);
    }

    SDL_Rect rect = {x - surface->w / 2, y - surface->h / 2, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}