#pragma once
#include <stdbool.h>
#include <gen/res_map.h>
#include <ren/base.h>

typedef struct {
	Tex* tex[MAX_RES_PNG];
} FileSystem;

extern FileSystem* fs;

bool fs_create(void);
void fs_destroy(void);
