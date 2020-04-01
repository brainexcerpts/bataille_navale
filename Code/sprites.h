/**

    Sprite is an image included sub image named clip :

    A sprite:

    *-------*-------*
    |       |       |
    | clip  | clip2 |
    |       |       |
    *-------*-------*
    |       |       |
    | clip3 | clip..|
    |       |       |
    *-------*-------*

*/

#ifndef SPRITE_H
#define SPRITE_H

/**
	Author : Claverie Paul
	Creation date :     15/03/2008
	Last modification : 28/03/2008

	void create_sprites()
    start_animation()
    set_position()
    reset_position()
    invert_sense_anim()
    update_animation()
    draw_sprite()
    get_surface()
    get_clip()
    get_position()
    get_nbr_sprites()
    close_sprites()


*/

#include <stdio.h>
#include <stdbool.h>
#include <SDL/SDL.h>
#include "error.h"
#include "rand.h"
#include "types.h"
#include "sdl_tool.h"


typedef enum
{
   NONE = 0,       // Animation off
   TO_UP = 1,      // Animation top to bottom ( Do not use with TO_DOWN )
   TO_DOWN = 2,    // Animation bottom to top (!Set by default!) (N.B: Do not use with TO_UP )
   TO_LEFT = 4,    // Animation right to left (N.B: Do not use with TO_RIGHT )
   TO_RIGHT = 8,   // Animation left to right (!Set by default!) (N.B: Do not use with TO_LEFT )
   RAND = 16,      // Random animation: take sequence of image randomly
   REPEAT = 32,    // Repeat animation
   CYCLIC = 64,    // Do a loop from begining if not enable REPEAT go back to the begining
   DIFFERENT = 128 // Try to not repeat successively two image ( when RANDOM or NONE CYCLIC )

} Animation;

typedef struct s_sprites* Sprites;

// Init sprites
void create_sprites(Sprites* s, SDL_Surface* pic, Point* size_sprite, SDL_Rect* clip);

// As it says
void start_animation(Sprites* s, unsigned long time_next, Animation a);

// Set position of the desire clip
void set_position(Sprites* s, Point p);

// Set position to the first clip
void reset_position(Sprites* s);

// Reverse animation sens
void invert_sense_anim(Sprites* s);

// Update animation. return false if animation finishes
bool update_animation(Sprites *s);

// Update animaion and print sprite to screen
bool draw_sprite(Sprites *s, SDL_Rect position);

// Get entire surface of the sprite
SDL_Surface* get_surface(Sprites s);

// Get current clip
SDL_Rect* get_clip(Sprites s);

// Get position ( current clip ) in the current sprite array
Point get_position(Sprites s);

// Number of clip
Point get_nbr_sprites(Sprites s);

// Free memory
void close_sprites(Sprites* s);

#endif
