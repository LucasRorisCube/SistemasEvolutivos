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
float defaultTaxMutation;

int mode;

int geration;

char* evolutionMode;

chromosome* individuals = NULL;

chromosome Bestindividuals[10];

float modFloat(float x){
    return (x<0)?-x:x;
}

void setupAG(int new_min_x, int new_max_x, int new_numberPopulation, float new_TaxMutation){
    minRange_x = new_min_x;
    maxRange_x = new_max_x;
    numberPopulation = new_numberPopulation;
    TaxMutation = new_TaxMutation;
    defaultTaxMutation = new_TaxMutation;
    evolutionMode = (char*)malloc(sizeof(char)*20);
    strcpy(evolutionMode,"Elitismo");
    mode = 1;
    geration = 0;
    for(int i = 0; i < 10 ; i++){
        Bestindividuals[i].x = 0;
    }
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
            tempPopulation[i].x = tempPopulation[i].x + TaxMutation*(maxRange_x-minRange_x);
        } else {
            tempPopulation[i].x = tempPopulation[i].x - TaxMutation*(maxRange_x-minRange_x);
        }
        
    }

    for(int i = 0 ; i < numberPopulation ; i++){
        individuals[i] = tempPopulation[i];
    }

    free(tempPopulation);
}

void bubble_sort_mod(chromosome* individuals){
    for(int i = 0; i < numberPopulation-numberPopulation/2; i++){
        int ordenate = 1;
        for(int j = 0 ; j < numberPopulation - i; j++){
            if(function(individuals[j]) > function(individuals[j+1])){
                chromosome temp = individuals[j];
                individuals[j] = individuals[j+1];
                individuals[j+1] = temp;
                ordenate = 0;
            }
        }
        if(ordenate) break;
    }
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

    bubble_sort_mod(tempPopulation);
    bubble_sort_mod(individuals);

    for(int i = 0 ; i < numberPopulation*0.01 ; i++){
        individuals[i] = tempPopulation[numberPopulation-i];
    }

    free(tempPopulation);
}



void roleta(chromosome* individuals){
    chromosome* tempPopulation = (chromosome*)malloc(sizeof(chromosome)*numberPopulation);
    chromosome* tempPopulationSorted = (chromosome*)malloc(sizeof(chromosome)*numberPopulation);

    for(int i = 0 ; i < numberPopulation ; i++){
        tempPopulationSorted[i] = individuals[i];
    }

    bubble_sort_mod(tempPopulationSorted);

    int individualLowerFitness = -1;
    
    float loweFitness = INFINITY;
    for(int i = 0; i < numberPopulation; i++){
        if(function(tempPopulationSorted[i]) < loweFitness){
            loweFitness = function(tempPopulationSorted[i]);
            individualLowerFitness = i;
        }
    }
    
    float sumFitness = 0;
    float* IndividualFitness = (float*) malloc(sizeof(float)*numberPopulation);
    for(int i = numberPopulation-1 ; i >= 0 ; i--){
        if( i == individualLowerFitness){
            continue;
        }
        IndividualFitness[i] = function(tempPopulationSorted[i]) - function(tempPopulationSorted[individualLowerFitness]);
        sumFitness += IndividualFitness[i];
        //printf("i = %d, fitness = %f\n",i,IndividualFitness[i]);
    }
    IndividualFitness[individualLowerFitness] = 0;

    int individualBiggerFitness = getIndividualBiggerFitness();
    printf("best = %d\n",individualBiggerFitness);
    int sortedNumber;
    for (int i = 0 ; i < numberPopulation ; i++){

        if(i == individualBiggerFitness){
            //individuals[i] = tempPopulationSorted[i];
            printf("%d\n",i);
            continue;
        }

        sortedNumber = ((float)rand()/(float)(RAND_MAX))*(sumFitness);

        int father = -1;
        float tempSum = 0;
        do{
            father++;
            tempSum += IndividualFitness[father];
        }while(tempSum < sortedNumber);

        sortedNumber = ((float)rand()/(float)(RAND_MAX))*(sumFitness);

        int mother = -1;
        tempSum = 0;

        do{
            mother++;
            tempSum += IndividualFitness[mother];
        }while(tempSum < sortedNumber);

        individuals[i].x = (tempPopulationSorted[father].x + tempPopulationSorted[mother].x)/2.0;

        if(rand()%2){
            individuals[i].x += TaxMutation;
        } else {
            individuals[i].x -= TaxMutation;
        }
    }

    // for(int i = 0 ; i < numberPopulation ; i++){

    //     if(i == individualBiggerFitness){
    //         tempPopulation[i] = tempPopulationSorted[individualBiggerFitness];
    //         continue;
    //     }

    //     int sortedNumber = ((float)rand()/(float)(RAND_MAX))*(1000);

    //     float proportion = 0.5;
    //     int father = 0;
    //     while(1){
    //         if(sortedNumber < 1000*(1-proportion)){
    //             break;
    //         }
    //         father += 1;
    //         proportion /= 2.0;
    //     }
        
    //     /////

    //     sortedNumber = ((float)rand()/(float)(RAND_MAX))*(1000);

    //     proportion = 0.5;
    //     int mother = 0;
    //     while(1){
    //         if(sortedNumber < 1000*(1-proportion)){
    //             break;
    //         }
    //         mother += 1;
    //         proportion /= 2.0;
    //     }
        
    //     tempPopulation[i].x = (tempPopulationSorted[father].x + tempPopulationSorted[mother].x)/2.0;

    //     if(rand()%2){
    //         tempPopulation[i].x = tempPopulation[i].x + TaxMutation;
    //     } else {
    //         tempPopulation[i].x = tempPopulation[i].x - TaxMutation;
    //     }
    // }

    // for(int i = 0 ; i < numberPopulation ; i++){
    //     individuals[i] = tempPopulation[i];
    // }

    free(tempPopulation);
    free(tempPopulationSorted);
    free(IndividualFitness);
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

    chromosome temp;
    for(int i = 0; i < 9 ; i++){
        temp = Bestindividuals[i];
        Bestindividuals[i] = Bestindividuals[i+1];
        Bestindividuals[i+1] = temp;
    }
    Bestindividuals[0] = individuals[getIndividualBiggerFitness()];

    if(modFloat(Bestindividuals[4].x - Bestindividuals[0].x) < 0.001){
        TaxMutation *= 1.2;
    } else {
        TaxMutation = defaultTaxMutation;
    }

    if(TaxMutation > 10){
        TaxMutation = defaultTaxMutation;
    }
}

void resetTaxMutation(){
    TaxMutation = defaultTaxMutation;
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