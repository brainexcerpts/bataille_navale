#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "types.h"
#include "error.h"


typedef struct {

    TypeArea area;
    bool shoot;
    bool touch;
    bool sink;
    bool origin;
    Layout position;

} Case;

typedef Case** Grid;



/**
    I : Grid*
    O : Case Grid[10][10]

    Author : RVD
    Creation date : 17/03/2008

    It's a grid 10*10 Case Each case is set to SEA
*/

void init_grid( Grid* a_grid );

/**
    I : Grid*
    O : void

    Author : RVD
    Creation date : 17/03/2008

    Free memory of a grid
*/
void close_grid(Grid* a_grid);


void set_type( Grid* g, int x, int y, TypeArea type);
TypeArea get_type( Grid* g, int x, int y );

void set_layout( Grid* g, int x, int y, Layout position );
void set_touch( Grid* g, int x, int y );
void set_sink( Grid* g, int x, int y );
void set_origin( Grid* g, int x, int y, bool origin);
Layout get_layout( Grid* g, int x, int y );


void do_shoot( Grid* g, int x, int y );
void undo_shoot( Grid* g, int x, int y );


bool is_boat( Grid* g, int x, int y );
bool is_shoot( Grid* g, int x, int y );
bool is_origin( Grid* g, int x, int y );
bool is_touch( Grid* g, int x, int y );
bool is_sink( Grid* g, int x, int y );
bool is_valid_position( int x, int y );



#endif // GRID_H_INCLUDED
