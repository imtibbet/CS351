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
 * draws the complex plane at x0, y0 with width dx onto the destination image
 * coloring according to how quickly the point reaches the infinity set of the
 * mandelbrot set for a fixed number of iterations.
 */
void mandelbrot( Image *dst, float x0, float y0, float dx){

	int nIters = 500;
	int i, j, k, breakIters, rIters, gIters, bIters;
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

			// calculate (cx, cy) given (i, j)
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
			rIters = (float)(nIters)/3.0;
			gIters = (float)(nIters)/20.0;
			bIters = (float)(nIters)/50.0;
			dst->data[i][j].rgb[0] = fmod( (float)breakIters, rIters ) / rIters;
			dst->data[i][j].rgb[1] = fmod( (float)breakIters, gIters ) / gIters;
			dst->data[i][j].rgb[2] = fmod( (float)breakIters, bIters ) / bIters;
		}
	}
}

/*
 * draws the complex plane at x0, y0 with width dx onto the destination image
 * coloring according to how quickly the point reaches the infinity set of the
 * julia set for a fixed number of iterations and value of c.
 */
void julia(Image *dst, float x0, float y0, float dx){

	int nIters = 500;
	int i, j, k, breakIters, rIters, gIters, bIters;
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

			// set zx and zy depending on pixel location
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
			rIters = (float)(nIters)/3.0;
			gIters = (float)(nIters)/20.0;
			bIters = (float)(nIters)/50.0;
			dst->data[i][j].rgb[0] = fmod( (float)breakIters, rIters ) / rIters;
			dst->data[i][j].rgb[1] = fmod( (float)breakIters, gIters ) / gIters;
			dst->data[i][j].rgb[2] = fmod( (float)breakIters, bIters ) / bIters;
		}
	}
}

