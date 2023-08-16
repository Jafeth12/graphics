OPTS := -O0

CC = gcc

GLAD = glad

SRC_DIR = src
GLAD_DIR = $(SRC_DIR)/glad
ENTITY_DIR = $(SRC_DIR)/entity
GFX_DIR = $(SRC_DIR)/gfx
UTILS_DIR = $(SRC_DIR)/utils
WORLD_DIR = $(SRC_DIR)/world

INCLUDE = -I$(SRC_DIR)
INCLUDE_GLAD = -Iglad/include
SRC_GLAD_DIR = glad/src

BIN_DIR = bin
TARGET = $(BIN_DIR)/game

SRCS := $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/**/*.c)

OBJS := $(addprefix $(BIN_DIR)/,$(SRCS:.c=.o))
CFLAGS := $(OPTS) -g -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unused-variable -Wno-unused-but-set-variable -Wno-unused-function -Wno-unused-value
LDLIBS := -lglfw -lGL -lm -lX11 -lXrandr -lpthread -ldl

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) $(CFLAGS) -o $@ $^ $(LDLIBS)

$(BIN_DIR)/%.o: %.c | bin
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@

bin: 
	mkdir -p $(BIN_DIR) $(BIN_DIR)/$(GLAD_DIR) $(BIN_DIR)/$(SRC_DIR) $(BIN_DIR)/$(ENTITY_DIR) $(BIN_DIR)/$(GFX_DIR) $(BIN_DIR)/$(UTILS_DIR) $(BIN_DIR)/$(WORLD_DIR)

run: $(TARGET)
	$<

gdb: $(TARGET)
	gdb $<

clean:
	rm -rf $(BIN_DIR)/
