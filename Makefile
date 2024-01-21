OPTS := -O3

CC = gcc

GLAD = glad

SRC_DIR = src
LIBS_DIR = libs
ENTITY_DIR = $(SRC_DIR)/entity
GFX_DIR = $(SRC_DIR)/gfx
UTILS_DIR = $(SRC_DIR)/utils
WORLD_DIR = $(SRC_DIR)/world

INCLUDE_LIBS = -I$(LIBS_DIR)
INCLUDE = -I$(SRC_DIR)
SRC_GLAD_DIR = glad/src

BIN_DIR = bin
TARGET = $(BIN_DIR)/game

SRCS := $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/**/*.c)
LIB_SRCS := $(wildcard $(LIBS_DIR)/*.c)

OBJS := $(addprefix $(BIN_DIR)/,$(SRCS:.c=.o))
LIB_OBJS := $(LIB_SRCS:.c=.o)
CFLAGS := $(OPTS) -g -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unused-variable -Wno-unused-but-set-variable -Wno-unused-function -Wno-unused-value
LDLIBS := -lglfw -lm

$(TARGET): $(LIB_OBJS) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_LIBS) $(CFLAGS) -o $@ $^ $(LDLIBS)

# actual source
$(BIN_DIR)/%.o: %.c | bin
	$(CC) -c $(CFLAGS) $(INCLUDE) $(INCLUDE_LIBS) $< -o $@

# libs binaries are in the libs folder along with their source files
%.o: %.c
	$(CC) -c $(CFLAGS) $(INCLUDE_LIBS) $^ -o $@

bin: 
	mkdir -p $(BIN_DIR) $(BIN_DIR)/$(GLAD_DIR) $(BIN_DIR)/$(SRC_DIR) $(BIN_DIR)/$(ENTITY_DIR) $(BIN_DIR)/$(GFX_DIR) $(BIN_DIR)/$(UTILS_DIR) $(BIN_DIR)/$(WORLD_DIR)

run: $(TARGET)
	$<

gdb: $(TARGET)
	gdb $<

clean:
	rm -rf $(BIN_DIR)/
