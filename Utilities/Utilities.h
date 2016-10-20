#ifndef UTILITIES_H
#define UTILITIES_H

  int bernoulli(void);

  void* shuffle(void *items, size_t itemSize, size_t itemCount);

  int arrayEquals(const void **lhsArray, size_t lhsArrayLength,
                  const void **rhsArray, size_t rhsArrayLength,
                  size_t itemSize, int(*comparisonFunction)(const void*, const void*));

  size_t getRandomSizeTypeInteger(size_t lowerBoundInclusive, size_t upperBoundExclusive);

  int getRandomInteger(int lowerBoundInclusive, int upperBoundExclusive);

  void* makeRandomChoice(const void *items, size_t itemSize, size_t itemCount);

  char* generateRandomString(char buffer[], size_t bufferLength, const char *charsSelection);

#endif /* UTILITIES_H */
