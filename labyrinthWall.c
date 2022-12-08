#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include "index.h"

double axisY = 0;
double axisX = 0;

void Draw(void)
{
    //  Clear screen and Z-buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glLoadIdentity();

    glRotatef(axisX, 1.0, 0.0, 0.0);
    glRotatef(axisY, 0.0, 1.0, 0.0);

    // Multi-colored side - FRONT
    glBegin(GL_QUADS);
    glColor3f(0.8, 0.0, 0.4);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glEnd();

    // White side - BACK
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glEnd();

    // Purple side - RIGHT
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glEnd();

    // Green side - LEFT
    glBegin(GL_QUADS);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glEnd();

    // Blue side - TOP
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glEnd();

    // Red side - BOTTOM
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glEnd();

    glFlush();
    glutSwapBuffers();
}

// Fun��o callback chamada quando o tamanho da janela � alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
    // Evita a divisao por zero
    if (h == 0)
        h = 1;

    // Especifica as dimens�es da Viewport
    glViewport(0, 0, w, h);

    // init o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Estabelece a janela de sele��o (esquerda, direita, inferior,
    // superior) mantendo a propor��o com a janela de visualiza��o
    if (w <= h)
        gluOrtho2D(-50.0f, 50.0f, -50.0f * h / w, 50.0f * h / w);
    else
        gluOrtho2D(-50.0f * w / h, 50.0f * w / h, -50.0f, 50.0f);
}

// Fun��o callback chamada para gerenciar eventos de teclas
void Keyboard(unsigned char key, int x, int y)
{
    printf("%d\n", key);

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