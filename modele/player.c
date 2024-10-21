// player.c

#include "player.h"

// Fonction utilitaire pour vérifier les pointeurs et gérer les erreurs
void CheckPointer(void *ptr, const char *errorMessage) {
    if (ptr == NULL) {
        fprintf(stderr, "Erreur: %s\n", errorMessage);
        exit(EXIT_FAILURE);
    }
}

void resetPLayerlive(Player *player){
    CheckPointer(player, "Pointeur du joueur invalide.");
    player->isAlive = 1 ;
}

// Initialise le joueur avec une position et un identifiant
void InitializePlayer(Player *player, int id) {
    CheckPointer(player, "Pointeur du joueur invalide.");

    player->id = id;
    player->isAlive = 1;
    player->score = 0;
}

// Vérifie l'état du jeu en fonction de la vie des joueurs
GameState CheckGameState(const Player *player1, const Player *player2) {
    CheckPointer((void *)player1, "Informations du joueur 1 invalides.");
    CheckPointer((void *)player2, "Informations du joueur 2 invalides.");

    if (!player1->isAlive) return PLAYER2_WON;
    if (!player2->isAlive) return PLAYER1_WON;
    return GAME_ONGOING;
}

// Retourne 1 si la case est libre, 0 sinon
int CheckCollision(Map *map, int x, int y) {
    CheckPointer(map, "La carte est invalide.");
    CheckPointer(map->Grille, "La grille de la carte est invalide.");

    if (!IsCoordinateValid(x, y)) {
        return 0;
    }

    return (map->Grille[x][y] == VIDE);
}

// Retourne 1 si les coordonnées sont valides, 0 sinon
int IsCoordinateValid(int x, int y) {
    if (x < 0 || x >= Rows || y < 0 || y >= Cols) {
        fprintf(stderr, "Erreur: Coordonnées (%d, %d) en dehors des limites.\n", x, y);
        return 0;
    }
    return 1;
}

// Incrémente le score du joueur
void AddPlayerScore(Player *player) {
    CheckPointer(player, "Pointeur du joueur invalide.");
    player->score++;
}

// Retourne le score du joueur
int GetPlayerScore(const Player *player) {
    CheckPointer((void *)player, "Pointeur du joueur invalide.");
    return player->score;
}

// Déplace le joueur dans une direction
void MovePlayerInDirection(Player *player, Map *map, Direction direction) {
    CheckPointer(player, "Pointeur du joueur invalide.");
    CheckPointer(map, "La carte est invalide.");
    CheckPointer(map->Grille, "La grille de la carte est invalide.");
    if (!player->isAlive) return;

    int newX = player->x, newY = player->y;
    CalculateNewPosition(direction, &newX, &newY);

    if (CheckCollision(map, newX, newY)) {
        RecordPlayerPath(map, player);
        UpdatePlayerPosition(player, map, newX, newY);
    } else {
        HandlePlayerCollision(player);
    }
}

// Calcule la nouvelle position
void CalculateNewPosition(Direction direction, int *x, int *y) {
    switch (direction) {
        case TOP:    (*x)--; break;
        case DOWN:   (*x)++; break;
        case LEFT:   (*y)--; break;
        case RIGHT:  (*y)++; break;
    }
}

// Enregistre le chemin du joueur
void RecordPlayerPath(Map *map, Player *player) {
    CheckPointer(player, "Pointeur du joueur invalide.");
    CheckPointer(map, "La carte est invalide.");
    CheckPointer(map->Grille, "La grille de la carte est invalide.");

    if (IsCoordinateValid(player->x, player->y)) {
        DrawLineOnMap(map, player->id, player->x, player->y);
    } else {
        fprintf(stderr, "Erreur: Coordonnées (%d, %d) non valides.\n", player->x, player->y);
    }
}

// Met à jour la position du joueur
void UpdatePlayerPosition(Player *player, Map *map, int newX, int newY) {
    CheckPointer(player, "Pointeur du joueur invalide.");
    CheckPointer(map, "La carte est invalide.");
    CheckPointer(map->Grille, "La grille de la carte est invalide.");

    if (CheckCollision(map, newX, newY)) {
        player->x = newX;
        player->y = newY;
        map->Grille[newX][newY] = player->id;
    } else {
        fprintf(stderr, "Erreur: Impossible de déplacer le joueur aux coordonnées (%d, %d).\n", newX, newY);
        exit(EXIT_FAILURE);
    }
}

// Gère la collision du joueur
void HandlePlayerCollision(Player *player) {
    CheckPointer(player, "Pointeur du joueur invalide.");
    player->isAlive = 0;
    printf("Le joueur %d s'est ecrase.\n", player->id - 1);
}

// Génère des coordonnées valides aleatoire
int GenerateValidCoordinates(int *x, int *y, Map *map) {
    CheckPointer(map, "La carte est invalide.");
    CheckPointer(map->Grille, "La grille de la carte est invalide.");

    for (int attempts = 0; attempts < MAX_ATTEMPTS; attempts++) {
        *x = rand() % (Rows - 2) + 1;
        *y = rand() % (Cols - 2) + 1;

        if (CheckCollision(map, *x, *y)) {
            return 1;
        }
    }
    fprintf(stderr, "Erreur: Impossible de générer des coordonnées valides.\n");
    return 0;
}

// Fait apparaître deux joueurs
void SpawnTwoPlayers(Player *player1, Player *player2, Map *map) {
    CheckPointer(player1, "Pointeur du joueur1 invalide.");
    CheckPointer(player2, "Pointeur du joueur2 invalide.");
    CheckPointer(map, "La carte est invalide.");
    CheckPointer(map->Grille, "La grille de la carte est invalide.");

    srand(time(NULL));
    int x1, y1;

    if (!GenerateValidCoordinates(&x1, &y1, map)) {
        fprintf(stderr, "Erreur: Impossible de placer le joueur 1.\n");
        exit(EXIT_FAILURE);
    }

    int x2 = Rows - 1 - x1, y2 = Cols - 1 - y1;

    if (!CheckCollision(map, x2, y2)) {
        fprintf(stderr, "Erreur: Impossible de placer le joueur 2 aux coordonnées opposées (%d, %d).\n", x2, y2);
        exit(EXIT_FAILURE);
    }

    UpdatePlayerPosition(player1, map, x1, y1);
    UpdatePlayerPosition(player2, map, x2, y2);
}
