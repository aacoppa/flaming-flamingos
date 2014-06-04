all: bin/matrix.o bin/transformations.o bin/line.o bin/sphere.o bin/vector.o bin/box.o bin/screen.o bin/renderer.o bin/fill.o
	gcc lib/main.c $^ -lm `sdl-config --cflags --libs` -o bin/a.out

bin/%.o: lib/matrix/%.c
	gcc -o $@ -c $^

bin/%.o: lib/shapes/%.c
	gcc -o $@ -c $^

bin/%.o: lib/%.c
	gcc -o $@ -c $^
