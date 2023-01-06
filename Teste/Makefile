all: main

main: main.o
	gcc -o main main.o -lm -lGL -lGLU -lglut

main.o: main.c
	gcc -c -g main.c

clean: 
	rm *.o