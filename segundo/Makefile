PROGRAM = main
GLAD = glad
SHADERS = shader
WINDOW = window
TRIANGLE = triangle
CAMERA = camera

INCLUDE = -Iinclude
INCLUDE_GLAD = -I../glad/include
SRC_GLAD_DIR = ../glad/src

LIBS = -lglfw -lGL -lm -lX11 -lXrandr -lpthread -ldl

all: $(PROGRAM)

$(GLAD): $(SRC_GLAD_DIR)/$(GLAD).c
	gcc -c -o $(GLAD).o $(INCLUDE_GLAD) $(SRC_GLAD_DIR)/$(GLAD).c
#
# $(TRIANGLE): $(TRIANGLE).c $(GLAD)
# 	gcc -c -o $(TRIANGLE).o $(INCLUDE) $(INCLUDE_GLAD) $(TRIANGLE).c
#
# $(SHADERS): $(SHADERS).c $(GLAD)
# 	gcc -c -o $(SHADERS).o $(INCLUDE) $(INCLUDE_GLAD) $(SHADERS).c
#
# $(WINDOW): $(WINDOW).c $(SHADERS)
# 	gcc -c -o $(WINDOW).o $(INCLUDE) $(INCLUDE_GLAD) $(WINDOW).c

$(PROGRAM): $(PROGRAM).c $(CAMERA).c $(SHADERS).c $(WINDOW).c $(TRIANGLE).c $(GLAD)
	gcc -g -O3 $(PROGRAM).c $(INCLUDE) $(INCLUDE_GLAD) -o $(PROGRAM).exe $(GLAD).o $(SHADERS).c $(WINDOW).c $(TRIANGLE).c $(CAMERA).c $(LIBS)

# $(PROGRAM): $(PROGRAM).c $(SHADERS) $(WINDOW) $(TRIANGLE)
# 	gcc -g $(PROGRAM).c $(INCLUDE) $(INCLUDE_GLAD) -o $(PROGRAM) $(GLAD).o $(SHADERS).o $(WINDOW).o $(TRIANGLE).o $(LIBS)

run: $(PROGRAM)
	./$(PROGRAM).exe

gdb: $(PROGRAM)
	gdb ./$(PROGRAM).exe

clean:
	rm $(PROGRAM) *.o
