#include <string.h>
#include <assert.h>

#define ARRAY_SIZE(arr) sizeof(arr)/sizeof(arr[0])

#define PRINT_ARRAY(file, array, arraySize, valueFormatSpecifier)  \
do {                                                               \
  for (size_t index = 0; index < (arraySize); ++index) {           \
    (void)fprintf((file), (valueFormatSpecifier), (array)[index]); \
  }                                                                \
} while (0)

#define PRINT_ARRAY_PRINT_FUNCTION(stream, array, arraySize, valuePrintFunction)  \
do {                                                                              \
  for (size_t index = 0; index < (arraySize); ++index) {                          \
    (void)(valuePrintFunction)((stream), &(array)[index]);                        \
  }                                                                               \
} while (0)

// NOTE TO SELF:
// I noticed most of macro parameters are not parenthesized which is 
// a huge deal. I'm going to fix it ASAP. For now, use caution.

/*#define ASSERT_ARRAY_EQUALS(lhs, rhs)              \
do {                                                 \
  size_t lhsSize = ARRAY_SIZE(lhs);                  \
  size_t rhsSize = ARRAY_SIZE(rhs);                  \
  assert(lhsSize == rhsSize);                        \
  for (size_t index = 0; index < lhsSize; ++index) { \
    assert((lhs)[index] == (rhs)[index]);            \
  }                                                  \
} while (0)*/

#define ASSERT_ARRAY_EQUALS(lhs, lhsSize, rhs, rhsSize)            \
do {                                                               \
  int areEqual = 1;                                                \
  if (lhsSize == rhsSize) {                                        \
    for (size_t index = 0; index < lhsSize && areEqual; ++index) { \
      if (&(lhs)[index] != &(rhs)[index]) {                        \
        areEqual = 0;                                              \
      }                                                            \
    }                                                              \
  } else {                                                         \
    areEqual = 0;                                                  \
  }                                                                \
  assert(areEqual);                                                \
} while (0)

#define ASSERT_ARRAY_EQUALS_COMPARE_FN(lhs, rhs, cmp)\
do {                                                 \
  size_t lhsSize = ARRAY_SIZE(lhs);                  \
  size_t rhsSize = ARRAY_SIZE(rhs);                  \
  assert(lhsSize == rhsSize);                        \
  for (size_t index = 0; index < lhsSize; ++index) { \
    assert(!cmp(&(lhs)[index], &(rhs)[index]));      \
  }                                                  \
} while (0)

/*#define ASSERT_DYNAMIC_ARRAY_EQUALS(lhs, lhsSize, rhs, rhsSize)   \
 do {                                                             \
  assert((lhs) && (rhs) || !(lhs) && !(rhs));                     \
  if ((lhs) && (rhs)) {                                           \
    assert(lhsSize == rhsSize);                                   \
    assert(sizeof((lhs)[0]) == sizeof((rhs)[0]));                 \
    size_t itemSize = sizeof((lhs)[0]);                           \
    for (size_t index = 0; index < lhsSize; ++index) {            \
      const void **leftItem = (char*)(lhs) + index * itemSize;    \
      const void **rightItem = (char*)(rhs) + index * itemSize;   \
      assert(!memcmp(leftItem, rightItem, itemSize));             \
      }                                                           \
  }                                                               \
 } while (0)*/

#define ASSERT_DYNAMIC_ARRAY_EQUALS(lhs, lhsSize, rhs, rhsSize)                 \
 do {                                                                           \
  int areEqual = (lhs) && (rhs) || !(lhs) && !(rhs);                            \
  if ((lhs) && (rhs)) {                                                         \
    areEqual = lhsSize == rhsSize && sizeof((lhs)[0]) == sizeof((rhs)[0]);      \
    if (areEqual) {                                                             \
      size_t itemSize = sizeof((lhs)[0]);                                       \
      for (size_t index = 0; index < lhsSize && areEqual; ++index) {            \
        const void **leftItem = (char*)(lhs) + index * itemSize;                \
        const void **rightItem = (char*)(rhs) + index * itemSize;               \
        if (memcmp(leftItem, rightItem, itemSize) != 0) {                       \
          areEqual = 0;                                                         \
        }                                                                       \
      }                                                                         \
    }                                                                           \
  }                                                                             \
  assert(areEqual);                                                          \
 } while (0)

/*#define ASSERT_DYNAMIC_ARRAY_EQUALS_COMPARE_FN(lhs, lhsSize, rhs, rhsSize, cmp)  \
 do {                                                                            \
  assert((lhs) && (rhs) || !(lhs) && !(rhs));                                    \
  if ((lhs) && (rhs)) {                                                          \
    assert(lhsSize == rhsSize);                                                  \
    assert(sizeof(lhs[0]) == sizeof((rhs)[0]));                                  \
    size_t itemSize = sizeof((lhs)[0]);                                          \
    for (size_t index = 0; index < lhsSize; ++index) {                           \
      const void **leftItem = (char*)(lhs) + index * itemSize;                   \
      const void **rightItem = (char*)(rhs) + index * itemSize;                  \
      assert(!cmp(*leftItem, *rightItem));                                       \
    }                                                                            \
  }                                                                              \
 } while (0)*/

#define ASSERT_DYNAMIC_ARRAY_EQUALS_COMPARE_FN(lhs, lhsSize, rhs, rhsSize, cmp) \
 do {                                                                           \
  int areEqual = (lhs) && (rhs) || !(lhs) && !(rhs);                            \
  if ((lhs) && (rhs)) {                                                         \
    areEqual = lhsSize == rhsSize && sizeof((lhs)[0]) == sizeof((rhs)[0]);      \
    if (areEqual) {                                                             \
      size_t itemSize = sizeof((lhs)[0]);                                       \
      for (size_t index = 0; index < lhsSize && areEqual; ++index) {            \
        const void **leftItem = (char*)(lhs) + index * itemSize;                \
        const void **rightItem = (char*)(rhs) + index * itemSize;               \
        if (cmp(*leftItem, *rightItem) != 0) {                                  \
          areEqual = 0;                                                         \
        }                                                                       \
      }                                                                         \
    }                                                                           \
  }                                                                             \
  assert(areEqual);                                                             \
 } while (0)
