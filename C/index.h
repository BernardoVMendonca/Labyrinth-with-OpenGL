#ifndef _LABYRINTH_H
#define _LABYRINTH_H

#include <stdio.h>
#include <stdlib.h>

#include <math.h>

#include <GL/glut.h>

#define TRUE 1
#define FALSE 0

#define UP 1
#define DOWN 0

#define windowsHeight 1060
#define windowsWidth 840

typedef struct map
{
    char **map;
    int numberOfFloors;
    int floorSize;
    int numberOfItems;
} Map;

typedef struct camera
{
    // actual vector representing the camera's direction
    GLfloat lx, lz;
    // XZ position of the camera
    GLfloat x, z; // x = 48 z = 36
    // angle for rotating triangle
    GLfloat angle;
} Camera;

typedef struct player
{
    int currentFloor;
    Camera playerCamera;
} Player;

/*DRAW MAP*/

void DrawMap(Map labyrinth, Player labyrinthGuy);
void DrawItem(int x, int z, void(color)());
void DrawWall(int x, int z);
void DrawFloor(int x, int z, void(color)());
void DrawRoof(int x, int z, void(color)());

/*--------------*/

/*COLORS*/

void green();
void blue();
void red();
void yellow();
void orange();
void pink();
void white();
void grey();
void grey2();
void black();

/*--------------*/

#endif