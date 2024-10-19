// map->c

#include <stdio.h>
#include "map.h"
#include "elements.h"

void InitMap(Map *map){
    for (int i = 0; i < Rows; i++)
    {
        for (int j = 0; j < Cols; j++)
        {
            if(i == 0 || j == 0 || i == Rows-1 || j == Cols-1) map->Grille[i][j] = MUR ;
            else map->Grille[i][j] = VIDE ;
        }
    }
}//InitMap

void DrawMap(Map *map){
    for (int i = 0; i < Rows; i++)
    {
        for (int j = 0; j < Cols; j++)
        {   
            switch (map->Grille[i][j])
            {
            case MUR:
                printf("#");
                break;
            case JOUEUR_1:
                printf("@");
                break;
            case JOUEUR_2:
                printf("$");
                break;
            case LIGNE_JOUEUR_1:
                printf("X");
                break;
            case LIGNE_JOUEUR_2:
                printf("O");
                break;
            default:
                printf(" ");
                break;
            }
        }
        printf("\n"); 
    }
}//DrawMap

