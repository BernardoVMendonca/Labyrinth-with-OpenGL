#include "index.h"

void DrawMap(Map labyrinth, Player labyrinthGuy)
{
    int i, j;
    int stop;
    //printf("\nDRAW MAP\n");
    for (i = ((labyrinthGuy.currentFloor - 1) * labyrinth.floorSize); i < (labyrinth.floorSize * labyrinthGuy.currentFloor); i++)
    {
        for (j = 0; j < labyrinth.floorSize; j++)
        {
            //printf(" %c ", labyrinth.map[i][j]);
            if (labyrinth.map[i][j] == '1')
                DrawWall(i, j);
            else if (labyrinth.map[i][j] == '0')
            {
                DrawFloor(i, j, gray);
                DrawRoof(i, j, gray);
            }
            else if (labyrinth.map[i][j] == 'x')
            {
                DrawFloor(i, j, yellow);
                DrawRoof(i, j, yellow);
            }
            else if (labyrinth.map[i][j] == '2'){
                DrawFloor(i, j, red);
                DrawRoof(i, j, red);
            }
            else if (labyrinth.map[i][j] == '3'){
                DrawFloor(i, j, pink);
                DrawRoof(i, j, pink);
            }
            // else if (labyrinth.map[i] == '4')
            //     DrawWall(i, j);
        }
    }

    glutSwapBuffers();
    return;
}

void DrawRoof(int x, int z, void (color)())
{
    double convertedWindowsWidth = windowsWidth / 100;

    glBegin(GL_QUADS);

    color();
    glVertex3f(z * 6, convertedWindowsWidth, (x + 1) * 6);
    glVertex3f(z * 6, convertedWindowsWidth, x * 6);
    glVertex3f((z + 1) * 6, convertedWindowsWidth, x * 6);
    glVertex3f((z + 1) * 6, convertedWindowsWidth, (x + 1) * 6);

    glEnd();

    return;
}

void DrawFloor(int x, int z, void (color)())
{

    double convertedWindowsHeight = windowsHeight / 100;

    glBegin(GL_QUADS);

    color();
    glVertex3f(z * 6, 0, (x + 1) * 6);
    glVertex3f(z * 6, 0, x * 6);
    glVertex3f((z + 1) * 6, 0, x * 6);
    glVertex3f((z + 1) * 6, 0, (x + 1) * 6);

    glEnd();

    return;
}

void DrawWall(int x, int z)
{
    double convertedWindowsWidth = windowsWidth / 100;

    glBegin(GL_QUADS);

    // FRONT
    white();
    glVertex3f(z * 6, 0, (x + 1) * 6);
    glVertex3f(z * 6, convertedWindowsWidth, (x + 1) * 6);
    glVertex3f((z + 1) * 6, convertedWindowsWidth, (x + 1) * 6);
    glVertex3f((z + 1) * 6, 0, (x + 1) * 6);

    // BACK
    green();
    glVertex3f(z * 6, 0, x * 6);
    glVertex3f(z * 6, convertedWindowsWidth, x * 6);
    glVertex3f((z + 1) * 6, convertedWindowsWidth, x * 6);
    glVertex3f((z + 1) * 6, 0, x * 6);

    // LEFT
    blue();
    glVertex3f((z + 1) * 6, convertedWindowsWidth, (x + 1) * 6);
    glVertex3f((z + 1) * 6, convertedWindowsWidth, x * 6);
    glVertex3f((z + 1) * 6, 0, x * 6);
    glVertex3f((z + 1) * 6, 0, (x + 1) * 6);

    // RIGHT
    red();
    glVertex3f(z * 6, 0, (x + 1) * 6);
    glVertex3f(z * 6, 0, x * 6);
    glVertex3f(z * 6, convertedWindowsWidth, x * 6);
    glVertex3f(z * 6, convertedWindowsWidth, (x + 1) * 6);

    glEnd();
}