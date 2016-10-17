#include <stdlib.h>
#include <string.h>
#include "List.h"

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
  if (self && self->dispose) {
    for (int index = 0; index < self->count; ++index) {
      self->dispose((char*)self->buffer + index * self->itemSize);
    }
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
    if (self->count < minCapacityRequired) {
      int newCapacity = self->count * 2 > minCapacityRequired ? self->count * 2 : minCapacityRequired;
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

const void *ListGetAt(struct List *self, int index) {
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

int ListGetLength(struct List *self) {
  return self ? self->count : 0;
}
