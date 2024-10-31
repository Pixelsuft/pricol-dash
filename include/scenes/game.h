#pragma once
#include <scenes/base.h>
#include <array.h>
#include <go/base.h>

typedef struct {
	Scene parent;
	Point cam_pos;
	Color def_bg_col;
	Color def_gr_col;
	Array(GObject*) obj;
} SceneGame;
