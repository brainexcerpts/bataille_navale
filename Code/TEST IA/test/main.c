#include "main.h"

void affiche(Grid* g)
{
    int i,j;

    for( j=0 ; j!=10 ; j++ )
    {
        for( i=0 ; i!=10 ; i++ )
        {
            if(is_boat( g, i, j ))
            {
                if(is_shoot( g, i, j )) printf("T");
                else printf("O");
            }
            else if(is_shoot( g, i, j )) printf("x");
            else printf(".");
        }
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    int i, j;
    Point pt;
    Grid player_grid;
    init_grid( &player_grid );
    //init_rand_number();
    Action act;

    scanf("%d",&i);
    fflush(stdin);
    srand(i);

    set_type( &player_grid, 1, 1, PORTE_AVION);
    set_type( &player_grid, 2, 1, PORTE_AVION);
    set_type( &player_grid, 3, 1, PORTE_AVION);
    set_type( &player_grid, 4, 1, PORTE_AVION);

    set_type( &player_grid, 7, 1, CROISEUR);
    set_type( &player_grid, 7, 2, CROISEUR);
    set_type( &player_grid, 7, 3, CROISEUR);

    set_type( &player_grid, 2, 4, CROISEUR);
    set_type( &player_grid, 2, 5, CROISEUR);
    set_type( &player_grid, 2, 6, CROISEUR);

    set_type( &player_grid, 4, 3, DESTROYER);
    set_type( &player_grid, 5, 3, DESTROYER);

    set_type( &player_grid, 0, 8, DESTROYER);
    set_type( &player_grid, 0, 9, DESTROYER);

    set_type( &player_grid, 6, 8, DESTROYER);
    set_type( &player_grid, 7, 8, DESTROYER);

    set_type( &player_grid, 5, 5, VEDETTE);

    set_type( &player_grid, 8, 5, VEDETTE);

    set_type( &player_grid, 4, 7, VEDETTE);

    set_type( &player_grid, 3, 9, VEDETTE);

    affiche(&player_grid);
    scanf("%d",&i);
    fflush(stdin);

    j = 0;
    while(j!=100)
    {
        pt = IA_action(player_grid, HARD); // EASY, MEDIUM, HARD
        act = do_shoot( &player_grid, pt.x, pt.y );

        affiche(&player_grid);

        if(act==MISS)  printf("rater\n");
        if(act==TOUCH) printf("toucher\n");
        if(act==SINK)  printf("couler\n");

        scanf("%d",&i);
        fflush(stdin);
        j++;
    }

    //int i;
    //random_grid(&player_grid);
    //affiche(&player_grid);

    scanf("%d",&i);
    return 0;
}
