// Programa Principal
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "index.h"

int main(int argc, char **argv)
{
    /*FILE PROCESSING*/

    char *path = (char *)malloc(128 * sizeof(char));
    puts("Name/Path of the .txt file: ");
    scanf(" %s", path);
    FILE *fp = fopen(path, "r");
    if (fp == NULL)
    {
        printf("Impossible to open the file!\n");
        return 0;
    }

    Map labyrinth;

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

    /*--------------*/

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Labyrinth");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(Draw);
    glutKeyboardFunc(Keyboard);
    glutMainLoop();

    /*FREE MEMORY*/

    fclose(fp);
    for (; i < yIndex; i++)
        free(labyrinth.map[i]);
    free(labyrinth.map);

    /*--------------*/

    return 0;
}