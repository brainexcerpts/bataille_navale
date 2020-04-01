#include "grid.h"

/// ///////
/// ///////
void init_grid( Grid* a_grid )
{
    int i,j,k;

    // Allocation of 100 case
    (*a_grid) = (Case**)malloc( sizeof(Case*) * 10 );

    for ( i=0; i<10; i++)
    {
        (*a_grid)[i] = (Case*)malloc( sizeof(Case) * 10 );
    }

    // Look down the grid
    for ( j=0; j<10 ; j++ )
    {
        for ( k=0; k<10 ; k++ )
        {
        	(*a_grid)[j][k].area = SEA;
        	(*a_grid)[j][k].shoot = false;
        	(*a_grid)[j][k].touch = false;
        	(*a_grid)[j][k].origin = false;
        	(*a_grid)[j][k].sink = false;
        	(*a_grid)[j][k].position = NOLAYOUT;

        }

    }
}

/// ///////
/// ///////
void close_grid( Grid* a_grid )
{

    int i;
    for ( i=0; i<10; i++)
    {
        free( (*a_grid)[i] );
    }

    free(*a_grid);

}

/// ///////
/// ///////
void set_layout( Grid* g, int x, int y, Layout position )
{
    (*g)[x][y].position = position;
}

/// ///////
/// ///////
void do_shoot( Grid* g, int x, int y )
{
    (*g)[x][y].shoot = true;
}

/// ///////
/// ///////
void undo_shoot( Grid* g, int x, int y )
{
    (*g)[x][y].shoot = false;
}

/// ///////
/// ///////
TypeArea get_type( Grid* g, int x, int y )
{
    return (*g)[x][y].area;
}

/// ///////
/// ///////
void set_type( Grid* g, int x, int y, TypeArea type)
{
    (*g)[x][y].area = type;
}


/// ///////
/// ///////
void set_sink( Grid* g, int x, int y )
{
        (*g)[x][y].sink = true;
}

/// ///////
/// ///////
void set_origin( Grid* g, int x, int y, bool origin)
{
        (*g)[x][y].origin = origin;
}

/// ///////
/// ///////
void set_touch( Grid* g, int x, int y )
{
    (*g)[x][y].touch = true;
}

/// ///////
/// ///////
bool is_shoot( Grid* g, int x, int y )
{
    return (*g)[x][y].shoot;
}

/// ///////
/// ///////
bool is_origin( Grid* g, int x, int y  )
{
    if( (*g)[x][y].area==SEA && (*g)[x][y].origin==true  )
        error( "is_origin()","grid.c", "Grid corruption! Incorrect format!" );

    if( (*g)[x][y].area==UNKNOW && (*g)[x][y].origin==true  )
        error( "is_origin()","grid.c", "Grid corruption! Incorrect format!" );

    return (*g)[x][y].origin;
}

/// ///////
/// ///////
bool is_touch( Grid* g, int x, int y )
{
    return (*g)[x][y].touch;
}

/// ///////
/// ///////
bool is_sink( Grid* g, int x, int y )
{
    return (*g)[x][y].sink;
}

/// ///////
/// ///////
Layout get_layout( Grid* g, int x, int y )
{
    return (*g)[x][y].position;
}

/// ///////
/// ///////
bool is_valid_position( int x, int y )
{
    return ((x>0) && (x<9) && (y>0) && (y<9));
}

/// ///////
/// ///////
bool is_boat( Grid* g, int x, int y )
{
    return ((*g)[x][y].area == BOAT ||
           (*g)[x][y].area == PORTE_AVION ||
           (*g)[x][y].area == CROISEUR ||
           (*g)[x][y].area ==  DESTROYER ||
           (*g)[x][y].area ==  VEDETTE );
}
