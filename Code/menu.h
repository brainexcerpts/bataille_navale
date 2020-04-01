#ifndef MENU_H
#define MENU_H

/**
	Author : Claverie Paul
	Creation date :     22/03/2008
	Last modification : 29/03/2008


    create_item()
    create_menu()
    add_item_fore()
    add_item_back()
    open_menu()
    close_item()
    close_menu()

*/

#include <SDL/SDL.h>
#include "sdl_tool.h"
#include "types.h"
#include "sprites.h"


typedef struct s_item* Item;
typedef struct s_menu* Menu;


// Init an item of menu
void create_item(Item* i, Sprites normal, Sprites mouse_over, SDL_Rect area, unsigned int return_code);

// Init menu
void create_menu(Menu* m, Sprites background);

// Add an item at the start of menu
void add_item_fore(Menu* m, Item* i);

// Add an item at the end of menu
void add_item_back(Menu* m, Item* i);

// Lauch menu and return the id of the clicked item or : QUIT == 0, ESCAPE == 1
unsigned int open_menu(Menu m);

 // Free memory of an item
void close_item(Item* i);

 // Free memory of a menu
void close_menu(Menu* m);


#endif
