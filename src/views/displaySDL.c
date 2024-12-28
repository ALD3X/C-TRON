#include "../include/game.h"
#include "../include/display.h"
#include "../include/elements.h"
#include "../include/utils.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include <stdio.h>

const int WINDOW_WIDTH = 1300;
const int WINDOW_HEIGHT = 800;

// ==============================
// Section: Initialisation et terminaison de SDL
// ==============================

// Fonction pour initialiser SDL
bool InitSDL(DisplayContext *display) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        CheckSDLError(__LINE__);
        return false;
    }

    // Créer la fenêtre sans l'option SDL_WINDOW_RESIZABLE
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
        return false;
    }

    // Créer le renderer
    display->renderer = SDL_CreateRenderer(display->window, -1, SDL_RENDERER_ACCELERATED);
    if (display->renderer == NULL) {
        CheckSDLError(__LINE__);
        return false;
    }

    // Initialisation de TTF
    if (TTF_Init() == -1) {
        CheckTTFError(__LINE__);
        return false;
    }

    // Désactiver le mouvement de la souris en dehors de la fenêtre
    SDL_SetRelativeMouseMode(SDL_TRUE); 

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
void RenderText(SDL_Renderer *renderer, const char* text, int x, int y, SDL_Color color) {
    TTF_Font *font = TTF_OpenFont("assets/fonts/Tr2n.ttf", 72);
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

// Fonction pour afficher du texte non reconnu par la font avec SDL_ttf
void RenderUnicode(SDL_Renderer *renderer, const char* text, int x, int y, SDL_Color color) {
    TTF_Font *font = TTF_OpenFont("assets/fonts/Arial.ttf", 72);
    if (font == NULL) {
        CheckTTFError(__LINE__);
    }

    SDL_Surface *surface = TTF_RenderUTF8_Solid(font, text, color);
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

// Fonction pour afficher le compte a rebours
void DisplayCountdownSDL(SDL_Renderer *renderer) {
    char countdown[3];
    SDL_Color white = {255, 255, 255, 255};

    for (int i = 3; i > 0; i--) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        sprintf(countdown, "%d", i);
        RenderUnicode(renderer, countdown, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, white);

        SDL_RenderPresent(renderer);
        SDL_Delay(1000);
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    RenderText(renderer, "C'est parti !", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, white);

    SDL_RenderPresent(renderer);
    SDL_Delay(1000);
}

// Fonction pour afficher le score
void DisplayScoreSDL(SDL_Renderer *renderer, Player *player1, Player *player2) {
    char scoreText[50];
    sprintf(scoreText, "Joueur 1 [ %d ] - [ %d ] Joueur 2", GetPlayerScore(player1), GetPlayerScore(player2));

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    RenderText(renderer, "Score des Joueurs", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 200, (SDL_Color){37, 150, 190});
    RenderText(renderer, scoreText, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, (SDL_Color){255, 255, 255, 255});

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
        case LIGNE_JOUEUR_1: return (SDL_Color){135, 206, 250, 255}; // Bleu Claire pour la ligne du Joueur 1
        case LIGNE_JOUEUR_2: return (SDL_Color){255, 138, 138, 255}; // Jaune pour la ligne du Joueur 2
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
void DisplayEndScreenSDL(SDL_Renderer *renderer, GameState gameState, Player *player1, Player *player2, int selectedOption) {
    const char* winnerText;

    SDL_Color joueur ;
    if (gameState == PLAYER1_WON) { winnerText = "Joueur 1 a gagne !"; joueur = (SDL_Color){0, 0, 255, 255}; }
    if (gameState == PLAYER2_WON) { winnerText = "Joueur 2 a gagne !"; joueur = (SDL_Color){255, 0, 0, 255}; }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Color white = {255, 255, 255, 255};
    SDL_Color yellow = {255, 255, 0, 255}; 
    SDL_Color cyan = {37, 150, 190};  

    char scoreText[50];
    sprintf(scoreText, "Joueur 1 [ %d ] - [ %d ] Joueur 2", GetPlayerScore(player1), GetPlayerScore(player2));

    RenderText(renderer, scoreText, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 300, cyan);
    RenderText(renderer, winnerText, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 200, joueur);

    if (selectedOption == 1){
        RenderText(renderer, "> Rejouer <", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, yellow);
        RenderText(renderer, "Retour au Menu", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 100, white);
    }
    else{
        RenderText(renderer, "Rejouer", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, white);
        RenderText(renderer, "> Retour au Menu <", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 100, yellow);
    }
    SDL_RenderPresent(renderer);
}

// Fonction pour gerer les evenements de l'ecran de fin
int HandleEndScreenEventsSDL(SDL_Renderer *renderer, GameState gameState, Player *player1, Player *player2, DisplayContext *display) {
    SDL_Event event;
    int choice = 1;
    int quit = 0;
    int selectedOption = 1;

    // Premier affichage de l'écran de fin
    DisplayEndScreenSDL(renderer, gameState, player1, player2,selectedOption);

    while (!quit) {
        SDL_WaitEvent(&event);

        if (event.type == SDL_QUIT) {
            EndDisplay(display);
            exit(EXIT_SUCCESS);
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                case SDLK_DOWN:
                    selectedOption = !selectedOption;
                    DisplayEndScreenSDL(renderer, gameState, player1, player2,selectedOption);

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
void DisplayMenuSDL(SDL_Renderer *renderer, int selectedOption) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Color white = {255, 255, 255, 255};
    SDL_Color yellow = {255, 255, 0, 255};
    SDL_Color cyan = {37, 150, 190}; 

    RenderText(renderer, "Tron Game", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 200, cyan);

    // Affichage des options avec surbrillance sur l'option sélectionnée
    if (selectedOption == 1) {
        RenderText(renderer, "> Jouer <", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, yellow);
        RenderText(renderer, "Quitter", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 100, white);
    } else {
        RenderText(renderer, "Jouer", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, white);
        RenderText(renderer, "> Quitter <", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 100, yellow);
    }

    SDL_RenderPresent(renderer);
}

// Fonction pour gerer les evenements du menu
int HandleMenuEventsSDL(SDL_Renderer *renderer) {
    SDL_Event event;
    int choice = 1;  // 0 pour Quitter, 1 pour Jouer
    int quit = 0;
    int selectedOption = 1;  // Commence avec "Jouer" sélectionné

    // Premier affichage du menu
    DisplayMenuSDL(renderer, selectedOption);

    while (!quit) {
        SDL_WaitEvent(&event);

        if (event.type == SDL_QUIT) {
            choice = 0; // Quitter par défaut si l'utilisateur ferme la fenêtre
            quit = 1;
        }

        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                case SDLK_DOWN:
                    // Alterner entre les choix
                    selectedOption = !selectedOption;

                    // Réafficher le menu avec l'option sélectionnée
                    DisplayMenuSDL(renderer, selectedOption);
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

// Fonction pour afficher la sélection du mode de jeu
void DisplayModeDeJeuSDL(SDL_Renderer *renderer, int selectedOption) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Color white = {255, 255, 255, 255};
    SDL_Color yellow = {255, 255, 0, 255};
    SDL_Color cyan = {37, 150, 190}; 

    // Afficher le titre de la sélection
    RenderText(renderer, "Selection du mode de jeu", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 200, cyan);

    // Afficher les options du menu avec celle sélectionnée en surbrillance
    for (int i = 0; i < 3; i++) {
        if (i == selectedOption) {
            RenderText(renderer, (i == 0 ? "> Bo3 <" : (i == 1 ? "> Bo5 <" : "> Retour <")),
                       WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + i * 100, yellow);
        } else {
            RenderText(renderer, (i == 0 ? "Bo3" : (i == 1 ? "Bo5" : "Retour")),
                       WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + i * 100, white);
        }
    }

    if (selectedOption == 0) {
        RenderText(renderer, "Le premier a 2 points gagne", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 300, white);
    } else if (selectedOption == 1) {
        RenderText(renderer, "Le premier a 3 points gagne", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 300, white);
    } else if (selectedOption == 2) {
        RenderText(renderer, "Retour au menu principal", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 300, white);
    }

    SDL_RenderPresent(renderer);
}

// Fonction pour gérer les événements de la sélection du mode de jeu
int HandleModeDeJeuEventsSDL(SDL_Renderer *renderer, DisplayContext *display) {
    SDL_Event event;
    int choice = 1; // Choix validé : 0 = Bo3, 1 = Bo5, 2 = retour
    int quit = 0;
    int selectedOption = 0;  // Commence avec "Bo3" sélectionné

    // Premier affichage du mode de jeu
    DisplayModeDeJeuSDL(renderer, selectedOption);

    while (!quit) {
        SDL_WaitEvent(&event);

        if (event.type == SDL_QUIT) {
            EndDisplay(display);
            exit(EXIT_SUCCESS);
        }

        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    // Aller vers le choix précédent (circulaire)
                    selectedOption = (selectedOption - 1 + 3) % 3;
                    // Réafficher l'écran en fonction du choix
                    DisplayModeDeJeuSDL(renderer, selectedOption);
                    break;

                case SDLK_DOWN:
                    // Aller vers le choix suivant (circulaire)
                    selectedOption = (selectedOption + 1) % 3;
                    // Réafficher l'écran en fonction du choix
                    DisplayModeDeJeuSDL(renderer, selectedOption);
                    break;

                case SDLK_RETURN:
                    choice = selectedOption;  // Choix validé
                    quit = 1;
                    break;
            }
        }
    }

    return choice;  // Retourner le choix effectué
}

// ==============================
// Autres fonctions
// ==============================

// Fonction pour afficher les controles
void DisplayControlsSDL(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Définition des couleurs
    SDL_Color blue = {0, 0, 255, 255};
    SDL_Color red = {255, 0, 0, 255};
    SDL_Color white = {255, 255, 255, 255};

    // Affichage des touches pour le joueur 1
    RenderText(renderer, "Joueur 1", WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2 - 170, blue);
    RenderUnicode(renderer, "Z", WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2 - 60, white);
    RenderUnicode(renderer, "Q", WINDOW_WIDTH / 4 - 60, WINDOW_HEIGHT / 2, white);
    RenderUnicode(renderer, "S", WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2 + 60, white);
    RenderUnicode(renderer, "D", WINDOW_WIDTH / 4 + 60, WINDOW_HEIGHT / 2, white);

    // Affichage des touches pour le joueur 2
    RenderText(renderer, "Joueur 2", 3 * WINDOW_WIDTH / 4 - 20, WINDOW_HEIGHT / 2 - 170, red);
    RenderUnicode(renderer, "\u2191", 3 * WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2 - 60, white); // Flèche Haut
    RenderUnicode(renderer, "\u2190", 3 * WINDOW_WIDTH / 4 - 60, WINDOW_HEIGHT / 2, white); // Flèche Gauche
    RenderUnicode(renderer, "\u2193", 3 * WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2 + 60, white); // Flèche Bas
    RenderUnicode(renderer, "\u2192", 3 * WINDOW_WIDTH / 4 + 60, WINDOW_HEIGHT / 2, white); // Flèche Droite

    SDL_RenderPresent(renderer);
    SDL_Delay(5000);
}

