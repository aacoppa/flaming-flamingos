all: bin/matrix.o bin/transformations.o bin/line.o bin/sphere.o bin/vector.o bin/box.o bin/screen.o bin/renderer.o bin/physics.o bin/world.o
	gcc src/main.c $^ -lm `sdl-config --cflags --libs` -o bin/a.out

#bin/matrix.o:
#	gcc -c src/matrix/matrix.c -o bin/matrix.o
#bin/transformations.o:
#	gcc -c src/matrix/transformations.c -o bin/transformations.o
#bin/line.o:
#	gcc -c src/shapes/line.c -o bin/line.o
#bin/parse_util.o:
#	gcc -c src/parse_util.c -o bin/parse_util.o
#bin/sphere.o:
#	gcc -c src/shapes/sphere.c -o bin/sphere.o
#bin/vector.o:
#	gcc -c src/matrix/vector.c -o bin/vector.o
#bin/box.o:
#	gcc -c src/shapes/box.c -o bin/box.o
#bin/screen.o:
#	gcc -c src/screen.c -o bin/screen.o
#bin/renderer.o:
#	gcc -c src/renderer.c -o bin/renderer.o
#bin/interpret.o:
#	gcc -c src/interpret.c -o bin/interpret.o
#bin/file_renderer.o:
#	gcc -c src/file_renderer.c -o bin/file_renderer.o
#
bin/%.o: src/matrix/%.c
	gcc -o $@ -c $^

bin/%.o: src/shapes/%.c
	gcc -o $@ -c $^

bin/%.o: src/%.c
	gcc -o $@ -c $^

clean:
	-rm bin/*.o 
	-rm bin/a.out
	-rm data/*.ppm
	-rm data/*.gif
	-rm data/*.png
run:
	make clean
	make all 
	./bin/a.out
runf:
	make clean
	make all
	./bin/a.out data/cull.data
	convert data/cull.ppm data/cull.png
	open data/cull.png
