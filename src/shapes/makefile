main: box.o vector.o matrix.o screen.o fill.o transformations.o renderer.o line.o sphere.o
	gcc main.c renderer.o line.o box.o vector.o matrix.o screen.o fill.o transformations.o sphere.o -lm `sdl-config --cflags --libs`

transformations.o:
	gcc -c ../matrix/transformations.c
box.o:
	gcc -c box.c
vector.o:
	gcc -c ../matrix/vector.c
matrix.o:
	gcc -c ../matrix/matrix.c
fill.o:
	gcc -c fill.c
screen.o:
	gcc -c ../screen.c
line.o:
	gcc -c line.c
renderer.o:
	gcc -c ../renderer.c
sphere.o:
	gcc -c sphere.c

clean:
	-rm *.o
	-rm a.out
run:
	make clean
	make
	./a.out
