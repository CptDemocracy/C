#include <assert.h>

#define ARRAY_SIZE(arr) sizeof(arr)/sizeof(arr[0])

#define ASSERT_ARRAY_EQUALS(lhs, rhs)                \
do {                                                 \
  size_t lhsSize = ARRAY_SIZE(lhs);                  \
  size_t rhsSize = ARRAY_SIZE(rhs);                  \
  assert(lhsSize == rhsSize);                        \
  for (size_t index = 0; index < lhsSize; ++index) { \
    assert(lhs[index] == rhs[index]);                \
  }                                                  \
} while (0)
