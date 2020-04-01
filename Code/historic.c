#include "historic.h"

/// ///////
/// ///////
void HIST_init( Hist* historic )
{
    NodeHist* new_node;
    new_node = (NodeHist*)malloc( sizeof(NodeHist) );

    historic->head = new_node;
    historic->current_position = new_node;

    new_node->next = NULL;
    new_node->back = NULL;
    new_node->point.x = -1;
    new_node->point.y = -1;

}

/// ///////
/// ///////
void HIST_stack( Hist* historic, Point point )
{
    NodeHist* new_node;

    HIST_unstack( historic );

    new_node = (NodeHist*)malloc( sizeof(NodeHist) );

    new_node->next = NULL;
    new_node->back = historic->head;
    new_node->point = point;

    if( historic->head !=  NULL )
        historic->head->next = new_node;

    historic->head = new_node;
    historic->current_position = new_node;

}

/// ///////
/// ///////
void HIST_unstack( Hist* historic)
{
    NodeHist* temp;

    if( historic->head != NULL )
    {
        while( historic->head != historic->current_position )
        {
            temp = historic->head;
            historic->head = historic->head->back;

            free( temp );
        }

        historic->current_position->next = NULL;
    }

}

/// ///////
/// ///////
void HIST_free( Hist* historic )
{
    NodeHist* temp;

    if( historic->head != NULL )
    {
        while( historic->head != NULL )
        {
            temp = historic->head;
            historic->head = historic->head->back;

            free( temp );
        }

    }

}

/// ///////
/// ///////
void HIST_print( Hist* historic )
{
    NodeHist* read;
    read = historic->head;

    printf("\n\n");
    while( read != NULL )
    {
        printf("x:%d y:%d\n", read->point.x, read->point.y );
        read = read->back;
    }
    printf("\n\n");

}

/// ///////
/// ///////
Point HIST_back( Hist* historic )
{
    Point temp;
    temp = historic->current_position->point;

    if( historic->current_position->back == NULL )
    {
        return temp;
    }
    else
    {
        historic->current_position = historic->current_position->back;
        return temp;
    }

}

/// ///////
/// ///////
Point HIST_next( Hist* historic )
{

    if( historic->current_position->next == NULL )
    {
        return historic->current_position->point;
    }
    else
    {
        historic->current_position = historic->current_position->next;
        return historic->current_position->point;
    }
}

/// ///////
/// ///////
bool HIST_is_top_of_stack( Hist* historic )
{
    return historic->current_position->next == NULL;
}

/// ///////
/// ///////
bool HIST_is_bottom_of_stack( Hist* historic )
{
    return historic->current_position->back == NULL;
}
