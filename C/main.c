// Programa Principal
#include "index.h"

/*GLOBAL*/

Map labyrinth;
Player labyrinthGuy;
int TeleportPermissionUP = TRUE;
int TeleportPermissionDOWN = TRUE;
/*--------------*/

void TeleportPlayer(int teleportType)
{
    if (teleportType == UP && labyrinthGuy.currentFloor < labyrinth.numberOfFloors)
    {
        labyrinthGuy.currentFloor++;
    }
    else if (teleportType == DOWN && labyrinthGuy.currentFloor > 1)
    {
        labyrinthGuy.currentFloor--;
    }

    int i, j;
    for (i = ((labyrinthGuy.currentFloor - 1) * labyrinth.floorSize); i < (labyrinth.floorSize * labyrinthGuy.currentFloor); i++)
    {
        for (j = 0; j < labyrinth.floorSize; j++)
        {
            if (labyrinth.map[i][j] == '2' && teleportType == UP)
            {
                labyrinthGuy.playerCamera.x = ((j + 1) * 6) - 3;
                labyrinthGuy.playerCamera.z = ((i + 1) * 6) - 3;
                break;
            }
            else if (labyrinth.map[i][j] == '3' && teleportType == DOWN)
            {
                labyrinthGuy.playerCamera.x = ((j + 1) * 6) - 3;
                labyrinthGuy.playerCamera.z = ((i + 1) * 6) - 3;
                break;
            }
            else if (teleportType == DOWN && labyrinthGuy.currentFloor == 1)
            {
                if (labyrinth.map[i][j] == '2')
                {
                    labyrinthGuy.playerCamera.x = ((j + 1) * 6) - 3;
                    labyrinthGuy.playerCamera.z = ((i + 1) * 6) - 3;
                    break;
                }
            }
            else if (teleportType == UP && labyrinthGuy.currentFloor == labyrinth.numberOfFloors)
            {
                if (labyrinth.map[i][j] == '3')
                {
                    labyrinthGuy.playerCamera.x = ((j + 1) * 6) - 3;
                    labyrinthGuy.playerCamera.z = ((i + 1) * 6) - 3;
                    break;
                }
            }
        }
    }
    return;
}

int PlayerCollision(unsigned char key, int time)
{

    float fraction = 0.5f;

    int blockPosX = ((labyrinthGuy.playerCamera.x) / 6),
        blockPosZ = ((labyrinthGuy.playerCamera.z) / 6);

    /*TELEPORT COLLISION*/

    if (time == 1 && TeleportPermissionUP == FALSE && labyrinth.map[blockPosZ][blockPosX] != '2')
        TeleportPermissionUP = TRUE;
    if (time == 1 && TeleportPermissionDOWN == FALSE && labyrinth.map[blockPosZ][blockPosX] != '3')
        TeleportPermissionDOWN = TRUE;

    if (labyrinth.map[blockPosZ][blockPosX] == '2' && TeleportPermissionUP == TRUE)
    {
        TeleportPlayer(UP);
        TeleportPermissionUP = FALSE;
        TeleportPermissionDOWN = FALSE;
        return TRUE;
    }
    else if (labyrinth.map[blockPosZ][blockPosX] == '3' && TeleportPermissionDOWN == TRUE)
    {
        TeleportPlayer(DOWN);
        TeleportPermissionDOWN = FALSE;
        TeleportPermissionUP = FALSE;
        return TRUE;
    }
    printf("current floor: %d\n", labyrinthGuy.currentFloor);

    /*--------------*/

    /*WALL COLLISION*/

    if (key == 'w')
    {
        blockPosX = ((labyrinthGuy.playerCamera.x + labyrinthGuy.playerCamera.lx * fraction) / 6);
        blockPosZ = ((labyrinthGuy.playerCamera.z + labyrinthGuy.playerCamera.lz * fraction) / 6);
    }
    else if (key == 's')
    {
        blockPosX = ((labyrinthGuy.playerCamera.x - labyrinthGuy.playerCamera.lx * fraction) / 6);
        blockPosZ = ((labyrinthGuy.playerCamera.z - labyrinthGuy.playerCamera.lz * fraction) / 6);
    };

    if (labyrinth.map[blockPosZ][blockPosX] == '1')
    {
        if (key == 'w')
        {
            labyrinthGuy.playerCamera.x -= labyrinthGuy.playerCamera.lx * fraction;
            labyrinthGuy.playerCamera.z -= labyrinthGuy.playerCamera.lz * fraction;
        }
        else if (key == 's')
        {
            labyrinthGuy.playerCamera.x += labyrinthGuy.playerCamera.lx * fraction;
            labyrinthGuy.playerCamera.z += labyrinthGuy.playerCamera.lz * fraction;
        }

        return TRUE;
    }

    /*--------------*/

    return FALSE;
}

void SetInitialPlayerConfig()
{
    labyrinthGuy.currentFloor = 1;

    int i, j;
    for (i = ((labyrinthGuy.currentFloor - 1) * labyrinth.floorSize); i < (labyrinth.floorSize * labyrinthGuy.currentFloor); i++)
    {
        for (j = 0; j < labyrinth.floorSize; j++)
        {
            if (labyrinth.map[i][j] == 'x')
            {
                labyrinthGuy.playerCamera.x = ((j + 1) * 6) - 3;
                labyrinthGuy.playerCamera.z = ((i + 1) * 6) - 3;
                break;
            }
        }
    }
    return;
}

void FreeMapMemory()
{
    int i;
    for (i = 0; i < (labyrinth.floorSize * labyrinth.numberOfFloors) + 1; i++)
        free(labyrinth.map[i]);
    free(labyrinth.map);

    return;
}

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
    char aux;
    labyrinth.map = (char **)malloc((yIndex + 1) * sizeof(char *));
    labyrinth.map[yIndex] = (char *)malloc(1 * sizeof(char));

    while (boolean)
    {
        aux = getc(fp);

        if (aux == EOF)
        {
            (boolean = FALSE);
            break;
        }

        // printf("aux: %c yIndex: %d xIndex: %d\n", aux, yIndex, xIndex);

        if (aux != '\n' && aux != ' ')
        {
            labyrinth.map[yIndex][xIndex] = aux;
            xIndex++;
            // if (xIndex % 15 == 0)
            labyrinth.map[yIndex] = (char *)realloc(labyrinth.map[yIndex], (xIndex + 1) * sizeof(char));
        }
        else if (aux == '\n')
        {
            labyrinth.map[yIndex][xIndex] = aux;
            xIndex = 0;
            yIndex++;
            labyrinth.map = (char **)realloc(labyrinth.map, (yIndex + 1) * sizeof(char *));
            labyrinth.map[yIndex] = (char *)malloc(15 * sizeof(char));
        }
    }
    labyrinth.floorSize = xIndex;
    labyrinth.numberOfFloors = (yIndex + 1) / labyrinth.floorSize;

    printf("\nfloor size: %d x %d\n", labyrinth.floorSize, labyrinth.floorSize);
    printf("number of floors: %d\n", labyrinth.numberOfFloors);

    /*MAP TEST*/

    // int j;
    // for (i = 0; i < labyrinth.floorSize; i++)
    // {
    //     for (j = 0; j < labyrinth.floorSize; j++)
    //         printf(" %c", labyrinth.map[i][j]);
    //     printf("\n");
    // }

    /*--------------*/

    fclose(fp);
    free(path);

    return TRUE;
}

void WindowsResize(int w, int h)
{

    if (h == 0)
        h = 1;
    float ratio = w * 1.0 / h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
}

void UserActions(unsigned char key, int xx, int yy)
{
    if (PlayerCollision(key, 1))
    {
        return;
    }

    float fraction = 0.3f;

    /*USER MOVEMENT*/
    if (key == 'd')
    {
        labyrinthGuy.playerCamera.angle += 0.05f;
        labyrinthGuy.playerCamera.lx = sin(labyrinthGuy.playerCamera.angle);
        labyrinthGuy.playerCamera.lz = -cos(labyrinthGuy.playerCamera.angle);
    }

    if (key == 'a')
    {
        labyrinthGuy.playerCamera.angle -= 0.05f;
        labyrinthGuy.playerCamera.lx = sin(labyrinthGuy.playerCamera.angle);
        labyrinthGuy.playerCamera.lz = -cos(labyrinthGuy.playerCamera.angle);
    }

    if (key == 'w')
    {
        labyrinthGuy.playerCamera.x += labyrinthGuy.playerCamera.lx * fraction;
        labyrinthGuy.playerCamera.z += labyrinthGuy.playerCamera.lz * fraction;
    }

    if (key == 's')
    {
        labyrinthGuy.playerCamera.x -= labyrinthGuy.playerCamera.lx * fraction;
        labyrinthGuy.playerCamera.z -= labyrinthGuy.playerCamera.lz * fraction;
    }

    PlayerCollision(key, 2);
    /*--------------*/

    /*USER GET ITEM*/
    /*--------------*/

    glutPostRedisplay();
}

void Display(void)
{
    glClearColor(0, 0, 0, 0.0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set the camera

    DrawMap(labyrinth, labyrinthGuy);
    glLoadIdentity();
    gluLookAt(labyrinthGuy.playerCamera.x, 1.0f, labyrinthGuy.playerCamera.z,
              labyrinthGuy.playerCamera.x + labyrinthGuy.playerCamera.lx, 1.0f, labyrinthGuy.playerCamera.z + labyrinthGuy.playerCamera.lz,
              0.0f, 1.0f, 0.0f);
    return;
}

void DefineCallbacks()
{
    glutDisplayFunc(Display);
    glutReshapeFunc(WindowsResize);
    glutIdleFunc(Display);
    glutKeyboardFunc(UserActions);

    return;
}

int main(int argc, char **argv)
{
    /*FILE READING*/

    if (!ReadFile())
        return FALSE;

    /*--------------*/

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowsHeight, windowsWidth);
    glutCreateWindow("Labyrinth");

    SetInitialPlayerConfig();

    DefineCallbacks();

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();

    /*FREE MEMORY*/

    FreeMapMemory();

    /*--------------*/

    return TRUE;
}