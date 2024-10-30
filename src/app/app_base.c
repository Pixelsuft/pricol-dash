#include <minstd.h>
#include <app/base.h>
#include <ren/base.h>
#include <scenes/base.h>

App* app;
float dt;

bool app_init(void) {
	return true;
}

void app_dummy_void(void) {}

void app_show_win(bool show) {
	UNUSED1(show);
}

void app_on_update(void) {
	app->clock_update();
	if (app->sc != NULL)
		app->sc->on_update(app->sc);
}

void app_stop(void) {
	app->running = false;
	if (app->sc != NULL) {
		app->sc->on_stop(app->sc);
		app->sc->on_destroy(app->sc);
		f_free(app->sc);
		app->sc = NULL;
	}
}

void app_run(void) {
	app->apply_dark();
	app->on_resize();
	app->running = true;
	app->show_win(true);
	while (app->running) {
		app->poll_events();
		if (!app->running)
			break;
		app_on_update();
		if (!app->running)
			break;
		ren->draw_scene();
	}
	app_stop();
}

void app_run_scene(Scene* scene) {
	if (app->sc != NULL) {
		app->sc->on_stop(app->sc);
		app->sc->on_destroy(app->sc);
		f_free(app->sc);
	}
	app->sc = scene;
	app->sc->on_run(app->sc);
}

void app_fill_base(void) {
	app->hwnd = NULL;
	app->sc = NULL;
	app->destroy = app_dummy_void;
	app->init = app_init;
	app->quit = app_dummy_void;
	app->apply_dark = app_dummy_void;
	app->show_win = app_show_win;
	app->run = app_run;
	app->stop = app_stop;
	app->poll_events = app_dummy_void;
	app->on_resize = app_dummy_void;
	app->clock_reset = app_dummy_void;
	app->clock_update = app_dummy_void;
	app->run_scene = app_run_scene;
}
