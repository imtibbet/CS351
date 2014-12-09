/*
 * Author: Ian Tibbetts
 * Date: 9/19/14
 *
 * The color function implementations
 */

#include "graphics.h"

// Leader 

/*
 * set the leader shape to the module and assign defaults to other attributes
 */
void leader_init(Leader *l, Module *shape){

}

/*
 * set the leader location
 */
void leader_setLocation(Leader *l, Point *location){

}

/*
 * set the leader velocity
 */
void leader_setVelocity(Leader *l, Vector *velocity){

}

/*
 * set the leader color
 */
void leader_setColor(Leader *l, Color *c){

}

// Actor

/*
 * set the actor shape to the module and assign defaults to other attributes
 */
void actor_init(Actor *a, Module *shape){

}

/*
 * set the actor location
 */
void actor_setLocation(Actor *a, Point *location){

}

/*
 * set the actor velocity
 */
void actor_setVelocity(Actor *a, Vector *velocity){

}

/*
 * set the actor color
 */
void actor_setColor(Actor *a, Color *c){

}

/*
 * set the actor's boss, which informs the actor how to update
 */
void actor_setBoss(Actor *a, Leader *boss){

}

/*
 * update the actor's location according to:
 * -moving towards the leader
 * -staying a minimum distance from other actors
 */
void actor_update(Actor *a, Leader *boss, Actor *others){

}

// Swarm

/*
 * Place a swarm at start with a number of leaders that all have 
 * the same initial velocity. 
 */
Swarm *swarm_create(Point *start, Vector *initVel, int numLeaders, int numActors){

}




