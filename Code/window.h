/**

    About window.h :

    function given here print to screen,
    different window with their own interface.

    When a WND_ is call it holds execution until user finishes.
    An event is return with an WND_event ( see enum field )
    An order can also be done with WND_order ( print a message, hide a button )

*/

/**

    Rodolphe Vaillant-David :

    void WND_init()
    void WND_close()
    void WND_set_player_grid()
    Point WND_play()

    Paul Claverie :

    void WND_menu()

*/
#ifndef WINDOW
#define WINDOW

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "config.h"
#include "sdl_tool.h"
#include "grid.h"
#include "sprites.h"
#include "menu.h"
#include "error.h"



/// /////////// ///
/// Game Window ///
/// /////////// ///

typedef enum{

    VALID,
    NEXT,
    BACK,
    QUIT_WINDOW,
    PLAY,
    NOTHING

} WND_event;

typedef enum{

    HIDE_NEXT = 1,
    HIDE_BACK = 2,
    HIDE_VALID = 4,
    CHEAT_ON = 8,
    GAME_OVER = 16

} WND_order;

typedef enum
{
    BN_QUIT = 0,
    BN_ESCAPE = 1,
    BN_PLAY,
    BN_EXIT,
    BN_START_LEFT,
    BN_START_RIGHT,
    BN_DIFFICULTY_LEFT,
    BN_DIFFICULTY_RIGHT,
    BN_CHEAT_LEFT,
    BN_CHEAT_RIGHT

} Choose;

typedef struct s_game_menu
{
	Choose option; /* Useless for user, needed for implemention in WND_menu()  */
	Difficulty IA; /* Possible value : HARD || MEDIUM || EASY */
	Start start;   /* Possible value : PLAYER_START || IA_START || RAND_START */
	bool cheat;    /* cheat mode disale|enable */

} GameMenu;

// Init screen, must be done before any call
// of a general WND_ function
// Last update :
void WND_init();

// Free memory and close the window
// Last update :
void WND_close();

// Permit player to set the position of the boats
// A valid format grid is given.
// Possible event : VALID (all boat set by player) || QUIT_WINDOW ( as it says )
// Last modification
void WND_set_player_grid( Grid* player_grid, WND_event* w_event );

// Permit player to do one shoot,
// ennemi_grid and player_grid are printed to the screen with specific display when a case is :
// shoot | touch | sink
// msg is printed to screen
// return the attack position made by player
// Possile event : VALID (aim done) || NEXT ( do following shot ) || BACK ( undo last shot ) || QUIT_WINDOW
// Possible order : HIDE_NEXT | HIDE_BACK | HIDE_VALID
// CHEAT_ON ( if not given hide next and back button )
// GAME_OVER ( disable war fog hide all button )
Point WND_play( Grid* player_grid, Grid* ennemi_grid, WND_event* w_event, WND_order w_order, char* msg  );

// Permit player to choose different option for instance :
// GameMenu option;
// option.IA == HARD || MEDIUM || EASY
// option.start == PLAYER_START || IA_START || RAND_START
// option.cheat ==  true || false
// Possile event : PLAY || QUIT_WINDOW
void WND_menu(GameMenu* mj, WND_event* w_event);


#endif // WINDOW
