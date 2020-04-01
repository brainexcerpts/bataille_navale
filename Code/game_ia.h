#ifndef GAME_IA
#define GAME_IA

/**

	Author : Claverie Paul
	Creation date :     23/03/2008
	Last modification : 23/03/2008

	IA_action()
    IA_rand()
    IA_size_boat_min()
    IA_hard()
    IA_shoot()

*/

#include "types.h"
#include "grid.h"
#include "rand.h"

// Returns an IA shoot considering the grid an difficulty
Point IA_action(Grid player, Difficulty d);

// Returns a random possible shoot
Point IA_rand( int *tab);

// returns size of the smallest boat remaining not sinking
int IA_size_boat_min( Grid* g );

// Delete cases where rules forbid boats to be.
void IA_hard( int *tab , int boat_min );

// returns a point beside a touch boat
Point IA_shoot( Grid* g, int *tab , int x, int y );

#endif
