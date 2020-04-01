/**
    About grid :

    grid 10 by 10, sens of axes :

    O               9
     *------------> X
     |
     |
     |
     |
     |
   9 Y

    Origin : Only mark the nearest position of the top left corner of the grid
    Layout : Indicates for each case of a boat wether the boat is HORIZONTAL or VERTICAL ( constante defines within types.h )
    Shoot : do a shoot occure in this case
    Touch : is a boat touch in this case
    Sink : When sink each case of a boat are set to sink

*/

/**

    Author : Rodolphe Vaillant-David :
	Creation date :     23/03/2008
	Last modification : 23/03/2008

    void print_grid()
    void init_grid()
    void reset_grid()
    void close_grid()
    void random_grid()
    bool is_valid_point()
    bool is_neighbour_boat()
    void set_type()
    void set_layout()
    void set_type_layout()
    void set_touch()
    void set_sink()
    void set_origin()
    Layout get_layout()
    TypeArea get_type()
    bool is_boat()
    bool is_shoot()
    bool is_origin()
    bool is_touch()
    bool is_sink()
    bool is_inside_grid()

    Author : Claverie Paul

    bool is_finish()
    Action do_shoot()
    void undo_shoot()

*/


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
    Layout position; /* HORIZONTAL || VERTICAL || NOLAYOUT */

} Case;

typedef Case** Grid;



/// It's a grid 10*10 case
/// Each case is set to SEA and false and NOLAYOUT
void init_grid( Grid* a_grid );

/// Set each case to SEA and false and NOLAYOUT
void reset_grid( Grid* g );

/// Free memory of a grid
void close_grid(Grid* g);

/// Print on stderr the grid ( help to debug )
void print_grid( Grid* g );

/// Generate a random grid wich match rules of the games
void random_grid( Grid* g );

/// is the point (x,y) has no neighbour point to a boat included itself
/// is the point (x,y) is inside the grid
bool is_valid_point(Grid* g, int x, int y);

/// is the boat of origin (x,y) touching another boat
bool is_neighbour_boat(Grid* g, int x, int y, TypeArea boat_type, Layout layout);

/// just set a case to what you want
/// sometimes make a test to ensure format of the case is correct
void set_type( Grid* g, int x, int y, TypeArea type);
void set_layout( Grid* g, int x, int y, Layout position );
void set_type_layout( Grid* g, int x, int y, TypeArea type, Layout position );
void set_touch( Grid* g, int x, int y );
void set_sink( Grid* g, int x, int y );
void set_origin( Grid* g, int x, int y, bool origin);
/*-------------------------------------*/

/// Do a shoot on case (x,y)
/// returns : MISS || TOUCH || SINK
Action do_shoot( Grid* g, int x, int y );
void undo_shoot( Grid* g, int x, int y );


/// Just test the case
Layout get_layout( Grid* g, int x, int y );
TypeArea get_type( Grid* g, int x, int y );
bool is_boat( Grid* g, int x, int y );
bool is_shoot( Grid* g, int x, int y );
bool is_origin( Grid* g, int x, int y );
bool is_touch( Grid* g, int x, int y );
bool is_sink( Grid* g, int x, int y );
bool is_inside_grid( int x, int y );
bool is_finish( Grid* g );
/*--------------------------------------*/





#endif // GRID_H_INCLUDED
