#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>

#include "draw.h"
#include "AG.h"

#define WIDTH glutGet(GLUT_SCREEN_WIDTH)
#define HEIGHT glutGet(GLUT_SCREEN_HEIGHT)

#define MIN_X -1000
#define MAX_X 1000
#define MIN_Y -1000
#define MAX_Y 1000
#define PRECISION 0.05

#define POPULATION 20
#define TAX_MUTATION 0.2

int showInformations = 1;

float function(chromosome individual){
    float res = -1;
    // if(individual.x < 5){
    //     res = individual.x;
    // } else if(individual.x < 10){
    //     res = 10-individual.x;
    // } else if(individual.x < 20){
    //     res = individual.x-10;
    // } else {
    //     res = 30-individual.x;
    // }
    res = (2*cos(0.039*individual.x) + 5*sin(0.05*individual.x) + 0.5*cos(0.01*individual.x) + 10*sin(0.07*individual.x) + 5*sin(0.1*individual.x) + 5*sin(0.035*individual.x))*10;
    return res;
}

void mouse(int button, int state, int x, int y)
{
    //float mouseX, mouseY;
    //mouseX = x;
    //mouseY = y;

}



void Draw(){

    glClearColor(112/255.0, 128/255.0, 144/255.0, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT);

    drawAxes();

    drawFunction();

    drawPopulation();

    if(showInformations){
        drawInformation();
    }

    glFlush();
}

void Keyboard(unsigned char key, int x, int y){

    //chromosome* individuals;

    switch (key)
    {
    case 'r':
        startPopulation();
        break;
    case 'e':
        evolve();
        break;
    case 'd':
        doubleTaxMutation();
        break;
    case 'f':
        halfTaxMutation();
        break;
    case 'c':
        increasePopulation(5);
        startPopulation();
        break;
    case 'v':
        decreasePopulation(5);
        startPopulation();
        break;
    case 'h':
        if(showInformations){
            showInformations = 0;
        } else {
            showInformations = 1;
        }
        break;
    case '1':
        setEvolveMode(1);
        
        break;
    case '2':
        setEvolveMode(2);
        
        break;
    case '3':
        setEvolveMode(3);
        
    default:
        break;
    }
    Draw();
    
}

int main(int argc, char *argv[]){

    srand(time(NULL));

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));

    glutCreateWindow("Evolutive Systems - Cubo, Lucas");

    glutDisplayFunc(Draw);

    glutKeyboardFunc(Keyboard);

    glutMouseFunc(mouse);

    setupAG(MIN_X,MAX_X,POPULATION,TAX_MUTATION);
    setupDraw(MIN_X,MAX_X,MIN_Y,MAX_Y,PRECISION);

    Draw();

    glutMainLoop();

    return EXIT_SUCCESS;

}