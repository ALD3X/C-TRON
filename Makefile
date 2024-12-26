# Définition des variables
CC = gcc
CFLAGS = -Iinclude -Wall -g
SDL_FLAGS = `sdl2-config --cflags --libs`
NCURSES_FLAGS = -lncurses
SDL_TTF_FLAGS = -lSDL2_ttf
MATH_FLAGS = -lm

# Répertoires
SRC_DIR = src
VUE_DIR = vue
INC_DIR = include
BUILD_DIR = build

# Fichiers objets
SRC_OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(wildcard $(SRC_DIR)/*.c))
VUE_OBJ = $(patsubst $(VUE_DIR)/%.c, $(BUILD_DIR)/%.o, $(wildcard $(VUE_DIR)/*.c))
OBJ = $(SRC_OBJ) $(VUE_OBJ)

# Nom de l'exécutable
TARGET = $(BUILD_DIR)/tron_game

# Règle principale
all: $(TARGET)

# Règle pour créer l'exécutable
$(TARGET): $(OBJ)
	@mkdir -p $(BUILD_DIR)
	$(CC) -o $@ $^ $(SDL_FLAGS) $(NCURSES_FLAGS) $(SDL_TTF_FLAGS) $(MATH_FLAGS)

# Règle pour créer les fichiers objets
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(VUE_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour nettoyer les fichiers générés
clean:
	rm -rf $(BUILD_DIR)

# Règle pour exécuter le programme
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
