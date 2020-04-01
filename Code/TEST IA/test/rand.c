#include "rand.h"


void init_rand_number(void)
{
    srand(time (NULL));
}


int rand_number(int n)
{
    return (int)(((float)(rand()) / RAND_MAX) * n);
}
