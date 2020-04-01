#include "sdl_tool.h"

static SDL_Rect origin = { 0,0,0,0 };

/// ///////
/// ///////
void mouse_interface( SDL_Surface* background, SDL_Surface* sliding_surface[], SDL_Rect* rectangle[], int n/* number of rect */, int surface_to_test )
{
    /// Init
    SDL_Event event;
    SDL_Surface* highlighting = NULL;
    SDL_Surface* forbidden = NULL;

    SDL_Rect aligned_rect;
    /*----------*/

    highlighting = draw_highlighting_area();
    forbidden = draw_forbidden_area();

    while ( (event.type != SDL_MOUSEBUTTONDOWN || event.button.button == SDL_BUTTON_RIGHT) || is_forbiden_area( aligned_rect, sliding_surface, rectangle, surface_to_test )  )
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
            case SDL_MOUSEMOTION:


                /// Change the position of the sliding surface
                rectangle[surface_to_test]->x = event.motion.x - (sliding_surface[surface_to_test]->w/2);
                rectangle[surface_to_test]->y = event.motion.y - (sliding_surface[surface_to_test]->h/2);

                /// Prevent surface to be outside the window
                if ( rectangle[surface_to_test]->x < 0 )
                {
                    rectangle[surface_to_test]->x = 0;
                }

                if ( rectangle[surface_to_test]->x + sliding_surface[surface_to_test]->w > RES_WIDTH )
                {
                    rectangle[surface_to_test]->x = RES_WIDTH-sliding_surface[surface_to_test]->w;
                }

                if ( rectangle[surface_to_test]->y < 0 )
                {
                    rectangle[surface_to_test]->y = 0;
                }

                if (  rectangle[surface_to_test]->y + sliding_surface[surface_to_test]->h > RES_HEIGHT )
                {
                    rectangle[surface_to_test]->y = RES_HEIGHT-sliding_surface[surface_to_test]->h;
                }
                /*--------------------*/

                /// Find the aligned position
                aligned_rect.w = sliding_surface[surface_to_test]->w;
                aligned_rect.h = sliding_surface[surface_to_test]->h;

                aligned_rect.x = rectangle[surface_to_test]->x;
                aligned_rect.y = rectangle[surface_to_test]->y;

                align_surface(&aligned_rect);
                /*---------------------*/


                /// Print result
                SDL_BlitSurface(background, NULL, screen, &origin);

                if( !is_on_menu(sliding_surface[surface_to_test], &aligned_rect) )
                {
                    SDL_BlitSurface(highlighting, &aligned_rect, screen, &aligned_rect );

                    if( is_forbiden_area(aligned_rect, sliding_surface, rectangle, surface_to_test) )
                        SDL_BlitSurface(forbidden, &aligned_rect, screen, &aligned_rect );
                }

                SDL_BlitSurface(sliding_surface[surface_to_test], NULL, screen, rectangle[surface_to_test]);


                SDL_Flip( screen );
                /*---------------*/


            break;

            case SDL_MOUSEBUTTONDOWN :

                if ( event.button.button == SDL_BUTTON_RIGHT )
                {
                    boat_rotation( &(sliding_surface[surface_to_test]), rectangle[surface_to_test] );

                    /// Change the position of the sliding surface
                    rectangle[surface_to_test]->x = event.button.x - (sliding_surface[surface_to_test]->w/2);
                    rectangle[surface_to_test]->y = event.button.y - (sliding_surface[surface_to_test]->h/2);

                    /// Set the enlighten position
                    aligned_rect.w = sliding_surface[surface_to_test]->w;
                    aligned_rect.h = sliding_surface[surface_to_test]->h;

                    aligned_rect.x = rectangle[surface_to_test]->x;
                    aligned_rect.y = rectangle[surface_to_test]->y;

                    align_surface(&aligned_rect);
                    /*---------------------*/


                    /// Print result
                    SDL_BlitSurface(background, NULL, screen, &origin);

                    if( !is_on_menu(sliding_surface[surface_to_test], &aligned_rect) )
                    {
                        SDL_BlitSurface(highlighting, &aligned_rect, screen, &aligned_rect );

                        if( is_forbiden_area(aligned_rect, sliding_surface, rectangle, surface_to_test) )
                        SDL_BlitSurface(forbidden, &aligned_rect, screen, &aligned_rect );
                    }

                    SDL_BlitSurface(sliding_surface[surface_to_test], NULL, screen, rectangle[surface_to_test]);


                    SDL_Flip( screen );
                    /*---------------*/
                }


            break;

        }// End of SWITCH


    }// End of WHILE

    SDL_FreeSurface( highlighting);
    SDL_FreeSurface( forbidden );


}

/// ///////
/// ///////
void align_point( Point* point )
{
    point->x = (point->x-BLOC_SIZE*10-GRID_ORIGIN_X)/BLOC_SIZE;
    point->y = (point->y-GRID_ORIGIN_Y)/BLOC_SIZE;

}
/// ///////
/// ///////
void align_surface(SDL_Rect* rectangle)
{
    int bloc_left_corner_x, bloc_left_corner_y;
    int offset_x, offset_y;
    int position_in_bloc_x, position_in_bloc_y;


    /// Relative position of the surface in a bloc */
    position_in_bloc_x = rectangle->x%BLOC_SIZE;
    position_in_bloc_y = rectangle->y%BLOC_SIZE;

    /// The nearest bloc top left-corner relative position
    /// from the top left-corner of the surface
    /// relative : i.e calculate as though the grid was beginning at 0,0
    bloc_left_corner_x = ( rectangle->x - position_in_bloc_x ) ;
    bloc_left_corner_y = ( rectangle->y - position_in_bloc_y ) ;


    /// Offset of the grid
    offset_x = GRID_ORIGIN_X%BLOC_SIZE;
    offset_y = GRID_ORIGIN_Y%BLOC_SIZE;

    /// Update the relative position in order to have
    /// the absolute position of the bloc
    bloc_left_corner_x += offset_x;
    bloc_left_corner_y += offset_y;




    /**

    To align the surface on the grid I divide in four equal case the bloc :
    If the top left-corner of the surface is within one of these case
    I act on purpose.

    **/

    /// the top left-corner surface is on the top left-corner of the case
    if ( (position_in_bloc_x - offset_x <= (BLOC_SIZE/2)) && (position_in_bloc_y - offset_y <= (BLOC_SIZE/2)) )
    {
        rectangle->x = bloc_left_corner_x;
        rectangle->y = bloc_left_corner_y;
    }

    if ( (position_in_bloc_x - offset_x > (BLOC_SIZE/2)) && (position_in_bloc_y - offset_y <= (BLOC_SIZE/2)) )
    {
        rectangle->x = bloc_left_corner_x+BLOC_SIZE;
        rectangle->y = bloc_left_corner_y;
    }

    if ( (position_in_bloc_x - offset_x > (BLOC_SIZE/2)) && (position_in_bloc_y - offset_y > (BLOC_SIZE/2)) )
    {
        rectangle->x = bloc_left_corner_x+BLOC_SIZE;
        rectangle->y = bloc_left_corner_y+BLOC_SIZE;
    }

    if ( (position_in_bloc_x - offset_x <= (BLOC_SIZE/2)) && (position_in_bloc_y - offset_y > (BLOC_SIZE/2)) )
    {
        rectangle->x = bloc_left_corner_x;
        rectangle->y = bloc_left_corner_y+BLOC_SIZE;
    }

}

/// ///////
/// ///////
void boat_rotation( SDL_Surface** boat, SDL_Rect* rectangle )
{

    SDL_FreeSurface(*boat);

    if ( (*boat)->h > (*boat)->w )
    {

        switch ( (*boat)->h )
        {
            case BLOC_SIZE*2: *boat = SDL_LoadBMP( IMG_PATH("destroyer_2.bmp") ); break;

            case BLOC_SIZE*3: *boat = SDL_LoadBMP( IMG_PATH("croiseur_2.bmp") ); break;

            case BLOC_SIZE*4: *boat = SDL_LoadBMP( IMG_PATH("porte_avion_2.bmp") ); break;

            // Error the surface isn't a boat !
            default:

                fprintf( stderr,"uncorrect argument given to :\n");
                fprintf( stderr,"boat_rotation( SDL_Surface** boat, SDL_Rect* rectangle )\n");
                fprintf( stderr,"SDL_Surface** boat seems to not fit the boat format\n\n");

                exit( EXIT_FAILURE );


        }// SWITCH //


    }
    else if ( (*boat)->h <= (*boat)->w )
    {
        switch ( (*boat)->w )
        {
            case BLOC_SIZE*2: *boat = SDL_LoadBMP( IMG_PATH("destroyer.bmp") ); break;

            case BLOC_SIZE*3: *boat = SDL_LoadBMP( IMG_PATH("croiseur.bmp") ); break;

            case BLOC_SIZE*4: *boat = SDL_LoadBMP( IMG_PATH("porte_avion.bmp") ); break;

            case BLOC_SIZE: *boat = SDL_LoadBMP( IMG_PATH("vedette.bmp") ); break;

            // Error the surface isn't a boat !
            default:

                fprintf( stderr,"uncorrect argument given to :\n");
                fprintf( stderr,"boat_rotation( SDL_Surface** boat, SDL_Rect* rectangle )\n");
                fprintf( stderr,"SDL_Surface** boat seems to not fit the boat format\n\n");

                exit( EXIT_FAILURE );

        }// SWITCH //


    }// IF //

    if ( *boat == NULL )
        error( "boat_rotation()","sdltool.h", SDL_GetError() );

    SDL_SetColorKey( *boat, SDL_SRCCOLORKEY, SDL_MapRGB( (*boat)->format, ALPHA_R, ALPHA_V, ALPHA_B));


}

/// ///////
/// ///////
void update_rect( SDL_Surface* surface, SDL_Rect* rectangle)
{
    rectangle->w = surface->w;
    rectangle->h = surface->h;
}

/// ///////
/// ///////
SDL_Surface* draw_background ()
{
    int i, x, y;
    SDL_Rect rect;
    SDL_Surface* background = NULL;
    SDL_Surface* grid = NULL;

    background = SDL_LoadBMP(IMG_PATH("background.bmp"));
    if( background == NULL )
        error( "draw_background()","sdltool.h", SDL_GetError() );

    grid = SDL_LoadBMP( IMG_PATH("grid.bmp") );
    if( grid == NULL ) error( "draw_background()","sdltool.h", SDL_GetError() );
    SDL_SetColorKey( grid, SDL_SRCCOLORKEY, SDL_MapRGB( grid->format, 255, 255, 255));
    SDL_SetAlpha(grid, SDL_SRCALPHA, 128);

    for ( i=0; i<100 ; i++ )
    {
        x = i%10;
        y = i/10;

        rect.x = (x*BLOC_SIZE) + GRID_ORIGIN_X;
        rect.y = (y*BLOC_SIZE) + GRID_ORIGIN_Y;

        SDL_BlitSurface( grid, NULL, background, &rect);
    }

    for ( i=0; i<100 ; i++ )
    {
        x = i%10;
        y = i/10;

        rect.x = (x*BLOC_SIZE) + GRID_ORIGIN_X + BLOC_SIZE*10;
        rect.y = (y*BLOC_SIZE) + GRID_ORIGIN_Y;

        SDL_BlitSurface( grid, NULL, background, &rect);
    }

    SDL_FreeSurface( grid );

    return background;
}

/// ///////
/// ///////
SDL_Surface* draw_forbidden_area()
{
    /// Init
    SDL_Surface* forbidden = NULL;
    /*---------*/


    forbidden = SDL_CreateRGBSurface(SDL_HWSURFACE, RES_WIDTH, RES_HEIGHT, 32, 0, 0, 0, 0);
    if( forbidden == NULL )
        error( "draw_forbidden_area()", "sdltool.h", SDL_GetError() );

    SDL_FillRect( forbidden, NULL, SDL_MapRGB( forbidden->format, 255, 0, 0) );

    SDL_SetAlpha(forbidden, SDL_SRCALPHA, 128);

    return forbidden;
}

/// ///////
/// ///////
SDL_Surface* draw_highlighting_area()
{
    SDL_Surface* highlighting = NULL;

    highlighting = SDL_CreateRGBSurface(SDL_HWSURFACE, RES_WIDTH, RES_HEIGHT, 32, 0, 0, 0, 0);
    SDL_FillRect( highlighting, NULL, SDL_MapRGB( highlighting->format, 0, 246, 255) );
    SDL_SetAlpha(highlighting, SDL_SRCALPHA, 128);

    return highlighting;
}

/// ///////
/// ///////
SDL_Surface** load_boat()
{
    SDL_Surface** boat;
    int i;

    boat = (SDL_Surface**)malloc( sizeof(SDL_Surface*) * 10 );


    boat[0] = SDL_LoadBMP( IMG_PATH("porte_avion_2.bmp") );
    if ( boat[0] == NULL ) error( "load_boat()","sdl_tool.c", SDL_GetError() );

    boat[1] = SDL_LoadBMP( IMG_PATH("croiseur_2.bmp") );
    if ( boat[1] == NULL ) error( "load_boat()","sdl_tool.c", SDL_GetError() );

    boat[2] = SDL_LoadBMP( IMG_PATH("croiseur_2.bmp") );
    if ( boat[2] == NULL ) error( "load_boat()","sdl_tool.c", SDL_GetError() );

    boat[3] = SDL_LoadBMP( IMG_PATH("destroyer_2.bmp") );
    if ( boat[3] == NULL ) error( "load_boat()","sdl_tool.c", SDL_GetError() );

    boat[4] = SDL_LoadBMP( IMG_PATH("destroyer_2.bmp") );
    if ( boat[4] == NULL ) error( "load_boat()","sdl_tool.c", SDL_GetError() );

    boat[5] = SDL_LoadBMP( IMG_PATH("destroyer_2.bmp") );
    if ( boat[5] == NULL ) error( "load_boat()","sdl_tool.c", SDL_GetError() );

    boat[6] = SDL_LoadBMP( IMG_PATH("vedette_2.bmp") );
    if ( boat[6] == NULL ) error( "load_boat()","sdl_tool.c", SDL_GetError() );

    boat[7] = SDL_LoadBMP( IMG_PATH("vedette_2.bmp") );
    if ( boat[7] == NULL ) error( "load_boat()","sdl_tool.c", SDL_GetError() );

    boat[8] = SDL_LoadBMP( IMG_PATH("vedette_2.bmp") );
    if ( boat[8] == NULL ) error( "load_boat()","sdl_tool.c", SDL_GetError() );

    boat[9] = SDL_LoadBMP( IMG_PATH("vedette_2.bmp") );
    if ( boat[9] == NULL ) error( "load_boat()","sdl_tool.c", SDL_GetError() );

    for ( i=0; i<10 ;i++ )
        SDL_SetColorKey(boat[i], SDL_SRCCOLORKEY, SDL_MapRGB(boat[i]->format, ALPHA_R, ALPHA_V, ALPHA_B));

    return boat;

}


/// ///////
/// //////
void free_boat(SDL_Surface** boat)
{
    int i;
    for ( i=0; i<10 ; i++ )
        SDL_FreeSurface(boat[i]);

    free(boat);

}

/// ///////
/// ///////
bool is_point_on_surface ( int x, int y, SDL_Rect* rect)
{

    return ( (x >= rect->x) && (x <= (rect->x+rect->w)) && (y >= rect->y) && (y <= (rect->y+rect->h))  );

}

/// ///////
/// ///////
bool is_surface_on_surface ( SDL_Rect* top, SDL_Rect* backward)
{
    /** A square surface cross the other if one of the eight corner
       cross the other surface


       *------*
       |      |
       |   *--|-*
       |   |  | |
       *------* |
           |    |
           |    |
           *----*
    */
    return ( is_point_on_surface( top->x, top->y, backward ) ||
             is_point_on_surface( top->x+top->w, top->y, backward ) ||
             is_point_on_surface( top->x+top->w, top->y+top->h, backward ) ||
             is_point_on_surface( top->x, top->y+top->h, backward ) ||
             is_point_on_surface( backward->x, backward->y, top ) ||
             is_point_on_surface( backward->x+backward->w, backward->y, top ) ||
             is_point_on_surface( backward->x+backward->w, backward->y+backward->h, top ) ||
             is_point_on_surface( backward->x, backward->y+backward->h, top )

             ||
/** Or in this case :



            *------*
            |      |
         *--|------|-*
         |  |      | |
         *--|------|-*
            *------*
*/
             (
                (top->x > backward->x) && ((top->x+top->w) < (backward->x+backward->w)) &&
                (backward->y > top->y) && ((backward->y+backward->h) < (top->y+top->h))
             )

        ||

             (
                (backward->x > top->x) && ((backward->x+backward->w) < (top->x+top->w)) &&
                (top->y > backward->y) && ((top->y+top->h) < (backward->y+backward->h))
             )

            );

}

/// ///////
/// ///////
bool is_forbiden_area( SDL_Rect rect_to_test, SDL_Surface* surface[], SDL_Rect* rectangle[], int surface_to_test)
{
    /**
            To restrict an area you must know how works
            'align_surface( SDL_Rect* surface )'
    */

    bool value = false;
    SDL_Rect forbidden_rect;

    rect_to_test.w = surface[surface_to_test]->w;
    rect_to_test.h = surface[surface_to_test]->h;


    /// First Rule :
    /// Boat aren't allowed to touch each other.
    int i;
    for ( i=surface_to_test+1; i < surface_to_test+10 ; i++ )
    {

        forbidden_rect.x = rectangle[i%10]->x;
        forbidden_rect.y = rectangle[i%10]->y;

        forbidden_rect.h = surface[i%10]->h;
        forbidden_rect.w = surface[i%10]->w;

        if ( is_surface_on_surface ( &rect_to_test, &forbidden_rect ) )
            value = true;

    }


    /// Second Rule :
    /// Boat aren't alowed to be above the menu.
    if( is_on_menu( surface[surface_to_test], &rect_to_test) )
        value = true;

    /// Third Rule :
    /// Boat aren't alowed to be above the ennemi's grid.
    if( is_on_ennemi_grid( surface[surface_to_test], &rect_to_test) )
        value = true;

    return value;


}
/// ///////
/// ///////
bool is_on_menu( SDL_Surface* surface, SDL_Rect* rectangle )
{
    bool value = false;
    SDL_Rect forbidden_rect;

    rectangle->w = surface->w;
    rectangle->h = surface->h;

    /// Rule :
    /// Boat aren't alowed to be above the menu.

    /**
        Top Menu
    */
    forbidden_rect.x = 0;
    forbidden_rect.y = 0;

    forbidden_rect.h = GRID_ORIGIN_Y - 1;
    forbidden_rect.w = RES_WIDTH;

    if ( is_surface_on_surface ( rectangle, &forbidden_rect ) )
        value = true;

    /**
        Bottom Menu
    */
    forbidden_rect.x = 0;
    forbidden_rect.y = GRID_ORIGIN_Y + (10*BLOC_SIZE) + 1;

    forbidden_rect.h = RES_HEIGHT - forbidden_rect.y ;
    forbidden_rect.w = RES_WIDTH;

    if ( is_surface_on_surface ( rectangle, &forbidden_rect ) )
        value = true;

    return value;

}

/// ///////
/// ///////
bool is_on_ennemi_grid( SDL_Surface* surface, SDL_Rect* rectangle )
{
    bool value = false;
    SDL_Rect forbidden_rect;

    rectangle->w = surface->w;
    rectangle->h = surface->h;

    /// Rule :
    /// Boat aren't alowed to be above the right grid.
    forbidden_rect.x = GRID_ORIGIN_X + (10*BLOC_SIZE) + 1;
    forbidden_rect.y = 0;

    forbidden_rect.h = RES_HEIGHT;
    forbidden_rect.w = (10*BLOC_SIZE);

    if ( is_surface_on_surface ( rectangle, &forbidden_rect ) )
        value = true;

    return value;

}

/// ///////
/// ///////
void draw_msg_error( char* msg)
{
    /// Init
    TTF_Font *font = NULL;
    SDL_Color font_color = {0, 0, 0};
    SDL_Rect msg_position;
    SDL_Surface* txt = NULL;
    /*-----*/

    msg_position.x = MSG_ERR_ORIGIN_X;
    msg_position.y = MSG_ERR_ORIGIN_Y;

    font = TTF_OpenFont( DATA_PATH("BELL.ttf"), MSG_ERR_SIZE);
    txt = TTF_RenderText_Blended(font, msg, font_color);

    SDL_BlitSurface( txt, NULL, screen, &msg_position );

    SDL_Flip( screen );

    TTF_CloseFont( font );
    SDL_FreeSurface( txt );

}

/// ///////
/// ///////
SDL_Surface* draw_a_boat( TypeArea boat_name, Layout position )
{
    SDL_Surface* boat = NULL;

    if( position == HORIZONTAL )
    {
        switch( boat_name )
        {
            case PORTE_AVION: boat = SDL_LoadBMP( IMG_PATH("porte_avion_2.bmp") ); break;
            case CROISEUR: boat = SDL_LoadBMP( IMG_PATH("croiseur_2.bmp") ); break;
            case DESTROYER: boat = SDL_LoadBMP( IMG_PATH("destroyer_2.bmp") ); break;
            default: break;

        }// End SWITCH
    }
    else if( position == VERTICAL )
    {
        switch( boat_name )
        {
            case PORTE_AVION: boat = SDL_LoadBMP( IMG_PATH("porte_avion.bmp") ); break;
            case CROISEUR: boat = SDL_LoadBMP( IMG_PATH("croiseur.bmp") ); break;
            case DESTROYER: boat = SDL_LoadBMP( IMG_PATH("destroyer.bmp") ); break;

            default: break;

        }// End SWITCH

    }

    if( (boat_name == VEDETTE) )
        boat = SDL_LoadBMP( IMG_PATH("vedette.bmp") );

    if ( boat == NULL )
        error( "draw_a_boat()","sdl_tool.c", SDL_GetError() );

    SDL_SetColorKey( boat, SDL_SRCCOLORKEY, SDL_MapRGB( boat->format, ALPHA_R, ALPHA_V, ALPHA_B));

    return boat;
}

/// ///////
/// ///////
void pause()
{
    SDL_Event event;

    while( true )
    {
        SDL_WaitEvent(&event);
        if( event.type == SDL_KEYDOWN )
            break;
    }
}

/// ///////
/// ///////
void draw_player_boat( Grid* player_grid, SDL_Surface* dst )
{
    SDL_Rect boat_location;
    SDL_Surface* boat = NULL;
    SDL_Surface* touch = NULL;
    SDL_Surface* shoot = NULL;

    touch = SDL_LoadBMP( IMG_PATH("touch.bmp") );
    if( touch == NULL ) error( "draw_player_boat()","sdl_tool.c", "Loading touch.bmp fail" );
    SDL_SetColorKey( touch, SDL_SRCCOLORKEY, SDL_MapRGB( touch->format, 255, 255, 255));

    shoot = SDL_LoadBMP( IMG_PATH("shoot.bmp") );
    if( shoot == NULL ) error( "draw_player_boat()","sdl_tool.c", "Loading shoot.bmp fail" );
    SDL_SetColorKey( shoot, SDL_SRCCOLORKEY, SDL_MapRGB( shoot->format, 255, 255, 255));

    int i,x,y;
    for ( i=0; i<100 ; i++ )
    {
        x = i%10;
        y = i/10;

        if( is_origin( player_grid, x, y ) )
        {
                boat = draw_a_boat( get_type( player_grid, x, y), get_layout(player_grid, x, y) );
                if( boat == NULL ) error( "draw_player_boat()","sdl_tool.c", SDL_GetError() );

                boat_location.x = (x*BLOC_SIZE) + GRID_ORIGIN_X;
                boat_location.y = (y*BLOC_SIZE) + GRID_ORIGIN_Y;

                SDL_BlitSurface( boat, NULL, dst, &boat_location);

                SDL_FreeSurface( boat );
                boat = NULL;
        }
        if( is_touch(player_grid, x, y) )
        {
            boat_location.x = (x*BLOC_SIZE) + GRID_ORIGIN_X;
            boat_location.y = (y*BLOC_SIZE) + GRID_ORIGIN_Y;

            SDL_BlitSurface( touch, NULL, dst, &boat_location);
        }else
        if( is_shoot(player_grid, x, y) )
        {
            boat_location.x = (x*BLOC_SIZE) + GRID_ORIGIN_X;
            boat_location.y = (y*BLOC_SIZE) + GRID_ORIGIN_Y;

            SDL_BlitSurface( shoot, NULL, dst, &boat_location);
        }


    }// FOR //


    SDL_FreeSurface(touch);


}

/// ///////
/// ///////
bool is_on_player_grid( SDL_Surface* surface, SDL_Rect* rectangle )
{

    SDL_Rect forbidden_rect;

    forbidden_rect.x = GRID_ORIGIN_X;
    forbidden_rect.y = GRID_ORIGIN_Y;

    forbidden_rect.h = BLOC_SIZE*10;
    forbidden_rect.w = BLOC_SIZE*10;

    return is_surface_on_surface ( rectangle, &forbidden_rect );

}

/// ///////
/// ///////
void boat_position_to_grid( SDL_Rect* boat_location[], SDL_Surface* boat[], Grid* player_grid )
{
    reset_grid( player_grid );

    int x, y, i;
    for ( i=0; i<10 ; i++ )
    {
        x = (boat_location[i]->x - GRID_ORIGIN_X)/BLOC_SIZE;
    	y = (boat_location[i]->y - GRID_ORIGIN_Y)/BLOC_SIZE;


    	if( x>10 || y>10 || x<0 || y<0 )
            error( "boat_position_to_grid", "window.c", "Boat outside of the grid");

    	if( boat[i]->w < boat[i]->h )
    	{
    	    set_origin( player_grid, x, y, true );

            switch(boat[i]->h)
            {
                case BLOC_SIZE*2:

                    set_type_layout( player_grid, x, y, DESTROYER, VERTICAL );
                    set_type_layout( player_grid, x, y+1, DESTROYER, VERTICAL );

                break;

                case BLOC_SIZE*3:

                    set_type_layout( player_grid, x, y, CROISEUR, VERTICAL );
                    set_type_layout( player_grid, x, y+1, CROISEUR, VERTICAL );
                    set_type_layout( player_grid, x, y+2, CROISEUR, VERTICAL );

                break;

                case BLOC_SIZE*4:

                    set_type_layout( player_grid, x, y, PORTE_AVION, VERTICAL );
                    set_type_layout( player_grid, x, y+1, PORTE_AVION, VERTICAL );
                    set_type_layout( player_grid, x, y+2, PORTE_AVION, VERTICAL );
                    set_type_layout( player_grid, x, y+3, PORTE_AVION, VERTICAL );

                break;
            }// End SWITCH
    	}
    	else if( boat[i]->w > boat[i]->h )
    	{
    	    set_origin( player_grid, x, y, true );

            switch(boat[i]->w)
            {
                case BLOC_SIZE*2:

                    set_type_layout( player_grid, x, y, DESTROYER, HORIZONTAL);
                    set_type_layout( player_grid, x+1, y, DESTROYER, HORIZONTAL );

                break;

                case BLOC_SIZE*3:

                    set_type_layout( player_grid, x, y, CROISEUR, HORIZONTAL );
                    set_type_layout( player_grid, x+1, y, CROISEUR, HORIZONTAL );
                    set_type_layout( player_grid, x+2, y, CROISEUR, HORIZONTAL );

                break;

                case BLOC_SIZE*4:

                    set_type_layout( player_grid, x, y, PORTE_AVION, HORIZONTAL );
                    set_type_layout( player_grid, x+1, y, PORTE_AVION, HORIZONTAL );
                    set_type_layout( player_grid, x+2, y, PORTE_AVION, HORIZONTAL );
                    set_type_layout( player_grid, x+3, y, PORTE_AVION, HORIZONTAL );

                break;
            }// End SWITCH
    	}
    	else
    	{/// VEDETTE

    	    set_origin( player_grid, x, y, true );

    	    set_type_layout( player_grid, x, y, VEDETTE, NOLAYOUT );

    	}

    }// End FOR


}

/// ///////
/// ///////
void init_boat_position( SDL_Rect* boat_location[] )
{
    boat_location[0]->x=BOAT_X;
    boat_location[0]->y=BOAT_Y;

    boat_location[1]->x=boat_location[0]->x+BLOC_SIZE*5;
    boat_location[1]->y=BOAT_Y;

    boat_location[2]->x=boat_location[1]->x+BLOC_SIZE*4;
    boat_location[2]->y=BOAT_Y;

    boat_location[3]->x=BOAT_X;
    boat_location[3]->y=BOAT_Y+BLOC_SIZE*(1.5);

    boat_location[4]->x = boat_location[3]->x + BLOC_SIZE*3;
    boat_location[4]->y=BOAT_Y+BLOC_SIZE*(1.5);

    boat_location[5]->x=boat_location[4]->x+BLOC_SIZE*3;
    boat_location[5]->y=BOAT_Y+BLOC_SIZE*(1.5);


    boat_location[6]->x=boat_location[5]->x+BLOC_SIZE*3;
    boat_location[6]->y=BOAT_Y+BLOC_SIZE*(1.5);

    boat_location[7]->x=boat_location[6]->x+BLOC_SIZE*2;
    boat_location[7]->y=BOAT_Y+BLOC_SIZE*(1.5);

    boat_location[8]->x=boat_location[7]->x+BLOC_SIZE*2;
    boat_location[8]->y=BOAT_Y+BLOC_SIZE*(1.5);

    boat_location[9]->x=boat_location[2]->x+BLOC_SIZE*4 ;
    boat_location[9]->y=BOAT_Y;

}

/// ///////
/// ///////
void boat_position_surface_from_grid( Grid* g, SDL_Rect* boat_location[], SDL_Surface* boat[] )
{
    int x,y;
    int c=1,d=3,v=6;

    for ( x=0; x<10 ; x++ )
        SDL_FreeSurface(boat[x]);

    for( y=0; y<10; y++ )
        for( x=0; x<10; x++ )
            if ( is_origin(g, x, y) )
            {

                if( get_layout(g, x, y) == HORIZONTAL )
                {
                    switch( get_type(g, x, y) )
                    {
                        case PORTE_AVION:

                            boat_location[0]->x = x*BLOC_SIZE + GRID_ORIGIN_X;
                            boat_location[0]->y = y*BLOC_SIZE + GRID_ORIGIN_Y;
                            boat_location[0]->w = 4*BLOC_SIZE;
                            boat_location[0]->h = BLOC_SIZE;

                            boat[0] = SDL_LoadBMP( IMG_PATH("porte_avion_2.bmp") );
                            if ( boat[0] == NULL )
                                error( "boat_position_surface_from_grid()","sdl_tool.c", "Loading Fail : porte_avion_2.bmp");
                        break;

                        case CROISEUR:



                            boat_location[c]->x = x*BLOC_SIZE + GRID_ORIGIN_X;
                            boat_location[c]->y = y*BLOC_SIZE + GRID_ORIGIN_Y;
                            boat_location[c]->w = 3*BLOC_SIZE;
                            boat_location[c]->h = BLOC_SIZE;

                            boat[c] = SDL_LoadBMP( IMG_PATH("croiseur_2.bmp") );
                            if ( boat[c] == NULL )
                                error( "boat_position_surface_from_grid()","sdl_tool.c", "Loading Fail : croiseur_2.bmp");

                            c++;

                        break;

                        case DESTROYER:

                            boat_location[d]->x = x*BLOC_SIZE + GRID_ORIGIN_X;
                            boat_location[d]->y = y*BLOC_SIZE + GRID_ORIGIN_Y;
                            boat_location[d]->w = 2*BLOC_SIZE;
                            boat_location[d]->h = BLOC_SIZE;

                            boat[d] = SDL_LoadBMP( IMG_PATH("destroyer_2.bmp") );
                            if ( boat[d] == NULL )
                                error( "boat_position_surface_from_grid()","sdl_tool.c", "Loading Fail : destroyer_2.bmp");

                            d++;

                        break;

                        default: break;


                    }//SWITCH

                }//If( HORIZONTAL )
                else

                if( get_layout(g, x, y) == VERTICAL )
                {

                    switch( get_type(g, x, y) )
                    {
                        case PORTE_AVION:

                            boat_location[0]->x = x*BLOC_SIZE + GRID_ORIGIN_X;
                            boat_location[0]->y = y*BLOC_SIZE + GRID_ORIGIN_Y;
                            boat_location[0]->w = BLOC_SIZE;
                            boat_location[0]->h = 4*BLOC_SIZE;

                            boat[0] = SDL_LoadBMP( IMG_PATH("porte_avion.bmp") );
                            if ( boat[0] == NULL )
                                error( "boat_position_surface_from_grid()","sdl_tool.c", "Loading Fail : porte_avion.bmp");
                        break;

                        case CROISEUR:

                            boat_location[c]->x = x*BLOC_SIZE + GRID_ORIGIN_X;
                            boat_location[c]->y = y*BLOC_SIZE + GRID_ORIGIN_Y;
                            boat_location[c]->w = BLOC_SIZE;
                            boat_location[c]->h = 3*BLOC_SIZE;

                            boat[c] = SDL_LoadBMP( IMG_PATH("croiseur.bmp") );
                            if ( boat[c] == NULL )
                                error( "boat_position_surface_from_grid()","sdl_tool.c", "Loading Fail : croiseur.bmp");

                            c++;

                        break;

                        case DESTROYER:

                            boat_location[d]->x = x*BLOC_SIZE + GRID_ORIGIN_X;
                            boat_location[d]->y = y*BLOC_SIZE + GRID_ORIGIN_Y;
                            boat_location[d]->w = BLOC_SIZE;
                            boat_location[d]->h = 2*BLOC_SIZE;

                            boat[d] = SDL_LoadBMP( IMG_PATH("destroyer.bmp") );
                            if ( boat[d] == NULL )
                                error( "boat_position_surface_from_grid()","sdl_tool.c", "Loading Fail : destroyer.bmp");

                            d++;

                        break;

                        default: break;

                    }//SWITCH

                }//IF( VERTICAL )
                if( get_type(g, x, y) == VEDETTE )
                {
                    boat_location[v]->x = x*BLOC_SIZE + GRID_ORIGIN_X;
                    boat_location[v]->y = y*BLOC_SIZE + GRID_ORIGIN_Y;
                    boat_location[v]->w = BLOC_SIZE;
                    boat_location[v]->h = BLOC_SIZE;

                    boat[v] = SDL_LoadBMP( IMG_PATH("vedette.bmp") );
                    if ( boat[v] == NULL )
                        error( "boat_position_surface_from_grid()","sdl_tool.c", "Loading Fail : vedette.bmp");

                    v++;
                }

            }// IF( origin )


    for ( x=0; x<10; x++ )
        SDL_SetColorKey(boat[x], SDL_SRCCOLORKEY, SDL_MapRGB(boat[x]->format, ALPHA_R, ALPHA_V, ALPHA_B));



}





