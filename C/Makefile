all: main

Draw.o: Draw.c
	gcc -c -g Draw.c

UserMovement.o: UserMovement.c
	gcc -c -g UserMovement.c

main: main.o UserMovement.o Draw.o
	gcc -o main main.o Draw.o UserMovement.o -lGL -lGLU -lglut

main.o: main.c
	gcc -c -g main.c

clean: 
	rm *.o