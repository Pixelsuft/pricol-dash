#pragma once
#include <stdint.h>

#define UNUSED1(arg1) ((void)arg1)
#define RGBA(_r, _g, _b, _a) ((Color){ .r = (float)(_r), .g = (float)(_g), .b = (float)(_b), .a = (float)(_a) })
#define RECT(_x, _y, _w, _h) ((Rect){ .x = (float)(_x), .y = (float)(_y), .w = (float)(_w), .h = (float)(_h) })
#define FCAST(ptr1, ptr2) (void*)ptr1 = (void*)ptr2;

typedef union {
    struct {
        float x;
        float y;
        float w;
        float h;
    };
    struct {
        float x1;
        float y1;
        float x2;
        float y2;
    };
    struct {
        float l;
        float t;
        float r;
        float b;
    };
    float val[4];
} Rect;

typedef union {
    struct {
        float x;
        float y;
    };
    struct {
        float w;
        float h;
    };
    float val[2];
} Point;

typedef union {
    struct {
        float r;
        float g;
        float b;
        float a;
    };
    float val[4];
} Color;

void* general_malloc(size_t size);
void general_free(void* ptr);
