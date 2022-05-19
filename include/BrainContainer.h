#pragma once

#include <string>
#include <fstream>

#include "Brain.h"

class BrainContainer
{
   private:
	// Every generation will be saved in file named
	// <filename><CurrentGenerationNumber>.generation
	std::string filename;

	unsigned int GenerationSize;
	unsigned int CurrentGenerationNumber = 1;

	// Arrays with size of GenerationSize
	Brain *brains;
	unsigned int *brains_fitness;

    unsigned int CurrentGame_LeftBrainIndex = 0;
    unsigned int CurrentGame_RightBrainIndex = 1;

   public:
    BrainContainer(const unsigned int pGenerationSize = 100);
    ~BrainContainer();
	Brain &left() const;
    Brain &right() const;
    void setResult(const bool LeftWon);
	void save() const;
    void generateNewPopulation();
};
