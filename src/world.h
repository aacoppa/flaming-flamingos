#ifndef WORLD_7KJMKBX3

#define WORLD_7KJMKBX3

#include "interface.h"

/* List of objects in the world
 */
int num_objects;
object ** objects;
//TO BE PUBLICLY CALLED
void go();
//Calls the next two functions...
void display_objects();
void update_objects();

//Called in update objects
void update_velocities();
void update_positions();

struct point eye;
    /* First update positions and check for collisions
     *
     */


#endif /* end of include guard: WORLD_7KJMKBX3 */