#include <stdlib.h>
#include <string.h>
#include "List.h"

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

struct List *ListNew(struct List *self, int itemSize, void(*dispose)(void*)) {
  if (self) {
    self->itemSize = itemSize;
    self->capacity = LIST_INIT_CAPACITY;
    self->count = 0;
    self->dispose = dispose;
    self->buffer = calloc(self->capacity, self->itemSize);
    return self->buffer ? self : NULL;
  }
  return NULL;
}

void ListDispose(struct List *self) {
  if (self) {
    if (self->dispose) {
      for (int index = 0; index < self->count; ++index) {
        self->dispose((char*)self->buffer + index * self->itemSize);
      }
    }
    free(self->buffer);
  }
}

void ListAdd(struct List *self, const void *item) {
  if (self && item) {
    (void)ListEnsureCapacity(self, self->count + 1);
    (void)memcpy((char*)self->buffer + self->count * self->itemSize, item, self->itemSize);
    ++self->count;
  }
}

struct List* ListEnsureCapacity(struct List *self, int minCapacityRequired) {
  if (self) {
    if (self->capacity < minCapacityRequired) {
      int newCapacity = self->count * 2 > minCapacityRequired ? self->capacity * 2 : minCapacityRequired;
      void *newBuffer = calloc(newCapacity, self->itemSize);
      if (newBuffer && memcpy(newBuffer, self->buffer, self->count * self->itemSize)) {
        self->capacity = newCapacity;
        free(self->buffer);
        self->buffer = newBuffer;        
      } else {
        return NULL;
      }
    }
    return self;
  }
  return NULL;
}

const void *ListGetAt(const struct List *self, int index) {
  if (self && index >= 0 && index < self->count) {
    return (char*)self->buffer + index * self->itemSize;
  }
  return NULL;
}

void ListSetAt(struct List *self, int index, const void *item) {
  if (self && index >= 0 && index < self->count && item) {
    (void)memcpy((char*)self->buffer + index * self->itemSize, item, self->itemSize);
  }
}

int ListGetLength(const struct List *self) {
  return self ? self->count : 0;
}

void ListSlice(const struct List *self, int start, int end, int step, struct List *destination) {
  const int sliceStep = step != 0 ? step : 1;
  if (sliceStep > 0) {
    const int sliceStart = MIN(self->count, MAX(0, start));
    const int sliceEnd = MIN(self->count, MAX(0, end));
    for (int index = sliceStart; index < sliceEnd; index += sliceStep) {
      ListAdd(destination, ListGetAt(self, index));
    }
  } else {
    const int sliceStart = MIN(self->count, MAX(0, start));
    const int sliceEnd = MIN(self->count, MAX(-1, end));
    for (int index = sliceStart; index > sliceEnd; index += sliceStep) {
      ListAdd(destination, ListGetAt(self, index));
    }
  }
}
