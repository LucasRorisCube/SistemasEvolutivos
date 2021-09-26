#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>

#include "AG.h"
#include "draw.h"

int minRange_x;
int maxRange_x;

int numberPopulation;

float TaxMutation;

int mode;

int geration;

char* evolutionMode;

chromosome* individuals = NULL;

void setupAG(int new_min_x, int new_max_x, int new_numberPopulation, float new_TaxMutation){
    minRange_x = new_min_x;
    maxRange_x = new_max_x;
    numberPopulation = new_numberPopulation;
    TaxMutation = new_TaxMutation;
    evolutionMode = (char*)malloc(sizeof(char)*20);
    strcpy(evolutionMode,"Elitismo");
    mode = 1;
    geration = 0;
}

void startPopulation(){
    free(individuals);
    individuals = (chromosome*) malloc(sizeof(chromosome)*numberPopulation);

    for(int i = 0; i < numberPopulation ; i++){
        individuals[i].x = minRange_x + ((float)rand()/(float)(RAND_MAX))*(maxRange_x-minRange_x);
    }
    geration = 0;
}

int getIndividualBiggerFitness(){
    int individualBiggerFitness;
    float biggerFitness;
    float tempFitness;
    for(int i = 0; i < numberPopulation ; i++){
        tempFitness = function(individuals[i]);
        if(tempFitness > biggerFitness){
            individualBiggerFitness = i;
            biggerFitness = tempFitness;
        }
    }
    return individualBiggerFitness;
}

void elitismo(chromosome* individuals){
    
    // Take the index of individual who have bigger fitness
    int individualBiggerFitness = getIndividualBiggerFitness();
    
    // Create a auxiliar population
    chromosome* tempPopulation = (chromosome*)malloc(sizeof(chromosome)*numberPopulation);

    for(int i = 0 ; i < numberPopulation ; i++){

        // if individual is who have bigger fitness, don't modified
        if(individuals[i].x == individuals[individualBiggerFitness].x){
            tempPopulation[i] = individuals[individualBiggerFitness];
            continue;
        }

        // CrossOver with arithmetic average
        tempPopulation[i].x = (individuals[i].x + individuals[individualBiggerFitness].x)/2.0;
        if(rand()%2){
            tempPopulation[i].x = tempPopulation[i].x + TaxMutation;
        } else {
            tempPopulation[i].x = tempPopulation[i].x - TaxMutation;
        }
        
    }

    for(int i = 0 ; i < numberPopulation ; i++){
        individuals[i] = tempPopulation[i];
    }

    free(tempPopulation);
}

void torneioDe2(chromosome* individuals){
    chromosome* tempPopulation = (chromosome*)malloc(sizeof(chromosome)*numberPopulation);

    int individualBiggerFitnes = getIndividualBiggerFitness();
    for(int i = 0 ; i < numberPopulation ; i++){

        if(i == individualBiggerFitnes){
            tempPopulation[i] = individuals[individualBiggerFitnes];
            continue;
        }
        int individual1 = rand()%numberPopulation;
        int individual2 = rand()%numberPopulation;
        while(individual1 == individual2){
            individual2 = rand()%numberPopulation;
        }
        
        int father;
        if(function(individuals[individual1]) > function(individuals[individual2])){
            father = individual1;
        } else {
            father = individual2;
        }
        /////
        individual1 = rand()%numberPopulation;
        individual2 = rand()%numberPopulation;
        while(individual1 == individual2){
            individual2 = rand()%numberPopulation;
        }
        
        int mother;
        if(function(individuals[individual1]) > function(individuals[individual2])){
            mother = individual1;
        } else {
            mother = individual2;
        }
        
        tempPopulation[i].x = (individuals[father].x + individuals[mother].x)/2.0;

        if(rand()%2){
            tempPopulation[i].x = tempPopulation[i].x + TaxMutation;
        } else {
            tempPopulation[i].x = tempPopulation[i].x - TaxMutation;
        }
    }

    for(int i = 0 ; i < numberPopulation ; i++){
        individuals[i] = tempPopulation[i];
    }

    free(tempPopulation);
}

void bubble_sort(chromosome* individuals){
    for(int i = 0; i < numberPopulation; i++){
        int ordenate = 1;
        for(int j = 0 ; j < numberPopulation - i; j++){
            if(function(individuals[j]) < function(individuals[j+1])){
                chromosome temp = individuals[j];
                individuals[j] = individuals[j+1];
                individuals[j+1] = temp;
                ordenate = 0;
            }
        }
        if(ordenate) break;
    }
}


void roleta(chromosome* individuals){
    chromosome* tempPopulation = (chromosome*)malloc(sizeof(chromosome)*numberPopulation);
    chromosome* tempPopulationSorted = (chromosome*)malloc(sizeof(chromosome)*numberPopulation);

    for(int i = 0 ; i < numberPopulation ; i++){
        tempPopulationSorted[i] = individuals[i];
    }

    bubble_sort(tempPopulationSorted);

    int individualBiggerFitness = getIndividualBiggerFitness();

    for(int i = 0 ; i < numberPopulation ; i++){

        if(i == individualBiggerFitness){
            tempPopulation[i] = tempPopulationSorted[individualBiggerFitness];
            continue;
        }

        int sortedNumber = ((float)rand()/(float)(RAND_MAX))*(1000);

        float proportion = 0.5;
        int father = 0;
        while(1){
            if(sortedNumber < 1000*(1-proportion)){
                break;
            }
            father += 1;
            proportion /= 2.0;
        }
        
        /////

        sortedNumber = ((float)rand()/(float)(RAND_MAX))*(1000);

        proportion = 0.5;
        int mother = 0;
        while(1){
            if(sortedNumber < 1000*(1-proportion)){
                break;
            }
            mother += 1;
            proportion /= 2.0;
        }
        
        tempPopulation[i].x = (tempPopulationSorted[father].x + tempPopulationSorted[mother].x)/2.0;

        if(rand()%2){
            tempPopulation[i].x = tempPopulation[i].x + TaxMutation;
        } else {
            tempPopulation[i].x = tempPopulation[i].x - TaxMutation;
        }
    }

    for(int i = 0 ; i < numberPopulation ; i++){
        individuals[i] = tempPopulation[i];
    }

    free(tempPopulation);
    free(tempPopulationSorted);
}

void evolve(){

    switch (mode)
    {
    case 1:
        elitismo(individuals);
        geration++;
        break;
    case 2:
        torneioDe2(individuals);
        geration++;
        break;
    case 3:
        roleta(individuals);
        geration++;
        break;
    default:
        break;
    }
}

void doubleTaxMutation(){
    TaxMutation *= 2.0;
}

void halfTaxMutation(){
    TaxMutation /= 2.0;
}

void setEvolveMode(int new_mode){
    switch (new_mode)
    {
    case 1:
        strcpy(evolutionMode,"Elitismo");
        break;
    case 2:
        strcpy(evolutionMode,"TorneioDe2");
        break;
    case 3:
        strcpy(evolutionMode,"Roleta");
        break;
    default:
        break;
    }
    
    mode = new_mode;
}

int getGeration(){
    return geration;
}

float getTaxMutation(){
    return TaxMutation;
}

chromosome* getIndividuals(){
    return individuals;
}

float getBiggerFitness(){
    return function(individuals[getIndividualBiggerFitness()]);
}

float getPopulationAverage(){
    float average = 0;
    for (int i = 0 ; i < numberPopulation ; i++){
        average += function(individuals[i]);
    }
    average /= numberPopulation;
    return average;
}

char* getEvolutionMode(){
    return evolutionMode;
}

int getNumberPopulation(){
    return numberPopulation;
}

void increasePopulation(int increase){
    numberPopulation += increase;
}
void decreasePopulation(int decrease){
    numberPopulation -= decrease;
}