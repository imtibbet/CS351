#ifndef COLOR_H

#define COLOR_H

typedef struct {
	double val[4];
} Point;


typedef struct {
	int zBuffer;
	Point a;
	Point b;
} Line;


typedef struct {
	double r;
	Point c;
} Circle;


typedef struct {
	double ra;
	double rb;
	Point c;
	double a;
} Ellipse;


typedef struct {
	int zBuffer;
	int numVertex;
	Point *vertex;
} Polyline;

#endif
