#include "Utilities.h"

int bernoulli(void) {
  const int OPTIONS[] = { 0, 1 };
  return *(int*)makeRandomChoice(OPTIONS, sizeof(OPTIONS[0]), sizeof(OPTIONS) / sizeof(OPTIONS[0]));
}

void* shuffle(void *items, size_t itemSize, size_t itemCount) {
  char *buffer = (char*)malloc(itemSize);
  if (buffer) {
    for (size_t index = 0; index < itemCount; ++index) {
      size_t randomIndex = getRandomSizeTypeInteger(0, index + 1);
      void *source = (char*)items + index * itemSize;
      void *destination = (char*)items + randomIndex * itemSize;
      (void)memcpy(buffer, source, itemSize);
      (void)memcpy(source, destination, itemSize);
      (void)memcpy(destination, buffer, itemSize);
    }
    free(buffer);
    return items;
  }
  return NULL;
}

int arrayEquals(const void **lhsArray, size_t lhsArrayLength,
                const void **rhsArray, size_t rhsArrayLength,
                size_t itemSize, int(*comparisonFunction)(const void*, const void*))
{
  if (lhsArrayLength == rhsArrayLength) {
    size_t length = lhsArrayLength;
    for (size_t index = 0; index < length; ++index) {
      const void **lhsItem = (void**)((char*)lhsArray + index * itemSize);
      const void **rhsItem = (void**)((char*)rhsArray + index * itemSize);
      if (comparisonFunction(*lhsItem, *rhsItem) != 0) {
        return 0;
      }
    }
    return 1;
  }
  return 0;
}

size_t getRandomSizeTypeInteger(size_t lowerBoundInclusive, size_t upperBoundExclusive) {
  return (size_t)rand() % (upperBoundExclusive - lowerBoundInclusive) + lowerBoundInclusive;
}

int getRandomInteger(int lowerBoundInclusive, int upperBoundExclusive) {
  return rand() % (upperBoundExclusive - lowerBoundInclusive) + lowerBoundInclusive;
}

void* makeRandomChoice(const void *items, size_t itemSize, size_t itemCount) {
  size_t index = getRandomSizeTypeInteger(0, itemCount);
  return (void*)((char*)items + index * itemSize);
}

char* generateRandomString(char buffer[], size_t bufferLength, const char *charsSelection) {
  size_t charsSelectionLength = strlen(charsSelection);
  size_t index = 0;
  while (index < bufferLength - 1) {
    char selectedChar = *((char*)makeRandomChoice(charsSelection, sizeof(char), charsSelectionLength));
    buffer[index] = selectedChar;
    ++index;
  }
  buffer[index] = '\0';
  return buffer;
}
