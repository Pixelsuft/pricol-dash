#include <fs.h>
#include <app/base.h>

FileSystem* fs;

bool fs_create(void) {
	fs = m_alloc(sizeof(FileSystem));
	if (fs == NULL)
		return true;
	return false;
}

void fs_destroy(void) {
	m_free(fs);
}
