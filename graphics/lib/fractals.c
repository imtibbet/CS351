/*
Author: Ian Tibbetts
Date: 9/17/2014

The fractal functions for project 2
*/

#include <stdio.h>
#include <math.h>
#include "image.h"
#include "fractals.h"

/*
 *
 */
void mandelbrot( Image *dst, float x0, float y0, float dx){

	int nIters = 500;
	int i, j, k, breakIters;
	float fcols, frows, dy, cx, cy, zx, zy, zxNext, zyNext;

	// floating point rows and cols for convenience
	fcols = (float)(dst->cols);
	frows = (float)(dst->rows);

	// compute the height of the rectangle on the complex plane given the
	// rows and columns in the given image.
	dy = ( frows / fcols ) * dx;	

	// iterate over the image
	for(i=0;i<dst->rows;i++) {
		for(j=0;j<dst->cols;j++) {

			// calculate (x, y) given (i, j)
			// this corresponds to cx and cy in the Mandelbrot equation
			cx = dx*j/fcols + x0;
			cy = -dy*i/frows + y0 + dy;

			// set zx and zy to (0, 0)
			zx = zy = 0.0;
			breakIters = nIters;

			// for some number of iterations up to N (e.g. 500)
			for(k=0;k<nIters;k++){

				// iterate the Mandelbrot equation
				// make sure you do not overwrite the zx or zy values before
				// you use them in both equations
				zxNext = zx*zx - zy*zy - cx;
				zyNext = 2*zx*zy - cy;
				zx = zxNext;
				zy = zyNext;

				// if the length of z is greater than 2.0,
				// store the number of iterations and break
				if(sqrt(zx*zx + zy*zy) > 2.0){
					breakIters = k;
					break;
				}
			}

			// color pixel (i, j) 
			if(breakIters == nIters){
				dst->data[i][j].rgb[0] = 0.5;
				dst->data[i][j].rgb[1] = 0.0;
				dst->data[i][j].rgb[2] = 0.0;
			} else {
				dst->data[i][j].rgb[0] = 0.0;
				dst->data[i][j].rgb[1] = 0.0;
				dst->data[i][j].rgb[2] = (float)(breakIters % nIters) / (float)(nIters);
			}
		}
	}
}

/*
 * 
 */
void julia(Image *dst, float x0, float y0, float dx){

	int nIters = 500;
	int i, j, k, breakIters;
	float fcols, frows, dy, cx, cy, zx, zy, zxNext, zyNext;

	// floating point rows and cols for convenience
	fcols = (float)(dst->cols);
	frows = (float)(dst->rows);

	// compute the height of the rectangle on the complex plane given the
	// rows and columns in the given image.
	dy = ( frows / fcols ) * dx;	

	// iterate over the image
	for(i=0;i<dst->rows;i++) {
		for(j=0;j<dst->cols;j++) {

			// define julia set
			cx = 0.7454054;
			cy = 0.1130063;

			// set zx and zy
			zx = dx*j/fcols + x0;
			zy = -dy*i/frows + y0 + dy;
			breakIters = nIters;

			// for some number of iterations up to N (e.g. 500)
			for(k=0;k<nIters;k++){

				// iterate the Mandelbrot equation
				// make sure you do not overwrite the zx or zy values before
				// you use them in both equations
				zxNext = zx*zx - zy*zy - cx;
				zyNext = 2*zx*zy - cy;
				zx = zxNext;
				zy = zyNext;

				// if the length of z is greater than 2.0,
				// store the number of iterations and break
				if(sqrt(zx*zx + zy*zy) > 2.0){
					breakIters = k;
					break;
				}
			}

			// color pixel (i, j) 
			if(breakIters == nIters){
				dst->data[i][j].rgb[0] = 0.5;
				dst->data[i][j].rgb[1] = 0.0;
				dst->data[i][j].rgb[2] = 0.0;
			} else {
				dst->data[i][j].rgb[0] = 0.0;
				dst->data[i][j].rgb[1] = 0.0;
				dst->data[i][j].rgb[2] = (float)(breakIters % nIters) / (float)(nIters);
			}
		}
	}
}

