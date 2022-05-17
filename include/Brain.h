#pragma once

#include <cstdlib>
#include <cstring>
#include <ctime>

#include "Utils.h"

class Brain
{
   private:
	float dna[46];

   public:
	Brain();
	Brain(const Brain &from);
	void randomize();
	bool operator()(float Px, float Py, float Pvx, float Pvy, float Bx,
	                float By, float Bvx, float Bvy) const;
	// static Brain crossingover(const Brain &A, const Brain &B);
	void mutate(const float alpha);
};
