#include "../include/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <ncurses.h>


// ==============================
// Section: Fonctions utilitaires
// ==============================

// Fonction pour verifier plusieurs pointeurs a la fois
void CheckMultiplePointersHelper(const char *file, int line, void *first_ptr, ...) {
    va_list args;
    va_start(args, first_ptr);

    void *ptr = first_ptr;
    int count = 1;

    while (ptr != NULL) {
        if (ptr == NULL) {
            LOG("Erreur: Le pointeur %d est NULL dans %s a la ligne %d.\n", count, file, line);
            exit(EXIT_FAILURE);
        }
        ptr = va_arg(args, void*);
        count++;
    }

    va_end(args);
}

// Fonction pour verifier les erreurs SDL
void CheckSDLError(int line) {
    const char *error = SDL_GetError();
    if (*error != '\0') {
        LOG("SDL Error: %s at line %d\n", error, line);
        SDL_ClearError();
        exit(EXIT_FAILURE);
    }
}

// Fonction pour verifier les erreurs TTF
void CheckTTFError(int line) {
    const char *error = TTF_GetError();
    if (*error != '\0') {
        LOG("TTF Error: %s at line %d\n", error, line);
        exit(EXIT_FAILURE);
    }
}

// Fonction pour verifier les erreurs ncurses
void CheckNcursesError(int result, int line) {
    if (result == ERR) {
        LOG("Ncurses Error at line %d\n", line);
        exit(EXIT_FAILURE);
    }
}


