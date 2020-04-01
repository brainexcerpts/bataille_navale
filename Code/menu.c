#include "menu.h"


struct s_item
{
	Sprites normal;           // Sprite printed if mouse outside the area
	Sprites mouse_over;       // Sprite printed if mouse inside the area ( if mouse_over==NULL button none clickable) */
	SDL_Rect area;            // Sub-menu area within window
	struct s_item* next;      // next item
	struct s_item* back;      // Back item
	bool focus;               // True when mouse over the button
	bool use;                 // Indicates if the sub-menu is associated with a menu
	unsigned int return_code; // ID of an item (unique between 0 and 1)
};


struct s_menu
{
	Sprites background;  // Background sprite
	struct s_item* head; // First item ( Forground )
	struct s_item* tail; // Last item  ( background )
};


void create_item(Item* i, Sprites normal, Sprites mouse_over, SDL_Rect pos, unsigned int return_code)
{
    if(i==NULL) error("create_item", "menu.h", "the pointer Item (i) is NULL");

	if(normal==NULL) error("create_item", "menu.h", "the pointer Sprites (normal) is NULL");

    SDL_Rect* pr;
    SDL_Rect r_normal;
    SDL_Rect r_mouse_over;

	pr = get_clip(normal);

	r_normal.w = pr->w;
	r_normal.h = pr->h;

	if(mouse_over!=NULL)
	{
	    pr = get_clip(mouse_over);

        r_mouse_over.w = pr->w;
        r_mouse_over.h = pr->h;

        if( r_normal.w!=r_mouse_over.w || r_normal.h!=r_mouse_over.h )
        {
            error("create_item", "menu.h", "size Sprites (normal) different size Sprites (mouse_over)");
        }
	}

	(*i) = (struct s_item*)malloc(sizeof(struct s_item));

	(*i)->area.x = pos.x;
	(*i)->area.y = pos.y;
	(*i)->area.w = r_normal.w;
	(*i)->area.h = r_normal.h;

	if( (*i)->area.x<0 || (*i)->area.y<0 || (*i)->area.x+(*i)->area.w>screen->w || (*i)->area.y+(*i)->area.h>screen->h )
	{
	    free(*i);
		error("create_item", "menu.h", "the SDL_Rect's (area) value is incorrect");
	}

	(*i)->normal = normal;
	(*i)->mouse_over = mouse_over;

	(*i)->next = NULL;
	(*i)->back = NULL;

	(*i)->focus = false;
	(*i)->use = false;

	(*i)->return_code = return_code;
}


void create_menu(Menu* m, Sprites background)
{
	if(m==NULL) error("create_menu", "menu.h", "the pointer Menu (m) is NULL");

	(*m) = (struct s_menu*)malloc(sizeof(struct s_menu));

	(*m)->background = background;

	(*m)->head = NULL;
	(*m)->tail = NULL;
}


void add_item_fore(Menu* m, Item* i)
{
    if(m==NULL) error("add_item_fore", "menu.h", "the pointer Menu (m) is NULL");
    if(i==NULL) error("add_item_fore", "menu.h", "the pointer Item (i) is NULL");

    if((*i)->use) error("add_item_fore", "menu.h", "the Item is already use");

    (*i)->next = (*m)->head;
    if((*m)->head!=NULL) ((*i)->next)->back = *i;

    (*m)->head = *i;
    (*i)->use = true;

    if((*m)->tail==NULL) (*m)->tail = *i;
}


void add_item_back(Menu* m, Item* i)
{
    if(m==NULL) error("add_item_back", "menu.h", "the pointer Menu (m) is NULL");
    if(i==NULL) error("add_item_back", "menu.h", "the pointer Item (i) is NULL");

    if((*i)->use) error("add_item_back", "menu.h", "the Item is already use");

    (*i)->back = (*m)->tail;
    if((*m)->tail!=NULL) ((*i)->back)->next = *i;

    (*m)->tail =  *i;
    (*i)->use = true;

    if((*m)->head==NULL) (*m)->head = *i;
}


unsigned int open_menu(Menu m)
{
    if(m==NULL) error("open_menu", "menu.h", "the pointer Menu (m) is NULL");

    SDL_Event event;
    struct s_item *i,*i2;
    Point mouse = {0,0};
    bool result;

    result = false;
    i2 = i;

    SDL_PollEvent(&event);
    mouse.x = event.button.x;
    mouse.y = event.button.y;

    while(true)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    return 0;

                case SDL_KEYDOWN:
                    if(event.key.keysym.sym==SDLK_ESCAPE) return 1;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if(event.button.button==SDL_BUTTON_LEFT)
                    {
                        i = m->head;

                        while(i!=NULL)
                        {
                            if(i->mouse_over!=NULL)
                            {
                                if(mouse.x>=i->area.x && mouse.x<=i->area.x+i->area.w &&
                                    mouse.y>=i->area.y && mouse.y<=i->area.y+i->area.h)
                                {
                                    return i->return_code;
                                }
                            }

                            i = i->next;
                        }
                    }
                    break;

                case SDL_MOUSEMOTION:
                    mouse.x = event.button.x;
                    mouse.y = event.button.y;
                    break;
            }
        }

        if(m->background!=NULL)
        {
            update_animation(&m->background);
            SDL_BlitSurface(get_surface(m->background), get_clip(m->background), screen, NULL);
        }
        else
        {
            /* Coloration du fond en noir */
            SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
        }

        i = m->head;
        i2 = NULL;

        while(i!=NULL)
        {
            if(i->mouse_over!=NULL)
            {
                if(mouse.x>=i->area.x && mouse.x<=i->area.x+i->area.w &&
                    mouse.y>=i->area.y && mouse.y<=i->area.y+i->area.h)
                {
                    i2 = i;
                }
            }

            i = i->next;
        }

        i = m->tail;

        while(i!=NULL)
        {
            update_animation(&i->normal);

            if(i!=i2)
            {
                SDL_BlitSurface(get_surface(i->normal), get_clip(i->normal), screen, &(i->area));
                i->focus = false;
            }
            else
            {
                if(i->mouse_over!=NULL)
                {
                    if( !i->focus && !update_animation(&i->mouse_over) ) reset_position(&i->mouse_over);

                    SDL_BlitSurface(get_surface(i->mouse_over), get_clip(i->mouse_over), screen, &(i->area));
                }
                else SDL_BlitSurface(get_surface(i->normal), get_clip(i->normal), screen, &(i->area));
            }

            i = i->back;
        }

        SDL_Flip(screen);
        SDL_Delay(30);
    }

	return 0;
}


void close_item(Item* i)
{
	if(i==NULL) error("close_item", "menu.h", "the pointer Item (i) is NULL");

    (*i)->next = NULL;
	(*i)->back = NULL;

    free(*i);
}


void close_menu(Menu* m)
{
	if(m==NULL) error("close_menu", "menu.h", "the pointer Menu (m) is NULL");

    (*m)->head = NULL;
	(*m)->tail = NULL;

	free(*m);
}
