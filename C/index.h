#ifndef _LABYRINTH_H
#define _LABYRINTH_H

#define TRUE 1
#define FALSE 0

typedef struct map {
    char **map;
    int numberOfFloors;
    int floorSize;
}Map;

void Display(void);
void DrawWall();
void DrawFloor();
void DrawRoof();

#endif