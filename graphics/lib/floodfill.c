/*
* Author: Ian Tibbetts and Astrid Moore
* Date: 9/25/14
*
* The floodfill scanline algorithm
*/
#include "graphics.h"

void floodfill(Image *src, Color fillc, Color borderc, int x){
    FPixelStackItem *stack;
    FPixelStackItem curp;
    int stacksize = 0;
    int curx, cury;

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

    printf("start loop\n");
    // while the stack is not empty
    while(stacksize){
        
        // pop pixel off the stack
        curp = stack[--stacksize];
        printf("got pixel, stack size=%d, x=%d, y=%d\n", stacksize,curp.x,curp.y);
        
        // find the far left pixel in the row that is not a boundary color
        curx = (curp.x)-1;
        cury = curp.y;
        while( 	(src->data[cury][curx].rgb[0] != borderc.c[0]) &&
              (src->data[cury][curx].rgb[1] != borderc.c[1]) &&
              (src->data[cury][curx].rgb[2] != borderc.c[2]) ){
            curx--;
        }
        curx++;
        
        // traverse the row, coloring until a boundary pixel is reached
        while( 	(src->data[cury][curx].rgb[0] != borderc.c[0]) &&
              (src->data[cury][curx].rgb[1] != borderc.c[1]) &&
              (src->data[cury][curx].rgb[2] != borderc.c[2]) ){
            
            // color active pixel
            image_setColor(src, cury, curx, fillc);
            
            // add pixels to the stack if above is clear and above right is not
            if( (src->data[cury+1][curx].rgb[0] != borderc.c[0]) &&
               (src->data[cury+1][curx].rgb[1] != borderc.c[1]) &&
               (src->data[cury+1][curx].rgb[2] != borderc.c[2]) &&
               (src->data[cury+1][curx].rgb[0] != fillc.c[0]) &&
               (src->data[cury+1][curx].rgb[1] != fillc.c[1]) &&
               (src->data[cury+1][curx].rgb[2] != fillc.c[2]) &&
               (src->data[cury+1][curx+1].rgb[0] == borderc.c[0]) &&
               (src->data[cury+1][curx+1].rgb[1] == borderc.c[1]) &&
               (src->data[cury+1][curx+1].rgb[2] == borderc.c[2]) ){
                curp.x = curx;
                curp.y = cury+1;
                stack[stacksize++] = curp;
            }
            // add pixels to the stack if below is clear and below right is not
            if( (src->data[cury-1][curx].rgb[0] != borderc.c[0]) &&
               (src->data[cury-1][curx].rgb[1] != borderc.c[1]) &&
               (src->data[cury-1][curx].rgb[2] != borderc.c[2]) &&
               (src->data[cury-1][curx].rgb[0] != fillc.c[0]) &&
               (src->data[cury-1][curx].rgb[1] != fillc.c[1]) &&
               (src->data[cury-1][curx].rgb[2] != fillc.c[2]) &&
               (src->data[cury-1][curx+1].rgb[0] == borderc.c[0]) &&
               (src->data[cury-1][curx+1].rgb[1] == borderc.c[1]) &&
               (src->data[cury-1][curx+1].rgb[2] == borderc.c[2]) ){
                curp.x = curx;
                curp.y = cury-1;
                stack[stacksize++] = curp;
            }
            // advance
            curx++;
        }
        
        // when a bounday ends the traversal, add above if clear
        if( (src->data[cury+1][curx-1].rgb[0] != borderc.c[0]) &&
           (src->data[cury+1][curx-1].rgb[1] != borderc.c[1]) &&
           (src->data[cury+1][curx-1].rgb[2] != borderc.c[2]) &&
           (src->data[cury+1][curx-1].rgb[0] != fillc.c[0]) &&
           (src->data[cury+1][curx-1].rgb[1] != fillc.c[1]) &&
           (src->data[cury+1][curx-1].rgb[2] != fillc.c[2]) ){
            curp.x = curx-1;
            curp.y = cury+1;
            stack[stacksize++] = curp;
        }
        // when a bounday ends the traversal, add below if clear
        if( (src->data[cury-1][curx-1].rgb[0] != borderc.c[0]) &&
           (src->data[cury-1][curx-1].rgb[1] != borderc.c[1]) &&
           (src->data[cury-1][curx-1].rgb[2] != borderc.c[2]) &&
           (src->data[cury-1][curx-1].rgb[0] != fillc.c[0]) &&
           (src->data[cury-1][curx-1].rgb[1] != fillc.c[1]) &&
           (src->data[cury-1][curx-1].rgb[2] != fillc.c[2]) ){
            curp.x = curx-1;
            curp.y = cury-1;
            stack[stacksize++] = curp;
        }
        printf("at end of loop, stack size = %d\n", stacksize);
    }

    printf("flood fill done\n");
    free(stack);
}
