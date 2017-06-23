#include "mry_mngr.h"

#include <stdlib.h>
#include <string.h>

static mry_mngr_t *mry_ensure_lookup_capacity(
  mry_mngr_t *mngr, size_t new_size
);

mry_mngr_t *mry_init(mry_mngr_t *mngr)
{
    if (!mngr) return NULL;

    static const size_t INIT_CAPACITY = 16;

    void *const buffer = calloc(INIT_CAPACITY, sizeof(*mngr->addr_lookup));

    if (!buffer) return NULL;

    mngr->addr_lookup     = buffer;
    mngr->alloc_count     = 0;
    mngr->lookup_capacity = INIT_CAPACITY;

    return mngr;
}

static mry_mngr_t *mry_ensure_lookup_capacity(
  mry_mngr_t *mngr, size_t new_size
)
{
    if (!mngr) return NULL;

    if (new_size > mngr->lookup_capacity)
    {
        const size_t real_new_capacity = (2 * mngr->alloc_count > new_size ?
                                          2 * mngr->alloc_count : new_size );

        const size_t real_new_size = real_new_capacity * sizeof(void*);
        void       **new_buffer    = realloc(mngr->addr_lookup, real_new_size);

        if (!new_buffer) return NULL;

        mngr->addr_lookup     = new_buffer;
        mngr->lookup_capacity = real_new_capacity;
    }

    return mngr;
}

mry_mngr_t *mry_reg_block(mry_mngr_t *mngr, void *block)
{
    if (!mngr)  return NULL;
    if (!block) return NULL;

    if (mry_ensure_lookup_capacity(mngr, mngr->alloc_count + 1)) {
        mngr->addr_lookup[mngr->alloc_count] = block;
        ++mngr->alloc_count;
    } else {
        free(block); block = NULL;
        return NULL;
    }

    return mngr;
}

void *mry_alloc(mry_mngr_t *mngr, size_t size)
{
    if (!mngr) return NULL;

    void *block = malloc(size);

    if (block) {
      if (!mry_reg_block(mngr, block)) return NULL;
    }

    return block;
}

void *mry_calloc(mry_mngr_t *mngr, size_t count, size_t isize)
{
    if (!mngr) return NULL;

    void *block = calloc(count, isize);

    if (block) {
      if (!mry_reg_block(mngr, block)) return NULL;
    }

    return block;
}

void *mry_realloc(mry_mngr_t *mngr, void *block, size_t new_size)
{
    if (!mngr) return NULL;

    void *rblock = realloc(block, new_size);

    if (rblock) {
      if (!mry_reg_block(mngr, rblock)) return NULL;
    }

    return rblock;
}

void mry_free(mry_mngr_t *mngr, void *block)
{
    if (!mngr)  return;
    if (!block) return;

    mry_unreg_block(mngr, block);
}

void mry_unreg_block(mry_mngr_t *mngr, void *block)
{
    for (size_t i = 0; i < mngr->alloc_count; ++i)
    {
        if (mngr->addr_lookup[i] == block)
        {
            free(block);

            const size_t mv_size = sizeof(void*) * (mngr->lookup_capacity - i - 1);
            void *const  mv_dest = &mngr->addr_lookup[i];
            void *const  mv_src  = &mngr->addr_lookup[i + 1];

            (void)memmove(mv_dest, mv_src, mv_size);

            --mngr->alloc_count;

            return;
        }
    }
}

void mry_dispose(mry_mngr_t *mngr)
{
    if (!mngr) return;

    for (size_t i = 0; i < mngr->alloc_count; ++i) {
        void *const block = mngr->addr_lookup[i];
        free(block);
    }

    mngr->alloc_count     = 0;
    mngr->lookup_capacity = 0;

    free(mngr->addr_lookup); mngr->addr_lookup = NULL;
}
