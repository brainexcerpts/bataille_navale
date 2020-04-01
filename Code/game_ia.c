#include "game_ia.h"

/// /////
/// /////
Point IA_action(Grid player, Difficulty d)
{
    int i,j;
    int tab[100] = {0};

    /* Delete case already shoot */
    for( i=0 ; i!=10 ; i++ )
    {
        for( j=0 ; j!=10 ; j++ )
        {
            if(is_shoot( &player, i, j ))
                tab[i+j*10] = 1;
        }
    }

    // Easy mode nothing else than a random shoot
    if(d==EASY) return IA_rand(tab);

    // Medium & Hard delete case arround sinking boats
    for( i=0 ; i!=10 ; i++ )
    {
        for( j=0 ; j!=10 ; j++ )
        {
            if(is_sink( &player, i, j ))
            {
                if(i!=0 && j!=0) tab[ i-1 + (j-1)*10 ] = 1;
                if(i!=0)         tab[ i-1 +   j  *10 ] = 1;
                if(i!=0 && j!=9) tab[ i-1 + (j+1)*10 ] = 1;
                if(j!=0)         tab[  i  + (j-1)*10 ] = 1;
                if(j!=9)         tab[  i  + (j+1)*10 ] = 1;
                if(i!=9 && j!=0) tab[ i+1 + (j-1)*10 ] = 1;
                if(i!=9)         tab[ i+1 +   j  *10 ] = 1;
                if(i!=9 && j!=9) tab[ i+1 + (j+1)*10 ] = 1;
            }
        }
    }

    // Not apply for Medium mode
    if(d==HARD)
    {
        // Delete cases where boats cannot be.
        IA_hard( tab , IA_size_boat_min(&player) );
    }

    // Is a boat being previously touch
    for( i=0 ; i!=10 ; i++ )
    {
        for( j=0 ; j!=10 ; j++ )
        {
            if(is_shoot( &player, i, j ) && is_boat( &player, i, j ) && !is_sink( &player, i, j ))
            {
                return IA_shoot( &player, tab, i, j );
            }
        }
    }

    return IA_rand(tab);
}

/// /////
/// /////
Point IA_rand( int *tab)
{
    int n,i,j;
    Point p;

    n = 100;
    for( i=0 ; i!=100 ; i++ ) if(tab[i]==1) n--;

    n = rand_number(n);

    for( i=0 ; i!=10 ; i++ )
    {
        for( j=0 ; j!=10 ; j++ )
        {
            if(tab[i+j*10]==0)
            {
                if(n==0)
                {
                    p.x = i;
                    p.y = j;

                    return p;
                }

                n--;
            }
        }
    }

    p.x = 0;
    p.y = 0;

    return p;
}

/// /////
/// /////
int IA_size_boat_min( Grid* g )
{
    int i,j;
    int boat[4] = {0};
    int boat_size_min = 0;

    // Count number of case of sinking boat
    for( i=0 ; i!=10 ; i++ )
    {
        for( j=0 ; j!=10 ; j++ )
        {
            switch(get_type( g, i, j ))
            {
                case VEDETTE:
                    boat[0] += 1;
                    break;
                case DESTROYER:
                    boat[1] += 1;
                    break;
                case CROISEUR:
                    boat[2] += 1;
                    break;
                case PORTE_AVION:
                    boat[3] += 1;
                    break;
                default:
                    break;
            }
        }
    }

    boat[1] /= 2;
    boat[2] /= 3;
    boat[3] /= 4;

    if(boat[0]!=4) boat_size_min = 1;
    else if(boat[1]!=3) boat_size_min = 2;
    else if(boat[2]!=2) boat_size_min = 3;
    else if(boat[3]!=1) boat_size_min = 4;

    return boat_size_min;
}

/// /////
/// /////
void IA_hard( int *tab , int boat_min )
{
    int i,j,n;
    int tab2[100] = {0};

    if(boat_min==1) return; // We cannot del anything

    // Horyzontal
    for( j=0 ; j!=10 ; j++ )
    {
        n = 0;
        for( i=0 ; i!=10 ; i++ )
        {
            if(tab[i+j*10]==1)
            {
                if(n<boat_min) while(n--) tab2[i+j*10-n-1]++;
                n = 0;
            }
        }
        if(n<boat_min) while(n--) tab2[i+j*10-n-1]++;
    }

    // Vertical
    for( i=0 ; i!=10 ; i++ )
    {
        n = 0;
        for( j=0 ; j!=10 ; j++ )
        {
            if(tab[i+j*10]==1)
            {
                if(n<boat_min) while(n--) tab2[i+j*10-(n+1)*10]++;
                n = 0;
            }
        }
        if(n<boat_min) while(n--) tab2[i+j*10-(n+1)*10]++;
    }

     // Delete cases where boats cannot be.
    for( i=0 ; i!=10 ; i++ )
    {
        for( j=0 ; j!=10 ; j++ )
        {
            if(tab2[i+j*10]==1) tab[i+j*10] = 1;
        }
    }
}

/// /////
/// /////
Point IA_shoot( Grid* g, int *tab , int x, int y )
{
    Point tab2[4];
    int n, nbr_element = 0;

    if((x!=9 && is_shoot( g, x+1, y ) && is_boat( g, x+1, y )) ||
        (x!=0 && is_shoot( g, x-1, y ) && is_boat( g, x-1, y )))
    {
        // Horizontal boats
        while(is_shoot( g, x, y ) && is_boat( g, x, y ))
        {
            x--;
            if(x==-1) break;
        }
        if(x!=-1 && !is_shoot( g, x, y ) && tab[x+y*10]!=1)
        {
            tab2[nbr_element].x = x;
            tab2[nbr_element].y = y;
            nbr_element++;
        }

        x++;
        while(is_shoot( g, x, y ) && is_boat( g, x, y ))
        {
            x++;
            if(x==10) break;
        }
        if(x!=10 && !is_shoot( g, x, y ) && tab[x+y*10]!=1)
        {
            tab2[nbr_element].x = x;
            tab2[nbr_element].y = y;
            nbr_element++;
        }
    }
    else if((y!=9 && is_shoot( g, x, y+1 ) && is_boat( g, x, y+1 )) ||
    (y!=0 && is_shoot( g, x, y-1 ) && is_boat( g, x, y-1 )))
    {

        // Vertical boats
        while(is_shoot( g, x, y ) && is_boat( g, x, y ))
        {
            y--;
            if(y==-1) break;
        }
        if(y!=-1 && !is_shoot( g, x, y ) && tab[x+y*10]!=1)
        {
            tab2[nbr_element].x = x;
            tab2[nbr_element].y = y;
            nbr_element++;
        }

        y++;
        while(is_shoot( g, x, y ) && is_boat( g, x, y ))
        {
            y++;
            if(y==10) break;
        }
        if(y!=10 && !is_shoot( g, x, y ) && tab[x+y*10]!=1)
        {
            tab2[nbr_element].x = x;
            tab2[nbr_element].y = y;
            nbr_element++;
        }
    }
    else
    {
        if(x!=0 && !is_shoot( g, x-1, y ) && tab[x-1+y*10]!=1)
        {
            tab2[nbr_element].x = x-1;
            tab2[nbr_element].y = y;
            nbr_element++;
        }
        if(y!=0 && !is_shoot( g, x, y-1 ) && tab[x+(y-1)*10]!=1)
        {
            tab2[nbr_element].x = x;
            tab2[nbr_element].y = y-1;
            nbr_element++;
        }
        if(x!=9 && !is_shoot( g, x+1, y ) && tab[x+1+y*10]!=1)
        {
            tab2[nbr_element].x = x+1;
            tab2[nbr_element].y = y;
            nbr_element++;
        }
        if(y!=9 && !is_shoot( g, x, y+1 ) && tab[x+(y+1)*10]!=1)
        {
            tab2[nbr_element].x = x;
            tab2[nbr_element].y = y+1;
            nbr_element++;
        }
    }

    n = rand_number(nbr_element);

    return tab2[n];
}
