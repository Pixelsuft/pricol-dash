#pragma once

#ifdef _WIN32
#define WIN23_LEAN_AND_MEAN
#define IS_WIN 1
#else
#define IS_WIN 0
#endif

#ifdef _MSC_VER
#define IS_VS 1
#else
#define IS_VS 0
#endif

#ifndef DEBUG
#ifdef _DEBUG
#define DEBUG 1
#else
#define DEBUG 0
#endif
#endif
