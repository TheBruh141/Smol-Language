# Compiler and flags
CC = gcc
CFLAGS_COMMON = -Wall -Wextra -Isrc/libs -std=c2x -fsanitize=address,undefined,leak
CFLAGS_RELEASE = -O3
CFLAGS_DEBUG = -g -fsanitize=address,undefined,leak -O0 

# Directories
SRC_DIR = src
BUILD_DIR = build
RELEASE_DIR = $(BUILD_DIR)/release
DEBUG_DIR = $(BUILD_DIR)/debug

# List of source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
LIB_FILES = $(wildcard $(SRC_DIR)/libs/*.c)

# Create a list of object files corresponding to source files
OBJ_RELEASE = $(patsubst $(SRC_DIR)/%.c,$(RELEASE_DIR)/%.o,$(SRC_FILES) $(LIB_FILES))
OBJ_DEBUG = $(patsubst $(SRC_DIR)/%.c,$(DEBUG_DIR)/%.o,$(SRC_FILES) $(LIB_FILES))

# Target executables
RELEASE_TARGET = $(RELEASE_DIR)/smolc_release.out
DEBUG_TARGET = $(DEBUG_DIR)/smolc_debug.out

# By default, build the release version
all: release

# Release build
release: CFLAGS = $(CFLAGS_COMMON) $(CFLAGS_RELEASE)
release: $(RELEASE_TARGET)

$(RELEASE_TARGET): $(OBJ_RELEASE)
	$(CC) $(CFLAGS) -o $@ $^

$(RELEASE_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Debug build
debug: CFLAGS = $(CFLAGS_COMMON) $(CFLAGS_DEBUG)
debug: $(DEBUG_TARGET)

$(DEBUG_TARGET): $(OBJ_DEBUG)
	$(CC) $(CFLAGS) -o $@ $^

$(DEBUG_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all release debug clean
