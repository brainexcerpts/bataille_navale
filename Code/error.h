#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdlib.h>

/**
	Author : Claverie Paul
	Creation date :     23/03/2008
	Last modification : 23/03/2008

	error()
	warning()

*/

// Print an error on stderr and exit
void error(char* function, char* headers, char* msg_error);

// Print an error on stderr
void warning(char* function, char* headers, char* msg_error);


#endif
