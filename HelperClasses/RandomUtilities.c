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

void RandomGenerateString(struct RandomGenerator *generator, char *buffer, size_t stringLength, const char *charsSelection) {
  const size_t charsSelectionLength = strlen(charsSelection);
  for (size_t index = 0; index < stringLength; ++index) {
    const char selectedChar = *(char*)RandomChoice(generator, charsSelection, charsSelectionLength, sizeof(char));
    buffer[index] = selectedChar;
  }
  buffer[stringLength] = '\0';
}

int RandomGetInt(struct RandomGenerator *generator, int minValue, int maxValue) {
  return minValue + RandomGeneratorNextInt(generator, 1 + maxValue - minValue);
}
