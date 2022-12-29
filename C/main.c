// Programa Principal
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "index.h"

GLint axisY, axisX;
Map labyrinth;

int ReadFile()
{
    char *path = (char *)malloc(256 * sizeof(char));
    puts("Name/Path of the .txt file: ");
    scanf(" %s", path);
    FILE *fp = fopen(path, "r");
    if (fp == NULL)
    {
        printf("Impossible to open the file!\n");
        return FALSE;
    }

    int xIndex = 0, yIndex = 0, i = 0;
    int boolean = TRUE;

    labyrinth.map = (char **)malloc((yIndex + 1) * sizeof(char *));
    labyrinth.map[yIndex] = (char *)malloc((xIndex + 1) * sizeof(char));

    while (boolean)
    {
        labyrinth.map[yIndex][xIndex] = getc(fp);

        (labyrinth.map[yIndex][xIndex] == EOF) ? (boolean = FALSE) : printf(" %c", labyrinth.map[yIndex][xIndex]);

        if (labyrinth.map[yIndex][xIndex] != '\n' && labyrinth.map[yIndex][xIndex] != EOF)
            labyrinth.map[yIndex] = (char *)realloc(labyrinth.map[yIndex], (xIndex + 1) * sizeof(char));

        else if (labyrinth.map[yIndex][xIndex] != EOF)
        {
            xIndex = 0;
            yIndex++;
            labyrinth.map = (char **)realloc(labyrinth.map, (yIndex + 1) * sizeof(char *));
            labyrinth.map[yIndex] = (char *)malloc(1 * sizeof(char));
        }
        // printf("yIndex: %d xIndex: %d\n", yIndex, xIndex);
        xIndex++;
    }
    labyrinth.floorSize = (xIndex / 2);
    labyrinth.numberOfFloors = (yIndex + 1) / (xIndex / 2);
    printf("\nfloor size: %d x %d\n", labyrinth.floorSize, labyrinth.floorSize);
    printf("number of floors: %d\n", labyrinth.numberOfFloors);

    fclose(fp);
    free(path);

    return TRUE;
}

void Keyboard(unsigned char key, int x, int y)
{
    if (key == 27)
        exit(0);

    else if (key == 'd')
    {
        axisY += 5;
    }

    else if (key == 'a')
    {
        axisY -= 5;
    }

    else if (key == 'w')
    {
        axisX += 5;
    }

    else if (key == 's')
    {
        axisX -= 5;
    }

    glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{
    if (state == 1)
        return;
    if (button == 3)
        glScalef(1.1, 1.1, 1.1);
    else if (button == 4)
        glScalef(0.9, 0.9, 0.9);
    glutPostRedisplay();
}

void Init()
{
    return;
}

void DefineCallbacks()
{
    glutDisplayFunc(Display);
    glutKeyboardFunc(Keyboard);
    glutMouseFunc(Mouse);

    return;
}

int main(int argc, char **argv)
{
    int i;

    /*FILE READING*/

    if (!ReadFile())
        return FALSE;

    /*--------------*/

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Labyrinth");
    glEnable(GL_DEPTH_TEST);

    DefineCallbacks();

    Init();

    glutMainLoop();

    /*FREE MEMORY*/

    for (i = 0; i < (labyrinth.floorSize * labyrinth.numberOfFloors) + 1; i++)
        free(labyrinth.map[i]);
    free(labyrinth.map);

    /*--------------*/

    return TRUE;
}