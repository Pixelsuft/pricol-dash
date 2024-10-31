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
	else if (1) {
		Scene* sc = scene_game_create();
		sc->on_init(sc);
		app->run_scene(sc);
	}
}

void scene_loading_on_draw(SceneLoading* this) {
	Tex* bg_tex = fs->tex[RES_PNG("game_bg_01_001.png")];
	Tex* rob_tex = fs->tex[RES_PNG("RobTopLogoBig_001.png")];
	Tex* logo = fs->tex[RES_PNG("GJ_logo_001.png")];
	BMFont* fnt = &fs->fnt[RES_FNT("goldFont.fnt")];
	ren->clear(&RGBA(0, 0, 255, 255));
	if (bg_tex) {
		ren->tex_col(bg_tex, &RGBA(40, 62, 255, 255));
		ren->copy_sc(bg_tex, &POINT(ren->vs.w / 2.0f, ren->vs.h / 2.0f), 1.3f, 1.3f);
	}
	if (rob_tex)
		ren->copy(rob_tex, &POINT(ren->vs.w / 2.f, ren->vs.h / 4.f));
	if (logo)
		ren->copy(logo, &POINT(ren->vs.w / 2.f, ren->vs.h / 2.f));
	if (fnt->page) {
		fnt->sx = fnt->sy = 0.8f;
		bmfont_ren_line_size(fnt, "Made by Pixelsuft", 17, &POINT(ren->vs.w / 2.f, ren->vs.h * 5.f / 6.f), NULL);
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
