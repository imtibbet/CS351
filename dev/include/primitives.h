#ifndef PRIMITIVES_H

#define PRIMITIVES_H

typedef struct {
	double val[4]; // four element vector of doubles
} Point;

typedef struct {
	int zBuffer; // whether to use the z-buffer, should default to true (1)
	Point a; // starting point
	Point b; // ending point
} Line;

typedef struct {
	double r; // radius,
	Point c; // center
} Circle;

typedef struct {
	double ra; // major axis radius
	double rb; // minor axis radius
	Point c; // center
	double a; // (optional) angle of major axis relative to the X-axis
} Ellipse;

typedef struct {
	int zBuffer; // whether to use the z-buffer; should default to true (1)
	int numVertex; // Number of vertices
	Point *vertex; // vertex information
} Polyline;

typedef struct {
	int zBuffer; // whether to use the z-buffer; should default to true (1)
	int nVertex; // Number of vertices
	Point *vertex; // vertex information
} Polygon;

// Point functions

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

/** Print the point to the stream designated by FILE pointer **/
void point_print(Point *p, FILE *fp);

/** Normalize the Vector to unit length. Do not modify the homogeneous coordinate. **/
void point_normalize(Point *p);

// Line functions

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

// Circle functions

/** Initialize to center tc and radius tr. **/
void circle_set(Circle *c, Point tc, double tr);

/** Draw the circle into src using color c. **/
void circle_draw(Circle *circ, Image *src, Color c);

/** Draw a filled circled into src using color c. **/
void circle_drawFill(Circle *circ, Image *src, Color c);

/** Draw the specified octant range of a circle into src using color c. **/
void circle_drawoct(Circle *circ, Image *src, Color c, int startOct, int endOct);


// Elipse functions

/** Initialize an ellipse to location tc and radii ta and tb. **/
void ellipse_set(Ellipse *e, Point tc, double ta, double tb);

/** Draw into src using color c. **/
void ellipse_draw(Ellipse *e, Image *src, Color c);

/** Draw a filled ellipse into src using color c. **/
void ellipse_drawFill(Ellipse *e, Image *src, Color c);

/** Draw the specified octant range of a circle into src using color c. **/
void ellipse_drawquad(Ellipse *e, Image *src, Color c, int startQuad, int endQuad);

// Polyline functions

/* Returns an allocated Polyline pointer initialized so that 
* numVertex is 0 and vertex is NULL. */
Polyline *polyline_create(void);

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

/*
 * normalize the x and y values of each vertex by the homogeneous coord
 */
void polyline_normalize( Polyline *p);

// Polygon

/*
 * returns an allocated Polygon pointer initialized so that
 * numVertex is 0 and vertex is NULL.
 */
Polygon *polygon_create(void);

/*
 * returns an allocated Polygon pointer with the vertex list
 * initialized to a copy of the points in vlist.
 */
Polygon *polygon_createp(int numV, Point *vlist);

/*
 * frees the internal data for a Polygon and the Polygon pointer.
 * The functions polygon init, polygon set, and polygon
 * clear work on a pre-existing Polygon data structure
 * and manage only the memory required for the vertex list.
 */
void polygon_free(Polygon *p);

/*
 * initializes the existing Polygon to an empty Polygon.
 */
void polygon_init(Polygon *p);

/*
 * initializes the vertex array to the points in vlist.
 */
void polygon_set(Polygon *p, int numV, Point *vlist);

/*
 * frees the internal data and resets the fields.
 */
void polygon_clear(Polygon *p);

/*
 * sets the z-buffer flag to the given value.
 */
void polygon_zBuffer(Polygon *p, int flag);

/*
 * De-allocates/allocates space and copies the vertex and 
 * color data from one polygon to the other.
 */
void polygon_copy(Polygon *to, Polygon *from);

/*
 * prints polygon data to the stream designated by the FILE pointer.
 */
void polygon_print(Polygon *p, FILE *fp);

/*
 * normalize the x and y values of each vertex by the homogeneous coord
 */
void polygon_normalize( Polygon *p);

/*
 * draw the outline of the polygon using color c.
 */
void polygon_draw(Polygon *p, Image *src, Color c);

/*
 * draw the filled polygon using color c with the scanline rendering algorithm.
 */
void polygon_drawFill(Polygon *p, Image *src, Color c);

/*
 * draw the filled polygon using color c with the Barycentric coordinates algorithm.
 */
void polygon_drawFillB(Polygon *p, Image *src, Color c);




#endif
