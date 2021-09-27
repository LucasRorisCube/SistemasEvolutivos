#ifndef __drawFunction__
#define __drawFunction__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>

#include "AG.h"

void setupDraw(int newMin_x, int newMax_x, int newMin_y, int newMax_y,float new_precision);

void drawAxes();
void drawTriangle(float x, float y, float b, float h,int mode);
void drawFunction();
void drawPopulation();
void drawInformation();

float function(chromosome individual);


#endif