#ifndef RANDOM_UTILITIES_H
#define RANDOM_UTILITIES_H

#include <stdbool.h>
#include <stddef.h>

bool RandomBernoulli(struct RandomGenerator *generator);

void RandomShuffle(struct RandomGenerator *generator, void *items, size_t itemCount, size_t itemSize);

void *RandomChoice(struct RandomGenerator *generator, const void *items, size_t itemCount, size_t itemSize);

#endif /* RANDOM_UTILITIES_H */
