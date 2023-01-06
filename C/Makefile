all: main

Colors.o: Colors.c
	gcc -c -g Colors.c

Draw.o: Draw.c
	gcc -c -g Draw.c

main: main.o  Draw.o Colors.o
	gcc -o main main.o Draw.o Colors.o -lm -lGL -lGLU -lglut

main.o: main.c
	gcc -c -g main.c

clean: 
	rm *.o