#ifndef PRIMITIVES_H

#define PRIMITIVES_H

typedef struct {
	double val[4];
} Point;

/** Sets the first two values of the vector to x and y. Sets the third value to 0.0 and the fourth value to 1.0 **/
void point_set2D(Point *p, double x, double y);

/** Set the point's values to x and y and z. Sets the homogeneous coordinate to 1.0 **/
void point_set3D(Point *p, double x, double y, double z);

/** Set the four values of the vector to x, y, z, and h, respectively. **/
void point_set(Point *p, double x, double y, double z, double h);

/** Copy the point data structure. **/
void point_copy(Point *to, Point *from);

/** Draw the point into src using Color c. **/
void point_draw(Point *p, Image *src, Color c);

/** Draw the p into src using FPixel c. **/
void point_drawf(Point *p, Image *src, FPixel c);


typedef struct {
	int zBuffer;
	Point a;
	Point b;
} Line;

/** Initialize a 2D line. **/
void line_set2D(Line *l, double x0, double y0, double x1, double y1);

/** Initialze a line to ta and tb. **/
void line_set(Line *l, Point ta, Point tb);

/** Set the z-buffer flag to the given value. **/
void line_zBuffer(Line *l, int flag);

/** Copy the line data structure. **/
void line_copy(Line *to, Line *from);

/** Draw the line into src using Color c. **/
void line_draw(Line *l, Image *src, Color c);

typedef struct {
	double r;
	Point c;
} Circle;

/** Initialize to center tc and radius tr. **/
void circle_set(Circle *c, Point tc, double tr);

/** Draw the circle into src using color p. **/
void circle_draw(Circle *c, Image *src, Color p);

/** Draw a filled circled into src using color p. **/
void circle_drawFill(Circle *c, Image *src, Color p);

typedef struct {
	double ra;
	double rb;
	Point c;
	double a;
} Ellipse;

/** Initialize an ellipse to location tc and radii ta and tb. **/
void ellipse_set(Ellipse *e, Point tc, double ta, double tb);

/** Draw into src using color p. **/
void ellipse_draw(Ellipse *e, Image *src, Color p);

/** Draw a filled ellipse into src using color p. **/
void ellipse_drawFill(Ellipse *e, Image *src, Color p);

typedef struct {
	int zBuffer;
	int numVertex;
	Point *vertex;
} Polyline;

/* Returns an allocated Polyline pointer initialized so that 
* numVertex is 0 and vertex is NULL. */
Polyline *polyline_create();

/* Returns an allocated Polyline pointer with the vertex list initialized 
* to the points in vlist. */
Polyline *polyline_createp(int numV, Point *vlist);

/* Frees the internal data and the Polyline pointer. */
void polyline_free(Polyline *p);

/* Initializes the pre-existing Polyline to an empty Polyline. */
void polyline_init(Polyline *p);

/* Initializes the vertex list to the points in vlist. De-allocates/allocates
* the vertex list for p, as necessary. */
void polyline_set(Polyline *p, int numV, Point *vlist);

/* Frees the internal data for a Polyline, if necessary, and sets numVertex
* to 0 and vertex to NULL. */
void polyline_clear(Polyline *p);

/* Sets the z-buffer flag to the given value. */
void polyline_zBuffer(Polyline *p, int flag);

/* De-allocates/allocates space as necessary in the destination Polyline data
* structure and copies the vertex data from the source polyline (from) to the 
* destination (to). */
void polyline_copy (Polyline *to, Polyline *from);

/* Prints Polyline data to the stream designated by the FILE pointer. */
void polyline_print(Polyline *p, FILE *fp);

/* Draw the Polyline using color c. */
void polyline_draw(Polyline *p, Image *src, Color c);

#endif
