#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <array.h>
#include <ren/base.h>

struct Tex;

typedef struct {
    Array(int) ks;
    // Pos
    int x;
    int y;
    int w;
    int h;
    // Offset
    int xo;
    int yo;
    // Advance
    int xa;
} BMChar;

typedef struct {
    Array(BMChar) chars;
    Tex* page;
    size_t ch_count;
    size_t k_count;
    int line_height;
} BMFont;

void bmfont_init(BMFont* this, char* buf, size_t size, int png_id);
void bmfont_destroy(BMFont* this);
