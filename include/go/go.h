#pragma once
#include <go/base.h>

typedef struct {
	GObject parent;
} GBlock;

void gblock_init(GBlock* this);
