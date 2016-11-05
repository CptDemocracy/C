#include <stdlib.h>

#include "RandomGenerator.h"
#include "RandomUtilities.h"

bool RandomBernoulli(struct RandomGenerator *generator) {
  return RandomGeneratorNextInt(generator, 2);
}

void RandomShuffle(struct RandomGenerator *generator, void *items, size_t itemCount, size_t itemSize) {
  char *buffer = (char*)malloc(itemSize);
  if (buffer) {
    for (size_t index = 0; index < itemCount; ++index) {
      const size_t randomIndex = RandomGeneratorNextInt(generator, index + 1);
      void *source = (char*)items + index * itemSize;
      void *destination = (char*)items + randomIndex * itemSize;
      (void)memcpy(buffer, source, itemSize);
      (void)memcpy(source, destination, itemSize);
      (void)memcpy(destination, buffer, itemSize);
    }
    free(buffer);
  }
}

void *RandomChoice(struct RandomGenerator *generator, const void *items, size_t itemCount, size_t itemSize) {
  const size_t index = RandomGeneratorNextInt(generator, itemCount);
  return (void*)((char*)items + index * itemSize);
}
