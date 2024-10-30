#include <bmfont.h>
#include <app/sdl2.h>

void bmfont_destroy(BMFont* this) {
	array_destroy(&this->chars);
}

void bmfont_init(BMFont* this, char* buf, size_t size, int png_id) {
	// Assuming buf ends with '\n'
	int isc = ren->t_sc == 2.0f ? 1 : 0;
	char* iter = buf;
	while (1) {
		char* tmp_iter = iter;
		while (*tmp_iter != '\n')
			tmp_iter++;
		*tmp_iter = '\0';
		if ((size_t)(tmp_iter - buf) >= size - 5)
			break;
		if (iter[0] == 'i') {
			// Info
		}
		else if (iter[0] == 'c' && iter[1] == 'o') {
			// Common
			SASSERT(SSCANF(iter, "common lineHeight=%i", &this->line_height) == 1);
			this->line_height >>= isc;
		}
		else if (iter[0] == 'c' && iter[4] == 's') {
			// Chars (ANSI hardcode)
			SLOG_INFO("%s", iter);
			this->ch_count = 256;
			array_init(&this->chars, 256, sizeof(BMChar), 4 * sizeof(BMChar));
		}
		else if (iter[0] == 'c') {
			// Char
		}
		else if (iter[0] == 'k' && iter[7] == 's') {
			// Kernings
		}
		else if (iter[0] == 'k') {
			// Kerning
		}
		iter = tmp_iter + 1;
	}
}
