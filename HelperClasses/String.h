#ifndef STRING_H
#define STRING_H

  struct String {
    struct List *chars;  
  };

  struct String *StringNew(struct String *self, const char *source);

  void StringDispose(struct String *self);

  void StringAdd(struct String *self, const struct String *other);

  char StringGetAt(const struct String *self, int index);

  int StringGetLength(const struct String *self);

#endif /* STRING_H */
