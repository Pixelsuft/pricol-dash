#include <ren/base.h>

Ren* ren;

bool ren_init(void) {
	return true;
}

void ren_destroy(void) {}

void ren_quit(void) {}

void ren_draw_scene(void) {}

void ren_on_resize(void) {}

void ren_fill_base(void) {
	ren->t_sc = 2.0f;
	ren->destroy = ren_destroy;
	ren->init = ren_init;
	ren->quit = ren_quit;
	ren->draw_scene = ren_draw_scene;
	ren->on_resize = ren_on_resize;
}
