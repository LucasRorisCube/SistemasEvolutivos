#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>

#define WIDTH glutGet(GLUT_SCREEN_WIDTH)
#define HEIGHT glutGet(GLUT_SCREEN_HEIGHT)

#define MIN_X -1000
#define MAX_X 1000
#define MIN_Y -1000
#define MAX_Y 1000
#define PRECISION 0.05



void mouse(int button, int state, int x, int y)
{

}



void Draw(){

    glClearColor(255/255.0, 255/255.0, 255/255.0, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POLYGON); // desenha um polígono
        glNormal3f(0,-1,0);   // define a normal da face (essencial para usar luzes)
        glVertex3f(-10.0, -10.0, -10.0); // define os vértices da face
        glVertex3f(10.0, -10.0, -10.0);
        glVertex3f(10.0, -10.0, 10.0);
        glVertex3f(-10.0, -10.0, 10.0);
    glEnd;

    glBegin(GL_POLYGON); // desenha um polígono
           // define a normal da face (essencial para usar luzes)
        glVertex2f(-10.0, -10.0); // define os vértices da face
        glVertex2f(10.0, -10.0);
        glVertex2f(10.0, -10.0);
        glVertex2f(-10.0, -10.0);
    glEnd; 

    glFlush();
}

void Keyboard(unsigned char key, int x, int y){

    
}

void timer(){

    glutTimerFunc(1000/1, timer, 0);
}

int main(int argc, char *argv[]){

    srand(time(NULL));

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));

    glutCreateWindow("Rubik's Bube - Cubo, Lucas");



    glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

// define projeção perspectiva. Deve ser colocado ANTES do gluLookAt
    gluPerspective(0,1,1,1000);
// Define a posição do observador no cenário 3D
    gluLookAt(0,0,0, 0,0,29, 0,1,0);
    glMatrixMode(GL_MODELVIEW);

    glutDisplayFunc(Draw);

    glutKeyboardFunc(Keyboard);

    glutMouseFunc(mouse);

    Draw();

    glutTimerFunc(0, timer, 0);

    glutMainLoop();

    return EXIT_SUCCESS;

}