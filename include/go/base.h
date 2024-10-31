#pragma once
#include <minstd.h>

typedef struct GObject {
	Point pos;
	void (*on_init)(struct GObject* this);
	void (*on_update)(struct GObject* this);
	void (*on_draw)(struct GObject* this);
	int id;
} GObject;

void go_fill_base(GObject* this);
