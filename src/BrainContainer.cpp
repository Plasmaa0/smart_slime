#include "BrainContainer.h"

#include <iostream>

BrainContainer::BrainContainer(const unsigned int pGenerationSize)
    : filename("brains"),
      GenerationSize(pGenerationSize),
      brains(new Brain[GenerationSize]),
      brains_fitness(new unsigned int[GenerationSize])
{
    for(unsigned int i=0; i<GenerationSize; i++)
        brains[i].randomize();
    memset(brains_fitness, 0, sizeof(unsigned int) * GenerationSize);
}

BrainContainer::~BrainContainer() {
    delete [] brains;
    delete [] brains_fitness;
}

Brain &BrainContainer::left() const {
    return brains[CurrentGame_LeftBrainIndex];
}

Brain &BrainContainer::right() const {
    // return brains[CurrentGame_RightBrainIndex];
    return brains[CurrentGame_LeftBrainIndex];
}

void BrainContainer::setResult(const bool LeftWon) {
    // if(LeftWon)
    //     brains_fitness[CurrentGame_LeftBrainIndex] += 50 + brains[CurrentGame_LeftBrainIndex].getCountOfEval();
    // else
    //     brains_fitness[CurrentGame_RightBrainIndex] += 50 + brains[CurrentGame_RightBrainIndex].getCountOfEval();

    // if(CurrentGame_RightBrainIndex+1 == GenerationSize) {
    //     if(CurrentGame_LeftBrainIndex == GenerationSize - 2) {
    //         generateNewPopulation();
    //         CurrentGame_RightBrainIndex = 1;
    //         CurrentGame_LeftBrainIndex = 0;
    //     } else {
    //         CurrentGame_LeftBrainIndex++;
    //         CurrentGame_RightBrainIndex = CurrentGame_LeftBrainIndex + 1;
    //     }
    // } else {
    //     CurrentGame_RightBrainIndex++;
    // }
    brains_fitness[CurrentGame_LeftBrainIndex] = brains[CurrentGame_LeftBrainIndex].getCountOfEval();
    if(CurrentGame_LeftBrainIndex + 1 == GenerationSize) {
        generateNewPopulation();
        CurrentGame_LeftBrainIndex = 0;
    } else {
        CurrentGame_LeftBrainIndex++;
    }
}

void BrainContainer::generateNewPopulation() {
    // Selection
    unsigned int fitnessSum = 0;
    for(unsigned int i=0; i<GenerationSize; i++)
        fitnessSum += brains_fitness[i];
    for(unsigned int i=0; i<GenerationSize; i++)
        if(uniform(0.f, 1.f) <= (brains_fitness[i] * 1./fitnessSum)) {
            brains_fitness[i] = 0;
        }

    // Finding best brain in this generation
    unsigned int bestBrainI = 0;
    unsigned int bestBrainFitness = brains_fitness[0];
    for(unsigned int i=1; i<GenerationSize; i++) {
        // std::cout << brains_fitness[i] << " ";
        if(brains_fitness[i] >= bestBrainFitness) {
            bestBrainFitness = brains_fitness[i];
            bestBrainI = i;
        }
    }
    // Replacing all bad Brains (fitness = 0) with copies of the best brain
    for(unsigned int i=0; i<GenerationSize; i++)
        if(brains_fitness[i] == 0) {
            brains[i] = Brain(brains[bestBrainI]);
            brains[i].mutate(1./CurrentGenerationNumber);
        }
    std::cout << bestBrainFitness << std::endl;
    memset(brains_fitness, 0, sizeof(unsigned int) * GenerationSize);

    CurrentGenerationNumber++;
}
