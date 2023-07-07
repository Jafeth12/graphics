CC = gcc

GLAD = glad

INCLUDE = -Iinclude
INCLUDE_GLAD = -I../glad/include
SRC_GLAD_DIR = ../glad/src

SRCS := shader.c window.c main.c
OBJS := $(GLAD).o $(SRCS:.c=.o)
CFLAGS := -g -Wall -Wextra -Werror -Wno-unused-parameter -Wno-unused-variable -Wno-unused-but-set-variable -Wno-unused-function -Wno-unused-value
LDLIBS := -lglfw -lGL -lm -lX11 -lXrandr -lpthread -ldl

TARGET = game

all: $(TARGET)

%.o: %.c
	$(CC) -c $(CFLAGS) $(INCLUDE) $(INCLUDE_GLAD) $<

$(GLAD).o: $(SRC_GLAD_DIR)/$(GLAD).c
	$(CC) -c $(CFLAGS) $(INCLUDE_GLAD) $<

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) $(INCLUDE_GLAD) $(CFLAGS) -o $(TARGET).exe $^ $(LDLIBS)

run: $(TARGET)
	./$(TARGET).exe

gdb: $(TARGET)
	gdb ./$(TARGET).exe

clean:
	rm *.exe *.o
