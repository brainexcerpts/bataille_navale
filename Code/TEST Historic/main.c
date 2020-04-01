#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "historic.h"


int main()
{
    bool etat = true;
    Hist historic;
    Point point,temp;

    HIST_init( &historic );

    temp = HIST_back( &historic );

    if( temp.x == -1 && temp.y == -1 )
        printf("(%d,%d)HIST_back( hist_vide ) OK\n",temp.x,temp.y);
    else
    {
        printf("(%d,%d)HIST_back( hist_vide ) FAIL\n",temp.x,temp.y);
        etat = false;
    }

    puts("\n");//////////////////////////////////////////////////////////////

    point.x = 1;
    point.y = 1;
    HIST_stack( &historic, point );

    point.x = 2;
    point.y = 2;
    HIST_stack( &historic, point );

    point.x = 3;
    point.y = 3;
    HIST_stack( &historic, point );

    printf("HIST_stack(1,1)\n");
    printf("HIST_stack(2,2)\n");
    printf("HIST_stack(3,3)\n");

    puts("\n");///////////////////////////////////////////////////////////////

    temp = HIST_back( &historic );
    if( temp.x == 3 && temp.y == 3 )
        printf("(%d,%d) = HIST_back() OK\n",temp.x,temp.y);
    else
    {
        printf("(%d,%d)HIST_back() FAIL\n",temp.x,temp.y);
        etat = false;
    }


    temp = HIST_back( &historic );
    if( temp.x == 2 && temp.y == 2 )
        printf("(%d,%d) = HIST_back() OK\n",temp.x,temp.y);
    else
    {
        printf("(%d,%d)HIST_back() FAIL\n",temp.x,temp.y);
        etat = false;
    }

    temp = HIST_back( &historic );
    if( temp.x == 1 && temp.y == 1 )
       printf("(%d,%d) = HIST_back() OK\n",temp.x,temp.y);
    else
    {
        printf("(%d,%d)HIST_back() FAIL\n",temp.x,temp.y);
        etat = false;
    }

    if( HIST_is_bottom_of_stack( &historic ) )
        printf("HIST_is_bottom_of_stack() OK\n");
    else
    {
        printf("HIST_is_bottom_of_stack() FAIL\n");
        etat = false;
    }

    int i;
    for ( i=0; i<10 ; i++ )
    {
        temp = HIST_back( &historic );
        if(temp.x != -1 || temp.y != -1)
            etat = false;
    }

    puts("");

    temp = HIST_next( &historic );
    if( temp.x == 1 && temp.y == 1 )
       printf("(%d,%d) = HIST_next() OK\n",temp.x,temp.y);
    else
    {
        printf("(%d,%d) = HIST_next() FAIL\n",temp.x,temp.y);
        etat = false;
    }


     temp = HIST_next( &historic );
    if( temp.x == 2 && temp.y == 2 )
       printf("(%d,%d) = HIST_next() OK\n",temp.x,temp.y);
    else
    {
        printf("(%d,%d) = HIST_next() FAIL\n",temp.x,temp.y);
        etat = false;
    }

    temp = HIST_next( &historic );
    if( temp.x == 3 && temp.y == 3 )
       printf("(%d,%d) = HIST_next() OK\n",temp.x,temp.y);
    else
    {
        printf("(%d,%d) = HIST_next() FAIL\n",temp.x,temp.y);
        etat = false;
    }

    if( HIST_is_top_of_stack( &historic ) )
        printf("HIST_is_top_of_stack() OK\n");
    else
    {
        printf("HIST_is_top_of_stack FAIL\n");
        etat = false;
    }

    for ( i=0; i<10 ; i++ )
    {
        temp = HIST_next( &historic );
        if(temp.x != 3 || temp.y != 3)
            etat = false;
    }

    puts("");///////////////////////////////////////////////////////////////

    temp = HIST_back( &historic );
    if( temp.x == 3 && temp.y == 3 )
        printf("(%d,%d) = HIST_back() OK\n",temp.x,temp.y);
    else
    {
        printf("(%d,%d) = HIST_back() FAIL\n",temp.x,temp.y);
        etat = false;
    }

    puts("");///////////////////////////////////////////////////////////////

    point.x = 6;
    point.y = 6;
    HIST_stack( &historic, point );

    point.x = 7;
    point.y = 7;
    HIST_stack( &historic, point );

    printf("HIST_stack(6,6)\n");
    printf("HIST_stack(7,7)\n");

    puts("");///////////////////////////////////////////////////////////////

    temp = HIST_back( &historic );
    if( temp.x == 7 && temp.y == 7 )
        printf("(%d,%d) = HIST_back() OK\n",temp.x,temp.y);
    else
    {
        printf("(%d,%d) = HIST_back() FAIL\n",temp.x,temp.y);
        etat = false;
    }

    temp = HIST_back( &historic );
    if( temp.x == 6 && temp.y == 6 )
        printf("(%d,%d) = HIST_back() OK\n",temp.x,temp.y);
    else
    {
        printf("(%d,%d) = HIST_back() FAIL\n",temp.x,temp.y);
        etat = false;
    }

    temp = HIST_back( &historic );
    if( temp.x == 2 && temp.y == 2 )
        printf("(%d,%d) = HIST_back() OK\n",temp.x,temp.y);
    else
    {
        printf("(%d,%d) = HIST_back() FAIL\n",temp.x,temp.y);
        etat = false;
    }

    temp = HIST_back( &historic );
    if( temp.x == 1 && temp.y == 1 )
        printf("(%d,%d) = HIST_back() OK\n",temp.x,temp.y);
    else
    {
        printf("(%d,%d) = HIST_back() FAIL\n",temp.x,temp.y);
        etat = false;
    }

    if( HIST_is_bottom_of_stack( &historic ) )
        printf("HIST_is_bottom_of_stack() OK\n");
    else
    {
        printf("HIST_is_bottom_of_stack() FAIL\n");
        etat = false;
    }

    temp = HIST_back( &historic );
    if( temp.x == -1 && temp.y == -1 )
        printf("(%d,%d) = HIST_back() OK\n",temp.x,temp.y);
    else
    {
        printf("(%d,%d) = HIST_back() FAIL\n",temp.x,temp.y);
        etat = false;
    }

    if( HIST_is_bottom_of_stack( &historic ) )
        printf("HIST_is_bottom_of_stack() OK\n");
    else
    {
        printf("HIST_is_bottom_of_stack() FAIL\n");
        etat = false;
    }

    temp = HIST_next( &historic );
    if( temp.x == 1 && temp.y == 1 )
       printf("(%d,%d) = HIST_next() OK\n",temp.x,temp.y);
    else
    {
        printf("(%d,%d) = HIST_next() FAIL\n",temp.x,temp.y);
        etat = false;
    }

    temp = HIST_next( &historic );
    if( temp.x == 2 && temp.y == 2 )
       printf("(%d,%d) = HIST_next() OK\n",temp.x,temp.y);
    else
    {
        printf("(%d,%d) = HIST_next() FAIL\n",temp.x,temp.y);
        etat = false;
    }

    if( !HIST_is_bottom_of_stack( &historic ) )
        printf("false = HIST_is_bottom_of_stack() OK\n");
    else
    {
        printf("true = HIST_is_bottom_of_stack() FAIL\n");
        etat = false;
    }

    temp = HIST_next( &historic );
    if( temp.x == 6 && temp.y == 6 )
       printf("(%d,%d) = HIST_next() OK\n",temp.x,temp.y);
    else
    {
        printf("(%d,%d) = HIST_next() FAIL\n",temp.x,temp.y);
        etat = false;
    }

    if( !HIST_is_top_of_stack( &historic ) )
        printf("false = HIST_is_top_of_stack() OK\n");
    else
    {
        printf("true = HIST_is_top_of_stack FAIL\n");
        etat = false;
    }


    temp = HIST_next( &historic );
    if( temp.x == 7 && temp.y == 7 )
       printf("(%d,%d) = HIST_next() OK\n",temp.x,temp.y);
    else
    {
        printf("(%d,%d) = HIST_next() FAIL\n",temp.x,temp.y);
        etat = false;
    }

    if( HIST_is_top_of_stack( &historic ) )
        printf("true = HIST_is_top_of_stack() OK\n");
    else
    {
        printf("false = HIST_is_top_of_stack FAIL\n");
        etat = false;
    }





   if( etat )
        printf("TEST SUCCEED !\n");
    else
        printf("TEST FAIL !\n");

    HIST_free( &historic );


    return 0;
}
