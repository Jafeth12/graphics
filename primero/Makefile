INCLUDE = -I./include

PROGRAM = main
GLAD = glad
SHADERS = shader

LIBS = -lglfw -lGL -lm -lX11 -lXrandr -lpthread -ldl


all: $(PROGRAM)

$(GLAD): $(GLAD).c
	gcc -c -o $(GLAD).o $(INCLUDE) $(GLAD).c

$(SHADERS): $(SHADERS).c
	gcc -c -o $(SHADERS).o $(INCLUDE) $(SHADERS).c

$(PROGRAM): $(PROGRAM).c $(GLAD) $(SHADERS)
	gcc -g $(PROGRAM).c $(INCLUDE) -o $(PROGRAM).exe $(GLAD).o $(SHADERS).o $(LIBS)

run: $(PROGRAM)
	./$(PROGRAM)

clean:
	rm $(PROGRAM) *.o
