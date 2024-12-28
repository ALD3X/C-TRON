#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "map.h"
#include "player.h"

typedef enum {
    DISPLAY_NCURSES,
    DISPLAY_SDL
} DisplayType;

typedef struct {
    DisplayType type;        // Type d'affichage (ncurses ou SDL)
    SDL_Window* window;      // Fenetre SDL
    SDL_Renderer* renderer;  // Renderer SDL
} DisplayContext;


// ====================================================
//                    FONCTIONS
// ====================================================

// Initialise l'affichage
void InitDisplay(DisplayContext *display);

// Termine l'affichage
void EndDisplay(DisplayContext *display);

// Dessine la carte
void DrawMap(DisplayContext *display, Map *map);

// ====================================================
//              FONCTIONS SPECIFIQUES A SDL
// ====================================================

// Initialise SDL
bool InitSDL(DisplayContext *display);

// Termine SDL
void EndSDL(DisplayContext *display);

// Affiche du texte avec SDL
void renderText(SDL_Renderer *renderer, const char* text, int x, int y, SDL_Color color);

// Affiche le compte a rebours avec SDL
void displayCountdownSDL(SDL_Renderer *renderer);

// Dessine une cellule avec SDL
void DrawCell(SDL_Renderer* renderer, int i, int j, int cellWidth, int cellHeight, int cellType);

// Recupere la couleur d'une cellule
SDL_Color GetCellColor(int cellType);

// Dessine la carte avec SDL
void DrawSDL(SDL_Renderer* renderer, Map *map, int rows, int cols);

// Affiche l'ecran de fin avec SDL
void displayEndScreen(SDL_Renderer *renderer, GameState gameState, Player *player1, Player *player2, int selectedOption);

// Gere les evenements de l'ecran de fin
int handleEndScreenEvents(SDL_Renderer *renderer, GameState gameState, Player *player1, Player *player2, DisplayContext *display);

// Affiche le menu avec SDL
void displayMenuSDL(SDL_Renderer *renderer, int selectedOption);

// Gere les evenements du menu
int handleMenuEvents(SDL_Renderer *renderer);

// Affiche le score des joueurs
void displayScore(SDL_Renderer *renderer, Player *player1, Player *player2);

// Affiche la selection du mode de jeu avec SDL
void displayModeDeJeuSDL(SDL_Renderer *renderer, int selectedOption);

// Gere les evenements de la selection du mode de jeu
int handleModeDeJeuEvents(SDL_Renderer *renderer, DisplayContext *display);

// Affiche les touches des joueurs
void displayControls(SDL_Renderer *renderer);

void renderUnicode(SDL_Renderer *renderer, const char* text, int x, int y, SDL_Color color);


// ====================================================
//              FONCTIONS SPECIFIQUES A NCURSES
// ====================================================

// Initialise ncurses
void InitNcurses();

// Termine ncurses
void EndNcurses();

// Dessine la carte avec ncurses
void DrawNcurses(DisplayContext *display, Map *map);

// Initialise les couleurs avec ncurses
void InitColors(); 

// Affiche le compte a rebours avec ncurses
void displayCountdownNcurses();

// Affiche le menu avec ncurses
void displayMenuNcurses(int selectedOption);

int handleMenuEventsNcurses();

void displayModeDeJeuNcurses(int selectedOption);

int handleModeDeJeuEventsNcurses();

void displayEndScreenNcurses(GameState gameState, Player *player1, Player *player2, int selectedOption);

int handleEndScreenEventsNcurses(GameState gameState, Player *player1, Player *player2);

void displayScoreNcurses(Player *player1, Player *player2);
void displayControlsNcurses();

#endif // DISPLAY_H
