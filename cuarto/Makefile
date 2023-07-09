CC = gcc

GLAD = glad

INCLUDE = -Iinclude
INCLUDE_GLAD = -I../glad/include
SRC_GLAD_DIR = ../glad/src
BIN_DIR = bin
TARGET = $(BIN_DIR)/game

SRCS := shader.c list.c vbo_element.c vbo.c vao.c window.c main.c

GLAD_OBJ := $(BIN_DIR)/$(GLAD).o
OBJS := $(GLAD_OBJ) $(addprefix $(BIN_DIR)/,$(SRCS:.c=.o))
OPTS := -O0
CFLAGS := $(OPTS) -g -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unused-variable -Wno-unused-but-set-variable -Wno-unused-function -Wno-unused-value
LDLIBS := -lglfw -lGL -lm -lX11 -lXrandr -lpthread -ldl

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_GLAD) $(CFLAGS) -o $@ $^ $(LDLIBS)

$(BIN_DIR)/%.o: %.c | bin
	$(CC) -c $(CFLAGS) $(INCLUDE) $(INCLUDE_GLAD) $< -o $@

$(GLAD_OBJ): $(SRC_GLAD_DIR)/$(GLAD).c | bin
	$(CC) -c $(CFLAGS) $(INCLUDE_GLAD) $< -o $@

bin: 
	mkdir -p $(BIN_DIR)

run: $(TARGET)
	$<

gdb: $(TARGET)
	gdb $<

clean:
	rm -rf $(BIN_DIR)/
