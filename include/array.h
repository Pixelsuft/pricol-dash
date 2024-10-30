#pragma once
#include <minstd.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    void* data;
    size_t size;
    size_t len;
    int chunk_size;
} ArrayBase;

#define Array(array_type) struct { \
    array_type* data; \
    size_t size; \
    size_t len; \
    int chunk_size; \
}

#define ARRAY_INIT(this, initial_len, chunk_size) array_init((ArrayBase*)(this), initial_len, (size_t)sizeof(*(this)->data), chunk_size)
#define ARRAY_DESTROY(this) array_destroy((ArrayBase*)(this))
#define ARRAY_ADD_CHUNK(this) array_add_chunk((ArrayBase*)(this))
#define ARRAY_SET_LEN(this, need_len, trim) array_set_len((ArrayBase*)(this), need_len, (size_t)sizeof(*(this)->data), trim)
#define ARRAY_PUSH(this, new_elem) array_push((ArrayBase*)(this), (size_t)sizeof(*(this)->data), &(new_elem))
#define ARRAY_PUSH_DUMMY(this) array_push_dummy((ArrayBase*)(this), (size_t)sizeof(*(this)->data))
#define ARRAY_REMOVE(this, elem_id, trim) array_remove((ArrayBase*)(this), elem_id, (size_t)sizeof(*(this)->data), trim)
#define ARRAY_RESERVE_LEN(this, need_len) array_reserve_len((ArrayBase*)(this), need_len, (size_t)sizeof(*(this)->data))
#define ARRAY_CLEAN(this) array_remove((ArrayBase*)(this), (size_t)sizeof(*(this)->data))

bool array_init(ArrayBase* this, size_t initial_len, size_t elem_size, int chunk_size);
bool array_set_len(ArrayBase* this, size_t need_len, size_t elem_size, bool trim);
bool array_push(ArrayBase* this, size_t elem_size, const void* need_elem);
bool array_push_dummy(ArrayBase* this, size_t elem_size);
bool array_reserve_len(ArrayBase* this, size_t need_len, size_t elem_size);
bool array_remove(ArrayBase* this, size_t elem_id, size_t elem_size, bool trim);
bool array_clean(ArrayBase* this, size_t elem_size);
bool array_add_chunk(ArrayBase* this);
bool array_destroy(ArrayBase* this);