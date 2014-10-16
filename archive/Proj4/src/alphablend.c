/*
Author: Ian Tibbetts (Bruce Maxwell)
Date: 9/10/2014

A program that takes in two images and a mask image and merges the two images using the mask as an alpha mask, as well as allowing offset, mirroring, and rotation
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ppmIO.h"

#define USECPP 0

int main(int argc, char *argv[]) {
	Pixel *image1,*image2,*imageM;
	int rows1, cols1, colors1;
	int rows2, cols2, colors2;
	int rowsMask, colsMask, colorsMask;
	float alphaR, alphaG, alphaB;
	long i,j,bi,bj,fi,fj,backgroundIndex,foregroundIndex,fx,fy,fxr,fyr;

	// command line parameters
	int dx, dy, mirror;
	float rotate, rotateRad;

	dx = dy = mirror = 0;
	rotate = rotateRad = 0.0;
	if(argc < 5 || argc > 9) {
		printf(	"Usage: alphablend <input file1> <input file2> <mask file>" 				"<output file1> [dx (default=0)] [dy (default=0)]"
				"[mirror (default=0)] [rotatedegrees (default=0.0)]\n");
		exit(-1);
	} 
	if(argc > 5) {
		dx = atoi(argv[5]);
	} 
	if (argc > 6) {
		dy = atoi(argv[6]);
	}
	if (argc > 7) {
		mirror = atoi(argv[7]);
	} 
	if (argc > 8) {
		rotate = atof(argv[8]);
		rotateRad = (rotate/360.0)*2.0*M_PI;
	}

	/* read in the images */
	image1 = readPPM(&rows1, &cols1, &colors1, argv[1]);
	image2 = readPPM(&rows2, &cols2, &colors2, argv[2]);
	imageM = readPPM(&rowsMask, &colsMask, &colorsMask, argv[3]);
	if(!image1) {
		fprintf(stderr, "Unable to read %s\n", argv[1]);
		exit(-1);
	} else if(!image2) {
		fprintf(stderr, "Unable to read %s\n", argv[2]);
		exit(-1);
	} else if(!imageM) {
		fprintf(stderr, "Unable to read %s\n", argv[3]);
		exit(-1);
	}

	//for(rotateRad=0;rotateRad<=2.0*M_PI;rotateRad=rotateRad+M_PI/6.0) {
	/* loops over the entire foreground image
	* overwriting the background pixel values with the alpha blending
	* of the foreground image and the background using the mask */
	bi = bj = fi = fj = fx = fy = fxr = fyr = 0;
	for(i=0;i<rows2-1;i++) {
		for(j=0;j<cols2-1;j++) {

			// perform transformations if specified on command line
			if(mirror){

				// flip x and y
				bi = j;
				bj = i;
			} else if(rotate) {

				// define the coordinates centered on foreground
				fx = j - ((cols2 - 1) / 2);
				fy = i - ((rows2 - 1) / 2);

				// rotate about the center of the foreground image
				fxr = cos(rotateRad)*fx + sin(rotateRad)*fy;
				fyr = -sin(rotateRad)*fx + cos(rotateRad)*fy;

				// transform back to coordinates centered at top left
				bi = fyr + ((rows2 - 1) / 2);
				bj = fxr + ((cols2 - 1) / 2);
			} else {

				// default normal behaviour
				bi = i;
				bj = j;
			}

			// apply offset if any to the destination pixel in background
			bi = bi + dy;
			bj = bj + dx;

			// test if the offset puts the index outside of the boundaries
			// of the background image, dx and dy can be negative
			if( 	(bi < 0 || bi > rows1-1) || 
					(bj < 0 || bj > cols1-1) ) {
				continue;
			}

			// assign separate index values to offset foreground and mask
			backgroundIndex = (bi) * cols1 + (bj);
			foregroundIndex = i * cols1 + j;

			// alpha blend two inputs using mask
			alphaR = (float)imageM[foregroundIndex].r / 255.0;
			alphaG = (float)imageM[foregroundIndex].g / 255.0;
			alphaB = (float)imageM[foregroundIndex].b / 255.0;
			image1[backgroundIndex].r = alphaR*image1[backgroundIndex].r + 
										(1-alphaR)*image2[foregroundIndex].r;
			image1[backgroundIndex].g = alphaG*image1[backgroundIndex].g +
										(1-alphaG)*image2[foregroundIndex].g;
			image1[backgroundIndex].b = alphaB*image1[backgroundIndex].b +
										(1-alphaB)*image2[foregroundIndex].b;
		}
	}

	/* write out the resulting image */
	writePPM(image1, rows1, cols1, colors1 /* s/b 255 */, argv[4]);
	//}
	/* free the image memory */
	#if USECPP
	delete[] image1;
	delete[] image2;
	delete[] imageM;
	#else
	free(image1);
	free(image2);
	free(imageM);
	#endif

	return(0);
}
