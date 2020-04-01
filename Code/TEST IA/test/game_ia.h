#ifndef GAME_IA
#define GAME_IA

#include "types.h"
#include "grid.h"
#include "rand.h"

Point IA_action(Grid player, Difficulty d);

Point IA_rand( int *tab);
int IA_size_boat_min( Grid* g );
void IA_hard( int *tab , int boat_min );
Point IA_shoot( Grid* g, int *tab , int x, int y );

#endif
