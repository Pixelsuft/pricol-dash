#pragma once
#include <scenes/base.h>
#include <go/base.h>

typedef struct {
	Scene parent;
	Color def_bg_col;
	Color def_gr_col;
	GObject** obj;
} SceneGame;
