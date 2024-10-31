#pragma once
#include <scenes/base.h>
#include <array.h>
#include <box2d/box2d.h>

typedef struct GObject GObject;

typedef struct {
	Scene parent;
	Array(GObject*) obj;
	Color def_bg_col;
	Color def_gr_col;
	Point cam_pos;
	b2WorldId world;
} SceneGame;
