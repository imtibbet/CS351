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

/*
 * Copy the point data structure. 
 */
void point_copy(Point *to, Point *from){
	*to = *from;
}

/*
 * Draw the point into src using Color c. 
 */
void point_draw(Point *p, Image *src, Color c){
	image_setColor( src, p->val[1], p->val[0], c );
}

/*
 * Draw the p into src using FPixel c. 
 */
void point_drawf(Point *p, Image *src, FPixel c){
	image_setf(src, p->val[1], p->val[0], c);
}

// LINE

/*
 * Initialize a 2D line. 
 */
void line_set2D(Line *l, double x0, double y0, double x1, double y1){
	Point a;
	Point b;
	point_set2D(&a, x0, y0);
	point_set2D(&b, x1, y1);

	l->a = a;
	l->b = b;
}

/*
 * Initialze a line to ta and tb. 
 */
void line_set(Line *l, Point ta, Point tb){
	l->a = ta;
	l->b = tb;
}

/*
 * Set the z-buffer flag to the given value. 
 */
void line_zBuffer(Line *l, int flag){
	l->zBuffer = flag;
}

/*
 * Copy the line data structure. 
 */
void line_copy(Line *to, Line *from){
	*to = *from;
}

/*
 * Draw the line into src using Color c 
 */
void line_draw(Line *l, Image *src, Color c){
	
	// Bresenham's line-drawing algorithm
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
			//printf("horizontal line drawn\n");
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
		//printf("right half line drawn\n");
	}
	// 3rd and 4th octants (left half)
	else if(dx<0){

		if(dy==0){
			while(x!=x1){
				point_set2D(&curp, (double)x, (double)y);
				point_draw(&curp, src, c);
				x--;
			}
			//printf("horizontal line drawn\n");
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
		//printf("left half line drawn\n");
	}
	// special case of vertical lines
	else {//dx==0
		while(y!=y1){
			point_set2D(&curp, (double)x, (double)y);
			point_draw(&curp, src, c);
			y++;
		}
		//printf("vertical line drawn\n");
	}
}

// CIRCLE

/*
 * Initialize to center tc and radius tr. 
 */
void circle_set(Circle *c, Point tc, double tr){
	c->r = tr;
	c->c = tc;
}

/*
 * Draw the circle into src using color c. 
 */
void circle_draw(Circle *circ, Image *src, Color c){

	// template connected with the Hearn and Baker textbook
	int xCenter = (int)(circ->c.val[0]);
	int yCenter = (int)(circ->c.val[1]);
	int tr = (int)(circ->r);
	int x = -1;
	int y = -tr;
	int p = 1 - tr;

	// draw the edge cases not handled by the algorithm b/cause x=-1
	image_setColor(src, yCenter + tr, xCenter + 0, c);
	image_setColor(src, yCenter + 0, xCenter + tr, c);
	image_setColor(src, yCenter - tr, xCenter - 0, c);
	image_setColor(src, yCenter - 0, xCenter - tr, c);

	// circle draw here - plot first set of points
	image_setColor(src, yCenter + y, xCenter + x, c);
	image_setColor(src, yCenter - y, xCenter + x, c);
	image_setColor(src, yCenter + y, xCenter - x, c);
	image_setColor(src, yCenter - y, xCenter - x, c);
	image_setColor(src, yCenter + x, xCenter + y, c);
	image_setColor(src, yCenter - x, xCenter + y, c);
	image_setColor(src, yCenter + x, xCenter - y, c);
	image_setColor(src, yCenter - x, xCenter - y, c);

	// sixth octant
	while(x>y){
		x--;
		if(p<0)
			p += 1 - 2*x;
		else{
			y++;
			p += 1 - 2*(x-y);
		}

		// draw in all 8 octants
		image_setColor(src, yCenter + y, xCenter + x, c);
		image_setColor(src, yCenter - y, xCenter + x, c);
		image_setColor(src, yCenter + y, xCenter - x, c);
		image_setColor(src, yCenter - y, xCenter - x, c);
		image_setColor(src, yCenter + x, xCenter + y, c);
		image_setColor(src, yCenter - x, xCenter + y, c);
		image_setColor(src, yCenter + x, xCenter - y, c);
		image_setColor(src, yCenter - x, xCenter - y, c);
	}
}

/*
 * Draw a filled circled into src using color c. 
 */
void circle_drawFill(Circle *circ, Image *src, Color c){

	// template connected with the Hearn and Baker textbook
	int xCenter = (int)(circ->c.val[0]);
	int yCenter = (int)(circ->c.val[1]);
	int tr = (int)(circ->r);
	int x = -1;
	int y = -tr;
	int p = 1 - tr;
	int curx;

	// draw the edge cases not handled by the algorithm b/cause x=-1
	image_setColor(src, yCenter + tr, xCenter + 0, c);
	image_setColor(src, yCenter - tr, xCenter - 0, c);
	//middle line
	curx = -tr;
	while(curx!=tr){
		image_setColor(src, yCenter, xCenter + curx, c);
		curx++;
	}

	// circle draw here - plot first set of lines
	// line above bottom
	curx = x;
	while(curx!=-x){
		image_setColor(src, yCenter + y, xCenter + curx, c);
		curx++;
	}
	// line below top
	curx = x;
	while(curx!=-x){
		image_setColor(src, yCenter - y, xCenter + curx, c);
		curx++;
	}
	// line below middle
	curx = y;
	while(curx!=-y){
		image_setColor(src, yCenter + x, xCenter + curx, c);
		curx++;
	}
	// line above middle
	curx = y;
	while(curx!=-y){
		image_setColor(src, yCenter - x, xCenter + curx, c);
		curx++;
	}

	// sixth octant
	while(x>y){
		x--;
		if(p<0)
			p += 1 - 2*x;
		else{
			y++;
			p += 1 - 2*(x-y);
		}

		// draw in all 8 octants
		// line above bottom
		curx = x;
		while(curx!=-x){
			image_setColor(src, yCenter + y, xCenter + curx, c);
			curx++;
		}
		// line below top
		curx = x;
		while(curx!=-x){
			image_setColor(src, yCenter - y, xCenter + curx, c);
			curx++;
		}
		// line below middle
		curx = y;
		while(curx!=-y){
			image_setColor(src, yCenter + x, xCenter + curx, c);
			curx++;
		}
		// line above middle
		curx = y;
		while(curx!=-y){
			image_setColor(src, yCenter - x, xCenter + curx, c);
			curx++;
		}
	}
}

// ELLIPSE

/*
 * Initialize an ellipse to location tc and radii ta and tb. 
 */
void ellipse_set(Ellipse *e, Point tc, double ta, double tb){
	e->ra = ta;
	e->rb = tb;
	e->c = tc;
	e->a = 0.0;
}

/*
 * Draw a filled ellipse into src using color c.
 */
void ellipse_draw(Ellipse *e, Image *src, Color c){

	// template connected with the Hearn and Baker textbook
	int xCenter = (int)(e->c.val[0]);
	int yCenter = (int)(e->c.val[1]);
	int Rx = (int)(e->ra);
	int Ry = (int)(e->rb);
	int Rx2 = Rx*Rx;
	int Ry2 = Ry*Ry;
	int twoRx2 = 2*Rx2;
	int twoRy2 = 2*Ry2;
	int p;
	int x = -1;
	int y = -Ry;
	int px = twoRy2;
	int py = twoRx2 * (-y);

	// draw the edge cases not handled by the algorithm b/cause x=-1
	image_setColor(src, yCenter + Ry, xCenter + 0, c);
	image_setColor(src, yCenter + 0, xCenter + Rx, c);
	image_setColor(src, yCenter - Ry, xCenter - 0, c);
	image_setColor(src, yCenter - 0, xCenter - Rx, c);
	
	/* Plot the first set of points */
	image_setColor(src, yCenter + y, xCenter + x, c);
	image_setColor(src, yCenter + y, xCenter - x, c);
	image_setColor(src, yCenter - y, xCenter + x, c);
	image_setColor(src, yCenter - y, xCenter - x, c);

	/* Region 1 */
	p = (int)( (Ry2 - (Rx2 * Ry) + (0.25 * Rx2)) + Ry2 + px + 0.5 );
	while (px < py) {
		x--;
		px += twoRy2;
		if (p < 0)
			p += Ry2 + px;
		else {
			y++;
			py -= twoRx2;
			p += Ry2 + px - py;
		}
		image_setColor(src, yCenter + y, xCenter + x, c);
		image_setColor(src, yCenter - y, xCenter + x, c);
		image_setColor(src, yCenter + y, xCenter - x, c);
		image_setColor(src, yCenter - y, xCenter - x, c);
	}

	/* Region 2 */
	p = (int)( (Ry2*(x+0.5)*(x+0.5) + Rx2*(y-1)*(y-1) - Rx2*Ry2) + (Rx2 - py) + 0.5 );
	while (y < 0) {
		y++;
		py -= twoRx2;
		if (p > 0) 
			p += Rx2 - py;
		else {
			x--;
			px += twoRy2;
			p += Rx2 - py + px;
		}
		image_setColor(src, yCenter + y, xCenter + x, c);
		image_setColor(src, yCenter - y, xCenter + x, c);
		image_setColor(src, yCenter + y, xCenter - x, c);
		image_setColor(src, yCenter - y, xCenter - x, c);
	}
}

/*
 * Draw into src using color c. 
 */
void ellipse_drawFill(Ellipse *e, Image *src, Color c){

	// template connected with the Hearn and Baker textbook
	int xCenter = (int)(e->c.val[0]);
	int yCenter = (int)(e->c.val[1]);
	int Rx = (int)(e->ra);
	int Ry = (int)(e->rb);
	int Rx2 = Rx*Rx;
	int Ry2 = Ry*Ry;
	int twoRx2 = 2*Rx2;
	int twoRy2 = 2*Ry2;
	int p;
	int x = -1;
	int y = -Ry;
	int px = twoRy2;
	int py = twoRx2 * (-y);
	int curx;

	// draw the edge cases not handled by the algorithm b/cause x=-1
	image_setColor(src, yCenter + Ry, xCenter + 0, c);
	image_setColor(src, yCenter - Ry, xCenter - 0, c);
	//middle line
	curx = -Rx;
	while(curx!=Rx){
		image_setColor(src, yCenter, xCenter + curx, c);
		curx++;
	}

	// circle draw here - plot first set of lines
	// line above bottom
	curx = x;
	while(curx!=-x){
		image_setColor(src, yCenter + y, xCenter + curx, c);
		curx++;
	}
	// line below top
	curx = x;
	while(curx!=-x){
		image_setColor(src, yCenter - y, xCenter + curx, c);
		curx++;
	}

	/* Region 1 */
	p = (int)( (Ry2 - (Rx2 * Ry) + (0.25 * Rx2)) + Ry2 + px + 0.5 );
	while (px < py) {
		x--;
		px += twoRy2;
		if (p < 0)
			p += Ry2 + px;
		else {
			y++;
			py -= twoRx2;
			p += Ry2 + px - py;
		}
		
		// plot two lines
		// line above bottom
		curx = x;
		while(curx!=-x){
			image_setColor(src, yCenter + y, xCenter + curx, c);
			curx++;
		}
		// line below top
		curx = x;
		while(curx!=-x){
			image_setColor(src, yCenter - y, xCenter + curx, c);
			curx++;
		}
	}

	/* Region 2 */
	p = (int)( (Ry2*(x+0.5)*(x+0.5) + Rx2*(y-1)*(y-1) - Rx2*Ry2) + (Rx2 - py) + 0.5 );
	while (y < 0) {
		y++;
		py -= twoRx2;
		if (p > 0) 
			p += Rx2 - py;
		else {
			x--;
			px += twoRy2;
			p += Rx2 - py + px;
		}
		
		// plot two lines
		// line above bottom
		curx = x;
		while(curx!=-x){
			image_setColor(src, yCenter + y, xCenter + curx, c);
			curx++;
		}
		// line below top
		curx = x;
		while(curx!=-x){
			image_setColor(src, yCenter - y, xCenter + curx, c);
			curx++;
		}
	}
}

// POLYLINE

// The functions polyline_create and polyline_free manage both the Polyline data
//  structure and the memory required for the vertex list

/* 
 * Returns an allocated Polyline pointer initialized so that 
 * numVertex is 0 and vertex is NULL. 
 */
Polyline *polyline_create(int x){
	Polyline *p;
	
	// get space for the polyline
	p = malloc(sizeof(Polyline));
	if(!p){
		return(NULL);
	}
	
	// initialize structure
	p->zBuffer = x;
	p->numVertex = 0;
	p->vertex = NULL;	
	
	// return pointer
	return(p);
}

/* 
 * Returns an allocated Polyline pointer with the vertex list initialized 
 * to the points in vlist. 
 */
Polyline *polyline_createp(int numV, Point *vlist){

	Polyline *p;
	int i;
	
	// make sure that numV and vlist match well enough
	if( sizeof(vlist) < (sizeof(Point) * numV) ){
		printf("vlist passed to polyline_createp has fewer Points than numV\n");
		return(NULL); 
	}
	
	// get space for the polyline
	p = malloc(sizeof(Polyline));
	if(!p){
		return(NULL);
	}
	
	// get space for the vertex list
	p->vertex = malloc(sizeof(Point) * numV);
	if(!p->vertex){
		free(p);
		return(NULL);
	}
	
	// initialize structure
	p->zBuffer = 1;
	p->numVertex = numV;
	for(i=0;i<numV;i++){
		p->vertex[i] = vlist[i];
	}
	
	// return pointer
	return(p);
}

/* 
 * Frees the internal data and the Polyline pointer. 
 */
void polyline_free(Polyline *p){

	if(p){
		if(p->vertex){
			free(p->vertex);
		}
		free(p);
	} else {
		printf("null p passed to polyline_free\n");
	}
}

// The functions polyline_init, polyline_set, and polyline_clear work on a pre-
// existing Polyline data structure and manage only the memory required for the 
// vertex list

/* 
 * Initializes the pre-existing Polyline to an empty Polyline. 
 */
void polyline_init(Polyline *p){

	// detect null pointer passed
	if(!p){
		printf("null p passed to polyline_init\n");
		return;
	}
	
	// free existing vertex list
	if(p->vertex){
		free(p->vertex);
	}
	
	// reset structure
	p->zBuffer = 1;
	p->numVertex = 0;
	p->vertex = NULL;
}

/* Initializes the vertex list to the points in vlist. De-allocates/allocates
 * the vertex list for p, as necessary. 
 */
void polyline_set(Polyline *p, int numV, Point *vlist){
	
	// make sure that numV and vlist match well enough
	if( sizeof(vlist) < (sizeof(Point) * numV) ){
		printf("vlist passed to polyline_set has fewer Points than numV\n");
		return; 
	}
	
	// detect null pointer passed
	if(!p){
		printf("null p passed to polyline_set\n");
		return;
	}	
	
	// free existing vertex list
	if(p->vertex){
		free(p->vertex);
	}
	
	// get space for the vertex list
	p->vertex = malloc(sizeof(Point) * numV);
	if(!p->vertex){
		return(NULL);
	}
	
	// initialize structure
	p->zBuffer = 1;
	p->numVertex = numV;
	for(i=0;i<numV;i++){
		p->vertex[i] = vlist[i];
	}
}

/* 
 * Frees the internal data for a Polyline, if necessary, and sets numVertex
 * to 0 and vertex to NULL. 
 */
void polyline_clear(Polyline *p){

	// detect null pointer passed
	if(!p){
		printf("null p passed to polyline_clear\n");
		return;
	}
	
	// free internal data
	if(p->vertex){
		free(p->vertex);
	}
	
	// reset structure
	p->numVertex = 0;
	p->vertex = NULL;
}

/* 
 * Sets the z-buffer flag to the given value. 
 */
void polyline_zBuffer(Polyline *p, int flag){

	// detect null pointer passed
	if(!p){
		printf("null p passed to polyline_zBuffer\n");
		return;
	}

	p->zBuffer = flag;
}

/* 
 * De-allocates/allocates space as necessary in the destination Polyline data
 * structure and copies the vertex data from the source polyline (from) to the 
 * destination (to). 
 */
void polyline_copy (Polyline *to, Polyline *from){

	// detect null pointer passed
	if(!to){
		printf("null to passed to polyline_copy\n");
		return;
	}
	if(!from){
		printf("null from passed to polyline_copy\n");
		return;
	}
	
	// free internal data in destination
	if(to->vertex){
		free(to->vertex);
	}
	
	// allocate new destination space
	to->vertex = malloc( sizeof(Point) * from->numVertex) );
	if(!to->vertex){
		return;
	}
	
	// make sure the source polyline is correctly set up
	if( sizeof(from->vertex) < (sizeof(Point) * from->numVertex) ){
		printf("vertex list of source polyline has fewer Points than its own numVertex\n");
		return; 
	}
	
	// copy the points to destination
	to->numVertex = from->numVertex;
	for(i=0;i<(to->numVertex);i++){
		to->vertex[i] = from->vertex[i];
	}
}

/* 
 * Prints Polyline data to the stream designated by the FILE pointer. 
 */
void polyline_print(Polyline *p, FILE *fp){
	int i;

	if(p){
		if(!p->vertex){
			return;
		}
	} else{
		return;
	}	

	// make sure the source polyline is correctly set up
	if( sizeof(p->vertex) < (sizeof(Point) * p->numVertex) ){
		printf("vertex list of source polyline has fewer Points than its own numVertex\n");
		return; 
	}

	// print polyline points as x,y pairs
	fprintf(fp, "about to print polyline points\n")
	for(i = 0; i<(p->numVertex); i++){
		fprintf(fp,"x:%f, y:%f\n", p->vertex[i].val[0], p->vertex[i].val[1]);
	}
}

/* 
 * Draw the Polyline using color c. 
 */
void polyline_draw(Polyline *p, Image *src, Color c){
	int i;
	Line *l;

	if(p){
		if(!p->vertex){
			return;
		}
	} else{
		return;
	}

	// make sure the source polyline is correctly set up
	if( sizeof(p->vertex) < (sizeof(Point) * p->numVertex) ){
		printf("vertex list of source polyline has fewer Points than its own numVertex\n");
		return; 
	}

	if (p->numVertex < 2){
		printf("can't draw a polyline with less than two points\n")
	}

	// iterate through polyline
	for(i=0; i<(p->numVertex-1); i++){
		// take coordinates for polyline point
		// create a line
		line_set(l, p->vertex[i], p->vertex[i +1]);
		// draw line on src using Color c
		line_draw(l, src, c);
	}


}
