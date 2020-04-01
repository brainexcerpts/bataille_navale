/**

    About sdl_tool.h :

    miscelenous graphics functions used by window.h
    Should be divided later...
    More explanation further.

*/

/**

    Author : Rodolphe Vaillant-David
	Creation date :     22/03/2008
	Last modification : 29/03/2008

	init_video()
    close_video()
    is_forbiden_area()
    is_on_menu()
    is_on_ennemi_grid()
    is_on_player_grid()
    mouse_interface()
    boat_rotation()
    align_surface()
    align_point()
    init_boat_position()
    boat_position_surface_from_grid()
    boat_position_to_grid()
    draw_msg_error()
    draw_background ()
    draw_a_boat()
    draw_forbidden_area()
    draw_highlighting_area()
    draw_player_boat()
    load_boat()
    free_boat()
    is_point_on_surface()
    is_surface_on_surface()
    pause()

*/

#ifndef SDL_TOOL
#define SDL_TOOL

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "config.h"
#include "grid.h"
#include "error.h"

/* Global Variable */
SDL_Surface* screen;
/*-----------------*/


/**---------------
 General function
-----------------*/

void init_video();
void close_video();


/**---------------
 Specific function
-----------------*/

/// Function to call after a SDL_MOUSEBUTTONDOWN
/// Drag and drop interface : surface_to_test followed the mouse until left-click is done
/// A right click rotate the boat
void mouse_interface( SDL_Surface* background, SDL_Surface* sliding_surface[], SDL_Rect* rectangle[], int n/* number of rect */, int surface_to_test );

/// See if the sliding surface is within a forbiden area such as:
/// menu, ennemi grid, over or beside a boat
bool is_forbiden_area( SDL_Rect rect_to_test, SDL_Surface* surface[], SDL_Rect* rectangle[], int surface_to_test);

/// As it says
bool is_on_menu( SDL_Surface* surface, SDL_Rect* rectangle );
bool is_on_ennemi_grid( SDL_Surface* surface, SDL_Rect* rectangle );
bool is_on_player_grid( SDL_Surface* surface, SDL_Rect* rectangle );
/*------------*/


/// Update the SDL_Surface
/// Do a rotation of 90°
void boat_rotation( SDL_Surface** boat, SDL_Rect* rectangle );

/// Align the given surface on the grid
void align_surface( SDL_Rect* rectangle);

/// Align the point on the top left corner of the case
void align_point( Point* point );

/// Initial position into the window set_player_grid
void init_boat_position( SDL_Rect* boat_location[] );

/// Set the boat_location to position define by the grid g
/// Boat_location set for the player grid
void boat_position_surface_from_grid( Grid* g, SDL_Rect* boat_location[], SDL_Surface* boat[] );

/// Transform given graphic position to grid position
/// Set the layout/origin/TypeArea of the grid
void boat_position_to_grid( SDL_Rect* boat_location[], SDL_Surface* surface[], Grid* destination );


/**-------------
 Draw Librairie
---------------*/
/**
    Don't forget to free the surfaces after a draw

*/


/// Directly print to screen msg with a Flip
void draw_msg_error( char* msg);

/// Create a background to set boat
SDL_Surface* draw_background ();

/// return a surface which match to boat_name and layout
SDL_Surface* draw_a_boat( TypeArea boat_name, Layout position );

SDL_Surface* draw_forbidden_area();

SDL_Surface* draw_highlighting_area();

/// Draw on dst every oat player from grid
void draw_player_boat( Grid* player_grid, SDL_Surface* dst );

/// Load an array of 10 surface* boat
SDL_Surface** load_boat();
void free_boat(SDL_Surface** boat);
/*-----------*/


/**---------------
 position function
------------------*/

/// Check if x and y are above the given rectangle
bool is_point_on_surface ( int x, int y, SDL_Rect* rect);

/// Check if the top surface is above the backward surface */
bool is_surface_on_surface ( SDL_Rect* top, SDL_Rect* backward);


/**---------------
 Trash function
----------------*/

/// Pause executing until keydown usefull for debug
void pause();



#endif // SDL_TOOL
