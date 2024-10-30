#include <bmfont.h>
#include <app/sdl2.h>

void bmfont_destroy(BMFont* this) {
	for (size_t i = 0; i < this->chars.len; i++) {
		if (this->chars.data[i].ks.data != NULL)
			array_destroy(&this->chars.data[i].ks);
	}
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
			this->ch_count = 256;
			array_init(&this->chars, 256, sizeof(BMChar), 4 * sizeof(BMChar));
			MEMSET(this->chars.data, 0, sizeof(BMChar) * 256);
		}
		else if (iter[0] == 'c') {
			// Char
			iter += 8;
			int ch_id = ATOI(iter);
			if (ch_id >= 0 && ch_id < 256) {
				BMChar* chr = &this->chars.data[ch_id];
				while (*iter != '=')
					iter++;
				iter++;
				chr->x = ATOI(iter);
				while (*iter != '=')
					iter++;
				iter++;
				chr->y = ATOI(iter);
				while (*iter != '=')
					iter++;
				iter++;
				chr->w = ATOI(iter);
				while (*iter != '=')
					iter++;
				iter++;
				chr->h = ATOI(iter);
				while (*iter != '=')
					iter++;
				iter++;
				chr->xo = ATOI(iter);
				while (*iter != '=')
					iter++;
				iter++;
				chr->yo = ATOI(iter);
				while (*iter != '=')
					iter++;
				iter++;
				chr->xa = ATOI(iter);
			}
		}
		else if (iter[0] == 'k' && iter[7] == 's') {
			// Kernings
		}
		else if (iter[0] == 'k') {
			// Kerning
			iter += 14;
			int first = ATOI(iter);
			while (*iter != '=')
				iter++;
			iter++;
			int second = ATOI(iter);
			while (*iter != '=')
				iter++;
			iter++;
			int ammount = ATOI(iter);
			if (second >= 0 && second < 256) {
				BMChar* chr = &this->chars.data[second];
				if (chr->ks.data == NULL)
					array_init(&chr->ks, 0, sizeof(int), sizeof(int) * 32);
				array_push(&chr->ks, sizeof(int), &first);
				array_push(&chr->ks, sizeof(int), &ammount);
			}
		}
		iter = tmp_iter + 1;
	}
}
