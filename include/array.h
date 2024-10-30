#pragma once
#include <minstd.h>
#include <stdbool.h>
#include <stdint.h>

#define Array(array_type) struct { \
    array_type* data; \
    size_t size; \
    size_t len; \
    int chunk_size; \
}

#ifdef ARRAY_IMPL
typedef struct {
    void* data;
    size_t size;
    size_t len;
    int chunk_size;
} ArrayBase;
#else
typedef void ArrayBase;
#endif

bool array_init(ArrayBase* this, size_t initial_len, size_t elem_size, int chunk_size);
bool array_set_len(ArrayBase* this, size_t need_len, size_t elem_size, bool trim);
bool array_push(ArrayBase* this, size_t elem_size, const void* need_elem);
bool array_push_dummy(ArrayBase* this, size_t elem_size);
bool array_reserve_len(ArrayBase* this, size_t need_len, size_t elem_size);
bool array_remove(ArrayBase* this, size_t elem_id, size_t elem_size, bool trim);
bool array_clean(ArrayBase* this, size_t elem_size);
bool array_add_chunk(ArrayBase* this);
bool array_destroy(ArrayBase* this);