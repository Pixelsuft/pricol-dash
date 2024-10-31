#pragma once
#include <minstd.h>
#include <scenes/game.h>
#include <ren/base.h>

typedef struct Player {
	Point pos;
	void (*on_init)(struct Player* this, SceneGame* game);
	void (*on_run)(struct Player* this, SceneGame* game);
	void (*on_update)(struct Player* this, SceneGame* game);
	void (*on_draw)(struct Player* this, SceneGame* game);
	void (*on_destroy)(struct Player* this, SceneGame* game);
	Tex* tex1;
	Tex* tex2;
	b2BodyId body;
	b2ShapeId shape;
} Player;

void player_create(Player* this);
