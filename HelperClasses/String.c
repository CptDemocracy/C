#include <stdlib.h>
#include <string.h>

#include "String.h"
#include "List.h"

struct String *StringNew(struct String *self, const char *source) {
  if (self) {
    self->chars = (struct List*)malloc(sizeof(struct List));
    if (self->chars && ListNew(self->chars, sizeof(char), NULL)) {
      for (const char *pchar = source; *pchar; ++pchar) {
        ListAdd(self->chars, pchar);
      }
      return self;
    }
  }
  return NULL;
}

void StringDispose(struct String *self) {
  ListDispose(self->chars);
  free(self->chars);
}

void StringAdd(struct String *self, const struct String *other) {
  for (int index = 0; index < StringGetLength(other); ++index) {
	const char character = StringGetAt(other, index);
	ListAdd(self->chars, &character);
  }
}

char StringGetAt(const struct String *self, int index) {
  if (self && index >= 0 && index < StringGetLength(self)) {
	return *(char*)ListGetAt(self->chars, index);
  }
  return '\0';
}

int StringGetLength(const struct String *self) {
  return ListGetLength(self->chars);
}

void StringSlice(const struct String *self, int start, int end, int step, struct String *destination) {
  ListSlice(self->chars, start, end, step, destination->chars);
}
