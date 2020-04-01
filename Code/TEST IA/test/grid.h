#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "types.h"
#include "error.h"
#include "rand.h"


typedef struct {

    TypeArea area;
    bool shoot;
    bool touch;
    bool sink;
    bool origin;
    Layout position;

} Case;

typedef Case** Grid;


/// It's a grid 10*10 Case Each case is set to SEA
void init_grid( Grid* a_grid );



/// Free memory of a grid
void close_grid(Grid* g);

void random_grid( Grid* g );

/// is the point (x,y) has no neighbour point set to BOAT
/// is the point (x'y) is inside the grid
bool is_valid_point(Grid* g, int x, int y);

/// is the boat of origin (x,y) touching another boat
/// origin is the top left corner of the boat
bool is_neighbour_boat(Grid* g, int x, int y, TypeArea boat_type, Layout layout);

void set_type( Grid* g, int x, int y, TypeArea type);
void set_layout( Grid* g, int x, int y, Layout position );
void set_touch( Grid* g, int x, int y );
void set_sink( Grid* g, int x, int y );
void set_origin( Grid* g, int x, int y, bool origin);
Action do_shoot( Grid* g, int x, int y );
void undo_shoot( Grid* g, int x, int y );


Layout get_layout( Grid* g, int x, int y );
TypeArea get_type( Grid* g, int x, int y );
bool is_boat( Grid* g, int x, int y );
bool is_shoot( Grid* g, int x, int y );
bool is_origin( Grid* g, int x, int y );
bool is_touch( Grid* g, int x, int y );
bool is_sink( Grid* g, int x, int y );
bool is_inside_grid( int x, int y );



#endif // GRID_H_INCLUDED
