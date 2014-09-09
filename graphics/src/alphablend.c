/*
Author: Ian Tibbetts (Bruce Maxwell)
Date: 9/9/2014

Write a program that takes in two images and a mask image and merges the two images using the mask as an alpha mask. The alpha blending function is I = alpha*image1 + (1 - alpha)*image2. Note that you'll need to interpolate the 0-255 values in the mask to the range [0, 1].
*/

#include <stdio.h>
#include <stdlib.h>
#include "ppmIO.h"

#define USECPP 0

int main(int argc, char *argv[]) {
  Pixel *image1,*image2,*imageMask;
  int rows1, cols1, colors1;
  int rows2, cols2, colors2;
  int rowsMask, colsMask, colorsMask;
  float alphaR, alphaG, alphaB;
  long imagesize1, imagesize2, imagesizeMask;
  long i;

  if(argc < 5) {
    printf("Usage: alphablend <input file1> <input file2> <mask file> <output file1>\n");
    exit(-1);
  }

  /* read in the images */
  image1 = readPPM(&rows1, &cols1, &colors1, argv[1]);
  image2 = readPPM(&rows2, &cols2, &colors2, argv[2]);
  imageMask = readPPM(&rowsMask, &colsMask, &colorsMask, argv[3]);
  if(!image1) {
    fprintf(stderr, "Unable to read %s\n", argv[1]);
    exit(-1);
  } else if(!image2) {
    fprintf(stderr, "Unable to read %s\n", argv[2]);
    exit(-1);
  } else if(!imageMask) {
    fprintf(stderr, "Unable to read %s\n", argv[3]);
    exit(-1);
  }

  /* calculate the image size */
  imagesize1 = (long)rows1 * (long)cols1;
  imagesize2 = (long)rows2 * (long)cols2;
  imagesizeMask = (long)rowsMask * (long)colsMask;

  //TODO: this would be where the images would be resized for program

  /* mess with the image here  */
  for(i=0;i<imagesize1;i++) {

    // alpha blend two inputs using mask
    alphaR = (float)imageMask[i].r/255.0;
    alphaG = (float)imageMask[i].g/255.0;
    alphaB = (float)imageMask[i].b/255.0;
    image1[i].r = alphaR*image1[i].r + (1 - alphaR)*image2[i].r;
    image1[i].g = alphaG*image1[i].g + (1 - alphaG)*image2[i].g;
    image1[i].b = alphaB*image1[i].b + (1 - alphaB)*image2[i].b;
  }

  /* write out the resulting image */
  writePPM(image1, rows1, cols1, colors1 /* s/b 255 */, argv[4]);

  /* free the image memory */
#if USECPP
  delete[] image1;
  delete[] image2;
  delete[] imageMask;
#else
  free(image1);
  free(image2);
  free(imageMask);
#endif

  return(0);
}
