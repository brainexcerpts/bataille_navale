#include "error.h"


void error(char* function, char* headers, char* msg_error)
{
    fprintf(stderr, "Error, in function %s (%s) : %s\n", function, headers, msg_error);
}


void warning(char* function, char* headers, char* msg_error)
{
    fprintf(stderr, "Warning, in function %s (%s) : %s\n", function, headers, msg_error);
}
