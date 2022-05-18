#pragma once

#include <cstdlib>
#include <cstring>
#include <ctime>

#include "Utils.h"

class Brain
{
   private:
	float dna[51];

   public:
	Brain();
	Brain(const Brain &from);
	void randomize();

	/* brain(...) returns
	 * 0 - not doing anything
	 * 1 - move left
	 * 2 - move right
	 * 3 - jump
	 */
	unsigned int operator()(float Px, float Py, float Pvx, float Pvy, float Bx,
	                        float By, float Bvx, float Bvy) const;

	// static Brain crossingover(const Brain &A, const Brain &B);
	void mutate(const float alpha);
};
