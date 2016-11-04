#ifndef RANDOM_H
#define RANDOM_H

/*
 * PLEASE NOTICE!
 * I am not the author of the code. The original code can be found at:
 * https://github.com/v8/v8/blob/085fed0fb5c3b0136827b5d7c190b4bd1c23a23e/src/base/utils/
 *
 * https://github.com/v8/v8/blob/085fed0fb5c3b0136827b5d7c190b4bd1c23a23e/src/base/utils/random-number-generator.h
 *
 * https://github.com/v8/v8/blob/085fed0fb5c3b0136827b5d7c190b4bd1c23a23e/src/base/utils/random-number-generator.cc
 *
 * I have simply adapted some of the code for my own use in C.
 */

#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#define VerifySizesAreEqual(lhs, rhs) (sizeof(lhs) == sizeof(rhs))

struct RandomGenerator {
  int64_t initial_seed_;
  uint64_t state0_;
  uint64_t state1_;
};

struct RandomGenerator *RandomGeneratorNew(struct RandomGenerator *self, int64_t seed);

void RandomGeneratorDispose(struct RandomGenerator *self);

double RandomGeneratorNextDouble(struct RandomGenerator *self);

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

#endif /* RANDOM_H */
