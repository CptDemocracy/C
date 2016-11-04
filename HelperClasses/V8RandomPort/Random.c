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

#include "Random.h"

#define IS_POWER_OF_TWO(value) (((value) & ((value) - 1)) == 0)

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
