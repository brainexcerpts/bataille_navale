/**
    About SDL function :

    Type: SDL_Surface always a rectangle
    Type: SDL_Rect is a structure { x,y,w,h }

    surface =  SDL_LoadBMP( IMG_PATH("image.bmp") );
    Load a surface from the given image;

    SDL_FreeSurface( surface );
    Free memory of a surface

    SDL_BlitSurface( item , NULL, background, &position );
    Stick the SDL_Surface item onto background at position (x,y)
    be aware that a Blit update w,h of position from the w,h of item ! ( ugly I know )

    SDL_Flip( screen );
    Directly update screen

    SDL_WaitEvent( &event );
    Stop executing and wait an event such as:
    a key down, a click, mouse motion.

*/

#include "main.h"

int main(int argc, char *argv[])
{
    GameMenu menu_jeu;
    Grid player_grid;
    Grid ennemi_grid;
    WND_event w_event;
    Point pt;
    Hist historic_player;
    Hist historic_IA;
    bool gameover = false;
    bool done;
    char msg[256];
    WND_order order;

    strcpy(msg, "");

    WND_init();
    HIST_init(&historic_player);
    HIST_init(&historic_IA);
    init_rand_number();

    init_grid( &player_grid );
    init_grid( &ennemi_grid );
    w_event = NOTHING;

    WND_menu( &menu_jeu, &w_event );

    if(w_event == PLAY)
    {
            if(menu_jeu.start==RAND_START)
            {
                if(rand_number(2)==0) menu_jeu.start = PLAYER_START;
                else menu_jeu.start = IA_START;
            }

            WND_set_player_grid( &player_grid, &w_event );
            if(w_event==QUIT_WINDOW)
            {
                HIST_free(&historic_player);
                HIST_free(&historic_IA);
                WND_close();
                return 0;
            }

            random_grid( &ennemi_grid );

            while(!gameover)
            {
                if( menu_jeu.start==IA_START )
                {
                    pt = IA_action(player_grid, menu_jeu.IA);
                    HIST_stack( &historic_IA, pt );

                    do_shoot( &player_grid, pt.x, pt.y );

                    if(is_finish(&player_grid))
                    {
                        gameover = true;
                        strcpy(msg, "IA Gagne ...");
                        continue;
                    }
                }

                do
                {
                    order = 0;
                    if(menu_jeu.cheat) order |= CHEAT_ON;
                    if(HIST_is_top_of_stack(&historic_player)) order |= HIDE_NEXT;
                    if(HIST_is_bottom_of_stack(&historic_player)) order |= HIDE_BACK;

                    do
                    {
                        done = false;
                        pt = WND_play( &player_grid, &ennemi_grid, &w_event, order, msg );
                        strcpy(msg, "");
                        if(w_event==VALID && is_shoot(&ennemi_grid, pt.x, pt.y ))
                        {
                            done = true;
                            strcpy(msg, "Deja tire");
                        }
                    }
                    while(done);

                    switch( w_event )
                    {
                        case QUIT_WINDOW:
                            HIST_free(&historic_player);
                            HIST_free(&historic_IA);
                            WND_close();
                            return 0;

                        case NEXT:
                            pt = HIST_next( &historic_player );
                            do_shoot( &ennemi_grid, pt.x, pt.y );
                            pt = HIST_next( &historic_IA );
                            do_shoot( &player_grid, pt.x, pt.y );
                            continue;
                        break;

                        case BACK:
                            pt = HIST_back( &historic_player );
                            undo_shoot( &ennemi_grid, pt.x, pt.y );
                            pt = HIST_back( &historic_IA );
                            undo_shoot( &player_grid, pt.x, pt.y );
                            continue;
                        break;

                        default:
                            break;

                    } // SWITCH(event)
                }
                while(w_event!=VALID);

                HIST_stack( &historic_player, pt );

                switch(do_shoot( &ennemi_grid, pt.x, pt.y ))
                {
                case MISS:
                    strcpy(msg, "Rate !!!");
                    break;
                case TOUCH:
                    strcpy(msg, "Touche !!!");
                    break;
                case SINK:
                    strcpy(msg, "Coule !!!");
                    break;
                }

                if(is_finish(&ennemi_grid))
                {
                    gameover = true;
                    strcpy(msg, "Joueur gagne !!!");
                    continue;
                }

                if( menu_jeu.start==PLAYER_START )
                {
                    pt = IA_action(player_grid, menu_jeu.IA);
                    HIST_stack( &historic_IA, pt );

                    do_shoot( &player_grid, pt.x, pt.y );

                    if(is_finish(&player_grid))
                    {
                        gameover = true;
                        strcpy(msg, "IA Gagne ...");
                        continue;
                    }
                }
            } // While( gameover )

            WND_play( &player_grid, &ennemi_grid, &w_event, HIDE_VALID | GAME_OVER, msg );
    } // IF(event=PLAY)

    HIST_free(&historic_player);
    HIST_free(&historic_IA);
    WND_close();

    return EXIT_SUCCESS;
}
