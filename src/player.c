// player.c

#include "player.h"


// Initialise le joueur avec une position et un identifiant
void InitializePlayer(Player *player, int id) {
    CheckPointer(player, "Pointeur du joueur invalide.");

    player->id = id;
    player->isAlive = 1;
    player->score = 0;
    player->vitesse = 60;
    player->lastMoveTime = clock();
}

// Retourne 1 si la case est libre, 0 sinon
int CheckCollision(Map *map, int x, int y) {
    CheckMap(map);

    if (!IsCoordinateValid(x, y)) return 0;
    return (map->Grille[x][y] == VIDE);
}

// Retourne 1 si les coordonnées sont valides, 0 sinon
int IsCoordinateValid(int x, int y) {
    return (x > 0 || x < Rows || y > 0 || y < Cols);
}

void switchPlayerDirection(Player *player, Direction direction_){
    player->direction = direction_ ;
}

// Déplace le joueur dans une direction
void MovePlayerInDirection(Player *player, Map *map) {
    CheckALL(1, map, player);
    if (!player->isAlive) return;

    int newX = player->x, newY = player->y;

    CalculateNewPosition(player->direction, &newX, &newY);
    RecordPlayerPath(map, player);
    UpdatePlayerPosition(player, map, newX, newY);
    

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
    CheckALL(1, map, player);

    if (!IsCoordinateValid(player->x, player->y) || !player->isAlive) return ;
    DrawLineOnMap(map, player->id, player->x, player->y);
    
}

// Met à jour la position du joueur
void UpdatePlayerPosition(Player *player, Map *map, int newX, int newY) {
    CheckALL(1, map, player);

    if (!IsCoordinateValid(player->x, player->y) || !player->isAlive) return ;

    if (CheckCollision(map, newX, newY)) {
        player->x = newX;
        player->y = newY;
        map->Grille[newX][newY] = player->id;
    } 
    else HandlePlayerCollision(player);
}

// Gère la collision du joueur
void HandlePlayerCollision(Player *player) {
    CheckPointer(player, "Pointeur du joueur invalide.");
    player->isAlive = 0;
    printf("Le joueur %d s'est ecrase.\n", player->id - 1);
}

// Mettre à jour le joueur en fonction de la vitesse
void UpdatePlayerMovement(Player *player, Map *map) {

    // Vérifier si le temps écoulé est suffisant pour déplacer le joueur
    clock_t currentTime = clock();
    double elapsedTime = (double)(currentTime - player->lastMoveTime) / CLOCKS_PER_SEC;

    // Si l'intervalle de temps est suffisant pour faire avancer le joueur en fonction de sa vitesse
    if (elapsedTime >= (1.0 / player->vitesse)) {
        
        MovePlayerInDirection(player, map);
        player->lastMoveTime = currentTime;
    }
}



// --- Spawn des joueur --- a revoir 

// Génère des coordonnées valides aleatoire
int GenerateValidCoordinates(int *x, int *y, Map *map) {
    CheckMap(map);

    for (int attempts = 0; attempts < MAX_ATTEMPTS; attempts++) {
        *x = rand() % (Rows - 2) + 1;
        *y = rand() % (Cols - 2) + 1;

        if (CheckCollision(map, *x, *y)) return 1;
        
    }
    fprintf(stderr, "Erreur: Impossible de générer des coordonnées valides.\n");
    return 0;
}

// Fait apparaître deux joueurs
void SpawnTwoPlayers(Player *player1, Player *player2, Map *map) {
    CheckALL(2, map, player1, player2);

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
