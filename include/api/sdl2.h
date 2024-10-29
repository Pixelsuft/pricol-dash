#pragma once
#include <config.h>
#include <platform.h>

#ifdef SDL2_ENABLE
#if IS_VS || 1
#define SDL2_INCLUDE_DIR 0
#else
#define SDL2_INCLUDE_DIR 1
#endif
#if SDL2_INCLUDE_DIR
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif
#endif
