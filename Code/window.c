#include "window.h"

static SDL_Rect origin = { 0,0,0,0 };

/// ///////
/// ///////
Point WND_play( Grid* player_grid, Grid* ennemi_grid, WND_event* w_event, WND_order w_order, char* msg  )
{

    /// Init
    int i, x, y;

    SDL_Surface* background = NULL;
    SDL_Surface* touch = NULL;
    SDL_Surface* aim = NULL;
    SDL_Surface* back = NULL;
    SDL_Surface* next = NULL;
    SDL_Surface* valid = NULL;
    SDL_Surface* war_fog = NULL;
    SDL_Surface* boat = NULL;
    SDL_Surface* shoot = NULL;
    SDL_Surface* fire = NULL;
    Sprites s;
    Point fire_size;

    Point attack_location;
    SDL_Rect boat_location;
    SDL_Rect valid_rect;
    SDL_Rect next_rect;
    SDL_Rect back_rect;
    SDL_Rect temp;
    /*---------*/

    attack_location.x = -1;
    attack_location.y = -1;

    *w_event = NOTHING;
    background = draw_background ();

    /// Draw player's boat on background
    draw_player_boat( player_grid, background );
    /*-------------------------------*/


    /// Draw cursor and indicator
    shoot = SDL_LoadBMP( IMG_PATH("shoot.bmp") );
    if( shoot == NULL ) error( "draw_player_boat()","sdl_tool.c", "Loading shoot.bmp fail" );
    SDL_SetColorKey( shoot, SDL_SRCCOLORKEY, SDL_MapRGB( shoot->format, 255, 255, 255));

    aim = SDL_LoadBMP( IMG_PATH("aim.bmp") );
    if( aim == NULL ) error( "WND_play", "window.c", "Loading fail aim.bmp" );
    SDL_SetColorKey( aim, SDL_SRCCOLORKEY, SDL_MapRGB( aim->format, 0, 0, 0));


    touch = SDL_LoadBMP( IMG_PATH("touch.bmp") );
    if( touch == NULL ) error( "WND_play", "window.c", SDL_GetError() );
    SDL_SetColorKey( touch, SDL_SRCCOLORKEY, SDL_MapRGB( touch->format, 255, 255, 255));

    war_fog = SDL_CreateRGBSurface(SDL_HWSURFACE, BLOC_SIZE, BLOC_SIZE, 32, 0, 0, 0, 0);
    SDL_FillRect( war_fog, NULL, SDL_MapRGB( war_fog->format, 0, 0, 64) );
    SDL_SetAlpha(war_fog, SDL_SRCALPHA, 128);
    /*--------------*/


    /// Draw Ennemi's map on background
    for ( i=0; i<100 ; i++ )
    {
        x = i%10;
        y = i/10;

        boat_location.x = (x*BLOC_SIZE) + GRID_ORIGIN_X + BLOC_SIZE*10;
        boat_location.y = (y*BLOC_SIZE) + GRID_ORIGIN_Y;

        if( !(w_order & GAME_OVER) )
        {
            if( is_touch(ennemi_grid, x, y) )
            {
                    if( is_sink(ennemi_grid, x, y) && is_origin(ennemi_grid, x, y) )
                    {
                        boat = draw_a_boat( get_type(ennemi_grid,x,y), get_layout(ennemi_grid,x,y) );
                        SDL_BlitSurface( boat, NULL, background, &boat_location);
                        SDL_FreeSurface( boat );
                    }

                    SDL_BlitSurface(touch , NULL, background, &boat_location);

            }
            else if( !is_shoot(ennemi_grid, x, y) )
                SDL_BlitSurface(war_fog , NULL, background, &boat_location);

        }// If( !GAME_OVER )
        else
        {
            if( is_origin(ennemi_grid, x, y) )
            {
                        boat = draw_a_boat( get_type(ennemi_grid,x,y), get_layout(ennemi_grid,x,y) );
                        SDL_BlitSurface( boat, NULL, background, &boat_location);
                        SDL_FreeSurface( boat );
            }
            if( is_touch(ennemi_grid, x, y) )
                SDL_BlitSurface(touch , NULL, background, &boat_location);
            else if( is_shoot(ennemi_grid, x, y) )
                SDL_BlitSurface(shoot , NULL, background, &boat_location);

        }// If( GAME_OVER )

    }
    /*-----------------------*/


    ///Draw game button
    valid = SDL_LoadBMP( IMG_PATH("valid.bmp") );
    if( valid == NULL ) error( "WINDOW_play", "window.c", SDL_GetError() );

    next = SDL_LoadBMP( IMG_PATH("next.bmp") );
    if( next == NULL ) error( "WINDOW_play", "window.c", SDL_GetError() );

    back = SDL_LoadBMP( IMG_PATH("back.bmp") );
    if( back == NULL ) error( "WINDOW_play", "window.c", SDL_GetError() );

    fire = SDL_LoadBMP( IMG_PATH("fire.bmp") );
    if( fire == NULL ) error( "WND_play", "window.c", "Loading fail fire.bmp" );
    SDL_SetColorKey( fire, SDL_SRCCOLORKEY, SDL_MapRGB( fire->format, 0, 0, 255));

    valid_rect.x = VALID_X;
    valid_rect.y = VALID_Y;

    next_rect.x = NEXT_X ;
    next_rect.y = NEXT_Y ;


    back_rect.x = BACK_X;
    back_rect.y = BACK_Y;


    if( !(w_order & HIDE_VALID) )
        SDL_BlitSurface(valid , NULL, background, &valid_rect);

    if( w_order & CHEAT_ON )
    {
        if( !(w_order & HIDE_NEXT) )
            SDL_BlitSurface(next , NULL, background, &next_rect);

        if( !(w_order & HIDE_BACK) )
            SDL_BlitSurface(back , NULL, background, &back_rect);
    }
    /*--------------------------------------*/


    ///Print to screen
    SDL_BlitSurface( background, NULL, screen, &origin );
    SDL_Flip( screen );
    draw_msg_error( msg );
    /*------------*/


    SDL_Rect ennemi_area;

    ennemi_area.x = (BLOC_SIZE*10) + GRID_ORIGIN_X;
    ennemi_area.y =  GRID_ORIGIN_Y;

    ennemi_area.w = (BLOC_SIZE*10)-1;
    ennemi_area.h = (BLOC_SIZE*10)-1;/* Eternal bug of alignement */



    /// ///////////// ///
    /// Event Manager ///
    /// ///////////// ///
    SDL_Event event;
    int quit = 1;

    while( quit )
    {
        SDL_WaitEvent( &event );
        switch( event.type )
        {
            /////////////////////////////////////////////////////////////
            case SDL_KEYDOWN:

                if( event.key.keysym.sym == SDLK_ESCAPE )
                {
                    *w_event = QUIT_WINDOW;
                    return attack_location;
                }

            break;
            ///////////////////////////////////////////////////////////////
            case SDL_QUIT :

                *w_event = QUIT_WINDOW;
                return attack_location;

            break;

            case SDL_MOUSEBUTTONDOWN:

                // Click on ennemi's grid
                if( is_point_on_surface(event.button.x, event.button.y, &ennemi_area) &&
                    !(w_order & GAME_OVER) )
                {
                    attack_location.x = event.button.x;
                    attack_location.y = event.button.y;

                    align_point( &attack_location );

                    temp.x = attack_location.x*BLOC_SIZE+BLOC_SIZE*10+GRID_ORIGIN_X;
                    temp.y = attack_location.y*BLOC_SIZE+GRID_ORIGIN_Y;

                    SDL_BlitSurface( background, NULL, screen, &origin );
                    SDL_BlitSurface( aim, NULL, screen, &temp );
                    SDL_Flip( screen );

                }

                /// Click on next ///
                if( is_point_on_surface ( event.button.x, event.button.y, &next_rect) &&
                    (w_order & CHEAT_ON) && !(w_order & HIDE_NEXT)
                  )
                {
                    *w_event = NEXT;
                    quit = false;
                }

                /// Click on back ///
                if( is_point_on_surface ( event.button.x, event.button.y, &back_rect) &&
                    (w_order & CHEAT_ON) && !(w_order & HIDE_BACK)
                  )
                {
                    *w_event = BACK;
                    quit = false;
                }

                /// Click on valid ///
                if( is_point_on_surface ( event.button.x, event.button.y, &valid_rect) &&
                    !(w_order & HIDE_VALID)
                  )
                {
                    if( attack_location.x == -1 && attack_location.y == -1 )
                    {
                        // Refresh screen
                        SDL_BlitSurface( background, NULL, screen, &origin );
                        draw_msg_error( "Tire sur la grille ennemi indefini !" );
                    }
                    else
                    {

                        /////////////////////////
                        fire_size.x = 40;
                        fire_size.y = 40;
                        create_sprites(&s, fire, &fire_size, NULL);
                        start_animation(&s, 50, TO_RIGHT);

                        while(update_animation(&s))
                        {
                            SDL_BlitSurface(get_surface(s), get_clip(s), screen, &temp);
                            SDL_Flip( screen );
                            SDL_Delay(50);
                            SDL_BlitSurface( background, NULL, screen, &origin );
                        }
                        SDL_Flip( screen );
                        close_sprites(&s);

                        *w_event = VALID;
                        quit = false;
                    }
                }

            break;

        }// SWITCH

    }// WHILE

    SDL_FreeSurface( background );
    SDL_FreeSurface( touch );
    SDL_FreeSurface( aim );
    SDL_FreeSurface( back );
    SDL_FreeSurface( next );
    SDL_FreeSurface( valid );
    SDL_FreeSurface( war_fog );
    SDL_FreeSurface( shoot );
    SDL_FreeSurface( fire );

    return attack_location;
}

/// //////
/// //////
void WND_set_player_grid( Grid* player_grid, WND_event* w_event )
{
    /// Init
    int i, j;
    SDL_Event event;
    SDL_Surface* background = NULL;
    SDL_Surface* background_temp = NULL;
    SDL_Surface** boat;
    SDL_Surface* valid = NULL;
    SDL_Surface* random = NULL;
    SDL_Surface* war_fog;

    SDL_Rect* boat_location[10] = {0};
    SDL_Rect valid_rect;
    SDL_Rect random_rect;
    SDL_Rect war_fog_rect;
    Grid tmp_grid;
    /*-------*/

    init_grid( &tmp_grid );

    *w_event = NOTHING;
    boat = load_boat();
    background = draw_background ();

    background_temp = SDL_CreateRGBSurface(SDL_HWSURFACE, RES_WIDTH, RES_HEIGHT, 32, 0, 0, 0, 0);


    /// Draw valid button
    valid = SDL_LoadBMP( IMG_PATH("valid.bmp") );
        if( valid == NULL ) error( "WINDOW_set_player_grid", "window.c", SDL_GetError() );

    valid_rect.x = VALID_X;
    valid_rect.y = VALID_Y;

    SDL_BlitSurface(valid , NULL, background, &valid_rect);
    SDL_FreeSurface( valid );
    valid = NULL;
    /*-------*/

    /// Draw random button
    random = SDL_LoadBMP( IMG_PATH("random.bmp") );
        if( random == NULL ) error( "WINDOW_set_player_grid", "window.c", SDL_GetError() );

    random_rect.x = RAND_X;
    random_rect.y = RAND_Y;

    SDL_BlitSurface(random , NULL, background, &random_rect);
    SDL_FreeSurface( random );
    random = NULL;
    /*-------*/


    /// Allocation
    for ( i=0; i<10 ; i++ )
        	boat_location[i] = (SDL_Rect*)malloc( sizeof(SDL_Rect) );
    /*-------*/

    /// Init starting position of boat
    init_boat_position( boat_location );
    /*------------*/

    war_fog = SDL_CreateRGBSurface(SDL_HWSURFACE, BLOC_SIZE*10, BLOC_SIZE*10, 32, 0, 0, 0, 0);
    SDL_FillRect( war_fog, NULL, SDL_MapRGB( war_fog->format, 0, 0, 64) );
    SDL_SetAlpha(war_fog, SDL_SRCALPHA, 128);

    war_fog_rect.x = BLOC_SIZE*10 + GRID_ORIGIN_X;
    war_fog_rect.y = GRID_ORIGIN_Y;
    SDL_BlitSurface(war_fog, NULL, background, &war_fog_rect);


    /// Print starting screen
    SDL_BlitSurface(background, NULL, screen, &origin);

    for ( i=0; i<10 ; i++ )
        SDL_BlitSurface(boat[i], NULL, screen, boat_location[i]);

    SDL_Flip(screen);
    /*----------------*/

    /// ///////////// ///
    /// Event Manager ///
    /// ///////////// ///

    bool cont = true;
    while (cont)
    {

        SDL_WaitEvent(&event);
        switch(event.type)
        {
            /////////////////////////////////////////////////////////////
            case SDL_KEYDOWN:

                if( event.key.keysym.sym == SDLK_ESCAPE )
                {
                    *w_event = QUIT_WINDOW;
                    return ;
                }

            break;
            ///////////////////////////////////////////////////////////////
            case SDL_QUIT:

                *w_event = QUIT_WINDOW;
                return ;

            break;

            case SDL_MOUSEBUTTONDOWN:

                /// Move a boat
                for ( i=0; i<10 ; i++ )
                {
                    // Do I have click on a boat
                    if ( is_point_on_surface (event.button.x, event.button.y, boat_location[i]) )
                    {

                        // Refresh the background
                        SDL_BlitSurface( background, NULL, background_temp, &origin);

                        // Paste position of the boats, except the moving boat
                        for ( j=i+1; j<(10+i) ; j++ )
                            SDL_BlitSurface(boat[j%10], NULL, background_temp, boat_location[j%10]);


                        // Drag&drop, and rotation
                        mouse_interface( background_temp, boat, boat_location, 10, i);

                        align_surface( boat_location[i] );

                        SDL_BlitSurface( background_temp, NULL, screen, &origin);
                        SDL_BlitSurface( boat[i], NULL, screen, boat_location[i]);
                        SDL_Flip( screen );

                    }

                }// End of FOR

                /// Push the valid button
                if( is_point_on_surface ( event.button.x, event.button.y, &valid_rect) )
                {
                    *w_event = VALID;
                    cont = false;

                    // Every boat must have been set
                    for ( i=0; i<10 ; i++ )
                    {
                        if( !is_on_player_grid(boat[i], boat_location[i]) )
                        {
                            //refresh screen
                            SDL_BlitSurface( background, NULL, background_temp, &origin);
                            // Paste position of the boats
                            for ( j=0; j<10 ; j++ )
                                SDL_BlitSurface(boat[j], NULL, background_temp, boat_location[j]);
                            SDL_BlitSurface( background_temp, NULL, screen,  &origin );

                            draw_msg_error( "Placer tout les bateaux !" );
                            *w_event = NOTHING;
                            cont = true;

                        }

                    }
                }//IF( valid button )

                /// Push Random
                if( is_point_on_surface ( event.button.x, event.button.y, &random_rect) )
                {
                    random_grid( &tmp_grid );
                    boat_position_surface_from_grid( &tmp_grid, boat_location, boat );

                    //refresh screen
                    SDL_BlitSurface( background, NULL, background_temp, &origin);
                    // Paste position of the boats
                    for ( j=0; j<10 ; j++ )
                        SDL_BlitSurface(boat[j], NULL, background_temp, boat_location[j]);


                    SDL_BlitSurface( background_temp, NULL, screen,  &origin );
                    SDL_Flip( screen );
                }

            break;

        }// End of SWITCH

    }// End of WHILE



    /// Set the grid
    boat_position_to_grid( boat_location, boat, player_grid );


    /// Free
    SDL_FreeSurface(war_fog);
    SDL_FreeSurface(background);
    SDL_FreeSurface(background_temp);

    for ( i=0; i<10 ; i++ )
        free( boat_location[i] );

    free_boat(boat);
    close_grid( &tmp_grid );
    /*--------*/

}

/// ///////
/// ///////
void WND_init()
{

    SDL_Surface* pic_ico;

    // Start SDL
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }


    // Load window icon
    if( (pic_ico = SDL_LoadBMP(IMG_PATH("logo.bmp")) ) == NULL )
    {
        fprintf(stderr, "Erreur chargement de l'icône : %s\n", SDL_GetError());
    }
    else
    {
        // Set transparency
        SDL_SetColorKey(pic_ico, SDL_SRCCOLORKEY, SDL_MapRGB(pic_ico->format, 255, 255, 255));

        SDL_WM_SetIcon(pic_ico, NULL);
        SDL_FreeSurface(pic_ico);
    }


    // Init global variable screen
    if((screen = SDL_SetVideoMode(RES_WIDTH, RES_HEIGHT, 32, VIDEO_MODE)) == NULL )
    {
        fprintf(stderr, "Impossible d'ouvrir la fenêtre : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Set window title
    SDL_WM_SetCaption(" Bataille Navale", NULL);

    // Init lib SDL_ttf
    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

}

/// ///////
/// ///////
void WND_close()
{
    SDL_FreeSurface(screen);
    // ...
    TTF_Quit();
    SDL_Quit();

}


/// ///////
/// ///////
void WND_menu(GameMenu* mj, WND_event* w_event)
{
    int i,n;
    bool done = true;
    Menu m;
    Item i_title, i_clic[2], i_clic2[6], i_option[5];
    Sprites s_title, s_clic[4], s_clic2[4], s_option[5];
    SDL_Surface *img_title, *img_clic, *img_clic2, *img_option;
    SDL_Rect r_title, r_clic[2], r_clic2[6], r_option[5], r_temp;
    Point size_title, size_clic, size_clic2, size_option;
    Point p[5];

    /// Loading image
    img_title = IMG_Load("Data\\title.bmp");
    if(img_title==NULL) error("draw_menu","game_menu.h", SDL_GetError());

    img_clic = IMG_Load("Data\\clic.bmp");
    if(img_clic==NULL) error("draw_menu","game_menu.h", SDL_GetError());

    img_clic2 = IMG_Load("Data\\clic2.bmp");
    if(img_clic2==NULL) error("draw_menu","game_menu.h", SDL_GetError());

    img_option = IMG_Load("Data\\option.bmp");
    if(img_option==NULL) error("draw_menu","game_menu.h", SDL_GetError());

    /// Set transparency
    SDL_SetColorKey(img_title, SDL_SRCCOLORKEY, SDL_MapRGB(img_title->format, 0, 0, 255));
    SDL_SetColorKey(img_clic, SDL_SRCCOLORKEY, SDL_MapRGB(img_clic->format, 0, 0, 255));
    SDL_SetColorKey(img_clic2, SDL_SRCCOLORKEY, SDL_MapRGB(img_clic2->format, 0, 0, 255));
    SDL_SetColorKey(img_option, SDL_SRCCOLORKEY, SDL_MapRGB(img_option->format, 0, 0, 255));

    /// Number of clip within sprites
    size_title.x = img_title->w;
    size_title.y = img_title->h;

    size_clic.x = img_clic->w/10;
    size_clic.y = img_clic->h/4;

    size_clic2.x = img_clic2->w/12;
    size_clic2.y = img_clic2->h/4;

    size_option.x = img_option->w;
    size_option.y = img_option->h/10;

    /// Loading sprites
    r_temp.x = 0;
    r_temp.y = 0;
    r_temp.w = img_clic->w;
    r_temp.h = img_clic->h/4;

    for( i=0 ; i!=4 ; i++ )
    {
        create_sprites(&s_clic[i], img_clic, &size_clic, &r_temp);
        r_temp.y += r_temp.h;
    }

    r_temp.x = 0;
    r_temp.y = 0;
    r_temp.w = img_clic2->w;
    r_temp.h = img_clic2->h/4;

    for( i=0 ; i!=4 ; i++ )
    {
        create_sprites(&s_clic2[i], img_clic2, &size_clic2, &r_temp);
        r_temp.y += r_temp.h;
    }

    create_sprites(&s_title, img_title, &size_title, NULL);

    for( i=0 ; i!=5 ; i++ ) create_sprites(&s_option[i], img_option, &size_option, NULL);

    /// Animate sprites
    for( i=0 ; i!=4 ; i++ )
    {
        start_animation(&s_clic[i], 50, TO_RIGHT | REPEAT | DIFFERENT);
        start_animation(&s_clic2[i], 50, TO_RIGHT | REPEAT | CYCLIC);
    }

    /// Size of each option
    r_title.w = size_title.x;
    r_title.h = size_title.y;

    for( i=0 ; i!=2 ; i++ )
    {
        r_clic[i].w = size_clic.x;
        r_clic[i].h = size_clic.y;
    }

    for( i=0 ; i!=6 ; i++ )
    {
        r_clic2[i].w = size_clic2.x;
        r_clic2[i].h = size_clic2.y;
    }

    for( i=0 ; i!=5 ; i++ )
    {
        r_option[i].w = size_option.x;
        r_option[i].h = size_option.y;
    }

    /// Position x of each image
    r_title.x = (screen->w-r_title.w)/2;

    for( i=0 ; i!=2 ; i++ ) r_clic[i].x = (screen->w-r_clic[i].w)/2;

    for( i=0 ; i!=5 ; i++ ) r_option[i].x = (screen->w-r_option[i].w)/2;

    for( i=0 ; i!=6 ; i+=2 )
    {
        r_clic2[i].x = r_option[i].x - r_clic2[i].w - 20;
        r_clic2[i+1].x = r_option[i].x + r_option[i].w + 20;
    }

    /// Position y of each image
    r_title.y = 30;

    n = screen->h - r_title.y - r_title.h - 2*r_clic[0].h - 5*r_option[0].h - 15;
    n /= 5;

    r_clic[0].y = r_title.y + r_title.h + n;
    r_option[0].y = r_clic[0].h + r_clic[0].y + 5;
    r_clic2[0].y = r_option[0].y + (r_option[0].h-r_clic2[0].h)/2;
    r_clic2[1].y = r_clic2[0].y;

    r_option[1].y = r_option[0].y + r_option[0].h + n;
    r_option[2].y = r_option[1].h + r_option[1].y + 5;
    r_clic2[2].y = r_option[2].y + (r_option[2].h-r_clic2[2].h)/2;
    r_clic2[3].y = r_clic2[2].y;

    r_option[3].y = r_option[2].y + r_option[2].h + n;
    r_option[4].y = r_option[3].h + r_option[3].y + 5;
    r_clic2[4].y = r_option[4].y + (r_option[4].h-r_clic2[4].h)/2;
    r_clic2[5].y = r_clic2[4].y;

    r_clic[1].y = r_option[4].y + r_option[4].h + n;

    /// Loading item
    create_item(&i_title, s_title, NULL, r_title, 0);
    create_item(&i_clic[0], s_clic[0], s_clic[1], r_clic[0], BN_PLAY);
    create_item(&i_clic[1], s_clic[2], s_clic[3], r_clic[1], BN_EXIT);
    create_item(&i_clic2[0], s_clic2[2], s_clic2[3], r_clic2[0], BN_START_RIGHT);
    create_item(&i_clic2[1], s_clic2[0], s_clic2[1], r_clic2[1], BN_START_LEFT);
    create_item(&i_clic2[2], s_clic2[2], s_clic2[3], r_clic2[2], BN_DIFFICULTY_RIGHT);
    create_item(&i_clic2[3], s_clic2[0], s_clic2[1], r_clic2[3], BN_DIFFICULTY_LEFT);
    create_item(&i_clic2[4], s_clic2[2], s_clic2[3], r_clic2[4], BN_CHEAT_RIGHT);
    create_item(&i_clic2[5], s_clic2[0], s_clic2[1], r_clic2[5], BN_CHEAT_LEFT);
    create_item(&i_option[0], s_option[0], NULL, r_option[0], 0);
    create_item(&i_option[1], s_option[1], NULL, r_option[1], 0);
    create_item(&i_option[2], s_option[2], NULL, r_option[2], 0);
    create_item(&i_option[3], s_option[3], NULL, r_option[3], 0);
    create_item(&i_option[4], s_option[4], NULL, r_option[4], 0);

    /// Loading menu
    create_menu(&m, NULL); /* Game menu */

    add_item_fore(&m, &i_title);     /* Title */
    add_item_fore(&m, &i_clic[0]);   /* Play */
    add_item_fore(&m, &i_clic[1]);   /* Quit */
    add_item_fore(&m, &i_clic2[0]);  /* Right arrow  (begin) */
    add_item_fore(&m, &i_clic2[1]);  /* Left arrow  (begin) */
    add_item_fore(&m, &i_clic2[2]);  /* Right arrow (Difficulty) */
    add_item_fore(&m, &i_clic2[3]);  /* Left arrow  (Difficulty) */
    add_item_fore(&m, &i_clic2[4]);  /* Right arrow (cheat) */
    add_item_fore(&m, &i_clic2[5]);  /* Left arrow  (cheat) */
    add_item_fore(&m, &i_option[0]); /* Begin otion */
    add_item_fore(&m, &i_option[1]); /* Difficulty */
    add_item_fore(&m, &i_option[2]); /* Option Difficulty */
    add_item_fore(&m, &i_option[3]); /* Cheat */
    add_item_fore(&m, &i_option[4]); /* Cheat option */

    /// Lauch menu
    mj->IA = EASY;
    mj->cheat = false;
    mj->start = PLAYER_START;

    for( i=0 ; i!=5 ; i++ ) p[i].x = 0;
    p[0].y = 2;
    p[1].y = 0;
    p[2].y = 5;
    p[3].y = 1;
    p[4].y = 9;
    set_position(&s_option[0], p[0]);
    set_position(&s_option[1], p[1]);
    set_position(&s_option[2], p[2]);
    set_position(&s_option[3], p[3]);
    set_position(&s_option[4], p[4]);

    do
    {
        mj->option = open_menu(m);

        switch( mj->option)
        {
            case BN_QUIT:
            case BN_ESCAPE:
            case BN_EXIT:
                *w_event = QUIT_WINDOW;
                done = false;
                break;

            case BN_PLAY:
                *w_event = PLAY;
                done = false;
                break;
            case BN_START_LEFT:
                if(p[0].y==2)
                {
                    p[0].y = 3;
                    mj->start = IA_START;
                }
                else if(p[0].y==3)
                {
                    p[0].y = 4;
                    mj->start = RAND_START;
                }
                else
                {
                    p[0].y = 2;
                    mj->start = PLAYER_START;
                }
                set_position(&s_option[0], p[0]);
                break;
            case BN_START_RIGHT:
                if(p[0].y==2)
                {
                    p[0].y = 4;
                    mj->start = RAND_START;
                }
                else if(p[0].y==3)
                {
                    p[0].y = 2;
                    mj->start = PLAYER_START;
                }
                else
                {
                    p[0].y = 3;
                    mj->start = IA_START;
                }
                set_position(&s_option[0], p[0]);
                break;
            case BN_DIFFICULTY_LEFT:
                if(p[2].y==5)
                {
                    p[2].y = 6;
                    mj->IA = MEDIUM;
                }
                else if(p[2].y==6)
                {
                    p[2].y = 7;
                    mj->IA = HARD;
                }
                else
                {
                    p[2].y = 5;
                    mj->IA = EASY;
                }
                set_position(&s_option[2], p[2]);
                break;
            case BN_DIFFICULTY_RIGHT:
                if(p[2].y==5)
                {
                    p[2].y = 7;
                    mj->IA = HARD;
                }
                else if(p[2].y==6)
                {
                    p[2].y = 5;
                    mj->IA = EASY;
                }
                else
                {
                    p[2].y = 6;
                    mj->IA = MEDIUM;
                }
                set_position(&s_option[2], p[2]);
                break;
            case BN_CHEAT_LEFT:
                if(p[4].y==8)
                {
                    p[4].y = 9;
                    mj->cheat = false;
                }
                else
                {
                    p[4].y = 8;
                    mj->cheat = true;
                }
                set_position(&s_option[4], p[4]);
                break;
            case BN_CHEAT_RIGHT:
                if(p[4].y==8)
                {
                    p[4].y = 9;
                    mj->cheat = false;
                }
                else
                {
                    p[4].y = 8;
                    mj->cheat = true;
                }
                set_position(&s_option[4], p[4]);
                break;
            break;
        }
    }
    while(done);

    /// Free
    close_menu(&m);

    close_item(&i_title);
    for( i=0 ; i!=2 ; i++ ) close_item(&i_clic[i]);
    for( i=0 ; i!=6 ; i++ ) close_item(&i_clic2[i]);
    for( i=0 ; i!=5 ; i++ ) close_item(&i_option[i]);

    close_sprites(&s_title);
    for( i=0 ; i!=4 ; i++ ) close_sprites(&s_clic[i]);
    for( i=0 ; i!=4 ; i++ ) close_sprites(&s_clic2[i]);
    for( i=0 ; i!=5 ; i++ ) close_sprites(&s_option[i]);

    SDL_FreeSurface(img_title);
    SDL_FreeSurface(img_clic);
    SDL_FreeSurface(img_clic2);
    SDL_FreeSurface(img_option);
    /*---------------*/
}
