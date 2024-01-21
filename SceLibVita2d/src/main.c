
#include <psp2/kernel/modulemgr.h>
#include <psp2/kernel/clib.h>
#include <vita2d.h>


/*
int test_print(void){

	vita2d_init();
	vita2d_load_PNG_file(NULL);
	vita2d_load_JPEG_file(NULL);
	vita2d_load_BMP_file(NULL);
	// vita2d_load_font_file(NULL);

	vita2d_load_default_pvf();
	vita2d_load_default_pgf();

	return 0;
}
*/

void _start() __attribute__ ((weak, alias("module_start")));
int module_start(SceSize args, void *argp){
	return SCE_KERNEL_START_SUCCESS;
}
