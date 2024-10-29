#include <platform.h>
#include <minstd.h>
#include <api/sdl2.h>
#if IS_WIN && 0
#include <Windows.h>
#endif

void* general_malloc(size_t size) {
#if SDL2_ENABLE
	return SDL_malloc(size);
#elif IS_WIN
	return HeapAlloc(GetProcessHeap(), HEAP_GENERATE_EXCEPTIONS | HEAP_NO_SERIALIZE, (SIZE_T)size);
#else
	UNUSED1(size);
	return NULL;
#endif
}

void general_free(void* ptr) {
#if SDL2_ENABLE
	SDL_free(ptr);
#elif IS_WIN
	HeapFree(GetProcessHeap(), HEAP_GENERATE_EXCEPTIONS | HEAP_NO_SERIALIZE, ptr);
#else
	UNUSED1(ptr);
#endif
}
