#include <scenes/base.h>

void scene_dummy_func(Scene* this) {}

void scene_fill_defaults(Scene* this) {
	this->on_init = scene_dummy_func;
	this->on_run = scene_dummy_func;
	this->on_update = scene_dummy_func;
	this->on_draw = scene_dummy_func;
	this->on_stop = scene_dummy_func;
	this->on_destroy = scene_dummy_func;
}
