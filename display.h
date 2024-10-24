// display.h

#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "map.h"
#include "elements.h"
#include <ncurses.h>
#include <SDL2/SDL.h>

// Type d'affichage (pour sélectionner l'affichage)
typedef enum {
    DISPLAY_NCURSES,
    DISPLAY_SDL
} DisplayType;

// Structure pour le contexte d'affichage
typedef struct {
    DisplayType type;        // Type d'affichage (ncurses ou SDL)
    SDL_Window* window;      // Fenêtre SDL
    SDL_Renderer* renderer;  // Renderer SDL
} DisplayContext;

// Déclarations des fonctions
void InitDisplay(DisplayContext *display);
void EndDisplay(DisplayContext *display);
void DrawMap(DisplayContext *display, Map *map);

// Fonctions spécifiques à SDL
bool InitSDL(DisplayContext *display);
void EndSDL(DisplayContext *display);
void DrawSDL(SDL_Renderer* renderer, Map *map, int rows, int cols);

// Fonctions spécifiques à ncurses
void InitNcurses();
void EndNcurses();
void DrawNcurses(DisplayContext *display, Map *map);
void InitColors(); // Ajoutez cette ligne

#endif // DISPLAY_H
