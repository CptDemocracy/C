#ifndef LIST_H
#define LIST_H
  #define LIST_INIT_CAPACITY 16

  struct List {
    int itemSize;
    int capacity;
    int count;
    void (*dispose)(void*);
    void *buffer;    
  };

  struct List *ListNew(struct List *self, int itemSize, void(*dispose)(void*));

  void ListDispose(struct List *self);

  void ListAdd(struct List *self, const void *item);

  struct List* ListEnsureCapacity(struct List *self, int minCapacityRequired);

  const void *ListGetAt(const struct List *self, int index);

  void ListSetAt(struct List *self, int index, const void *item);

  int ListGetLength(const struct List *self);

  void ListSlice(const struct List *self, int start, int end, int step, struct List *destination);

#endif/* LIST_H */
