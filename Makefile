all: labyrinthWall.o main

labyrinthWall.o: labyrinthWall.c
	gcc -c -g labyrinthWall.c

main: main.o
	gcc -o main main.o labyrinthWall.o -lGL -lGLU -lglut

main.o: main.c
	gcc -c -g main.c

clean: 
	rm *.o