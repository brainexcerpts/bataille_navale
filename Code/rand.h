#ifndef RAND_H
#define RAND_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
	Author : Claverie Paul
	Creation date :     23/03/2008
	Last modification : 23/03/2008


    init_rand_number()
    rand_number()

*/

// Init rand must be done inside main just one time
void init_rand_number(void);

// returns a random number between 0 and N-1
int rand_number(int n);

#endif
