#include "Brain.h"

Brain::Brain() {}
Brain::Brain(const Brain &from)
{
	memcpy(dna, from.dna, sizeof(float) * 51);
}

void Brain::randomize()
{
	// TODO using std::normal_distribution
	for (unsigned int i = 0; i < 51; i++) dna[i] = uniform(-1.f, 1.f);
}

unsigned int Brain::operator()(float Px, float Py, float Pvx, float Pvy, float Bx,
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
	float result[3]{dna[48], dna[49], dna[50]};
	for (unsigned int i = 0; i < 4; i++) {
		result[0] += dna[36 + i] * a[i];
		result[1] += dna[40 + i] * a[i];
		result[2] += dna[44 + i] * a[i];
	}
	result[0] = sigmoid(result[0]);
	result[1] = sigmoid(result[1]);
	result[2] = sigmoid(result[2]);
	if (result[0] >= result[1] and result[0] >= result[2] and result[0] > 0.5)
		return 1;
	if (result[1] >= result[0] and result[1] >= result[2] and result[1] > 0.5)
		return 2;
	if (result[2] >= result[0] and result[2] >= result[1] and result[2] > 0.5)
		return 3;

    countOfEval++;
	return 0;
}

// static Brain crossingover(const Brain &A, const Brain &B);

void Brain::mutate(const float alpha)
{
	// TODO: USE normal_distribution much better!!!
	// this implementation made just for testing
	// if (uniform(0, 1) > alpha) {
	// 	int r1 = uniformInt(0, 50);
	// 	dna[r1] += uniform(-0.5f, 0.5f);
	// }
    for(unsigned int i=0; i<51; i++)
    	dna[i] += uniform(-alpha, alpha);
}

unsigned int Brain::getCountOfEval() const {
    return countOfEval;
}
