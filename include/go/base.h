#pragma once
#include <minstd.h>
#include <scenes/game.h>

typedef struct GObject {
	Point pos;
	void (*on_init)(struct GObject* this, SceneGame* game);
	void (*on_update)(struct GObject* this, SceneGame* game);
	void (*on_draw)(struct GObject* this, SceneGame* game);
	void (*on_destroy)(struct GObject* this, SceneGame* game);
	float rot;
	int flip;
	int id;
} GObject;

void go_fill_base(GObject* this);
