/*
 * Author: Ian Tibbetts
 * Date: 9/19/14
 *
 * The color function implementations
 */

#include "graphics.h"

// copies the Color data.
void color_copy(Color *to, Color *from){
	to->c[0] = from->c[0];
	to->c[1] = from->c[1];
	to->c[2] = from->c[2];
	printf("color copied\n");
}

// sets the Color data.
void color_set(Color *to, float r, float g, float b){
	to->c[0] = r;
	to->c[1] = g;
	to->c[2] = b;
	printf("color set\n");
}

