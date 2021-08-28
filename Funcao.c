#include<stdlib.h>
#include<stdio.h>
#include <time.h>
#include <math.h>

#define Population 10
#define TaxOfMutation 5
#define Geration 20

float F(float x){
    int res = 0;
    /*
    if(x < 500){
        res = x;
    } else if(x < 1000){
        res = 1000-x;
    } else if(x < 2000){
        res = x-1000;
    } else {
        res = 3000-x;
    }
    */
    res = (2*cos(0.039*x) + 5*sin(0.05*x) + 0.5*cos(0.01*x) + 10*sin(0.07*x) + 5*sin(0.1*x) + 5*sin(0.035*x))*10+500;
    return res;
}

float mod(float x){
    return (x < 0)?-x:x;
}
int main(){
    /*
    for(int l = 0; l < 3000; l++){
        printf("%d,%f\n",l,F(l));
    }
    */
    
    int mutacao = TaxOfMutation; 
    srand(time(NULL));
    // Inicialization
    
    float ind[Population];
    for(int i = 0; i < Population; i++){
        ind[i] = rand() % 100;
        //ind[i] = 3000 - rand() % 100;
    }
    
    float max = -1;
    float fitAnt = -1;
    int count = 0;
    for(int g = 0; g < 1000; g++){
        
        // Avaliation

        float fit[Population];

        for(int i = 0; i < Population; i++){
            fit[i] = F(ind[i]);
        }

        // Selection

        max = fit[0];
        int maxInd = 0;

        for(int i = 1; i < Population; i++){
            if(fit[i] > max){
                max = fit[i];
                maxInd = i;
            }
            
        }

        // Crossover

        float newPopulation[Population];
        for(int i = 0; i < Population; i++){
            if(i == maxInd){
                newPopulation[i] = ind[maxInd];
                continue;
            }
            newPopulation[i] = (ind[i] + ind[maxInd]) / 2.0;
        }

        // Mutation

        for(int i = 0; i < Population; i++){
            if(i == maxInd) continue;
            if (rand()%2 == 1){
                //newPopulation[i] = newPopulation[i] + newPopulation[i]*TaxOfMutation/100;
                newPopulation[i] = newPopulation[i] + mutacao;
            } else {
                //newPopulation[i] = newPopulation[i] - newPopulation[i]*TaxOfMutation/100;
                newPopulation[i] = newPopulation[i] - mutacao;
            }
            
        }

        // Rearranjo da população

        float media = 0;
        for(int i = 0; i < Population; i++){
            ind[i] = newPopulation[i];
            media += F(ind[i]);
        }
        media = media/Population;
        //printf("Geracao = %d Melhor Ind = %f Media da geracao = %f\n",g,max,media);
        printf("%d,%f,%f\n",g,max,media);

        
        if(mod(max - fitAnt) < 0.00000001){
            if(count == 10){
                mutacao *= 2;
                count = 0;
            }
            count++;
        } else {
            mutacao = TaxOfMutation;
            count = 0;
        }
        fitAnt = max;
    }
    
    
}