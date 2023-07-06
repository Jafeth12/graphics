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

all: $(PROGRAM)

$(GLAD): $(SRC_GLAD_DIR)/$(GLAD).c
	gcc -c -g $(INCLUDE_GLAD) $(SRC_GLAD_DIR)/$(GLAD).c -o $(GLAD).o

$(SHADERS): $(SHADERS).c $(GLAD)
	gcc -c -g $(SHADERS).c -o $(SHADERS).o $(INCLUDE) $(INCLUDE_GLAD)

$(WORLD): $(WORLD).c $(SHADERS)
	gcc -c -g $(WORLD).c -o $(WORLD).o $(INCLUDE) $(INCLUDE_GLAD)

$(PROGRAM): $(PROGRAM).c $(WORLD)
	gcc -g $(PROGRAM).c $(INCLUDE) $(INCLUDE_GLAD) -o $(PROGRAM).exe $(WORLD).o $(LIBS)

# $(PROGRAM): $(PROGRAM).c $(SHADERS).c $(WORLD).c $(GLAD)
# 	gcc -g $(PROGRAM).c $(INCLUDE) $(INCLUDE_GLAD) -o $(PROGRAM).exe $(SHADERS).c $(WORLD).c $(GLAD).o $(LIBS)

# $(PROGRAM): $(PROGRAM).c $(SHADERS) $(WORLD) $(TRIANGLE)
# 	gcc -o $(PROGRAM).c $(INCLUDE) $(INCLUDE_GLAD) -o $(PROGRAM) $(GLAD).o $(SHADERS).o $(WORLD).o $(TRIANGLE).o $(LIBS)

run: $(PROGRAM)
	./$(PROGRAM).exe

gdb: $(PROGRAM)
	gdb ./$(PROGRAM).exe

clean:
	rm $(PROGRAM) *.o
