#include <bmfont.h>
#include <app/sdl2.h>

// My ANSI-only impl for BMFont

void bmfont_destroy(BMFont* this) {
	for (size_t i = 0; i < this->chars.len; i++) {
		if (this->chars.data[i].ks.data != NULL)
			array_destroy(&this->chars.data[i].ks);
	}
	array_destroy(&this->chars);
}

void bmfont_calc_line_size(BMFont* this, const char* text, size_t text_len, Point* size_buf) {
	size_buf->x = 0.f;
	size_buf->y = (float)this->line_height * this->sy;
	int last_chr = 0;
	BMChar* bm_char;
	for (size_t i = 0; i < text_len; i++) {
		size_t chr = (size_t)text[i];
		if ((chr > this->chars.len) || ((this->chars.data[chr].w <= 0) && (this->chars.data[chr].xa < 0)))
			continue;
		bm_char = &this->chars.data[chr];
		if (i > 0 && this->chars.data[chr].ks.data != NULL) {
			if (i > 0 && bm_char->ks.data != NULL) {
				for (size_t j = 0; j < bm_char->ks.len; j += 2) {
					if (bm_char->ks.data[j] == last_chr) {
						//size_buf->x += (float)bm_char->ks.data[j + 1];
						break;
					}
				}
			}
		}
		size_buf->x += (float)this->chars.data[chr].xa;
		last_chr = (int)chr;
	}
	size_buf->x *= this->sx;
	size_buf->x /= ren->t_sc;
}

void bmfont_ren_line_size(BMFont* this, const char* text, size_t text_len, const Point* pos, const Point* size_buf) {
	Point real_size;
	if (size_buf == NULL) {
		bmfont_calc_line_size(this, text, text_len, &real_size);
	}
	else {
		real_size.w = size_buf->w;
		real_size.h = size_buf->h;
	}
	float cur_x = pos->x - real_size.w / 2.f;
	float cur_y = pos->y - real_size.h / 2.f;
	BMChar* bm_char;
	bool res = false;
	Rect src_rect, dst_rect;
	dst_rect.w = dst_rect.h = 0.0f;
	int last_chr = 0;
	for (size_t i = 0; i < text_len; i++) {
		size_t chr = (size_t)text[i];
		if ((chr > this->chars.len) || ((this->chars.data[chr].w <= 0) && (this->chars.data[chr].xa < 0)))
			continue;
		bm_char = &this->chars.data[chr];
		if (bm_char->w > 0) {
			src_rect.x = (float)bm_char->x;
			src_rect.y = (float)bm_char->y;
			src_rect.w = (float)bm_char->w;
			src_rect.h = (float)bm_char->h;
			dst_rect.x = cur_x + (float)bm_char->xo * this->sx / ren->t_sc;
			if (i > 0 && bm_char->ks.data != NULL) {
				for (size_t j = 0; j < bm_char->ks.len; j += 2) {
					if (bm_char->ks.data[j] == last_chr) {
						dst_rect.x += (float)bm_char->ks.data[j + 1] * this->sx / ren->t_sc;
						cur_x += (float)bm_char->ks.data[j + 1] * this->sx / ren->t_sc;
						break;
					}
				}
			}
			dst_rect.y = cur_y + (float)bm_char->yo * this->sy / ren->t_sc;
			dst_rect.w = (float)bm_char->w * this->sx / ren->t_sc;
			dst_rect.h = (float)bm_char->h * this->sy / ren->t_sc;
			ren->copy_orig(this->page, &src_rect, &dst_rect);
		}
		cur_x += (float)bm_char->xa * this->sx / ren->t_sc;
		last_chr = (int)chr;
	}
}

void bmfont_init(BMFont* this, char* buf, size_t size) {
	// Assuming buf ends with '\n'
	this->sx = this->sy = 1.f;
	int isc = ren->t_sc == 2.f ? 1 : 0;
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
