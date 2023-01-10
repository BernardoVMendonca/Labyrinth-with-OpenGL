#include "index.h"

void DrawMap(Map labyrinth, Player labyrinthGuy)
{
    int i, j;

    int blockPosX = ((labyrinthGuy.playerCamera.x) / 6),
        blockPosZ = ((labyrinthGuy.playerCamera.z) / 6);

    for (i = ((labyrinthGuy.currentFloor - 1) * labyrinth.floorSize); i < (labyrinth.floorSize * labyrinthGuy.currentFloor); i++)
    {
        for (j = 0; j < labyrinth.floorSize; j++)
        {
            switch (labyrinth.map[i][j])
            {
            case '0':
                ((i == blockPosZ) && (blockPosX == j)) ? DrawFloor(i, j, green) : DrawFloor(i, j, grey2);
                break;
            case '1':
                DrawWall(i, j);
                break;
            case '2':
                DrawFloor(i, j, red);
                break;
            case '3':
                DrawFloor(i, j, pink);
                break;
            case '4':
                DrawFloor(i, j, orange);
                break;
            case 'x':
                DrawFloor(i, j, yellow);
                break;

            default:
                break;
            }
        }
    }

    glutSwapBuffers();
    return;
}

void DrawRoof(int x, int z, void(color)())
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

void DrawFloor(int x, int z, void(color)())
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
    grey();

    // FRONT

    glVertex3f(z * 6, 0, (x + 1) * 6);
    glVertex3f(z * 6, convertedWindowsWidth, (x + 1) * 6);
    glVertex3f((z + 1) * 6, convertedWindowsWidth, (x + 1) * 6);
    glVertex3f((z + 1) * 6, 0, (x + 1) * 6);

    // BACK

    glVertex3f(z * 6, 0, x * 6);
    glVertex3f(z * 6, convertedWindowsWidth, x * 6);
    glVertex3f((z + 1) * 6, convertedWindowsWidth, x * 6);
    glVertex3f((z + 1) * 6, 0, x * 6);

    // LEFT

    glVertex3f((z + 1) * 6, convertedWindowsWidth, (x + 1) * 6);
    glVertex3f((z + 1) * 6, convertedWindowsWidth, x * 6);
    glVertex3f((z + 1) * 6, 0, x * 6);
    glVertex3f((z + 1) * 6, 0, (x + 1) * 6);

    // RIGHT

    glVertex3f(z * 6, 0, (x + 1) * 6);
    glVertex3f(z * 6, 0, x * 6);
    glVertex3f(z * 6, convertedWindowsWidth, x * 6);
    glVertex3f(z * 6, convertedWindowsWidth, (x + 1) * 6);

    // TOP

    glVertex3f(z * 6, convertedWindowsWidth, (x + 1) * 6);
    glVertex3f(z * 6, convertedWindowsWidth, x * 6);
    glVertex3f((z + 1) * 6, convertedWindowsWidth, x * 6);
    glVertex3f((z + 1) * 6, convertedWindowsWidth, (x + 1) * 6);

    glEnd();
}