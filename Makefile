# Définition des variables
CC = gcc
CFLAGS = -Iinclude -Wall -g
SDL_FLAGS = `sdl2-config --cflags --libs` 
NCURSES_FLAGS = -lncurses

# Répertoires
SRC_DIR = src
VUE_DIR = vue
INC_DIR = include

# Fichiers objets
OBJ = $(patsubst $(SRC_DIR)/%.c, $(SRC_DIR)/%.o, $(wildcard $(SRC_DIR)/*.c)) \
      $(patsubst $(VUE_DIR)/%.c, $(VUE_DIR)/%.o, $(wildcard $(VUE_DIR)/*.c))

# Nom de l'exécutable
TARGET = tron_game

# Règle principale
all: $(TARGET)

# Règle pour créer l'exécutable
$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(SDL_FLAGS) $(NCURSES_FLAGS)

# Règle pour créer les fichiers objets
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(VUE_DIR)/%.o: $(VUE_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour nettoyer les fichiers générés
clean:
	rm -f $(SRC_DIR)/*.o $(VUE_DIR)/*.o $(TARGET)

# Règle pour exécuter le programme
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
