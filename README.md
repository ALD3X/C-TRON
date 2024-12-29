# Tron Game

Tron Game est un jeu multijoueur inspiré du film Tron, où deux joueurs s'affrontent en essayant de faire s'écraser l'autre joueur contre les murs ou les lignes de lumière laissées derrière eux.

## Structure du projet

Le projet est organisé de la manière suivante :

### Fichiers principaux

## Structure du projet

Le projet est organisé de la manière suivante :

### Fichiers principaux

- #### `src/main.c`

Le point d'entrée du programme. Il initialise le type d'affichage (SDL ou Ncurses), initialise le jeu et gère la boucle principale du jeu.

- #### `src/models/game.c`

Contient les fonctions principales de gestion du jeu, y compris l'initialisation, la mise à jour, et la gestion de la boucle de jeu.

- #### `src/controllers/input.c`

Gère les entrées des joueurs pour les deux modes d'affichage (SDL et Ncurses).

- #### `src/models/map.c`

Gère la carte du jeu, y compris l'initialisation et la réinitialisation de la carte.

- #### `src/models/player.c`

Gère les joueurs, y compris l'initialisation, la mise à jour des mouvements, et la gestion des scores.

- #### `src/utils/utils.c`

Contient des fonctions utilitaires pour vérifier les erreurs et les pointeurs.

- #### `src/views/display.c`

Gère l'initialisation et la terminaison de l'affichage, ainsi que le dessin de la carte.

- #### `src/views/displayNcurses.c`

Gère l'affichage et les événements du menu, du mode de jeu, et de l'écran de fin pour Ncurses.

- #### `src/views/displaySDL.c`

Gère l'affichage et les événements du menu, du mode de jeu, et de l'écran de fin pour SDL.

## Compilation et exécution

Pour compiler le projet, utilisez le `Makefile` fourni. Exécutez la commande suivante dans le terminal :

```sh
make
```

Pour exécuter le jeu, utilisez la commande suivante :
```sh
make run
```

Pour nettoyer les fichiers générés par la compilation, utilisez la commande suivante :
```sh
make clean
```

## Dépendances
Le projet dépend des bibliothèques suivantes :

- SDL2         (`sudo apt-get update && sudo apt-get install libsdl2-dev`)
- SDL2_ttf     (`sudo apt-get update && sudo apt-get install libsdl2-ttf-dev`)
- SDL2_mix     (`sudo apt-get update && sudo apt-get install libsdl2-mixer-dev`)
- ncurses

## Sources

- Police d'écriture : 
    - [Google Font - Arial](https://fonts.google.com/?query=Arial)
    - [1001 Font - TR2N](https://www.1001fonts.com/tr2n-font.html)

- Unicode
    - [Wikipedia - Table des Unicodes](https://fr.wikipedia.org/wiki/Table_des_caractères_Unicode/U2190)

- [SDL2](https://wiki.libsdl.org/SDL2/FrontPage)

- [NCURSES](https://invisible-island.net/ncurses/)

## Contrôles du jeu
- Joueur 1
    - Haut : Z
    - Bas : S
    - Gauche : Q
    - Droite : D
- Joueur 2
    - Haut : Flèche haut
    - Bas : Flèche bas
    - Gauche : Flèche gauche
    - Droite : Flèche droite

## Auteurs
Ce projet a été développé par Anthony Dubart et Alexandre Dhainaut.
