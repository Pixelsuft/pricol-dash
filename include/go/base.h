#pragma once
#include <minstd.h>

typedef struct GObject {
	Point pos;
	void (*on_draw)(struct GObject* this);
} GObject;
