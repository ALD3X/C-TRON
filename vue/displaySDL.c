#include "display.h"

// Dimensions de la fenêtre
const int WINDOW_WIDTH = 1000;  // Largeur de la fenêtre
const int WINDOW_HEIGHT = 800;  // Hauteur de la fenêtre

// Fonction pour initialiser SDL
bool InitSDL(DisplayContext *display) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Erreur d'initialisation de SDL : %s\n", SDL_GetError());
        return false;
    }

    // Création de la fenêtre
    display->window = SDL_CreateWindow(
        "Tron Game", 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        WINDOW_WIDTH, 
        WINDOW_HEIGHT, 
        SDL_WINDOW_SHOWN
    );

    if (display->window == NULL) {
        fprintf(stderr, "Erreur de création de la fenêtre : %s\n", SDL_GetError());
        SDL_Quit();
        return false;
    }

    // Création du renderer
    display->renderer = SDL_CreateRenderer(display->window, -1, SDL_RENDERER_ACCELERATED);
    if (display->renderer == NULL) {
        fprintf(stderr, "Erreur de création du renderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(display->window);
        SDL_Quit();
        return false;
    }

    // Initialiser SDL_ttf
    if (TTF_Init() == -1) {
        fprintf(stderr, "Erreur d'initialisation de SDL_ttf : %s\n", TTF_GetError());
        return false;
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

    // Terminer SDL_ttf
    TTF_Quit();
    SDL_Quit();
}

// Fonction pour afficher du texte avec SDL_ttf
void renderText(SDL_Renderer *renderer, const char* text, int x, int y) {
    TTF_Font *font = TTF_OpenFont("assets/Fonts/Monas-BLBW8.ttf", 72);
    if (font == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture de la police : %s\n", TTF_GetError());
        exit(1);
    }

    SDL_Color color = {255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rect = {x - surface->w / 2, y - surface->h / 2, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}

// Fonction pour afficher un compte à rebours
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
        case VIDE: return (SDL_Color){249, 235, 234};
        case MUR: return (SDL_Color){171, 178, 185};
        case JOUEUR_1: return (SDL_Color){142, 68, 173};
        case JOUEUR_2: return (SDL_Color){22, 160, 133};
        case LIGNE_JOUEUR_1: return (SDL_Color){210, 180, 222};
        case LIGNE_JOUEUR_2: return (SDL_Color){163, 228, 215};
        default: return (SDL_Color){128, 128, 128}; // Gris
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

void displayEndScreen(SDL_Renderer *renderer, GameState gameState) {
    const char* winnerText;
    if (gameState == PLAYER1_WON) {
        winnerText = "Joueur 1 a gagne !";
    } else if (gameState == PLAYER2_WON) {
        winnerText = "Joueur 2 a gagne !";
    } else {
        winnerText = "Match nul !";
    }

    // Effacer l'écran
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Fond noir
    SDL_RenderClear(renderer);

    // Afficher le texte de victoire au centre
    renderText(renderer, winnerText, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 100);

    // Ajouter des instructions pour les clics de souris
    renderText(renderer, "Clic droit pour Rejouer", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 50);
    renderText(renderer, "Clic gauche pour Quitter", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 200);

    // Présenter à l'écran
    SDL_RenderPresent(renderer);
}


int handleEndScreenEvents(SDL_Renderer *renderer) {
    SDL_Event event;
    int replayClicked = -1;  // Valeur par défaut, indiquant qu'aucun choix n'a été fait.
    int quit = 0;  // Flag pour sortir de la boucle

    while (!quit) {
        SDL_WaitEvent(&event);

        if (event.type == SDL_QUIT) {
            quit = 1; // Quitter le jeu
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState(&x, &y);

            // Si le clic est à droite (1 pour droit)
            if (event.button.button == SDL_BUTTON_RIGHT) {
                replayClicked = 1; // Rejouer
                quit = 1;  // Sortir de la boucle
            }
            // Si le clic est à gauche (0 pour quitter)
            else if (event.button.button == SDL_BUTTON_LEFT) {
                replayClicked = 0; // Quitter
                quit = 1;  // Sortir de la boucle
            }
        }
    }

    return replayClicked; // 1 pour "Rejouer", 0 pour "Quitter"
}


