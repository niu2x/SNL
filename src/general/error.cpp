#include "error.h"
#include <stdio.h>
#include <stdlib.h>
void error(char *str, ...)
{
	if(str == 0)
		printf("error.\n");
	else
		vprintf(str, (char *)((int)(&str)+4));
	exit(1);
}