#pragma once
#include <go/base.h>
#include <ren/base.h>

typedef struct {
	GObject parent;
	Tex* tex;
	Tex* glow;
	b2BodyId body;
	b2ShapeId shape;
} GBlock;

void gblock_create(GBlock* this);

typedef struct {
	GObject parent;
	Tex* tex;
	Tex* glow;
} GSpike;

void gspike_create(GSpike* this);
