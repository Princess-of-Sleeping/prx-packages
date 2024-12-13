
#include <psp2/kernel/modulemgr.h>


void *(* _sceCapstoneMalloc)(size_t len) = NULL;
void *(* _sceCapstoneRealloc)(void *ptr, size_t len) = NULL;
void *(* _sceCapstoneCalloc)(size_t count, size_t len) = NULL;
void (* _sceCapstoneFree)(void *ptr) = NULL;

void *malloc(size_t len){
	return _sceCapstoneMalloc(len);
}

void *realloc(void *ptr, size_t len){
	return _sceCapstoneRealloc(ptr, len);
}

void *calloc(size_t count, size_t len){
	return _sceCapstoneCalloc(count, len);
}

void free(void *ptr){
	_sceCapstoneFree(ptr);
}

void *_malloc(size_t len){
	return NULL;
}

void *_realloc(void *ptr, size_t len){
	return NULL;
}

void *_calloc(size_t count, size_t len){
	return NULL;
}

void _free(void *ptr){
}

int module_start(SceSize args, void *argp){

	_sceCapstoneMalloc  = _malloc;
	_sceCapstoneRealloc = _realloc;
	_sceCapstoneCalloc  = _calloc;
	_sceCapstoneFree    = _free;

	return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize args, void *argp){
	return SCE_KERNEL_STOP_SUCCESS;
}
