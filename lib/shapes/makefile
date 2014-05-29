main: fill.o
	gcc main.c fill.o ../../bin/matrix.o ../../bin/vector.o ../../bin/box.o ../../bin/transformations.o `sdl-config --cflags --libs` 

fill.o: fill.c fill.h
	gcc -c fill.c
run:
	make main
	./a.out
