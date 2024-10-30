#pragma once
#include <stdbool.h>

typedef struct {
	int dummy;
} FileSystem;

extern FileSystem* fs;

bool fs_create(void);
void fs_destroy(void);
