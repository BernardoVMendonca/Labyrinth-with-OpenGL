// Programa Principal
#include "index.h"

/*GLOBAL*/

Map labyrinth;
Player labyrinthGuy;
int mapViewState = FALSE;

/*--------------*/

void TeleportPlayer(int teleportType)
{
    (teleportType == UP && labyrinthGuy.currentFloor < labyrinth.numberOfFloors) ? labyrinthGuy.currentFloor++ : 0;
    (teleportType == DOWN && labyrinthGuy.currentFloor > 1) ? labyrinthGuy.currentFloor-- : 0;

    int i, j;
    for (i = ((labyrinthGuy.currentFloor - 1) * labyrinth.floorSize); i < (labyrinth.floorSize * labyrinthGuy.currentFloor); i++)
    {
        for (j = 0; j < labyrinth.floorSize; j++)
        {
            if ((teleportType == UP && labyrinth.map[i][j] == '2') ||
                (teleportType == DOWN && labyrinth.map[i][j] == '3') ||
                (teleportType == DOWN && labyrinthGuy.currentFloor == 1 && labyrinth.map[i][j] == '2') ||
                (teleportType == UP && labyrinthGuy.currentFloor == labyrinth.numberOfFloors && labyrinth.map[i][j] == '3'))
            {
                labyrinthGuy.playerCamera.x = ((j + 1) * 6) - 3;
                labyrinthGuy.playerCamera.z = ((i + 1) * 6) - 3;
                break;
            }
        }
    }

    glClearColor(0, 0, 0, 0.0);
    return;
}

int PlayerCollision(unsigned char key)
{
    float fraction = 0.5f;

    int mulFactor = 1;

    int blockPosX = ((labyrinthGuy.playerCamera.x) / 6),
        blockPosZ = ((labyrinthGuy.playerCamera.z) / 6);

    (key == 's') ? mulFactor *= -1 : 0;

    /*START COLLISION*/

    if (labyrinth.map[blockPosZ][blockPosX] == 'x' && labyrinth.numberOfItems == 0)
    {
        printf("\n******YOU WON THE GAME******\n");
        exit(0);
    }

    /*--------------*/

    /*COLLISION*/

    switch (key)
    {
    case 'w':
    case 's':
        blockPosX = ((labyrinthGuy.playerCamera.x + (labyrinthGuy.playerCamera.lx * fraction * mulFactor)) / 6);
        blockPosZ = ((labyrinthGuy.playerCamera.z + (labyrinthGuy.playerCamera.lz * fraction * mulFactor)) / 6);
        break;
    case 'e':
        switch (labyrinth.map[blockPosZ][blockPosX])
        {
        case '2':
            TeleportPlayer(UP);
            break;
        case '3':
            TeleportPlayer(DOWN);
            break;
        case '4':
            labyrinth.numberOfItems--;
            labyrinth.map[blockPosZ][blockPosX] = '0';
            break;
        default:
            break;
        }
        return TRUE;
    default:
        break;
    }

    if (labyrinth.map[blockPosZ][blockPosX] == '1')
    {
        labyrinthGuy.playerCamera.x -= (labyrinthGuy.playerCamera.lx * fraction * mulFactor);
        labyrinthGuy.playerCamera.z -= (labyrinthGuy.playerCamera.lz * fraction * mulFactor);

        return TRUE;
    }

    /*--------------*/

    return FALSE;
}

void SetInitialMapConfig()
{
    /*MAP CONFIG*/

    labyrinth.map = (char **)malloc(1 * sizeof(char *));
    labyrinth.map[0] = (char *)malloc(1 * sizeof(char));
    labyrinth.numberOfItems = 0;
    labyrinth.floorSize = 0;
    labyrinth.numberOfFloors = 0;

    /*--------------*/

    return;
}

void SetInitialPlayerConfig()
{
    /*PLAYER CONFIG*/

    labyrinthGuy.playerCamera.angle = 0;
    labyrinthGuy.playerCamera.lx = sin(labyrinthGuy.playerCamera.angle);
    labyrinthGuy.playerCamera.lz = -cos(labyrinthGuy.playerCamera.angle);

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

    /*--------------*/

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

    int xIndex = 0, yIndex = 0;
    char aux;

    while (TRUE)
    {
        aux = getc(fp);

        if (aux == EOF)
            break;

        if (aux != '\n' && aux != ' ')
        {
            (aux == '4') ? labyrinth.numberOfItems++ : 0;

            labyrinth.map[yIndex][xIndex] = aux;
            xIndex++;
            labyrinth.map[yIndex] = (char *)realloc(labyrinth.map[yIndex], (xIndex + 1) * sizeof(char));
        }
        else if (aux == '\n')
        {
            xIndex = 0;
            yIndex++;
            labyrinth.map = (char **)realloc(labyrinth.map, (yIndex + 1) * sizeof(char *));
            labyrinth.map[yIndex] = (char *)malloc(1 * sizeof(char));
        }
    }
    
    labyrinth.floorSize = xIndex;
    labyrinth.numberOfFloors = (yIndex + 1) / labyrinth.floorSize;

    printf("\nfloor size: %d x %d\n", labyrinth.floorSize, labyrinth.floorSize);
    printf("number of floors: %d\n", labyrinth.numberOfFloors);
    printf("number of items: %d\n", labyrinth.numberOfItems);

    /*MAP TEST*/

    // int i, j;
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
    if (PlayerCollision(key))
        return;

    if (mapViewState)
    {
        mapViewState = FALSE;
        return;
    }

    float fraction = 0.3f;

    if (key == 'm' && mapViewState == FALSE)
    {
        mapViewState = TRUE;
        return;
    }

    switch (key)
    {
    case 'd':
        labyrinthGuy.playerCamera.angle += 0.05f;
        labyrinthGuy.playerCamera.lx = sin(labyrinthGuy.playerCamera.angle);
        labyrinthGuy.playerCamera.lz = -cos(labyrinthGuy.playerCamera.angle);
        break;
    case 'a':
        labyrinthGuy.playerCamera.angle -= 0.05f;
        labyrinthGuy.playerCamera.lx = sin(labyrinthGuy.playerCamera.angle);
        labyrinthGuy.playerCamera.lz = -cos(labyrinthGuy.playerCamera.angle);
        break;
    case 'w':
        labyrinthGuy.playerCamera.x += labyrinthGuy.playerCamera.lx * fraction;
        labyrinthGuy.playerCamera.z += labyrinthGuy.playerCamera.lz * fraction;
        break;
    case 's':
        labyrinthGuy.playerCamera.x -= labyrinthGuy.playerCamera.lx * fraction;
        labyrinthGuy.playerCamera.z -= labyrinthGuy.playerCamera.lz * fraction;
        break;
    default:
        break;
    }

    PlayerCollision(key);

    glutPostRedisplay();
}

void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    DrawMap(labyrinth, labyrinthGuy);

    glLoadIdentity();

    (mapViewState == FALSE) ? gluLookAt(labyrinthGuy.playerCamera.x, 1.0f, labyrinthGuy.playerCamera.z,
                                        labyrinthGuy.playerCamera.x + labyrinthGuy.playerCamera.lx, 1.0f, labyrinthGuy.playerCamera.z + labyrinthGuy.playerCamera.lz,
                                        0.0f, 1.0f, 0.0f)
                            : gluLookAt(labyrinthGuy.playerCamera.x, windowsWidth / 100 + 30, labyrinthGuy.playerCamera.z,
                                        labyrinthGuy.playerCamera.x, 0.0f, labyrinthGuy.playerCamera.z,
                                        1.0f, 1.0f, 0.0f);

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
    SetInitialMapConfig();

    /*FILE READING*/

    if (!ReadFile())
        return FALSE;

    /*--------------*/

    SetInitialPlayerConfig();

    /*PRINT INSTRUCTIONS*/

    printf("\n*--------------*\n\n");
    printf("GAME GOAL: Get all the items across the map and return to the start position to win the game\n\n");
    printf("PLAYER MOVEMENT:\n   w --> Up\n   s --> Down\n   a --> Left\n   d --> Right\n\n");
    printf("PLAYER ACTIONS:\n   e --> Use teleport and get items\n   m --> See the map\n\n");
    printf("MAP COMPONENTS:\n   green block --> Player position\n   red block --> Teleport up\n   pink block --> Teleport down\n   orange block --> Item\n\n");
    printf("*--------------*\n");

    /*--------------*/

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowsHeight, windowsWidth);
    glutCreateWindow("Labyrinth");

    DefineCallbacks();

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();

    /*FREE MEMORY*/

    FreeMapMemory();

    /*--------------*/

    return TRUE;
}
