#include <go/base.h>

void go_dummy_func(GObject* this) {}

void go_fill_base(GObject* this) {
	this->on_init = go_dummy_func;
	this->on_update = go_dummy_func;
	this->on_draw = go_dummy_func;
	this->pos.x = this->pos.y = 0.f;
	this->id = 0;
}
