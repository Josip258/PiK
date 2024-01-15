#include "include/fractals.h"
#include <omp.h>

#define MAXCOUNT 30	//broj iteracija petlje

/*
 *Ove varijable bi trebalo stavit u main() funkciju
 */
float left = -1.75;
float top = -0.25;
float xside = 0.25;
float yside = 0.45;

void fractal(float left, float top, float xside, float yside)
{
	float xscale, yscale, zx, zy, cx, tempx, cy;
	int x, y, i, j;
	int maxx, maxy, count;

	// getting maximum value of x-axis of screen
	maxx = getmaxx();

    	// getting maximum value of y-axis of screen
	maxy = getmaxy();

	// setting up the xscale and yscale
	xscale = xside / maxx;
	yscale = yside / maxy;

	// calling rectangle function where required image will be seen
	rectangle(0, 0, maxx, maxy);

    	// scanning every point in that rectangular area.
    	// Each point represents a Complex number (x + yi).
    	// Iterate that complex number
	for (y = 1; y <= maxy - 1; y++) {
		for (x = 1; x <= maxx - 1; x++) {
            		// c_real
			cx = x * xscale + left;

    			// c_imaginary
			cy = y * yscale + top;

   			// z_real
			zx = 0;

	                // z_imaginary
			zy = 0;
			count = 0;

            		// Calculate whether c(c_real + c_imaginary) belongs
            		// to the Mandelbrot set or not and draw a pixel
            		// at coordinates (x, y) accordingly
       			// If you reach the Maximum number of iterations
            		// and If the distance from the origin is
            		// greater than 2 exit the loop
			while ((zx * zx + zy * zy < 4) && (count < MAXCOUNT)) {
				tempx = zx * zx - zy * zy + cx;
				zy = 2 * zx * zy + cy;
				zx = tempx;

				count = count + 1;
			}

            		/* Oboji taj pixel s bojom count (definirane su
			u graphics.h) */

			putpixel(x, y, count);
		}
	}
}
