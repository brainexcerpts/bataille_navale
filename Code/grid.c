#include "grid.h"

/// ///////
/// ///////
void print_grid( Grid* g )
{
    int i,j;
    for ( i=0; i<10 ; i++ )
    {
        for ( j=0; j<10 ; j++ )
        {
            if((*g)[j][i].area == SEA)
                fprintf(stderr,". ");
            else
                fprintf(stderr,"%d ",(int)(*g)[j][i].area);

        }
        fprintf(stderr,"\n");
    }
    fprintf(stderr,"\n");
}

/// ///////
/// ///////
void init_grid( Grid* a_grid )
{
    int i;

    // Allocation of 100 case
    (*a_grid) = (Case**)malloc( sizeof(Case*) * 10 );

    for ( i=0; i<10; i++)
    {
        (*a_grid)[i] = (Case*)malloc( sizeof(Case) * 10 );
    }

    reset_grid( a_grid );
}

/// ///////
/// ///////
void reset_grid( Grid* g )
{
    int j,k;
    // Look down the grid
    for ( j=0; j<10 ; j++ )
    {
        for ( k=0; k<10 ; k++ )
        {
        	(*g)[j][k].area = SEA;
        	(*g)[j][k].shoot = false;
        	(*g)[j][k].touch = false;
        	(*g)[j][k].origin = false;
        	(*g)[j][k].sink = false;
        	(*g)[j][k].position = NOLAYOUT;
        }
    }
}

/// ///////
/// ///////
void close_grid( Grid* g )
{

    int i;
    for ( i=0; i<10; i++)
    {
        free( (*g)[i] );
    }

    free(*g);

}

/// ///////
/// ///////
void set_layout( Grid* g, int x, int y, Layout position )
{
    (*g)[x][y].position = position;
}

/// ///////
/// ///////
Action do_shoot( Grid* g, int x, int y )
{
    int i, nbr = 0;
    int tab[4][2];
    (*g)[x][y].shoot = true;

    if((*g)[x][y].area==SEA) return MISS;

    (*g)[x][y].touch = true;

    for( i=x ; i<=9 ; i++ )
    {
        if((*g)[i][y].area!=SEA)
        {
            if(!(*g)[i][y].touch) return TOUCH;
            else
            {
                tab[nbr][0] = i;
                tab[nbr][1] = y;
                nbr++;
            }
        }
        else break;
    }

    for( i=x-1 ; i>=0 ; i-- )
    {
        if((*g)[i][y].area!=SEA)
        {
            if(!(*g)[i][y].touch) return TOUCH;
            else
            {
                tab[nbr][0] = i;
                tab[nbr][1] = y;
                nbr++;
            }
        }
        else break;
    }

    for( i=y+1 ; i<=9 ; i++ )
    {
        if((*g)[x][i].area!=SEA)
        {
            if(!(*g)[x][i].touch) return TOUCH;
            else
            {
                tab[nbr][0] = x;
                tab[nbr][1] = i;
                nbr++;
            }
        }
        else break;
    }

    for( i=y-1 ; i>=0 ; i-- )
    {
        if((*g)[x][i].area!=SEA)
        {
            if(!(*g)[x][i].touch) return TOUCH;
            else
            {
                tab[nbr][0] = x;
                tab[nbr][1] = i;
                nbr++;
            }
        }
        else break;
    }

    for( i=0 ; i!=nbr ; i++ )
    {
        (*g)[tab[i][0]][tab[i][1]].sink = true;
    }

    return SINK;
}

/// ///////
/// ///////
void undo_shoot( Grid* g, int x, int y )
{
    int i;
    (*g)[x][y].shoot = false;

    if((*g)[x][y].area!=SEA)
    {
        (*g)[x][y].touch = false;

        if((*g)[x][y].sink==false) return;

        for( i=x ; i<=9 ; i++ )
        {
            if((*g)[i][y].area!=SEA)
            {
                (*g)[i][y].sink = false;
            }
            else break;
        }

        for( i=x-1 ; i>=0 ; i-- )
        {
            if((*g)[i][y].area!=SEA)
            {
                (*g)[i][y].sink = false;
            }
            else break;
        }

        for( i=y+1 ; i<=9 ; i++ )
        {
            if((*g)[x][i].area!=SEA)
            {
                (*g)[x][i].sink = false;
            }
            else break;
        }

        for( i=y-1 ; i>=0 ; i-- )
        {
            if((*g)[x][i].area!=SEA)
            {
                (*g)[x][i].sink = false;
            }
            else break;
        }
    }
}

/// ///////
/// ///////
TypeArea get_type( Grid* g, int x, int y )
{
    return (*g)[x][y].area;
}

/// ///////
/// ///////
void set_type_layout( Grid* g, int x, int y, TypeArea type, Layout position )
{
    (*g)[x][y].area = type;
    (*g)[x][y].position = position;
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
bool is_inside_grid( int x, int y )
{
    return ((x>=0) && (x<10) && (y>=0) && (y<10));
}

/// ///////
/// ///////
bool is_boat( Grid* g, int x, int y )
{
    return ((*g)[x][y].area == PORTE_AVION ||
           (*g)[x][y].area == CROISEUR ||
           (*g)[x][y].area ==  DESTROYER ||
           (*g)[x][y].area ==  VEDETTE );
}

/// ///////
/// ///////
void random_grid( Grid* g )
{
    /// Init
    int rand_position;
    int x;
    int y;
    int set_boat = 0;

    reset_grid( g );
    /*-------*/

    while( set_boat < 10 )
    {

        rand_position = rand_number(2);
        x = rand_number(10);
        y = rand_number(10);


        /// Vertical position
        if( rand_position )
        {

            // Set PORTE_AVION
            if( set_boat == 0 )
            {
                if( is_neighbour_boat( g, x, y, PORTE_AVION, VERTICAL) )
                    continue;

                set_origin( g, x, y, true);
                set_type_layout( g, x, y, PORTE_AVION, VERTICAL );
                set_type_layout( g, x, y+1, PORTE_AVION, VERTICAL );
                set_type_layout( g, x, y+2, PORTE_AVION, VERTICAL );
                set_type_layout( g, x, y+3, PORTE_AVION, VERTICAL );
                set_boat++;

            }else
            // Set CROISEUR
            if( set_boat > 0 && set_boat < 3 )
            {

                if( is_neighbour_boat( g, x, y, CROISEUR, VERTICAL) )
                    continue;

                set_origin( g, x, y, true);
                set_type_layout( g, x, y, CROISEUR, VERTICAL );
                set_type_layout( g, x, y+1, CROISEUR, VERTICAL );
                set_type_layout( g, x, y+2, CROISEUR, VERTICAL );
                set_boat++;

            }else
            // Set DESTROYER
            if( set_boat >= 3 && set_boat < 6 )
            {

                if( is_neighbour_boat( g, x, y, DESTROYER, VERTICAL) )
                    continue;

                set_origin( g, x, y, true);
                set_type_layout( g, x, y, DESTROYER, VERTICAL );
                set_type_layout( g, x, y+1, DESTROYER, VERTICAL );
                set_boat++;

            }else
            // Set VEDETTE
            if( set_boat >= 6 && set_boat < 10 )
            {
                 if( is_neighbour_boat( g, x, y, VEDETTE, NOLAYOUT) )
                   continue;


                set_origin( g, x, y, true);
                set_type_layout( g, x, y, VEDETTE, NOLAYOUT );
                set_boat++;
            }


        }/// Or Horizontal position
        else
        {
            // Set PORTE_AVION
            if( set_boat == 0 )
            {
                if( is_neighbour_boat( g, x, y, PORTE_AVION, HORIZONTAL) )
                    continue;

                set_origin( g, x, y, true);
                set_type_layout( g, x, y, PORTE_AVION, HORIZONTAL );
                set_type_layout( g, x+1, y, PORTE_AVION, HORIZONTAL );
                set_type_layout( g, x+2, y, PORTE_AVION, HORIZONTAL );
                set_type_layout( g, x+3, y, PORTE_AVION, HORIZONTAL );
                set_boat++;

            }else
            // Set CROISEUR
            if( set_boat > 0 && set_boat < 3 )
            {
                if( is_neighbour_boat( g, x, y, CROISEUR, HORIZONTAL) )
                    continue;

                set_origin( g, x, y, true);
                set_type_layout( g, x, y, CROISEUR, HORIZONTAL );
                set_type_layout( g, x+1, y, CROISEUR, HORIZONTAL );
                set_type_layout( g, x+2, y, CROISEUR, HORIZONTAL );
                set_boat++;

            }else
            // Set DESTROYER
            if( set_boat >= 3 && set_boat < 6 )
            {
                if( is_neighbour_boat( g, x, y, DESTROYER, HORIZONTAL) )
                    continue;

                set_origin( g, x, y, true);
                set_type_layout( g, x, y, DESTROYER, HORIZONTAL );
                set_type_layout( g, x+1, y, DESTROYER, HORIZONTAL );
                set_boat++;

            }else
            // Set VEDETTE
            if( set_boat >= 6 && set_boat < 10 )
            {
                 if( is_neighbour_boat( g, x, y, VEDETTE, NOLAYOUT) )
                    continue;

                set_origin( g, x, y, true);
                set_type_layout( g, x, y, VEDETTE, NOLAYOUT );
                set_boat++;

            }

        }//IF

    }// while( set_boat<10 )


}

/// ///////
/// ///////
bool is_valid_point(Grid* g, int x, int y)
{
    bool status = true;

    if( is_inside_grid(x, y) )
        status &= ( (*g)[x][y].area == SEA );
    else
        return false;


    if( is_inside_grid(x+1, y+1) )
       status &= ( (*g)[x+1][y+1].area == SEA );

    if( is_inside_grid(x+1, y) )
        status &= ( (*g)[x+1][y].area == SEA );

    if( is_inside_grid(x, y+1) )
        status &= ( (*g)[x][y+1].area == SEA );

    if( is_inside_grid(x, y-1) )
        status &= ( (*g)[x][y-1].area == SEA );

    if( is_inside_grid(x-1, y) )
        status &= ( (*g)[x-1][y].area == SEA );

    if( is_inside_grid(x-1, y-1) )
        status &= ( (*g)[x-1][y-1].area == SEA );

    if( is_inside_grid(x-1, y+1) )
        status &= ( (*g)[x-1][y+1].area == SEA );

    if( is_inside_grid(x+1, y-1) )
        status &= ( (*g)[x+1][y-1].area == SEA );

    return status;
}

/// ///////
/// ///////
bool is_neighbour_boat(Grid* g, int x, int y, TypeArea boat_type, Layout layout)
{
    if( layout == VERTICAL )
    {
        switch( boat_type )
        {
            case PORTE_AVION:
                return !(
                        is_valid_point( g, x, y) &&
                        is_valid_point( g, x, y+1) &&
                        is_valid_point( g, x, y+2) &&
                        is_valid_point( g, x, y+3)
                        );
            break;

            case CROISEUR:
                return !(is_valid_point( g, x, y) &&
                        is_valid_point( g, x, y+1) &&
                        is_valid_point( g, x, y+2));
            break;

            case DESTROYER:
                return !(is_valid_point( g, x, y) &&
                        is_valid_point( g, x, y+1));
            break;

            default: break;

        }// End SWITCH
    }
    else if( layout == HORIZONTAL )
    {
        switch( boat_type )
        {
            case PORTE_AVION:
                return !(is_valid_point( g, x, y) &&
                        is_valid_point( g, x+1, y) &&
                        is_valid_point( g, x+2, y) &&
                        is_valid_point( g, x+3, y));
            break;

            case CROISEUR:
                return !(is_valid_point( g, x, y) &&
                        is_valid_point( g, x+1, y) &&
                        is_valid_point( g, x+2, y));
            break;

            case DESTROYER:
                return !(is_valid_point( g, x, y) &&
                        is_valid_point( g, x+1, y));
            break;

            default: break;

        }// End SWITCH
    }else if( (boat_type==VEDETTE) && (layout==NOLAYOUT) )
        return !is_valid_point( g, x, y);


    return false;
}

bool is_finish( Grid* g )
{
    int i, j;

    for( j=0 ; j!=10 ; j++ )
        for( i=0 ; i!=10 ; i++ )
            if((*g)[i][j].area!=SEA && !(*g)[i][j].touch) return false;

    return true;
}
