#ifndef _LABYRINTH_H
#define _LABYRINTH_H

#define TRUE 1
#define FALSE 0

typedef struct map {
    char **map;
    int numberOfFloors;
    int floorSize;
}Map;

void Draw(void);
void Keyboard(unsigned char key, int x, int y);

#endif