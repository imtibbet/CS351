/*
  Bruce A. Maxwell
  Fall 2013

  Creates a Mandelbrot set at a selected location
*/
#include "image.h"
#include "fractals.h"

int main(int argc, char *argv[]) {
  Image *src;
  
  src = image_create(750, 1000);
  //src = image_read("1view.ppm");

  mandelbrot( src, 1.755, -0.02, 0.02);
  //mandelbrot( src, -1.0, -1.0, 3.0);
  //julia( src, -2.0, -2.0, 4.0);
  //image_noise( src, 50);
  
  image_write( src, "fractal.ppm");

  image_free( src );

  return(0);
}
