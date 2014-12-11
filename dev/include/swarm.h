#ifndef SWARM_H

#define SWARM_H

typedef struct {
	Point location;
	Vector velocity;
	Module *shape;
	Color color;
} Leader;

typedef struct {
	Point location;
	float dispersion;
	float speed;
	Module *shape;
	Color color;
	Leader *boss;
} Actor;

typedef struct {
	int numLeaders;
	int numActors;
	Leader *leaders;
	Actor *actors;
} Swarm;

// Leader 

/*
 * set the leader shape to the module and assign defaults to other attributes
 */
void leader_init(Leader *l);

/*
 * set the leader location
 */
void leader_setLocation(Leader *l, Point *location);

/*
 * set the leader velocity
 */
void leader_setVelocity(Leader *l, Vector *velocity);

/*
 * set the leader color
 */
void leader_setColor(Leader *l, Color *c);

/*
 * update the leader's location
 */
void leader_update(Leader *l);

/*
 * set the Module* shape of the leader
 */
 void leader_setModule(Leader *l, Module *shape);

// Actor

/*
 * set the actor shape to the module and assign defaults to other attributes
 */
void actor_init(Actor *a, Leader *boss);

/*
 * set the actor location
 */
void actor_setLocation(Actor *a, Point *location);

/*
 * set the actor speed
 */
void actor_setSpeed(Actor *a, float speed);

/*
 * set the actor dispersion
 */
void actor_setDispersion(Actor *a, float dispersion);

/*
 * set the actor color
 */
void actor_setColor(Actor *a, Color *c);

/*
 * set the actor's boss, which informs the actor how to update
 */
void actor_setBoss(Actor *a, Leader *boss);

/*
 * update the actor's location according to:
 * -moving towards the leader
 * -staying a minimum distance from other actors
 */
void actor_update(Actor *a, Actor *others, int nothers);

/*
 * set the Module* shape of the leader
 */
 void actor_setModule(Actor *a, Module *shape);

// Swarm

/*
 * Place a swarm at start with a number of leaders that all have 
 * the same initial velocity. 
 */
Swarm *swarm_create(Point *start, Vector *initVel, int numLeaders, int numActors);

/*
 * free the swarm memory, setting numbers to zero
 */
void swarm_clear(Swarm *s);

/*
 * free the swarm memory, including the pointer to the swarm
 */
void swarm_free(Swarm *s);

/*
 * update the swarm's leaders and actors
 */
void swarm_update(Swarm *s);



#endif
