/*
Author: Ian Tibbetts (Bruce Maxwell)
Date: 9/9/2014

Use some kind of test to read in the blue/green screen image and create and write out a mask that is 1 for the blue/green background and 0 for the foreground. Make this a command line program. 
*/

#include <stdio.h>
#include <stdlib.h>
#include "ppmIO.h"

#define USECPP 0

int main(int argc, char *argv[]) {
  Pixel *image;
  int rows, cols, colors;
  long imagesize;
  long i;

  if(argc < 3) {
    printf("Usage: lab1 <input file> <output file>\n");
    exit(-1);
  }

  /* read in the image */
  image = readPPM(&rows, &cols, &colors, argv[1]);
  if(!image) {
    fprintf(stderr, "Unable to read %s\n", argv[1]);
    exit(-1);
  }

  /* calculate the image size */
  imagesize = (long)rows * (long)cols;

  /* mess with the image here  */
  for(i=0;i<imagesize;i++) {

    // invert image
    /*image[i].r = 255 - image[i].r;
    image[i].g = 255 - image[i].g;
    image[i].b = 255 - image[i].b;*/

    // define mask using the ratio of green to blue and red
    // mask has white where green is found (background) and black elsewhere (foreground)
    if(	(((float)image[i].g/(float)image[i].b) > 1.2) &&
    	(((float)image[i].g/(float)image[i].r) > 1.1) ) {
	image[i].r = 255;
	image[i].g = 255;
	image[i].b = 255;
    } else {
	image[i].r = 0;
	image[i].g = 0;
	image[i].b = 0;
    }
  }

  /* write out the resulting image */
  writePPM(image, rows, cols, colors /* s/b 255 */, argv[2]);

  /* free the image memory */
#if USECPP
  delete[] image;
#else
  free(image);
#endif

  return(0);
}
