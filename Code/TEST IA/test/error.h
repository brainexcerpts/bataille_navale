#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdlib.h>

/*
	Author : Claverie Paul
	Creation date :     23/03/2008
	Last modification : 23/03/2008
*/

void error(char* function, char* headers, char* msg_error);   /* affiche une erreur puis quitte le programme */
void warning(char* function, char* headers, char* msg_error); /* affiche une erreur */


#endif
