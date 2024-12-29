# Définition des variables
CC = gcc
CFLAGS = -Iinclude -Wall -g
SDL_FLAGS = `sdl2-config --cflags --libs` 
NCURSES_FLAGS = -lncurses
SDL_ADDON_FLAGS = -lSDL2_ttf -lSDL2_mixer
MATH_FLAGS = -lm

# Répertoires
CONTROLLERS_DIR = src/controllers
VUE_DIR = src/views
MODELS_DIR = src/models
UTILS_DIR = src/utils
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

# Fichiers objets
SRC_OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(wildcard $(SRC_DIR)/*.c))
CONTROLLERS_OBJ = $(patsubst $(CONTROLLERS_DIR)/%.c, $(BUILD_DIR)/%.o, $(wildcard $(CONTROLLERS_DIR)/*.c))
MODELS_OBJ = $(patsubst $(MODELS_DIR)/%.c, $(BUILD_DIR)/%.o, $(wildcard $(MODELS_DIR)/*.c))
VIEWS_OBJ = $(patsubst $(VUE_DIR)/%.c, $(BUILD_DIR)/%.o, $(wildcard $(VUE_DIR)/*.c))
UTILS_OBJ = $(patsubst $(UTILS_DIR)/%.c, $(BUILD_DIR)/%.o, $(wildcard $(UTILS_DIR)/*.c))

OBJ = $(MODELS_OBJ) $(CONTROLLERS_OBJ) $(VIEWS_OBJ) $(SRC_OBJ) $(UTILS_OBJ)

# Nom de l'exécutable
TARGET = $(BUILD_DIR)/tron_game

# Règle principale
all: $(TARGET)

# Règle pour créer l'exécutable
$(TARGET): $(OBJ)
	@mkdir -p $(BUILD_DIR)
	$(CC) -o $@ $^ $(SDL_FLAGS) $(NCURSES_FLAGS) $(SDL_ADDON_FLAGS) $(MATH_FLAGS)

# Règle pour créer les fichiers objets
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(CONTROLLERS_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(MODELS_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(VUE_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(UTILS_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour nettoyer les fichiers générés
clean:
	rm -rf $(BUILD_DIR)

# Règle pour exécuter le programme
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
