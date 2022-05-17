#include "Brain.h"

Brain::Brain() {}
Brain::Brain(const Brain &from)
{
	memcpy(dna, from.dna, sizeof(float) * 46);
}

void Brain::randomize()
{
	// TODO using std::normal_distribution instead of rand()
	for (unsigned int i = 0; i < 46; i++) dna[i] = (rand() % 100 - 50) / 50.;
}

bool Brain::operator()(float Px, float Py, float Pvx, float Pvy, float Bx,
                       float By, float Bvx, float Bvy) const
{
	float a[4];
	for (unsigned int i = 0; i < 4; i++) {
		a[i] = Px * dna[i * 8 + 0] + Py * dna[i * 8 + 1] +
		       Pvx * dna[i * 8 + 2] + Pvy * dna[i * 8 + 3] +
		       Bx * dna[i * 8 + 4] + By * dna[i * 8 + 5] +
		       Bvx * dna[i * 8 + 6] + Bvy * dna[i * 8 + 7] + dna[32 + i];
		a[i] = sigmoid(a[i]);
	}
	float result[2]{dna[40], dna[41]};
	for (unsigned int i = 0; i < 4; i++) {
		result[0] += dna[32 + i] * a[i];
		result[1] += dna[36 + i] * a[i];
	}
	return result[1] >= result[0];
}

// static Brain crossingover(const Brain &A, const Brain &B);

void Brain::mutate(const float alpha)
{
	// TODO: USE normal_distribution much better!!!
	// this implementation made just for testing
	if (rand() % 100 > (alpha * 100)) {
		int r1 = rand() % 46;
		dna[r1] += (rand() % 100 - 50) / 100.;
	}
}
