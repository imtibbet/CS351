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
        //for each neighbor N of pixel
        if(image_getColor(src, xSeed+1, ySeed) == borderc){
            return;
        }else{
            image_setColor(src, xSeed+1, ySeed, fillc);
        }
        
        if(image_getColor(src, xSeed+1, ySeed) == borderc){
            return;
        }else{
            image_setColor(src, xSeed+1, ySeed, fillc);
        }
        
        if(image_getColor(src, xSeed+1, ySeed) == borderc){
            return;
        }else{
            image_setColor(src, xSeed+1, ySeed, fillc);
        }
        
        if(image_getColor(src, xSeed+1, ySeed) == borderc){
            return;
        }else{
            image_setColor(src, xSeed+1, ySeed, fillc);
        }
            //color N
            //push N on the stack
           
        stacksize--;
	}
    
	
	
	
	free(stack)
}

