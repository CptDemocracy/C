#ifndef MRY_MNGR_H
#define MRY_MNGR_H

#include <stdlib.h>
#include <string.h>

typedef struct mry_mngr {
    void **addr_lookup;
    size_t alloc_count;
    size_t lookup_capacity;
} mry_mngr_t;

mry_mngr_t *mry_init(mry_mngr_t *mngr);

mry_mngr_t *mry_reg_block(mry_mngr_t *mngr, void *block);

void *mry_alloc(mry_mngr_t *mngr, size_t size);

void *mry_calloc(mry_mngr_t *mngr, size_t count, size_t isize);

void *mry_realloc(mry_mngr_t *mngr, void *block, size_t new_size);

void mry_free(mry_mngr_t *mngr, void *block);

void mry_unreg_block(mry_mngr_t *mngr, void *block);

void mry_dispose(mry_mngr_t *mngr);

#endif /* MRY_MNGR_H */
