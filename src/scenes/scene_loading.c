#include <scenes/loading.h>
#include <app/base.h>
#include <app/sdl2.h>
#include <ren/base.h>
#include <fs.h>
#include <minstd.h>
#define base ((Scene*)this)

void scene_loading_on_init(SceneLoading* this) {
	fs_init();
}

void scene_loading_on_run(SceneLoading* this) {
	fs_run();
	app->clock_reset();
}

void scene_loading_on_update(SceneLoading* this) {
	if (fs->running)
		fs_update_from_loop();
}

void scene_loading_on_draw(SceneLoading* this) {
	Tex* bg_tex = fs->tex[RES_PNG("game_bg_01_001.png")];
	if (bg_tex) {
		ren->tex_col(bg_tex, &RGBA(40, 62, 255, 255));
		ren->copy_sc(bg_tex, &POINT(ren->vs.w / 2.0f, ren->vs.h / 2.0f), 1.3f, 1.3f);
	}
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
