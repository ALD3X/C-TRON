// main.c

#include <stdio.h>
#include "./modele/map.h"
#include "./modele/player.h"
#include "./modele/elements.h"

int main() {
    Map map;
    Player player1, player2;

    // Initialiser la carte
    InitMap(&map);

    // Faire apparaître les joueurs sur la carte
    SpawnPlayers(&player1, &player2, &map);

    MovePlayer(&player1,&map,RIGHT);
    MovePlayer(&player1,&map,RIGHT);
    MovePlayer(&player1,&map,RIGHT);
    MovePlayer(&player1,&map,RIGHT);
    MovePlayer(&player1,&map,RIGHT);
    MovePlayer(&player1,&map,RIGHT);
    MovePlayer(&player1,&map,RIGHT);
    MovePlayer(&player1,&map,RIGHT);

    MovePlayer(&player2,&map,LEFT);
    MovePlayer(&player2,&map,LEFT);
    MovePlayer(&player2,&map,LEFT);
    MovePlayer(&player2,&map,LEFT);
    MovePlayer(&player2,&map,LEFT);
    MovePlayer(&player2,&map,LEFT);
    MovePlayer(&player2,&map,LEFT);
    MovePlayer(&player2,&map,LEFT);
    MovePlayer(&player2,&map,LEFT);
    MovePlayer(&player2,&map,LEFT);
    MovePlayer(&player2,&map,LEFT);
    MovePlayer(&player2,&map,LEFT);
    MovePlayer(&player2,&map,LEFT);
    MovePlayer(&player2,&map,LEFT);

    while (player2.isAlive)
    {
        MovePlayer(&player2,&map,TOP);
        DrawMap(&map);
    }

    printf("j1 %d j2 %d",player1.isAlive,player2.isAlive);
    
    printf("end game \n");
    
    /*MovePlayer(&player2,&map,LEFT);
    MovePlayer(&player2,&map,LEFT);
    MovePlayer(&player2,&map,LEFT);
    MovePlayer(&player2,&map,LEFT);
    MovePlayer(&player2,&map,LEFT);
    MovePlayer(&player2,&map,TOP);
    MovePlayer(&player2,&map,TOP);
    MovePlayer(&player2,&map,TOP);
    MovePlayer(&player2,&map,TOP);*/

    // Dessiner la carte avec les joueurs
    DrawMap(&map);

    return 0;
}
