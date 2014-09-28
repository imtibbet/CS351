/*
* Author: Ian Tibbetts and Astrid Moore
* Date: 9/25/14
*
* The floodfill scanline algorithm
*/
#include "graphics.h"

void polygon_drawFill(Image *src, Color fillc, Color borderc, int xSeed, int ySeed){
    FPixelStackItem *stack;
    FPixelStackItem curp;
    int stacksize = 0;
    int curx, cury;
    Color curc, abovec, belowc, aboverightc, belowrightc;

    // reserve worst case amount of space (size of image)
    stack = malloc(sizeof(FPixelStackItem) * src->rows * src->cols);

    if(!stack){
        printf("no space for the flood fill stack\n");
        return;
    }
    
    // add seed pixel to the stack
    curp.x = xSeed;
    curp.y = ySeed;
    stack[stacksize++] = curp;

    printf("start flood fill loop\n");
    // while the stack is not empty
    while(stacksize){
        
        // pop pixel off the stack
        curp = stack[--stacksize];
        //printf("got pixel, stack size=%d, x=%d, y=%d\n", stacksize,curp.x,curp.y);
        
        // find the far left pixel in the row that is not a boundary color
        curx = (curp.x)-1;
        cury = curp.y;
    	curc = image_getColor(src, cury, curx);
        while( !color_compare(curc, borderc) ){
        	if(curx==0)
        		break;
    		curc = image_getColor(src, cury, --curx);
        }
        if(!color_compare(curc, borderc) && (curx==0))
        	continue;
        curx++;
        
    	curc = 			image_getColor(src, cury, curx);
    	abovec = 		image_getColor(src, cury+1, curx);
    	belowc = 		image_getColor(src, cury-1, curx);
    	aboverightc = 	image_getColor(src, cury+1, curx+1);
    	belowrightc = 	image_getColor(src, cury-1, curx+1);
        
        // traverse the row, coloring until a boundary pixel is reached
        while( !color_compare(curc, borderc) ){
            
            // color active pixel
            image_setColor(src, cury, curx, fillc);
            
            // add pixels to the stack if above is clear and above right is not
            if( (!color_compare(abovec, borderc)) &&
               	(!color_compare(abovec, fillc)) &&
               	(color_compare(aboverightc, borderc)) ){
                curp.x = curx;
                curp.y = cury+1;
                stack[stacksize++] = curp;
            }
            // add pixels to the stack if below is clear and below right is not
            if( (!color_compare(belowc, borderc)) &&
               	(!color_compare(belowc, fillc)) &&
               	(color_compare(belowrightc, borderc)) ){
                curp.x = curx;
                curp.y = cury-1;
                stack[stacksize++] = curp;
            }
            // advance
            curx++;
			curc = 			image_getColor(src, cury, curx);
			abovec = 		image_getColor(src, cury+1, curx);
			belowc = 		image_getColor(src, cury-1, curx);
			aboverightc = 	image_getColor(src, cury+1, curx+1);
			belowrightc = 	image_getColor(src, cury-1, curx+1);
        }
        curx--;
		abovec = image_getColor(src, cury+1, curx);
		belowc = image_getColor(src, cury-1, curx);

        // when a bounday ends the traversal, add above if clear
        if( (!color_compare(abovec, fillc)) &&
           	(!color_compare(abovec, borderc)) ){
            curp.x = curx;
            curp.y = cury+1;
            stack[stacksize++] = curp;
        }
        // when a bounday ends the traversal, add below if clear
        if( (!color_compare(belowc, fillc)) &&
           	(!color_compare(belowc, borderc)) ){
            curp.x = curx;
            curp.y = cury-1;
            stack[stacksize++] = curp;
        }
        //printf("at end of loop, stack size = %d\n", stacksize);
    }

    printf("flood fill done\n");
    free(stack);
}

