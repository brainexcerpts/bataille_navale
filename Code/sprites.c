#include "sprites.h"


struct s_sprites
{
	SDL_Surface* picture;     // Entire sprite
	Point origin;             // Origin of sprite in picture
	SDL_Rect sprite_clip;     // Current Clip
	Point nbr_sprites;        // Number of clip
	Point pos;                // Position of current clip within sprite
	unsigned long time_start; // Timer start to animate
	unsigned long time_next;  // Timer duration for animation
	Animation a;              // Repeating mode
	bool sens_normal;         // Usefull when none cyclic
};


void create_sprites(Sprites* s, SDL_Surface* pic, Point* size_sprite, SDL_Rect* clip)
{
    SDL_Rect picture_clip;

    if(s==NULL) error("create_sprites", "sprites.h", "the pointer Sprites (s) is NULL");
    if(pic==NULL) error("create_sprites", "sprites.h", "the pointer SDL_Surface (pic) is NULL");

    *s = (struct s_sprites*)malloc(sizeof(struct s_sprites));

    (*s)->picture = pic;

    if(clip==NULL)
    {
        picture_clip.x = 0;
        picture_clip.y = 0;
        picture_clip.w = pic->w;
        picture_clip.h = pic->h;
    }
    else
    {
        picture_clip = *clip;

        if( clip->x<0 || clip->y<0 || clip->w>pic->w || clip->h>pic->h )
            error("create_sprites", "sprites.h", "the SDL_Rect's (clip) value is incorrect");
    }

    if(size_sprite==NULL)
    {
        (*s)->sprite_clip.w = picture_clip.w;
        (*s)->sprite_clip.h = picture_clip.h;
    }
    else
    {
        (*s)->sprite_clip.w = size_sprite->x;
        (*s)->sprite_clip.h = size_sprite->y;

        if( size_sprite->x==0 || size_sprite->y==0 )
            error("create_sprites", "sprites.h", "the Point's (size_sprite) value is incorrect");

        if( picture_clip.w%size_sprite->x!=0 || picture_clip.h%size_sprite->y!=0 )
            error("create_sprites", "sprites.h", "the Point's (size_sprite) value is incorrect");
    }

    (*s)->a = NONE;
    (*s)->time_start = 0;
    (*s)->time_next = 0;
    (*s)->pos.x = 0;
    (*s)->pos.y = 0;

    (*s)->nbr_sprites.x = picture_clip.w/(*s)->sprite_clip.w;
    (*s)->nbr_sprites.y = picture_clip.h/(*s)->sprite_clip.h;

    (*s)->origin.x = picture_clip.x;
    (*s)->origin.y = picture_clip.y;

    (*s)->sprite_clip.x = (*s)->origin.x;
    (*s)->sprite_clip.y = (*s)->origin.y;

    (*s)->sens_normal = true;
}


void start_animation(Sprites* s, unsigned long time_next, Animation a)
{
    if(s==NULL) error("start_animation", "sprites.h", "the pointer Sprites (s) is NULL");

    if( !(a&NONE) && time_next<10 ) error("start_animation", "sprites.h", "the unsigned long's (time_next) value is incorrect");

    (*s)->time_start = SDL_GetTicks();
    (*s)->time_next = time_next;
    (*s)->a = a;

    if((*s)->a>255) warning("start_animation", "sprites.h", "the Animation (a) value is incorrect");

    if( ((*s)->a&TO_UP) && ((*s)->a&TO_DOWN) )
    {
        warning("start_animation", "sprites.h", "the Animation (a) value is incorrect");
        (*s)->a -= TO_UP;
    }

    if( ((*s)->a&TO_LEFT) && ((*s)->a&TO_RIGHT) )
    {
        warning("start_animation", "sprites.h", "the Animation (a) value is incorrect");
        (*s)->a -= TO_LEFT;
    }

    if( !((*s)->a&TO_UP) && !((*s)->a&TO_DOWN) ) (*s)->a += TO_DOWN;

    if( !((*s)->a&TO_LEFT) && !((*s)->a&TO_RIGHT) ) (*s)->a += TO_RIGHT;

    if((*s)->a&RAND)
    {
        if((*s)->a&TO_UP) (*s)->a -= TO_UP;
        if((*s)->a&TO_DOWN) (*s)->a -= TO_DOWN;
        if((*s)->a&TO_LEFT) (*s)->a -= TO_LEFT;
        if((*s)->a&TO_RIGHT) (*s)->a -= TO_RIGHT;

        (*s)->pos.x = rand_number((*s)->nbr_sprites.x);
        (*s)->pos.y = rand_number((*s)->nbr_sprites.y);
    }
    else
    {
        if((*s)->a&TO_RIGHT) (*s)->pos.x = 0;
        else (*s)->pos.x = (*s)->nbr_sprites.x-1;

        if((*s)->a&TO_DOWN) (*s)->pos.y = 0;
        else (*s)->pos.y = (*s)->nbr_sprites.y-1;
    }

    (*s)->sprite_clip.x = (*s)->pos.x*(*s)->sprite_clip.w + (*s)->origin.x;
    (*s)->sprite_clip.y = (*s)->pos.y*(*s)->sprite_clip.h + (*s)->origin.y;
}


void set_position(Sprites* s, Point p)
{
    if(s==NULL) error("set_position", "sprites.h", "the pointer Sprites (s) is NULL");

    if( p.x<0 || p.x>=(*s)->nbr_sprites.x || p.y<0 || p.y>=(*s)->nbr_sprites.y )
    {
        warning("set_position", "sprites.h", "the Point's (p) value is incorrect");
    }
    else
    {
        (*s)->pos = p;

        (*s)->sprite_clip.x = (*s)->pos.x*(*s)->sprite_clip.w + (*s)->origin.x;
        (*s)->sprite_clip.y = (*s)->pos.y*(*s)->sprite_clip.h + (*s)->origin.y;
    }
}


void reset_position(Sprites* s)
{
    if(s==NULL) error("reset_position", "sprites.h", "the pointer Sprites (s) is NULL");

    if((*s)->sens_normal)
    {
        if((*s)->a&TO_RIGHT) (*s)->pos.x = 0;
        if((*s)->a&TO_LEFT) (*s)->pos.x = (*s)->nbr_sprites.x-1;

        if((*s)->a&TO_DOWN) (*s)->pos.y = 0;
        if((*s)->a&TO_UP) (*s)->pos.y = (*s)->nbr_sprites.y-1;
    }
    else
    {
        if((*s)->a&TO_LEFT) (*s)->pos.x = 0;
        if((*s)->a&TO_RIGHT) (*s)->pos.x = (*s)->nbr_sprites.x-1;

        if((*s)->a&TO_UP) (*s)->pos.y = 0;
        if((*s)->a&TO_DOWN) (*s)->pos.y = (*s)->nbr_sprites.y-1;
    }

    (*s)->sprite_clip.x = (*s)->pos.x*(*s)->sprite_clip.w + (*s)->origin.x;
    (*s)->sprite_clip.y = (*s)->pos.y*(*s)->sprite_clip.h + (*s)->origin.y;
}


void invert_sense_anim(Sprites* s)
{
    if(s==NULL) error("invert_sense", "sprites.h", "the pointer Sprites (s) is NULL");

    if((*s)->sens_normal) (*s)->sens_normal = false;
    else (*s)->sens_normal = true;

    if((*s)->a&TO_RIGHT)
    {
        (*s)->a -= TO_RIGHT;
        (*s)->a += TO_LEFT;
    }
    else if((*s)->a&TO_LEFT)
    {
        (*s)->a -= TO_LEFT;
        (*s)->a += TO_RIGHT;
    }

    if((*s)->a&TO_DOWN)
    {
        (*s)->a -= TO_DOWN;
        (*s)->a += TO_UP;
    }
    else if((*s)->a&TO_UP)
    {
        (*s)->a -= TO_UP;
        (*s)->a += TO_DOWN;
    }
}


bool update_animation(Sprites *s)
{
    Point p;

    if(s==NULL) error("update_animation", "sprites.h", "the pointer Sprites (s) is NULL");

    if((*s)->a&RAND)
    {
        if((*s)->time_start+(*s)->time_next<SDL_GetTicks())
        {
            if(!((*s)->a&REPEAT)) return false;

            if((*s)->a&DIFFERENT && (*s)->nbr_sprites.x!=1 && (*s)->nbr_sprites.y!=1)
            {
                do
                {
                    p.x = (*s)->pos.x;
                    p.y = (*s)->pos.y;

                    (*s)->pos.x = rand_number((*s)->nbr_sprites.x);
                    (*s)->pos.y = rand_number((*s)->nbr_sprites.y);
                }
                while( p.x!=(*s)->pos.x && p.y!=(*s)->pos.y);
            }
            else
            {
                (*s)->pos.x = rand_number((*s)->nbr_sprites.x);
                (*s)->pos.y = rand_number((*s)->nbr_sprites.y);
            }

            (*s)->time_start += (*s)->time_next * ((SDL_GetTicks()-(*s)->time_start) / (*s)->time_next);
        }
    }
    else
    {
        while( (*s)->time_start+(*s)->time_next < SDL_GetTicks() )
        {
            (*s)->time_start += (*s)->time_next;

            if((*s)->a&TO_DOWN)
            {
                if((*s)->a&TO_RIGHT)
                {
                    if((*s)->pos.x==(*s)->nbr_sprites.x-1)
                    {
                        if((*s)->pos.y==(*s)->nbr_sprites.y-1)
                        {
                            if((*s)->a&REPEAT)
                            {
                                if(!((*s)->a&CYCLIC))
                                {
                                    invert_sense_anim(s);

                                    if((*s)->a&DIFFERENT && (*s)->nbr_sprites.x!=1 && (*s)->nbr_sprites.y!=1)
                                        (*s)->time_start -= (*s)->time_next;
                                }
                                else
                                {
                                    (*s)->pos.x = 0;
                                    (*s)->pos.y = 0;
                                }
                            }
                            else return false;
                        }
                        else
                        {
                            (*s)->pos.x = 0;
                            (*s)->pos.y++;
                        }
                    }
                    else (*s)->pos.x++;
                }
                else
                {
                    if((*s)->pos.x==0)
                    {
                        if((*s)->pos.y==(*s)->nbr_sprites.y-1)
                        {
                            if((*s)->a&REPEAT)
                            {
                                if(!((*s)->a&CYCLIC))
                                {
                                    invert_sense_anim(s);

                                    if((*s)->a&DIFFERENT && (*s)->nbr_sprites.x!=1 && (*s)->nbr_sprites.y!=1)
                                        (*s)->time_start -= (*s)->time_next;
                                }
                                else
                                {
                                    (*s)->pos.x = (*s)->nbr_sprites.x-1;
                                    (*s)->pos.y = 0;
                                }
                            }
                            else return false;
                        }
                        else
                        {
                            (*s)->pos.x = (*s)->nbr_sprites.x-1;
                            (*s)->pos.y++;
                        }
                    }
                    else (*s)->pos.x--;
                }
            }
            else
            {
                if((*s)->a&TO_RIGHT)
                {
                    if((*s)->pos.x==(*s)->nbr_sprites.x-1)
                    {
                        if((*s)->pos.y==0)
                        {
                            if((*s)->a&REPEAT)
                            {
                                if(!((*s)->a&CYCLIC))
                                {
                                    invert_sense_anim(s);

                                    if((*s)->a&DIFFERENT && (*s)->nbr_sprites.x!=1 && (*s)->nbr_sprites.y!=1)
                                        (*s)->time_start -= (*s)->time_next;
                                }
                                else
                                {
                                    (*s)->pos.x = 0;
                                    (*s)->pos.y = (*s)->nbr_sprites.y-1;
                                }
                            }
                            else return false;
                        }
                        else
                        {
                            (*s)->pos.x = 0;
                            (*s)->pos.y--;
                        }
                    }
                    else (*s)->pos.x++;
                }
                else
                {
                    if((*s)->pos.x==0)
                    {
                        if((*s)->pos.y==0)
                        {
                            if((*s)->a&REPEAT)
                            {
                                if(!((*s)->a&CYCLIC))
                                {
                                    invert_sense_anim(s);

                                    if((*s)->a&DIFFERENT && (*s)->nbr_sprites.x!=1 && (*s)->nbr_sprites.y!=1)
                                        (*s)->time_start -= (*s)->time_next;
                                }
                                else
                                {
                                    (*s)->pos.x = (*s)->nbr_sprites.x-1;
                                    (*s)->pos.y = (*s)->nbr_sprites.y-1;
                                }
                            }
                            else return false;
                        }
                        else
                        {
                            (*s)->pos.x = (*s)->nbr_sprites.x-1;
                            (*s)->pos.y--;
                        }
                    }
                    else (*s)->pos.x--;
                }
            }
        }
    }

    (*s)->sprite_clip.x = (*s)->pos.x*(*s)->sprite_clip.w + (*s)->origin.x;
    (*s)->sprite_clip.y = (*s)->pos.y*(*s)->sprite_clip.h + (*s)->origin.y;

    return true;
}


bool draw_sprite(Sprites *s, SDL_Rect position)
{
    bool up;
    up = update_animation(s);

    if(up) SDL_BlitSurface(get_surface(*s), get_clip(*s), screen, &position);

    return up;
}


SDL_Surface* get_surface(Sprites s)
{
    return s->picture;
}


SDL_Rect* get_clip(Sprites s)
{
    return &(s->sprite_clip);
}


Point get_position(Sprites s)
{
    return s->pos;
}


Point get_nbr_sprites(Sprites s)
{
    return s->nbr_sprites;
}


void close_sprites(Sprites* s)
{
    if(s==NULL) error("close_sprites", "sprites.h", "the pointer Sprites (s) is NULL");

    (*s)->picture = NULL;

    free(*s);
}
