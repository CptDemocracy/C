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

double RandomGeneratorNextDouble(struct RandomGenerator *self) {
  XorShift128(&self->state0_, &self->state1_);
  return ToDouble(self->state0_, self->state1_);
}
