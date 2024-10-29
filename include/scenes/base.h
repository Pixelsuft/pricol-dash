#pragma once
#include <config.h>
#include <minstd.h>

typedef struct Scene {
	void (*on_init)(struct Scene* this);
	void (*on_run)(struct Scene* this);
	void (*on_update)(struct Scene* this);
	void (*on_draw)(struct Scene* this);
	void (*on_stop)(struct Scene* this);
	void (*on_destroy)(struct Scene* this);
} Scene;

void scene_fill_defaults(Scene* this);
Scene* scene_game_create(void);
