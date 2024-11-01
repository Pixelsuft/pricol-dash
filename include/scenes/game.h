#pragma once
#include <scenes/base.h>
#include <array.h>
#include <ren/base.h>
#include <box2d/box2d.h>

typedef struct GObject GObject;
typedef struct Player Player;

typedef struct {
	Scene parent;
	Array(GObject*) obj;
	Player* pl;
	Color def_bg_col;
	Color def_gr_col;
	Point cam_pos;
	Tex* ground;
	Tex* floor;
	float ground_pos;
	b2WorldId world;
} SceneGame;
