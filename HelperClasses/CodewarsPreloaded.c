/*
 * PLEASE NOTICE!
 * I am not the author of the majority of this random generator code. 
 * The original code can be found at:
 * https://github.com/v8/v8/blob/085fed0fb5c3b0136827b5d7c190b4bd1c23a23e/src/base/utils/
 *
 * https://github.com/v8/v8/blob/085fed0fb5c3b0136827b5d7c190b4bd1c23a23e/src/base/utils/random-number-generator.h
 *
 * https://github.com/v8/v8/blob/085fed0fb5c3b0136827b5d7c190b4bd1c23a23e/src/base/utils/random-number-generator.cc
 *
 * I have simply adapted some of the code for my own use in C.
 *
 * In accordance with the license agreement, I'm providing the original copyright
 * notices. You can view them at the following addresses:
 *
 * https://github.com/v8/v8/blob/085fed0fb5c3b0136827b5d7c190b4bd1c23a23e/LICENSE
 *
 * https://github.com/v8/v8/blob/085fed0fb5c3b0136827b5d7c190b4bd1c23a23e/LICENSE.v8
 *
 * P.S. I did write some of the functions myself, but they are mostly built atop
 * the V8 ones and I don't deem necessary to list them. Eitherway, please include 
 * the copyright notice above, if you want to use it in your code. Thanks!
 *
 * If you find any bugs in the code, please message me here on Codewars, or create
 * a pull request on GitHub: 
 * https://github.com/CptDemocracy/C/tree/master/HelperClasses
 * The files you might be looking for are:
 * - RandomUtilities.h
 * - RandomUtilities.c
 * - V8RandomPort/RandomGenerator.h
 * - V8RandomPort/RandomGenerator.c
 *
 * Happy coding!
 */

#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

#define VerifySizesAreEqual(lhs, rhs) (sizeof(lhs) == sizeof(rhs))

#define IS_POWER_OF_TWO(value) (((value) & ((value) - 1)) == 0)

struct RandomGenerator {
  int64_t initial_seed_;
  uint64_t state0_;
  uint64_t state1_;
};

struct RandomGenerator *RandomGeneratorNew(struct RandomGenerator *self, int64_t seed);

void RandomGeneratorDispose(struct RandomGenerator *self);

// See: https://github.com/v8/v8/blob/085fed0fb5c3b0136827b5d7c190b4bd1c23a23e/src/base/utils/random-number-generator.cc#L105
int64_t RandomGeneratorNextInt64(struct RandomGenerator *self);

// See: https://github.com/v8/v8/blob/085fed0fb5c3b0136827b5d7c190b4bd1c23a23e/src/base/utils/random-number-generator.cc#L111
void RandomGeneratorNextBytes(struct RandomGenerator *self, void* buffer, size_t buflen);

// See: https://github.com/v8/v8/blob/085fed0fb5c3b0136827b5d7c190b4bd1c23a23e/src/base/utils/random-number-generator.cc#L99
double RandomGeneratorNextDouble(struct RandomGenerator *self);

// See: https://github.com/v8/v8/blob/085fed0fb5c3b0136827b5d7c190b4bd1c23a23e/src/base/utils/random-number-generator.cc#L81
int RandomGeneratorNextInt(struct RandomGenerator *self, int max);

// See: https://github.com/v8/v8/blob/085fed0fb5c3b0136827b5d7c190b4bd1c23a23e/src/base/utils/random-number-generator.cc#L118
int RandomGeneratorNext(struct RandomGenerator *self, int bits);

// See: https://github.com/v8/v8/blob/085fed0fb5c3b0136827b5d7c190b4bd1c23a23e/src/base/utils/random-number-generator.h#L101
static inline void XorShift128(uint64_t* state0, uint64_t* state1) {
  uint64_t s1 = *state0;
  uint64_t s0 = *state1;
  *state0 = s0;
  s1 ^= s1 << 23;
  s1 ^= s1 >> 17;
  s1 ^= s0;
  s1 ^= s0 >> 26;
  *state1 = s1;
}

// See: https://github.com/v8/v8/blob/085fed0fb5c3b0136827b5d7c190b4bd1c23a23e/src/base/utils/random-number-generator.h#L92
static inline double ToDouble(uint64_t state0, uint64_t state1) {
  // Exponent for double values for [1.0 .. 2.0)
  static const uint64_t kExponentBits = (uint64_t)0x3FF0000000000000;
  static const uint64_t kMantissaMask = (uint64_t)0x000FFFFFFFFFFFFF;
  uint64_t random = ((state0 + state1) & kMantissaMask) | kExponentBits;
	
  /*
   * For more information on bit casting, see:
   * https://github.com/v8/v8/blob/085fed0fb5c3b0136827b5d7c190b4bd1c23a23e/src/base/macros.h#L165
   * with a query for "bit_cast".
   */
  double destination;
  assert(VerifySizesAreEqual(destination, random));
  (void)memcpy(&destination, &random, sizeof(destination));
  return destination - 1;
}

// See: https://github.com/v8/v8/blob/085fed0fb5c3b0136827b5d7c190b4bd1c23a23e/src/base/utils/random-number-generator.cc#L133
static inline uint64_t MurmurHash3(uint64_t h) {
  h ^= h >> 33;
  h *= (uint64_t)0xFF51AFD7ED558CCD;
  h ^= h >> 33;
  h *= (uint64_t)0xC4CEB9FE1A85EC53;
  h ^= h >> 33;
  return h;
}

static inline void RandomGeneratorSetSeed(struct RandomGenerator *self, int64_t seed) {
  self->initial_seed_ = seed;

  /*
   * For more information on bit casting, see:
   * https://github.com/v8/v8/blob/085fed0fb5c3b0136827b5d7c190b4bd1c23a23e/src/base/macros.h#L165
   * with a query for "bit_cast".
   */
  uint64_t destination;
  assert(VerifySizesAreEqual(destination, seed));
  (void)memcpy(&destination, &seed, sizeof(destination));

  self->state0_ = MurmurHash3(destination);
  self->state1_ = MurmurHash3(self->state0_);
}

struct RandomGenerator *RandomGeneratorNew(struct RandomGenerator *self, int64_t seed) { 
  /* 
   * self->initial_seed_, self->state0_, self->state1_
   * will be set by RandomSetSeed.
   */
  RandomGeneratorSetSeed(self, seed);
  return self;
}

void RandomGeneratorDispose(struct RandomGenerator *self) {
  // Not much to do here...
}

int64_t RandomGeneratorNextInt64(struct RandomGenerator *self) {
  XorShift128(&self->state0_, &self->state1_);
  return (int64_t)(self->state0_ + self->state1_);
}

void RandomGeneratorNextBytes(struct RandomGenerator *self, void* buffer, size_t buflen) {
  for (size_t n = 0; n < buflen; ++n) {
    ((uint8_t*)(buffer))[n] = (uint8_t)(RandomGeneratorNext(self, 8));
  }
}

double RandomGeneratorNextDouble(struct RandomGenerator *self) {
  XorShift128(&self->state0_, &self->state1_);
  return ToDouble(self->state0_, self->state1_);
}

int RandomGeneratorNextInt(struct RandomGenerator *self, int max) {
  assert(max > 0);

  // Fast path if max is a power of 2.
  if (IS_POWER_OF_TWO(max)) {
    return (int)((max * (int64_t)(RandomGeneratorNext(self, 31))) >> 31);
  }

  while (true) {
    int rnd = RandomGeneratorNext(self, 31);
    int val = rnd % max;
    if (rnd - val + (max - 1) >= 0) {
      return val;
    }
  }
}

int RandomGeneratorNext(struct RandomGenerator *self, int bits) {
  assert(bits > 0);
  assert(bits <= 32);
  XorShift128(&self->state0_, &self->state1_);
  return (int)((self->state0_ + self->state1_) >> (64 - bits));
}

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
