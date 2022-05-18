#include "BrainContainer.h"

BrainContainer::BrainContainer(const unsigned int pGenerationSize)
    : filename("brains"),
      GenerationSize(pGenerationSize),
      brains(new Brain[GenerationSize]),
      brains_fitness(new int[GenerationSize])
{
    for(unsigned int i=0; i<GenerationSize; i++)
        brains[i].randomize();
    memset(brains_fitness, 0, sizeof(int) * GenerationSize);
}

Brain &BrainContainer::left() const {
    return brains[CurrentGame_LeftBrainIndex];
}

Brain &BrainContainer::right() const {
    return brains[CurrentGame_RightBrainIndex];
}

void BrainContainer::setResult(const bool LeftWon) {
    if(LeftWon)
        brains_fitness[CurrentGame_LeftBrainIndex]++;
    else
        brains_fitness[CurrentGame_RightBrainIndex]++;
    if(CurrentGame_RightBrainIndex+1 == GenerationSize) {
        if(CurrentGame_LeftBrainIndex+1 == GenerationSize) {
            // generateNewPopulation();
        } else {
            CurrentGame_LeftBrainIndex++;
            CurrentGame_RightBrainIndex = 0;
        }
    } else {
        CurrentGame_RightBrainIndex++;
    }
}
