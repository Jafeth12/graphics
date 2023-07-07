PROGRAM = main
GLAD = glad
SHADERS = shader
WORLD = world
BLOCK = block
CAMERA = camera

INCLUDE = -Iinclude
INCLUDE_GLAD = -I../glad/include
SRC_GLAD_DIR = ../glad/src

LIBS = -lglfw -lGL -lm -lX11 -lXrandr -lpthread -ldl

all: game

$(GLAD).o: $(SRC_GLAD_DIR)/$(GLAD).c
	gcc -c -g $(INCLUDE_GLAD) $(SRC_GLAD_DIR)/$(GLAD).c

$(SHADERS).o: $(SHADERS).c 
	gcc -c -g $(INCLUDE) $(INCLUDE_GLAD) $(SHADERS).c

# $(CAMERA).o: $(CAMERA).c
	# gcc -c -g $(INCLUDE) $(INCLUDE_GLAD) $(CAMERA).c

# $(BLOCK).o: $(BLOCK).c
# 	gcc -c -g $(INCLUDE) $(INCLUDE_GLAD) $(BLOCK).c

# $(WORLD).o: $(WORLD).c
# 	gcc -c -g $(INCLUDE) $(INCLUDE_GLAD) $(WORLD).c

$(PROGRAM).o: $(PROGRAM).c
	gcc -c -g $(INCLUDE) $(INCLUDE_GLAD) $(PROGRAM).c

game: $(GLAD).o $(SHADERS).o $(PROGRAM).o
	gcc -o game.exe $(INCLUDE) $(INCLUDE_GLAD) $(GLAD).o $(SHADERS).o $(PROGRAM).o $(LIBS)

run: game
	./game.exe

gdb: game
	gdb ./game.exe

clean:
	rm *.exe *.o
