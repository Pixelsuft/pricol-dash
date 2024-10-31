#pragma once
#include <go/base.h>
#include <ren/base.h>

typedef struct {
	GObject parent;
	Tex* tex;
} GBlock;

void gblock_create(GBlock* this);

typedef struct {
	GObject parent;
	Tex* tex;
} GSpike;

void gspike_create(GSpike* this);
