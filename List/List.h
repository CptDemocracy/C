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

  const void *ListGetAt(struct List *self, int index);

#endif/* LIST_H */
