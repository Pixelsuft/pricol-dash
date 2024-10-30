#include <platform.h>
#include <config.h>
#include <minstd.h>
#if SDL2_ENABLE
#if !IS_VS
#define SDL_MAIN_HANDLED
#endif
#include <api/sdl2.h>
#endif
#include <app/base.h>
#include <ren/base.h>
#include <fs.h>
#include <scenes/base.h>

bool main_func(void) {
    bool ret = true;
#if SDL2_ENABLE
    if (app_sdl2_create())
        return ret;
#endif
    if (app->init())
        goto ex1;
    fs_create();
#if SDL2_ENABLE
    if (ren_sdl2_create())
        goto ex2;
#endif
    if (ren->init())
        goto ex3;
    Scene* start_scene = scene_loading_create();
    start_scene->on_init(start_scene);
    app->run_scene(start_scene);
    app->run();
    ret = false;
    goto ex4;
ex4:
    ren->quit();
ex3:
    ren->destroy();
ex2:
    fs_destroy();
    app->quit();
ex1:
    app->destroy();
    return ret;
}

#if 0
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
    ExitProcess(0);
    return 0;
}
#else
int main(int argc, char* argv[]) {
    UNUSED1(argc);
    UNUSED1(argv);
    return main_func() ? 1 : 0;
}
#endif
