#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>

#include "AG.h"
#include "draw.h"

float precision;
int min_x;
int max_x;
int min_y; 
int max_y;

void setupDraw(int newMin_x, int newMax_x, int newMin_y, int newMax_y,float new_precision){

    min_x = newMin_x;
    max_x = newMax_x;
    min_y = newMin_y; 
    max_y = newMax_y;
    precision = new_precision;
    gluOrtho2D(min_x, max_x, min_y, max_y);
}

void drawAxes(){
    glLineWidth(5.0f);
    glColor3f(0.0f,0.0f,0.0f);
    glBegin(GL_LINES);
        glVertex2f(min_x,0);
        glVertex2f(max_x,0);

        glVertex2f(0,min_y);
        glVertex2f(0,max_y);
    glEnd();

    drawTriangle(0,max_y*0.95,0.5,1.0,0);
    drawTriangle(max_x*0.95,0,0.5,1.0,1);
}

void drawTriangle(float x, float y, float b, float h,int mode){
    glBegin(GL_POLYGON);
    
    switch (mode)
    {
    case 0: // Top
        glVertex2f(x,y+2*h/3.0);
        glVertex2f(x+b/2.0,y-h/3.0);
        glVertex2f(x-b/2.0,y-h/3.0);
        break;
    case 1: // Right
        glVertex2f(x+2*h/3.0,y);
        glVertex2f(x-h/3.0,y-2*b/3.0);
        glVertex2f(x-h/3.0,y+2*b/3.0);
        break;
    case 2: // Left
        glVertex2f(x-2*h/3.0,y);
        glVertex2f(x+h/3.0,y+2*b/3.0);
        glVertex2f(x+h/3.0,y-2*b/3.0);
        break;
    case 3: // Botton
        glVertex2f(x,y-2*h/3.0);
        glVertex2f(x-b/2.0,y+h/3.0);
        glVertex2f(x+b/2.0,y+h/3.0);
        break;
    default:
        break;
    }

    glEnd();
}

void drawFunction(){
    glPointSize(1);
    glBegin(GL_POINTS);
        float y;
        for (float i = min_x; i < max_x; i+=precision){
            chromosome tempIndividual;
            tempIndividual.x = i;
            y = function(tempIndividual);
            glVertex2f((float)i,y);
        }
    glEnd();
}

void drawPopulation(){

    chromosome* individuals = getIndividuals();

    if(individuals == NULL){
        startPopulation();
        individuals = getIndividuals();
    }
    int individualBiggerFitness = getIndividualBiggerFitness(individuals);
    float tempFitness;
    int numberPopulation = getNumberPopulation();
    glPointSize(4.0f);
    glColor3f(1.0f,0.0f,0.0f);
    glBegin(GL_POINTS);
        for(int i = 0; i <  numberPopulation; i++){
            if(i == individualBiggerFitness){
                continue;
            }
            tempFitness = function(individuals[i]);
            glVertex2f(individuals[i].x,tempFitness);
        }
    glEnd();

    glPointSize(7.0f);
    glColor3f(0.0f,0.0f,1.0f);

    glBegin(GL_POINTS);
        glVertex2f(individuals[individualBiggerFitness].x,function(individuals[individualBiggerFitness]));
    glEnd();
}


void drawCommands(){
    glRasterPos2f(min_x+(max_x-min_x)*0.005,min_y+(max_y-min_y)*0.015);

    char* auxiliarToPrint = (char*)malloc(sizeof(char)*50);

    strcpy(auxiliarToPrint,"r -> reset population");
    auxiliarToPrint[strlen(auxiliarToPrint)] = '\0';
    for(int i = 0; auxiliarToPrint[i]!='\0';i++){
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13,auxiliarToPrint[i]);
    }

    glutBitmapCharacter(GLUT_BITMAP_8_BY_13,' ');

    strcpy(auxiliarToPrint,"e -> evolve population");
    auxiliarToPrint[strlen(auxiliarToPrint)] = '\0';
    for(int i = 0; auxiliarToPrint[i]!='\0';i++){
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13,auxiliarToPrint[i]);
    }

    glRasterPos2f(min_x+(max_x-min_x)*0.005,min_y+(max_y-min_y)*0.035);

    strcpy(auxiliarToPrint,"d -> multiply per 2 Tax of mutation");
    auxiliarToPrint[strlen(auxiliarToPrint)] = '\0';
    for(int i = 0; auxiliarToPrint[i]!='\0';i++){
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13,auxiliarToPrint[i]);
    }

    glutBitmapCharacter(GLUT_BITMAP_8_BY_13,' ');

    strcpy(auxiliarToPrint,"f -> divide per 2 Tax of mutation");
    auxiliarToPrint[strlen(auxiliarToPrint)] = '\0';
    for(int i = 0; auxiliarToPrint[i]!='\0';i++){
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13,auxiliarToPrint[i]);
    }

    glRasterPos2f(min_x+(max_x-min_x)*0.005,min_y+(max_y-min_y)*0.055);

    strcpy(auxiliarToPrint,"c -> increase population");
    auxiliarToPrint[strlen(auxiliarToPrint)] = '\0';
    for(int i = 0; auxiliarToPrint[i]!='\0';i++){
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13,auxiliarToPrint[i]);
    }

    glutBitmapCharacter(GLUT_BITMAP_8_BY_13,' ');

    strcpy(auxiliarToPrint,"v -> decrease population");
    auxiliarToPrint[strlen(auxiliarToPrint)] = '\0';
    for(int i = 0; auxiliarToPrint[i]!='\0';i++){
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13,auxiliarToPrint[i]);
    }

    glRasterPos2f(min_x+(max_x-min_x)*0.005,min_y+(max_y-min_y)*0.075);

    strcpy(auxiliarToPrint,"1,2,3 -> change evolution mode");
    auxiliarToPrint[strlen(auxiliarToPrint)] = '\0';
    for(int i = 0; auxiliarToPrint[i]!='\0';i++){
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13,auxiliarToPrint[i]);
    }

    glutBitmapCharacter(GLUT_BITMAP_8_BY_13,' ');

    strcpy(auxiliarToPrint,"h -> hide/show informations");
    auxiliarToPrint[strlen(auxiliarToPrint)] = '\0';
    for(int i = 0; auxiliarToPrint[i]!='\0';i++){
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13,auxiliarToPrint[i]);
    }

    free(auxiliarToPrint);
}

void drawInformation(){

    chromosome* individuals = getIndividuals();

    if(individuals == NULL){
        startPopulation();
        individuals = getIndividuals();
    }

    glColor3f(0.0,1.0,0.0);

    glRasterPos2f(min_x+(max_x-min_x)*0.005,max_y-(max_y-min_y)*0.015);

    char* auxiliarToPrint = (char*)malloc(sizeof(char)*50);

    sprintf(auxiliarToPrint,"Geration: %d",getGeration());
    auxiliarToPrint[strlen(auxiliarToPrint)] = '\0';
    for(int i = 0; auxiliarToPrint[i]!='\0';i++){
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13,auxiliarToPrint[i]);
    }

    glRasterPos2f(min_x+(max_x-min_x)*0.005,max_y-(max_y-min_y)*0.035);

    sprintf(auxiliarToPrint,"TaxMutation: %.5f",getTaxMutation());
    auxiliarToPrint[strlen(auxiliarToPrint)] = '\0';
    for(int i = 0; auxiliarToPrint[i]!='\0';i++){
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13,auxiliarToPrint[i]);
    }
    
    glRasterPos2f(min_x+(max_x-min_x)*0.005,max_y-(max_y-min_y)*0.055);

    sprintf(auxiliarToPrint,"Best Fitness: %.5f",getBiggerFitness());
    auxiliarToPrint[strlen(auxiliarToPrint)] = '\0';
    
    for(int i = 0; auxiliarToPrint[i]!='\0';i++){
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13,auxiliarToPrint[i]);
    }

    glRasterPos2f(min_x+(max_x-min_x)*0.005,max_y-(max_y-min_y)*0.075);

    sprintf(auxiliarToPrint,"Population avarage: %.5f",getPopulationAverage());
    auxiliarToPrint[strlen(auxiliarToPrint)] = '\0';
    
    for(int i = 0; auxiliarToPrint[i]!='\0';i++){
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13,auxiliarToPrint[i]);
    }

    glRasterPos2f(min_x+(max_x-min_x)*0.005,max_y-(max_y-min_y)*0.095);

    sprintf(auxiliarToPrint,"Evolution mode: %s",getEvolutionMode());
    auxiliarToPrint[strlen(auxiliarToPrint)] = '\0';
    
    for(int i = 0; auxiliarToPrint[i]!='\0';i++){
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13,auxiliarToPrint[i]);
    }

    glRasterPos2f(min_x+(max_x-min_x)*0.005,max_y-(max_y-min_y)*0.115);

    sprintf(auxiliarToPrint,"Population: %d",getNumberPopulation());
    auxiliarToPrint[strlen(auxiliarToPrint)] = '\0';
    
    for(int i = 0; auxiliarToPrint[i]!='\0';i++){
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13,auxiliarToPrint[i]);
    }

    drawCommands();
    free(auxiliarToPrint);
}
