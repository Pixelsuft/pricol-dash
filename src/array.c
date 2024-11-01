#define ARRAY_IMPL
#include <array.h>
#include <app/base.h>
#include <app/sdl2.h>

// TODO: support fast allocator



bool array_destroy(ArrayBase* this) {
    if (this->data == NULL)
        return true;
    m_free(this->data);
    this->data = NULL;
    this->chunk_size = 0;
    this->size = 0;
    this->len = 0;
    return false;
}

bool array_add_chunk(ArrayBase* this) {
    void* new_ptr = m_realloc(this->data, this->size + (size_t)this->chunk_size);
    this->size += (size_t)this->chunk_size;
    this->data = new_ptr;
    return false;
}

bool array_set_len(ArrayBase* this, size_t need_len, size_t elem_size, bool trim) {
    size_t need_size = need_len * elem_size;
    if (need_size % (size_t)this->chunk_size || 1) {
        need_size /= (size_t)this->chunk_size;
        need_size++;
        need_size *= (size_t)this->chunk_size;
    }
    if ((need_size < this->size) && !trim) {
        this->len = need_len;
        return false;
    }
    void* new_ptr = m_realloc(this->data, need_size);
    this->size = need_size;
    this->data = new_ptr;
    this->len = need_len;
    return false;
}

bool array_push(ArrayBase* this, size_t elem_size, const void* need_elem) {
    if (((this->len + 1) * elem_size) > this->size) {
        if (array_add_chunk(this))
            return true;
    }
    MEMCPY((void*)((size_t)(this->data) + (this->len * elem_size)), need_elem, elem_size);
    this->len++;
    return false;
}

bool array_push_dummy(ArrayBase* this, size_t elem_size) {
    if (((this->len + 1) * elem_size) > this->size) {
        if (array_add_chunk(this))
            return true;
    }
    this->len++;
    return false;
}

bool array_remove(ArrayBase* this, size_t elem_id, size_t elem_size, bool trim) {
    if ((elem_id + 1) >= this->len) {
        this->len--;
        if (trim)
            return array_clean(this, elem_size);
        return false;
    }
    MEMMOVE(
        (void*)((size_t)(this->data) + (elem_id * elem_size)),
        (void*)((size_t)(this->data) + ((elem_id + 1) * elem_size)),
        (this->len - elem_id - 1) * elem_size
    );
    this->len--;
    if (trim)
        return array_clean(this, elem_size);
    return false;
}

bool array_reserve_len(ArrayBase* this, size_t need_len, size_t elem_size) {
    size_t need_size = need_len * elem_size;
    if (need_size % (size_t)this->chunk_size || 1) {
        need_size /= (size_t)this->chunk_size;
        need_size++;
        need_size *= (size_t)this->chunk_size;
    }
    if (this->size >= need_size)
        return false;
    void* new_ptr = m_realloc(this->data, need_size);
    this->data = new_ptr;
    this->size = need_size;
    return false;
}

bool array_clean(ArrayBase* this, size_t elem_size) {
    size_t need_size = this->len * elem_size;
    if (need_size % (size_t)this->chunk_size || 1) {
        need_size /= (size_t)this->chunk_size;
        need_size++;
        need_size *= (size_t)this->chunk_size;
    }
    if (this->size >= need_size) {
        void* new_ptr = m_realloc(this->data, need_size);
        this->data = new_ptr;
        this->size = need_size;
    }
    return false;
}

bool array_init(ArrayBase* this, size_t initial_len, size_t elem_size, int chunk_size) {
    if (chunk_size <= 0)
        chunk_size = (int)elem_size;
    this->chunk_size = chunk_size;
    this->len = initial_len;
    this->size = initial_len * elem_size;
    if ((this->size % (size_t)chunk_size) > 0) {
        this->size /= (size_t)chunk_size;
        this->size++;
        this->size *= (size_t)chunk_size;
    }
    this->data = m_alloc(this->size);
    return false;
}