/// About historic :
/**
    historic is a kind of stack.
    But it's also possible two look down inside the stack both way.

    example :

    Hist historic;
    HIST_init( historic );

    First we do some HIST_stack( historic, point );
    with 3 points (1.1) (2.2) (3.3)

    *-----*
    | 3.3 |<- head | current_position
    *-----*
    | 2.2 |
    *-----*
    | 1.1 |
    *-----*

    Then we move the current position with HIST_back or HIST_next.
    Use back to reach the bottom of the stack, and next to the top.

    HIST_back( &historic );

    *-----*
    | 3.3 |<- head
    *-----*
    | 2.2 |<- current_position
    *-----*
    | 1.1 |
    *-----*

    returned value : 3.3

    HIST_next( &historic );
    *-----*
    | 3.3 |<- head | current_position
    *-----*
    | 2.2 |
    *-----*
    | 1.1 |
    *-----*

    returned value : 3.3

    Be aware that stack also erase the elements from current_postion until the head :

    If we do HIST_stack( historic, 6.6 ); with this stack :
    *-----*
    | 3.3 |<- head
    *-----*
    | 2.2 |
    *-----*
    | 1.1 |<- current_position
    *-----*

    The result is :

    *-----*
    | 6.6 |<- head | current_position
    *-----*
    | 1.1 |
    *-----*

    Limited case :

    Hist_next on this stack returned x.y
    *-----*
    | x.y |<- head | current_position
    *-----*
    | i.j |
    *-----*

    Hist_back on this stack always returned -1.-1
    *-----*
    | x.y |<- head
    *-----*
    | i.j |<- current_position
    *-----*

    N.B :
    Do not forget to free memory with HIST_free();


*/

/**

    Author : Rodolphe Vaillant-David :
	Creation date :     23/03/2008
	Last modification : 23/03/2008

    HIST_init()
    void HIST_free()
    HIST_stack()
    HIST_back()
    HIST_next()
    HIST_is_top_of_stack()
    HIST_is_bottom_of_stack()
    HIST_print()
    HIST_unstack()

*/


#ifndef HISTORIC_INCLUDED
#define HISTORIC_INCLUDED

#include "types.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct s_node_hist {

    Point point;
    struct s_node_hist* next; // go towards the  head
    struct s_node_hist* back; // go towards the tail

}NodeHist;

typedef struct {

    NodeHist* head;
    NodeHist* current_position;

}Hist;

void HIST_init( Hist* historic );
void HIST_free( Hist* historic );

void HIST_stack( Hist* historic, Point point );

Point HIST_back( Hist* historic );
Point HIST_next( Hist* historic );

bool HIST_is_top_of_stack( Hist* historic );
bool HIST_is_bottom_of_stack( Hist* historic );

/// Users doesn't need these function :
void HIST_print( Hist* historic );
void HIST_unstack( Hist* historic );

#endif // HISTORIC_INCLUDED
