/*
 * Author: Ian Tibbetts and Astrid Moore
 * Date: 12/2014
 *
 * The swarm
 */

#include "graphics.h"

static inline float point_dist(Point *x, Point *y){
	return 	(x->val[0] - y->val[0]) * (x->val[0] - y->val[0]) +
			(x->val[1] - y->val[1]) * (x->val[1] - y->val[1]) +
			(x->val[2] - y->val[2]) * (x->val[2] - y->val[2])
}

// Leader 

/*
 * set the leader shape to the module and assign defaults to other attributes
 */
void leader_init(Leader *l, Module *shape){
	point_set3D(&(l->location), 0.0, 0.0, 0.0);
	vector_set(&(l->velocity), 0.0, 0.0, 0.0);
	color_set(&(l->color), 1.0, 1.0, 1.0);
	l->shape = shape;
}

/*
 * set the leader location
 */
void leader_setLocation(Leader *l, Point *location){
	point_copy(&(l->location), location);
}

/*
 * set the leader velocity
 */
void leader_setVelocity(Leader *l, Vector *velocity){
	vector_copy(&(l->velocity), velocity);
}

/*
 * set the leader color
 */
void leader_setColor(Leader *l, Color *c){
	color_copy(&(l->color), c);
}

/*
 * update the leader's location
 */
void leader_update(Leader *l){
	leader->location.val[0] += leader->velocity.val[0];
	leader->location.val[1] += leader->velocity.val[1];
	leader->location.val[2] += leader->velocity.val[2];
}

// Actor

/*
 * set the actor shape to the module and assign defaults to other attributes
 */
void actor_init(Actor *a, Module *shape, Leader *boss){
	a->deflection = a->speed = 0.0;
	point_set3D(&(a->location), 0.0, 0.0, 0.0);
	color_set(&(a->color), 1.0, 1.0, 1.0);
	a->shape = shape;
	a->boss = boss;
}

/*
 * set the actor location
 */
void actor_setLocation(Actor *a, Point *location){
	point_copy(&(a->location), location);
}

/*
 * set the actor velocity
 */
void actor_setVelocity(Actor *a, Vector *velocity){
	vector_copy(&(a->velocity), velocity);
}

/*
 * set the actor color
 */
void actor_setColor(Actor *a, Color *c){
	color_copy(&(a->color), color);
}

/*
 * set the actor's boss, which informs the actor how to update
 */
void actor_setBoss(Actor *a, Leader *boss){
	a->boss = boss
}

/*
 * update the actor's location according to:
 * -moving towards their leader
 * -staying a minimum distance from other actors
 */
void actor_update(Actor *a, Actor *others, int nothers){
	int i, verbose = 1;
	if(verbose) printf("updating actor\n");
	float dist, closest[2];
	Actor closestActors[2];
	Vector toBoss, awayFromOthers, heading;
	Point otherAvgLoc;

	// find closest two actors
	for(i=0; i<nothers; i++){
		dist = point_dist(&(others[i].location), a->location);
		if(dist && (dist < closest[0])) {
			closest[0] = dist;
			closestActors[0] = others[i];
		}
	}
	for(i=0; i<nothers; i++){
		dist = point_dist(&(others[i].location), a->location);
		if(dist && (dist < closest[1]) && (dist != closest[0])) {
			closest[1] = dist;
			closestActors[1] = others[i];
		}
	}

	// calculate vector away from average position of others
	point_avg(&otherAvgLoc, &(closest[0].location), &(closest[1].location));
	vector_set(&awayFromOthers, a->location.val[0] - otherAvgLoc.val[0], 
								a->location.val[1] - otherAvgLoc.val[1], 
								a->location.val[2] - otherAvgLoc.val[2] );

	// calculate vector to leader
	vector_set(&toBoss, a->boss->location.val[0] - a->location.val[0],
						a->boss->location.val[1] - a->location.val[1],
						a->boss->location.val[2] - a->location.val[2] ); 

	// new heading is the average of the two (normalize them first?)
	vector_normalize(&toBoss); // by normalizing out bugs move at pretty constant speed
	vector_normalize(&awayFromOthers); // unless vectors totally agree/disagree
	vector_avg(&heading, &toBoss, &awayFromOthers);

	// update location according to new heading and speed
	a->location.val[0] += heading.val[0] * a->speed;
	a->location.val[1] += heading.val[1] * a->speed;
	a->location.val[2] += heading.val[2] * a->speed;
}

// Swarm

/*
 * Place a swarm at start with a number of leaders that all have 
 * the same initial velocity. 
 */
Swarm *swarm_create(Point *start, Vector *initVel, int numLeaders, int numActorsPerLeader){
	int i, j, verbose = 1;
	if(verbose) printf("creating swarm\n");
	Swarm *s = malloc(sizeof(Swarm));
	s->leaders = malloc(sizeof(Leader)*numLeaders);
	s->actors = malloc(sizeof(Actor)*numActorsPerLeader*numLeaders);
	s->numActors = numActorsPerLeader*numLeaders;
	s->numLeaders = numLeaders;
	for(i=0; i<numLeaders; i++){
		leader_init(&(s->leaders[i]));
		for(j=0; j<numActorsPerLeader; j++){
			actor_init(&(s->actors[j+(i*numActorsPerLeader)]));
		}
	}
}

/*
 * free the swarm memory, setting numbers to zero
 */
 swarm_clear(Swarm *s){
 	if(s){
 		if(s->leaders)
 			free(leaders);
 		if(s->actors)
 			free(actors);
 		s->numLeaders = s->numActors = 0;
 	}
 }

/*
 * free the swarm memory, including the pointer to the swarm
 */
 swarm_free(Swarm *s){
 	if(s){
 		if(s->leaders)
 			free(leaders);
 		if(s->actors)
 			free(actors);
 		free(s);
 	}
 }

/*
 *
 */
void swarm_update(Swarm *s){
	int i, verbose = 1;
	if(verbose) printf("updating swarm\n");
	for (i = 0; i < s->numActors; i++)
		actor_update(&(s->actors[i]));
	for (i = 0; i < s->numLeaders; i++)
		leader_update(&(s->leaders[i]));
}




