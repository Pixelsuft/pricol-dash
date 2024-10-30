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
    int pad[4];
    int spac[2];
    int size;
    int line_height;
    int base;
    int scale_w;
    int scale_h;
} BMFont;
