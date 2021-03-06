/*
 * Barnsley Fern for RC2014 with TMS9918A video card
 * 
 * Compile with z88dk: 
 * zcc +cpm --math32 -create-app -ofern fern.c tmsc.asm z180c.asm
 * 
 * For Z180 hardware multiply, add -mz180:
 * zcc +cpm --math32 -mz180 -create-app -ofern fern.c tmsc.asm z180c.asm
 * 
 * Press any key to quit.
 * 
 * https://en.wikipedia.org/wiki/Barnsley_fern
 * 
 */
#include <stdint.h>
#include <stdlib.h>
#include <conio.h>
#include "tms.h"
#include "z180.h"

main()
{
	if (!TmsProbe()) {
		printf("TMS9918A not found, aborting!\n");
		return;
	}
	if (Z180Detect() != 0xFF) {
		TmsSetWait(Z180GetClock());
	} else {
		TmsSetWait(0);
	}
    TmsBitmap();
	TmsFill(TMS_FGBG(TMS_DARKGREEN, TMS_BLACK), TMS_BITMAPCOLORTBL, TMS_BITMAPCOLORLEN);
	float x = 0, y = 0, nx, ny;
	while (!kbhit()) {
		uint8_t r = rand()/(RAND_MAX/100);
		if (r <= 1) {
			nx = 0;
			ny = 0.16 * y;
		} else if (r <= 8) {
			nx = 0.2 * x - 0.26 * y;
			ny = 0.23 * x + 0.22 * y + 1.6;
		} else if (r <= 15) {
			nx = -0.15 * x + 0.28 * y;
			ny = 0.26 * x + 0.24 * y + 0.44;
		} else {
			nx = 0.85 * x + 0.04 * y;
			ny = -0.04 * x + 0.85 * y + 1.6;
		}
		x = nx;
		y = ny;
		TmsPlotPixel(127+x*17, 191-y*17);
	}
}