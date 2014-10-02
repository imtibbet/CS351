/*
  Bruce A. Maxwell
  Fall 2014

  Test function 1 for the graphics primitives assignment
  Enterpoop
 */

// edit the include files as necessary
#include "graphics.h"

// draw a few boxes, a circle, and some lines.
int main(int argc, char *argv[]) {
  Image *src;
  Color White;
  Color Red;
  Color Blue;
  Color Green;
  Line line;

  color_set( &White, 1.0, 1.0, 1.0 );
  color_set( &Red, 0.9, 0.05, 0.05 );
  color_set( &Blue, 0.05, 0.05, 0.9 );
  color_set( &Green, 0.05, 0.9, 0.05 );

  src = image_create( 600, 600 );

  line_set2D( &line, 300, 300, 400, 300);
  line_draw( &line, src, White );

  line_set2D( &line, 300, 300, 400, 400);
  line_draw( &line, src, Blue );

  line_set2D( &line, 300, 300, 300, 400);
  line_draw( &line, src, Red );

  line_set2D( &line, 300, 300, 200, 400);
  line_draw( &line, src, Green );

  line_set2D( &line, 300, 300, 200, 300);
  line_draw( &line, src, Blue );

  line_set2D( &line, 300, 300, 200, 200);
  line_draw( &line, src, Red );

  line_set2D( &line, 300, 300, 300, 200);
  line_draw( &line, src, Green );

  line_set2D( &line, 300, 300, 400, 200);
  line_draw( &line, src, White );
  
  image_write( src, "testLine.ppm" );

  image_free( src );

  return(0);
}
