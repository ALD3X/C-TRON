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

// Initialiser l'affichage
void InitDisplay(DisplayContext *display);

// Terminer l'affichage
void EndDisplay(DisplayContext *display);

// Dessiner la carte
void DrawMap(DisplayContext *display, Map *map);

// ====================================================
//              FONCTIONS SPECIFIQUES A SDL
// ====================================================

// Initialiser SDL
bool InitSDL(DisplayContext *display);

// Terminer SDL
void EndSDL(DisplayContext *display);

// Rendre du texte
void RenderText(SDL_Renderer *renderer, const char* text, int x, int y, SDL_Color color);

// Afficher le compte a rebours SDL
void DisplayCountdownSDL(SDL_Renderer *renderer);

// Dessiner une cellule
void DrawCell(SDL_Renderer* renderer, int i, int j, int cellWidth, int cellHeight, int cellType);

// Obtenir la couleur d'une cellule
SDL_Color GetCellColor(int cellType);

// Dessiner avec SDL
void DrawSDL(SDL_Renderer* renderer, Map *map, int rows, int cols);

// Afficher l'ecran de fin SDL
void DisplayEndScreenSDL(SDL_Renderer *renderer, GameState gameState, Player *player1, Player *player2, int selectedOption);

// Gerer les evenements de l'ecran de fin SDL
int HandleEndScreenEventsSDL(SDL_Renderer *renderer, GameState gameState, Player *player1, Player *player2, DisplayContext *display);

// Afficher le menu SDL
void DisplayMenuSDL(SDL_Renderer *renderer, int selectedOption);

// Gerer les evenements du menu SDL
int HandleMenuEventsSDL(SDL_Renderer *renderer);

// Afficher le score SDL
void DisplayScoreSDL(SDL_Renderer *renderer, Player *player1, Player *player2);

// Afficher le mode de jeu SDL
void DisplayModeDeJeuSDL(SDL_Renderer *renderer, int selectedOption);

// Gerer les evenements du mode de jeu SDL
int HandleModeDeJeuEventsSDL(SDL_Renderer *renderer, DisplayContext *display);

// Afficher les controles SDL
void DisplayControlsSDL(SDL_Renderer *renderer);

// Rendre du texte Unicode
void RenderUnicode(SDL_Renderer *renderer, const char* text, int x, int y, SDL_Color color);

// Charger une musique
Mix_Music* LoadMusic(const char* filePath);

// Charger un son
Mix_Chunk* LoadSound(const char* filePath);

// Jouer une musique
void PlayMusic(Mix_Music* music, int loops, int volume);

// Jouer un son
void PlaySound(Mix_Chunk* sound, int volume);

// ====================================================
//              FONCTIONS SPECIFIQUES A NCURSES
// ====================================================

// Initialiser Ncurses
void InitNcurses();

// Terminer Ncurses
void EndNcurses();

// Dessiner avec Ncurses
void DrawNcurses(DisplayContext *display, Map *map);

// Initialiser les couleurs
void InitColors();

// Afficher le compte a rebours Ncurses
void DisplayCountdownNcurses();

// Afficher le menu Ncurses
void DisplayMenuNcurses(int selectedOption);

// Gerer les evenements du menu Ncurses
int HandleMenuEventsNcurses();

// Afficher le mode de jeu Ncurses
void DisplayModeDeJeuNcurses(int selectedOption);

// Gerer les evenements du mode de jeu Ncurses
int HandleModeDeJeuEventsNcurses();

// Afficher l'ecran de fin Ncurses
void DisplayEndScreenNcurses(GameState gameState, Player *player1, Player *player2, int selectedOption);

// Gerer les evenements de l'ecran de fin Ncurses
int HandleEndScreenEventsNcurses(GameState gameState, Player *player1, Player *player2);

// Afficher le score Ncurses
void DisplayScoreNcurses(Player *player1, Player *player2);

// Afficher les controles Ncurses
void DisplayControlsNcurses();

#endif // DISPLAY_H
