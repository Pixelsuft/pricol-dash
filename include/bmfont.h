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
    float sx;
    float sy;
    int line_height;
} BMFont;

void bmfont_init(BMFont* this, char* buf, size_t size);
void bmfont_destroy(BMFont* this);
void bmfont_calc_line_size(BMFont* this, const char* text, size_t text_len, Point* size_buf);
void bmfont_ren_line_size(BMFont* this, const char* text, size_t text_len, const Point* pos, const Point* size_buf);
