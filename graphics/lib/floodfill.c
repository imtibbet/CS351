/*
=======
>>>>>>> FETCH_HEAD
 * Author: Ian Tibbetts
 * Date: 9/19/14
 *
 * The color function implementations
 */
=======

#include "graphics.h"

/*
 * fill on src starting from the seed pixel using fillc until closed by borderc
 */
void floodfill(Image *src, Color fillc, Color borderc, int xSeed, int ySeed){
	FPixelStackItem *stack;
	FPixelStackItem curp;
	int stacksize = 0;
	
	// reserve worst case amount of space (size of image)
	stack = malloc(sizeof(FPixelStackItem) * src->rows * src->cols);
	
	// add seed pixel to the stack
	stack[stacksize++] = {src->data[ySeed][xSeed], ySeed, xSeed};
	
	// while the stack is not empty
	while(stacksize){
		
		// pop pixel off the stack
		curp = stack[--stacksize];
	}
	
	
	
	
	free(stack)
	
}

=======
Astrid Moore (Bruce Maxwell)
Fall 2014
CS351

Flood fills a shape, like a paint can tool.
*/
>>>>>>> FETCH_HEAD

#include "graphics.h"

/*
 * fill on src starting from the seed pixel using fillc until closed by borderc
 */
void floodfill(Image *src, Color fillc, Color borderc, int xSeed, int ySeed){
	FPixelStackItem *stack;
	FPixelStackItem curp;
	int stacksize = 0;
	
	// reserve worst case amount of space (size of image)
	stack = malloc(sizeof(FPixelStackItem) * src->rows * src->cols);
	
	// add seed pixel to the stack
	stack[stacksize++] = {src->data[ySeed][xSeed], ySeed, xSeed};
	
	// while the stack is not empty
	while(stacksize){
		
		// pop pixel off the stack
		curp = stack[--stacksize];
	}
	free(stack)
}

=======
}
>>>>>>> e2f52db8c8097b9d5d1be3fda82b186d4e93cd31
>>>>>>> FETCH_HEAD
