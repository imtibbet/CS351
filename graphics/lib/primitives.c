/*
 * Author: Ian Tibbetts and Astrid Moore
 * Date: 9/22/14
 *
 * The color function implementations
 */

#include "graphics.h"
const float epsilon = 0.000001;

// POINT

/* 
 * Sets the first two values of the vector to x and y. 
 * Sets the third value to 0.0 and the fourth value to 1.0 
 */
void point_set2D(Point *p, double x, double y){
	if(!p){
		return;
	}
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
	if(!p){
		return;
	}
	p->val[0] = x;
	p->val[1] = y;
	p->val[2] = z;
	p->val[3] = 1.0;
}

/*
 * Set the four values of the vector to x, y, z, and h, respectively. 
 */
void point_set(Point *p, double x, double y, double z, double h){
	if(!p){
		return;
	}
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
	if(!p){
		return;
	}
	image_setColor( src, p->val[1], p->val[0], c );
}

/*
 * Draw the p into src using FPixel c. 
 */
void point_drawf(Point *p, Image *src, FPixel c){
	if(!p){
		return;
	}
	
	image_setf(src, p->val[1], p->val[0], c);
}

// LINE

/*
 * Initialize a 2D line. 
 */
void line_set2D(Line *l, double x0, double y0, double x1, double y1){
	if(!l){
		return;
	}

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
	if(!l){
		return;
	}
	
	l->a = ta;
	l->b = tb;
}

/*
 * Set the z-buffer flag to the given value. 
 */
void line_zBuffer(Line *l, int flag){
	if(!l){
		return;
	}
	
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
	if(!l){
		return;
	}
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
		dx=-dx;
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
	}
	// special case of vertical lines
	else {//dx==0
		while(y!=y1){
			point_set2D(&curp, (double)x, (double)y);
			point_draw(&curp, src, c);
			y++;
		}
	}
}

// CIRCLE

/*
 * Initialize to center tc and radius tr. 
 */
void circle_set(Circle *c, Point tc, double tr){
	if(!c){
		return;
	}
	c->r = tr;
	c->c = tc;
}

/*
 * Draw the circle into src using color c. 
 */
void circle_draw(Circle *circ, Image *src, Color c){
	circle_drawoct(circ, src, c, 1, 8);
}

/*
 * Draw a filled circled into src using color c. 
 */
void circle_drawFill(Circle *circ, Image *src, Color c){
	if(!circ){
		return;
	}

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
	while(curx!=tr)
		image_setColor(src, yCenter, xCenter + curx++, c);

	// circle draw here - plot first set of lines
	// line above bottom
	curx = x;
	while(curx!=-x)
		image_setColor(src, yCenter + y, xCenter + curx++, c);
	// line below top
	curx = x;
	while(curx!=-x)
		image_setColor(src, yCenter - y, xCenter + curx++, c);
	// line below middle
	curx = y;
	while(curx!=-y)
		image_setColor(src, yCenter + x, xCenter + curx++, c);
	// line above middle
	curx = y;
	while(curx!=-y)
		image_setColor(src, yCenter - x, xCenter + curx++, c);

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
		while(curx!=-x)
			image_setColor(src, yCenter + y, xCenter + curx++, c);
		// line below top
		curx = x;
		while(curx!=-x)
			image_setColor(src, yCenter - y, xCenter + curx++, c);
		// line below middle
		curx = y;
		while(curx!=-y)
			image_setColor(src, yCenter + x, xCenter + curx++, c);
		// line above middle
		curx = y;
		while(curx!=-y)
			image_setColor(src, yCenter - x, xCenter + curx++, c);
	}
}

/*
 * Draw the specified octant range of a circle into src using color c. 
 */
void circle_drawoct(Circle *circ, Image *src, Color c, int startOct, int endOct){
	if( (startOct<1) || (endOct>8) || (endOct<startOct) ){
		printf("bad start and end octant, must be between 1 and 8\n");
		return;
	}
	
	if(!circ){
		return;
	}

	// template connected with the Hearn and Baker textbook
	int xCenter = (int)(circ->c.val[0]);
	int yCenter = (int)(circ->c.val[1]);
	int tr = (int)(circ->r);
	int x = -1;
	int y = -tr;
	int p = 1 - tr;

	// draw the edge cases not handled by the algorithm b/cause x=-1
	if( (startOct==1) || (endOct==1) )
		image_setColor(src, yCenter + 0, xCenter + tr, c);
	if( (startOct<4) && (endOct>1) )
		image_setColor(src, yCenter + tr, xCenter + 0, c);
	if( (startOct<6) && (endOct>3) )
		image_setColor(src, yCenter - 0, xCenter - tr, c);
	if( (startOct<8) && (endOct>5) )
		image_setColor(src, yCenter - tr, xCenter - 0, c);

	// circle draw here - plot first set of points
	if( (startOct<7) && (endOct>5) )
		image_setColor(src, yCenter + y, xCenter + x, c); // sixth
	if( (startOct<4) && (endOct>2) )
		image_setColor(src, yCenter - y, xCenter + x, c); // third
	if( (startOct<8) && (endOct>6) )
		image_setColor(src, yCenter + y, xCenter - x, c); // seventh
	if( (startOct<3) && (endOct>1) )
		image_setColor(src, yCenter - y, xCenter - x, c); // second
	if( (startOct<6) && (endOct>4) )
		image_setColor(src, yCenter + x, xCenter + y, c); // fifth
	if( (startOct<5) && (endOct>3) )
		image_setColor(src, yCenter - x, xCenter + y, c); // fourth
	if( endOct==8 )
		image_setColor(src, yCenter + x, xCenter - y, c); // eigth
	if( startOct==1 )
		image_setColor(src, yCenter - x, xCenter - y, c); // first

	// sixth octant, moving clockwise
	while(x>y){
		x--;
		if(p<0)
			p += 1 - 2*x;
		else{
			y++;
			p += 1 - 2*(x-y);
		}

		// draw in all 8 octants
		if( (startOct<7) && (endOct>5) )
			image_setColor(src, yCenter + y, xCenter + x, c); // sixth
		if( (startOct<4) && (endOct>2) )
			image_setColor(src, yCenter - y, xCenter + x, c); // third
		if( (startOct<8) && (endOct>6) )
			image_setColor(src, yCenter + y, xCenter - x, c); // seventh
		if( (startOct<3) && (endOct>1) )
			image_setColor(src, yCenter - y, xCenter - x, c); // second
		if( (startOct<6) && (endOct>4) )
			image_setColor(src, yCenter + x, xCenter + y, c); // fifth
		if( (startOct<5) && (endOct>3) )
			image_setColor(src, yCenter - x, xCenter + y, c); // fourth
		if( endOct==8 )
			image_setColor(src, yCenter + x, xCenter - y, c); // eigth
		if( startOct==1 )
			image_setColor(src, yCenter - x, xCenter - y, c); // first
	}
}

// ELLIPSE

/*
 * Initialize an ellipse to location tc and radii ta and tb. 
 */
void ellipse_set(Ellipse *e, Point tc, double ta, double tb){
	if(!e){
		return;
	}
	e->ra = ta;
	e->rb = tb;
	e->c = tc;
	e->a = 0.0;
}

/*
 * Draw a filled ellipse into src using color c.
 */
void ellipse_draw(Ellipse *e, Image *src, Color c){
	ellipse_drawquad(e, src, c, 1, 4);
}

/*
 * Draw into src using color c. 
 */
void ellipse_drawFill(Ellipse *e, Image *src, Color c){
	if(!e){
		return;
	}

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
	while(curx!=Rx)
		image_setColor(src, yCenter, xCenter + curx++, c);

	// circle draw here - plot first set of lines
	// line above bottom
	curx = x;
	while(curx!=-x)
		image_setColor(src, yCenter + y, xCenter + curx++, c);
	// line below top
	curx = x;
	while(curx!=-x)
		image_setColor(src, yCenter - y, xCenter + curx++, c);

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
		while(curx!=-x)
			image_setColor(src, yCenter + y, xCenter + curx++, c);
		// line below top
		curx = x;
		while(curx!=-x)
			image_setColor(src, yCenter - y, xCenter + curx++, c);
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
		while(curx!=-x)
			image_setColor(src, yCenter + y, xCenter + curx++, c);
		// line below top
		curx = x;
		while(curx!=-x)
			image_setColor(src, yCenter - y, xCenter + curx++, c);
	}
}

/*
 * Draw the specified octant range of a circle into src using color c. 
 */
void ellipse_drawquad(Ellipse *e, Image *src, Color c, int startQuad, int endQuad){

	if( (startQuad<1) || (endQuad>4) || (endQuad<startQuad) ){
		printf("bad start and end quadrant, must be between 1 and 4\n");
		return;
	}
	
	if(!e){
		return;
	}

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
	if( (startQuad==1) || (endQuad==4) )
		image_setColor(src, yCenter + 0, xCenter + Rx, c);
	if( startQuad<3 )
		image_setColor(src, yCenter + Ry, xCenter + 0, c);
	if( (startQuad>4) && (endQuad>1) )
		image_setColor(src, yCenter - 0, xCenter - Rx, c);
	if( endQuad>2 )
		image_setColor(src, yCenter - Ry, xCenter - 0, c);
	
	/* Plot the first set of points */
	if( (startQuad<4) && (endQuad>2) )
		image_setColor(src, yCenter + y, xCenter + x, c); // third
	if( endQuad==4 )
		image_setColor(src, yCenter + y, xCenter - x, c); // fourth
	if( (startQuad<3) && (endQuad>1) )
		image_setColor(src, yCenter - y, xCenter + x, c); // second
	if( startQuad==1 )
		image_setColor(src, yCenter - y, xCenter - x, c); // first

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
		if( (startQuad<4) && (endQuad>2) )
			image_setColor(src, yCenter + y, xCenter + x, c); // third
		if( endQuad==4 )
			image_setColor(src, yCenter + y, xCenter - x, c); // fourth
		if( (startQuad<3) && (endQuad>1) )
			image_setColor(src, yCenter - y, xCenter + x, c); // second
		if( startQuad==1 )
			image_setColor(src, yCenter - y, xCenter - x, c); // first
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
		if( (startQuad<4) && (endQuad>2) )
			image_setColor(src, yCenter + y, xCenter + x, c); // third
		if( endQuad==4 )
			image_setColor(src, yCenter + y, xCenter - x, c); // fourth
		if( (startQuad<3) && (endQuad>1) )
			image_setColor(src, yCenter - y, xCenter + x, c); // second
		if( startQuad==1 )
			image_setColor(src, yCenter - y, xCenter - x, c); // first
	}
}

// POLYLINE

// The functions polyline_create and polyline_free manage both the Polyline data
//  structure and the memory required for the vertex list

/* 
 * Returns an allocated Polyline pointer initialized so that 
 * numVertex is 0 and vertex is NULL. 
 */
Polyline *polyline_create(){
	Polyline *p;
	
	// get space for the polyline
	p = malloc(sizeof(Polyline));
	if(!p){
		return(NULL);
	}
	
	// initialize structure
	p->zBuffer = 1;
	p->numVertex = 0;
	p->vertex = NULL;	
	
	// return pointer
	printf("polyline created\n");
	return(p);
}

/* 
 * Returns an allocated Polyline pointer with the vertex list initialized 
 * to the points in vlist. 
 */
Polyline *polyline_createp(int numV, Point *vlist){

	Polyline *p;
	int i;
	
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
	printf("polyline created\n");
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
	printf("polyline freed\n");
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
	
	// reset structure
	p->zBuffer = 1;
	p->numVertex = 0;
	p->vertex = NULL;
	
	printf("polyline initted\n");
}

/* Initializes the vertex list to the points in vlist. De-allocates/allocates
 * the vertex list for p, as necessary. 
 */
void polyline_set(Polyline *p, int numV, Point *vlist){
	int  i;
	
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
		return;
	}
	
	// initialize structure
	p->zBuffer = 1;
	p->numVertex = numV;
	for(i=0;i<numV;i++){
		p->vertex[i] = vlist[i];
	}
	printf("polyline set\n");
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
	printf("polyline cleared\n");
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
	int i;
	
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
	to->vertex = malloc( sizeof(Point) * (from->numVertex) );
	if(!to->vertex){
		return;
	}
	
	// copy the points to destination
	to->numVertex = from->numVertex;
	for(i=0;i<(to->numVertex);i++){
		to->vertex[i] = from->vertex[i];
	}
	printf("polyline copied\n");
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

	// print polyline points as x,y pairs
	fprintf(fp, "about to print polyline points\n");
	for(i = 0; i<(p->numVertex); i++){
		fprintf(fp,"x:%f, y:%f\n", p->vertex[i].val[0], p->vertex[i].val[1]);
	}
	printf("polyline printed\n");
}

/* 
 * Draw the Polyline using color c. 
 */
void polyline_draw(Polyline *p, Image *src, Color c){
	int i;
	Line l;

	if(p){
		if(!p->vertex){
			return;
		}
	} else{
		return;
	}

	if (p->numVertex < 2){
		printf("can't draw a polyline with less than two points\n");
	}

	// iterate through polyline
	for(i=0; i<(p->numVertex-1); i++){
		// take coordinates for polyline point
		// create a line
		line_set(&l, p->vertex[i], p->vertex[i +1]);
		// draw line on src using Color c
		line_draw(&l, src, c);
	}
	printf("polyline drawn\n");
}

// Polygon

/*
 * returns an allocated Polygon pointer initialized so that
 * nVertex is 0 and vertex is NULL.
 */
Polygon *polygon_create(){
	Polygon *p;
	
	// get space for the polyline
	p = malloc(sizeof(Polygon));
	if(!p){
		return(NULL);
	}
	
	// initialize structure
	p->zBuffer = 1;
	p->nVertex = 0;
	p->vertex = NULL;	
	
	// return pointer
	printf("polygon created\n");
	return(p);
}

/*
 * returns an allocated Polygon pointer with the vertex list
 * initialized to a copy of the points in vlist.
 */
Polygon *polygon_createp(int numV, Point *vlist){

	Polygon *p;
	int i;
	
	// get space for the polyline
	p = malloc(sizeof(Polygon));
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
	p->nVertex = numV;
	for(i=0;i<numV;i++){
		p->vertex[i] = vlist[i];
	}
	
	// return pointer
	printf("Polygon created\n");
	return(p);
}

/*
 * frees the internal data for a Polygon and the Polygon pointer.
 * The functions polygon init, polygon set, and polygon
 * clear work on a pre-existing Polygon data structure
 * and manage only the memory required for the vertex list.
 */
void polygon_free(Polygon *p){
	if(p){
		if(p->vertex){
			free(p->vertex);
		}
		free(p);
	} else {
		printf("null p passed to polygon_free\n");
	}
	printf("polygon freed\n");
}

/*
 * initializes the existing Polygon to an empty Polygon.
 */
void polygon_init(Polygon *p){

	// detect null pointer passed
	if(!p){
		printf("null p passed to polygon_init\n");
		return;
	}
	
	// reset structure
	p->zBuffer = 1;
	p->nVertex = 0;
	p->vertex = NULL;
	
	printf("polygon initted\n");
}

/*
 * initializes the vertex array to the points in vlist.
 */
void polygon_set(Polygon *p, int numV, Point *vlist){
	int  i;
	
	// detect null pointer passed
	if(!p){
		printf("null p passed to polygon_set\n");
		return;
	}	
	
	// free existing vertex list
	if(p->vertex){
		free(p->vertex);
	}
	
	// get space for the vertex list
	p->vertex = malloc(sizeof(Point) * numV);
	if(!p->vertex){
		return;
	}
	
	// initialize structure
	p->zBuffer = 1;
	p->nVertex = numV;
	for(i=0;i<numV;i++){
		p->vertex[i] = vlist[i];
	}
	printf("polygon set\n");
}

/*
 * frees the internal data and resets the fields.
 */
void polygon_clear(Polygon *p){

	// detect null pointer passed
	if(!p){
		printf("null p passed to polygon_clear\n");
		return;
	}
	
	// free internal data
	if(p->vertex){
		free(p->vertex);
	}
	
	// reset structure
	p->nVertex = 0;
	p->vertex = NULL;
	printf("polygon cleared\n");
}

/*
 * sets the z-buffer flag to the given value.
 */
void polygon_zBuffer(Polygon *p, int flag){
	// detect null pointer passed
	if(!p){
		printf("null p passed to polygon_zBuffer\n");
		return;
	}
	p->zBuffer = flag;
}

/*
 * De-allocates/allocates space and copies the vertex and 
 * color data from one polygon to the other.
 */
void polygon_copy(Polygon *to, Polygon *from){
	int i;
	
	// detect null pointer passed
	if(!to){
		printf("null to passed to polygon_copy\n");
		return;
	}
	if(!from){
		printf("null from passed to polygon_copy\n");
		return;
	}
	
	// free internal data in destination
	if(to->vertex){
		free(to->vertex);
	}
	
	// allocate new destination space
	to->vertex = malloc( sizeof(Point) * (from->nVertex) );
	if(!to->vertex){
		return;
	}
	
	// copy the points to destination
	to->nVertex = from->nVertex;
	for(i=0;i<(to->nVertex);i++){
		to->vertex[i] = from->vertex[i];
	}
	printf("polygon copied\n");
}

/*
 * prints polygon data to the stream designated by the FILE pointer.
 */
void polygon_print(Polygon *p, FILE *fp){
	int i;

	if(p){
		if(!p->vertex){
			return;
		}
	} else{
		return;
	}	

	// print polyline points as x,y pairs
	fprintf(fp, "about to print polygon points\n");
	for(i = 0; i<(p->nVertex); i++){
		fprintf(fp,"x:%f, y:%f\n", p->vertex[i].val[0], p->vertex[i].val[1]);
	}
	printf("polygon printed\n");
}

/*
 * draw the outline of the polygon using color c.
 */
void polygon_draw(Polygon *p, Image *src, Color c){
	int i;
	Line l;

	if(p){
		if(!p->vertex){
			return;
		}
	} else{
		return;
	}

	if (p->nVertex < 3){
		printf("can't draw a polygon with less than three points\n");
	}

	// iterate through polyline
	for(i=0; i<(p->nVertex-1); i++){
		// take coordinates for polyline point
		// create a line
		line_set(&l, p->vertex[i], p->vertex[i+1]);
		// draw line on src using Color c
		line_draw(&l, src, c);
	}
	//draw from last to first vertex at the end
	line_set(&l, p->vertex[p->nVertex-1], p->vertex[0]);
	line_draw(&l, src, c);
	printf("polygon drawn\n");
}

/*
	Ian Tibbetts And Astrid Moorse (Bruce A. Maxwell)
	Fall 2014

	scanline fill algorithm
*/
/********************
Scanline Fill Algorithm
********************/

// define the struct here, because it is local to only this file
typedef struct tEdge {
	float x0, y0;                   /* start point for the edge */
	float x1, y1;                   /* end point for the edge */
	int yStart, yEnd;               /* start row and end row */
	/* where the edge intersects the current scanline and how it changes */
	float xIntersect, dxPerScan;    
	
	/* we'll add more here later */
	struct tEdge *next;
} Edge;


/*
	This is a comparison function that returns a value < 0 if a < b, a
	value > 0 if a > b, and 0 if a = b.  It uses the yStart field of the
	Edge structure.  It is used to sort the overall edge list.
 */
static int compYStart( const void *a, const void *b ) {
	Edge *ea = (Edge *)a;
	Edge *eb = (Edge *)b;

	return(ea->yStart - eb->yStart);
}


/*
	This is a comparison function that returns a value < 0 if a < b, a
	value > 0 if a > b, and 0 if a = b.  It uses the xIntersect field of the
	Edge structure.  It is used to sort the active edge list.
 */
static int compXIntersect( const void *a, const void *b ) {
	Edge *ea = (Edge *)a;
	Edge *eb = (Edge *)b;

	if( ea->xIntersect < eb->xIntersect )
		return(-1);
	else if(ea->xIntersect > eb->xIntersect )
		return(1);

	return(0);
}

/*
	Allocates, creates, fills out, and returns an Edge structure given
	the inputs.

	Current inputs are just the start and end location in image space.
	Eventually, the points will be 3D and we'll add color and texture
	coordinates.
 */
static Edge *makeEdgeRec( Point start, Point end, Image *src)
{
	Edge *edge;
	float dscan = end.val[1] - start.val[1];
	float dwidth = end.val[0] - start.val[0];
	float xadjust,vyMinusFloor, floorMinusVy;

	/******
				 Your code starts here
	******/

	// Check if the starting row is below the image or the end row is
	// above the image and skip the edge if either is true
	if( (start.val[1] < epsilon) || (start.val[1] > ((float)(src->rows-1))) ){
		printf("row clipping, no edge\n");
		return(NULL);
	}

	// allocate an edge structure and set the x0, y0, x1, y1 values
	edge = malloc(sizeof(Edge));
	edge->x0 = start.val[0];
	edge->x1 = end.val[0];
	edge->y0 = start.val[1];
	edge->y1 = end.val[1];
	
	// define adjust, used to round
	// turn on an edge only if the edge starts in the top half of it or
	// the lower half of the pixel above it.  In other words, round the
	// start y value to the nearest integer and assign it to
	// edge->yStart.
	edge->yStart = (int)(edge->y0+0.5);
	
	// Turn off the edge if it starts in the lower half or the top half
	// of the next pixel.  In other words, round the end y value to the
	// nearest integer and subtract 1, assigning the result to
	// edge->yEnd.
	edge->yEnd = (int)(edge->y1+0.5)-1;

	// Clip yEnd to the number of rows-1.????????????
	if(edge->yEnd > (src->rows-1)){
		printf("row clipping bottom\n");
		edge->yEnd = src->rows-1;
	}

	// Calculate the slope, dxPerScan
	if(dwidth<epsilon && dwidth>-epsilon){
		edge->dxPerScan = 0.0;
	} else {
		edge->dxPerScan = dscan/dwidth;
	}
	
	// Calculate xIntersect, adjusting for the fraction of the point in the pixel.
	// Scanlines go through the middle of pixels
	// Move the edge to the first scanline it crosses
	floorMinusVy = ((float)((int)(edge->y0))) - (edge->y0);
	vyMinusFloor = (edge->y0)-((float)((int)(edge->y0)));
	if(0.5 < vyMinusFloor){
		xadjust = 1.5 - floorMinusVy;
	} else {
		xadjust = 0.5 - floorMinusVy;
	}
	edge->xIntersect = edge->x0 + xadjust*edge->dxPerScan;
	
	// adjust if the edge starts above the image??????????????????????
	// move the intersections down to scanline zero
	// if edge->y0 < 0
	if(edge->y0<epsilon){
		printf("row clipping top\n");
		//   update xIntersect
		edge->xIntersect += (0-edge->y0)*edge->dxPerScan;
		//   update y0
		edge->y0 = 0.0;
		//   update x0
		edge->x0 = edge->xIntersect;
		//   update yStart
		edge->yStart = 0;
	}

	// check for really bad cases with steep slopes where xIntersect 
	// has gone beyond the end of the edge
	if(edge->xIntersect>(edge->x1)){
		printf("bad bad xIntersect has gone beyond the end of the edge\n");
		//return(NULL);
	}

	// return the newly created edge data structure
	return( edge );
}


/*
	Returns a list of all the edges in the polygon in sorted order by
	smallest row.
*/
static LinkedList *setupEdgeList( Polygon *p, Image *src) {
	LinkedList *edges = NULL;
	Point v1, v2;
	int i;

	// create a linked list
	edges = ll_new();

	// walk around the polygon, starting with the last point
	v1 = p->vertex[p->nVertex-1];

	for(i=0;i<p->nVertex;i++) {
		
		// the current point (i) is the end of the segment
		v2 = p->vertex[i];

		// if it is not a horizontal line
		if( (int)(v1.val[1]+0.5) != (int)(v2.val[1]+0.5) ) {
			Edge *edge;

			// if the first coordinate is smaller (top edge)
			if( v1.val[1] < v2.val[1] )
				edge = makeEdgeRec( v1, v2, src );
			else
				edge = makeEdgeRec( v2, v1, src );

			// insert the edge into the list of edges if it's not null
			if( edge )
				ll_insert( edges, edge, compYStart );
		}
		v1 = v2;
	}

	// check for empty edges (like nothing in the viewport)
	if( ll_empty( edges ) ) {
		ll_delete( edges, NULL );
		edges = NULL;
	}

	return(edges);
}

/*
	Draw one scanline of a polygon given the scanline, the active edges,
	a DrawState, the image, and some Lights (for Phong shading only).
 */
static void fillScan( int scan, LinkedList *active, Image *src, Color c ) {
	Edge *p1, *p2;
	int i, f;

	// loop over the list
	p1 = ll_head( active );
	while(p1) {
		// the edges have to come in pairs, draw from one to the next
		p2 = ll_next( active );
		if( !p2 ) {
			printf("bad bad bad (your edges are not coming in pairs)\n");
			break;
		}

		// if the xIntersect values are the same, don't draw anything.
		// Just go to the next pair.
		if( p2->xIntersect == p1->xIntersect ) {
			p1 = ll_next( active );
			continue;
		}

		/**** Your code goes here ****/
		// identify the starting column
		i=(int)(fmin(p1->xIntersect,p2->xIntersect)+0.5);
		//printf("i=%d",i);
		// clip to the left side of the image
		if(i<0){
			//printf(" clipping left ");
			i=0;
		}
		
		// identify the ending column
		f=(int)(fmax(p1->xIntersect,p2->xIntersect)+0.5);
		//printf("f=%d\n",f);
		
		// clip to the right side of the image
		if(f>(src->cols-1)){
			//printf("clipping right\n");
			f=src->cols-1;
		}
		
		// loop from start to end and color in the pixels
		for(;i<f;i++){
			image_setColor(src, scan, i, c);
		}
		
		// move ahead to the next pair of edges
		p1 = ll_next( active );
	}

	return;
}

/* 
	 Process the edge list, assumes the edges list has at least one entry
*/
static int processEdgeList( LinkedList *edges, Image *src, Color c ) {
	LinkedList *active = NULL;
	LinkedList *tmplist = NULL;
	LinkedList *transfer = NULL;
	Edge *current;
	Edge *tedge;
	int scan = 0;

	active = ll_new( );
	tmplist = ll_new( );

	// get a pointer to the first item on the list and reset the current pointer
	current = ll_head( edges );

	// start at the first scanline and go until the active list is empty
	for(scan = current->yStart;scan < src->rows-1;scan++ ) {

		// grab all edges starting on this row
		while( current != NULL && current->yStart == scan ) {
			ll_insert( active, current, compXIntersect );
			current = ll_next( edges );
		}
		// current is either null, or the first edge to be handled on some future scanline

		if( ll_empty(active) ) {
			continue;
		}

		// if there are active edges
		// fill out the scanline
		fillScan( scan, active, src, c);

		// remove any ending edges and update the rest
		for( tedge = ll_pop( active ); tedge != NULL; tedge = ll_pop( active ) ) {

			// keep anything that's not ending
			if( tedge->yEnd > scan ) {
				//float a = 1.0;

				// update the edge information with the dPerScan values
				tedge->xIntersect += tedge->dxPerScan;

				// adjust in the case of partial overlap
				if( tedge->dxPerScan < 0.0 && tedge->xIntersect < tedge->x1 ) {
					//a = (tedge->xIntersect - tedge->x1) / tedge->dxPerScan;
					tedge->xIntersect = tedge->x1;
				}
				else if( tedge->dxPerScan > 0.0 && tedge->xIntersect > tedge->x1 ) {
					//a = (tedge->xIntersect - tedge->x1) / tedge->dxPerScan;
					tedge->xIntersect = tedge->x1;
				}

				ll_insert( tmplist, tedge, compXIntersect );
			}
		}

		transfer = active;
		active = tmplist;
		tmplist = transfer;

	}

	// get rid of the lists, but not the edge records
	ll_delete(active, NULL);
	ll_delete(tmplist, NULL);

	return(0);
}

/****************************************
End Scanline Fill
*****************************************/


/*
	Draws a filled polygon of the specified color into the image src.
 */
void polygon_drawFill(Polygon *p, Image *src, Color c ) {
	LinkedList *edges = NULL;

	// set up the edge list
	edges = setupEdgeList( p, src );
	if( !edges )
		return;
	
	// process the edge list (should be able to take an arbitrary edge list)
	processEdgeList( edges, src, c);

	// clean up
	ll_delete( edges, (void (*)(const void *))free );

	return;
}

/*
 * draw the filled polygon using color c with the Barycentric coordinates algorithm.
 */
void polygon_drawFillB(Polygon *p, Image *src, Color c){

}
