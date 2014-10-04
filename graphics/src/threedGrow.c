/*
  Ian Tibbetts (Bruce A. Maxwell)
  Fall 2014

  Creative required 3D image
 */

#include "graphics.h"

// draw a flower
static int flower( Image *src, Color stemColor, Color pedalColor, Color centerColor, 
					double pedalLength, double x0, double y0 , double x, double y);
static int flower( Image *src, Color stemColor, Color pedalColor, Color centerColor, 
					double pedalLength, double x0, double y0 , double x, double y ) {
	Polygon pedal;
	Point p;
	Line stem;
	Circle circ;
	int i;
	int numPedals = 18;
	double curRadAngle;
	Point pedalPoints[3];
	
	// draw stem
	line_set2D( &stem, x0, y0, x, y );
	line_draw( &stem, src, stemColor );

	// draw pedals
	for(i=0;i<numPedals;i++) {
		curRadAngle = i*2*M_PI/((double)numPedals);
		point_set2D( &(pedalPoints[0]), x, y );
		point_set2D( &(pedalPoints[1]), x+0.5*pedalLength*cos(curRadAngle+M_PI/6.0), 
										y+0.5*pedalLength*sin(curRadAngle+M_PI/6.0));
		point_set2D( &(pedalPoints[2]), x+pedalLength*cos(curRadAngle), 
										y+pedalLength*sin(curRadAngle) );
		polygon_init( &(pedal) );
		polygon_set( &(pedal), 3, &(pedalPoints[0]) );
		color_set( &(pedalColor), drand48(), drand48(), drand48() );
		polygon_drawFillB( &(pedal), src, pedalColor );
	}
	polygon_clear(&pedal);
	
	// draw center
	point_set2D( &p, x, y );
	circle_set( &circ, p, pedalLength/3.0 );
	circle_drawFill( &circ, src, centerColor );
	return(0);
}

// draw flowers growing
int main(int argc, char *argv[]) {
	Image src;
	Color White;
	Color Brown;
	Color Red;
	Color Green;
	Color Blue;
	Color Black;
	Color Yellow;
	Point p;
	Ellipse e;
	int i, frame, frames;
	char filename[100];
	
	color_set( &White, 1.0, 1.0, 1.0 );
	color_set( &Brown, 0.647059, 0.164706, 0.164706 );
	color_set( &Yellow, 0.9, 0.9, 0.4 );
	color_set( &Green, 0.2, 0.6, 0.2 );
	color_set( &Black, 0.0, 0.0, 0.0 );
	color_set( &Blue, 0.05, 0.05, 0.9 );
	color_set( &Red, 0.9, 0.05, 0.05 );

	image_init( &src );
	
	frames = 50;
	image_alloc( &src, 600, 400 );
	
	// growing up
	for(frame=0;frame<frames;frame++){
		image_reset(&src);
		//draw cone
		point_set2D( &p, 200, 500-40*5 );
		ellipse_set( &e, p, 2+2*40, 1+1*40 );
		ellipse_drawFill( &e, &src, Green );
		for(i=1;i<=40;i++){
			point_set2D( &p, 200, 500-i*5 );
			ellipse_set( &e, p, 2+2*i, 1+1*i );
			ellipse_drawquad( &e, &src, Brown, 1, 2 );
		}
		for(i=1;i<=40;i+=2){
			floodfill(&src, Green, Brown, 200, 500-i*4);
		}
	
		// draw flowers
		flower(&src, Brown, Yellow, Brown, 10+2*frame, 150, 300, 150-2*frame, 300-5*frame);
		flower(&src, Brown, Yellow, Brown, 10+2*frame, 200, 300, 200, 300-5*frame);
		flower(&src, Brown, Yellow, Brown, 10+2*frame, 250, 300, 250+2*frame, 300-5*frame);
	
		sprintf(filename,"%03dthreedGrow.ppm",frame);
		image_write( &src, filename );
	}	
	
	// shrinking back down to give continuous loop
	for(frame=48;frame>-1;frame--){
		image_reset(&src);
		//draw cone
		point_set2D( &p, 200, 500-40*5 );
		ellipse_set( &e, p, 2+2*40, 1+1*40 );
		ellipse_drawFill( &e, &src, Green );
		for(i=1;i<=40;i++){
			point_set2D( &p, 200, 500-i*5 );
			ellipse_set( &e, p, 2+2*i, 1+1*i );
			ellipse_drawquad( &e, &src, Brown, 1, 2 );
		}
		for(i=1;i<=40;i+=2){
			floodfill(&src, Green, Brown, 200, 500-i*4);
		}
	
		// draw flowers
		flower(&src, Brown, Yellow, Brown, 10+2*frame, 150, 300, 150-2*frame, 300-5*frame);
		flower(&src, Brown, Yellow, Brown, 10+2*frame, 200, 300, 200, 300-5*frame);
		flower(&src, Brown, Yellow, Brown, 10+2*frame, 250, 300, 250+2*frame, 300-5*frame);
	
		sprintf(filename,"%03dthreedGrow.ppm",100-frame);
		image_write( &src, filename );
	}
	
	// clean up
	image_dealloc( &src );
	printf("converting to gif...\n");
	system("convert -delay 10 -loop 0 *threedGrow.ppm threedGrow.gif");
	system("rm *threedGrow.ppm");
	system("animate threedGrow.gif");
	return(0);
}
