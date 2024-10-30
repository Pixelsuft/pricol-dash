#include <scenes/loading.h>
#include <app/base.h>
#include <app/sdl2.h>
#include <ren/base.h>
#include <minstd.h>
#define base ((Scene*)this)

void scene_loading_on_init(SceneLoading* this) {
}

void scene_loading_on_run(SceneLoading* this) {
	app->clock_reset();
}

void scene_loading_on_update(SceneLoading* this) {
	
}

void scene_loading_on_draw(SceneLoading* this) {
	ren->fill_rect_s(&RECT(100, 100, 30, 30), &RGBA(255, 0, 0, 255));
}

void scene_loading_on_stop(SceneLoading* this) {

}

void scene_loading_on_destroy(SceneLoading* this) {
	
}

Scene* scene_loading_create(void) {
	SceneLoading* this = f_alloc(sizeof(SceneLoading));
	scene_fill_defaults(base);
	FCAST(base->on_init, scene_loading_on_init);
	FCAST(base->on_run, scene_loading_on_run);
	FCAST(base->on_update, scene_loading_on_update);
	FCAST(base->on_draw, scene_loading_on_draw);
	FCAST(base->on_stop, scene_loading_on_stop);
	FCAST(base->on_destroy, scene_loading_on_destroy);
	return base;
}