/*
 * Author: Ian Tibbetts and Astrid Moore
 * Date: 9/22/14
 *
 * The color function implementations
 */

#include "graphics.h"

// POINT

/* 
 * Sets the first two values of the vector to x and y. 
 * Sets the third value to 0.0 and the fourth value to 1.0 
 */
void point_set2D(Point *p, double x, double y){
	p->val[0] = x;
	p->val[1] = y;
	p->val[2] = 0.0;
	p->val[3] = 1.0;
}

/*
 * Set the point's values to x and y and z. 
 * Sets the homogeneous coordinate to 1.0 
 */
void point_set3D(Point *p, double x, double y, double z){
	p->val[0] = x;
	p->val[1] = y;
	p->val[2] = z;
	p->val[3] = 1.0;
}

/*
 * Set the four values of the vector to x, y, z, and h, respectively. 
 */
void point_set(Point *p, double x, double y, double z, double h){
	p->val[0] = x;
	p->val[1] = y;
	p->val[2] = z;
	p->val[3] = h;
}

/** Copy the point data structure. **/
void point_copy(Point *to, Point *from){
	to->val[0] = from->val[0];
	to->val[1] = from->val[1];
	to->val[2] = from->val[2];
	to->val[3] = from->val[3];
}

/** Draw the point into src using Color c. **/
void point_draw(Point *p, Image *src, Color c){
	image_setColor( src, p->val[1], p->val[0], c );
}

/** Draw the p into src using FPixel c. **/
void point_drawf(Point *p, Image *src, FPixel c){
	image_setf(src, p->val[1], p->val[0], c);
}

// LINE

/** Initialize a 2D line. **/
void line_set2D(Line *l, double x0, double y0, double x1, double y1){
	Point a;
	Point b;
	point_set2D(&a, x0, y0);
	point_set2D(&b, x1, y1);

	l->a = a;
	l->b = b;
}

/** Initialze a line to ta and tb. **/
void line_set(Line *l, Point ta, Point tb){
	l->a = ta;
	l->b = tb;
}

/** Set the z-buffer flag to the given value. **/
void line_zBuffer(Line *l, int flag){
	l->zBuffer = flag;
}

/** Copy the line data structure. **/
void line_copy(Line *to, Line *from){
	to->zBuffer = from->zBuffer;
	point_copy(&(to->a), &(from->a));
	point_copy(&(to->b), &(from->b));
}

/** Draw the line into src using Color c. **/
void line_draw(Line *l, Image *src, Color c){
	int x0, y0, x1, y1;
	int x, y, dx, dy, e, i;
	Point curp;

	x = x0 = l->a.val[0];
	y = y0 = l->a.val[1];
	x1 = l->b.val[0];
	y1 = l->b.val[1];

	dx = x1 - x0;
	dy = y1 - y0;

	if(dy<0){
		x = x0 = l->b.val[0];
		y = y0 = l->b.val[1];
		x1 = l->a.val[0];
		y1 = l->a.val[1];

		dx = x1 - x0;
		dy = y1 - y0;
	}
	
	e = 3*dy-2*dx;

	// 1st and 2nd octants (right half)
	if(dx>0) {

		if(dy==0){
			while(x!=x1){
				point_set2D(&curp, (double)x, (double)y);
				point_draw(&curp, src, c);
				x++;
			}
			printf("horizontal line drawn\n");
			return;
		}

		// 1st octant
		if(dx>=dy) {
			for(i=0; i<=dx; i++){
				point_set2D(&curp, (double)x, (double)y);
				point_draw(&curp, src, c);
				if(e>0){
					y++;
					e-=(2*dx);
				}
				x++;
				e+=(2*dy);
			}
		}
		// 2nd octant
		else if(dy>dx){
			for(i=0; i<=dy; i++){
				point_set2D(&curp, (double)x, (double)y);
				point_draw(&curp, src, c);
				if(e>0){
					x++;
					e-=(2*dy);
				}
				y++;
				e+=(2*dx);
			} 
		}
		printf("right half line drawn\n");
	}
	// 3rd and 4th octants (left half)
	else if(dx<0){

		if(dy==0){
			while(x!=x1){
				point_set2D(&curp, (double)x, (double)y);
				point_draw(&curp, src, c);
				x--;
			}
			printf("horizontal line drawn\n");
			return;
		}

		// 4th octant
		if(dx>=dy) {
			for(i=0; i<=dx; i++){
				point_set2D(&curp, (double)x, (double)y);
				point_draw(&curp, src, c);
				if(e>0){
					y++;
					e-=(2*dx);
				}
				x--;
				e+=(2*dy);
			}
		}
		// 3rd octant
		else if(dy>dx){
			for(i=0; i<=dy; i++){
				point_set2D(&curp, (double)x, (double)y);
				point_draw(&curp, src, c);
				if(e>0){
					x--;
					e-=(2*dy);
				}
				y++;
				e+=(2*dx);
			} 
		}
		printf("left half line drawn\n");
	}
	// special case of vertical lines
	else {//dx==0
		while(y!=y1){
			point_set2D(&curp, (double)x, (double)y);
			point_draw(&curp, src, c);
			y++;
		}
		printf("vertical line drawn\n");
	}
}

// CIRCLE

/** Initialize to center tc and radius tr. **/
void circle_set(Circle *c, Point tc, double tr){}

/** Draw the circle into src using color p. **/
void circle_draw(Circle *c, Image *src, Color p){}

/** Draw a filled circled into src using color p. **/
void circle_drawFill(Circle *c, Image *src, Color p){}

// ELLIPSE

/** Initialize an ellipse to location tc and radii ta and tb. **/
void ellipse_set(Ellipse *e, Point tc, double ta, double tb){}

/** Draw into src using color p. **/
void ellipse_draw(Ellipse *e, Image *src, Color p){}

/** Draw a filled ellipse into src using color p. **/
void ellipse_drawFill(Ellipse *e, Image *src, Color p){}

// POLYLINE

/* Returns an allocated Polyline pointer initialized so that 
* numVertex is 0 and vertex is NULL. */
Polyline *polyline_create(int x){
	Polyline *p = NULL;
	return(p);
}

/* Returns an allocated Polyline pointer with the vertex list initialized 
* to the points in vlist. */
Polyline *polyline_createp(int numV, Point *vlist){
	Polyline *p = NULL;
	return(p);
}

/* Frees the internal data and the Polyline pointer. */
void polyline_free(Polyline *p){}

/* Initializes the pre-existing Polyline to an empty Polyline. */
void polyline_init(Polyline *p){}

/* Initializes the vertex list to the points in vlist. De-allocates/allocates
* the vertex list for p, as necessary. */
void polyline_set(Polyline *p, int numV, Point *vlist){}

/* Frees the internal data for a Polyline, if necessary, and sets numVertex
* to 0 and vertex to NULL. */
void polyline_clear(Polyline *p){}

/* Sets the z-buffer flag to the given value. */
void polyline_zBuffer(Polyline *p, int flag){}

/* De-allocates/allocates space as necessary in the destination Polyline data
* structure and copies the vertex data from the source polyline (from) to the 
* destination (to). */
void polyline_copy (Polyline *to, Polyline *from){}

/* Prints Polyline data to the stream designated by the FILE pointer. */
void polyline_print(Polyline *p, FILE *fp){}

/* Draw the Polyline using color c. */
void polyline_draw(Polyline *p, Image *src, Color c){}
