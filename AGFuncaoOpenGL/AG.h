#ifndef __AG__
#define __AG__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>

typedef struct{
    float x;
}chromosome;


void setupAG(int new_min_x, int new_max_x, int new_numberPopulation, float new_TaxMutation);
void startPopulation();
void evolve();
int getIndividualBiggerFitness();
void doubleTaxMutation();
void halfTaxMutation();
void setEvolveMode(int new_mode);

int getGeration();
float getTaxMutation();
chromosome* getIndividuals();
float getBiggerFitness();
float getPopulationAverage();
char* getEvolutionMode();
int getNumberPopulation();

void increasePopulation(int increase);
void decreasePopulation(int decrease);
#endif