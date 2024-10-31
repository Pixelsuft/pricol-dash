#pragma once
#include <stdbool.h>
#include <gen/res_map.h>
#include <ren/base.h>
#include <bmfont.h>
#define MAX_LEVELS 8

typedef struct {
	BMFont fnt[MAX_RES_FNT];
	Tex* tex[MAX_RES_PNG];
	char* lv_data[MAX_LEVELS];
	void* temp_surf;
	Tex* temp_tex;
	void* thread_h;
	int progress;
	int total_count;
	bool temp_no_scale;
	bool threaded;
	bool running;
} FileSystem;

extern FileSystem* fs;

bool fs_create(void);
void fs_destroy(void);
void fs_update_from_loop(void);
void fs_run(void);
bool fs_init(void);
