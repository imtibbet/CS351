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
	double val[4];
} Circle;


typedef struct {
	double val[4];
} Ellipse;


typedef struct {
	double val[4];
} Polyline;

#endif
