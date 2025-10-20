#include "parser.h"
#include <stdio.h>

int main(void)
{
	char *test = "-50,0,20";
	char *ptr = test;
	double x = parse_double(&ptr);
	printf("x=%f, next='%s', nextchar='%c' (0x%x)\n", x, ptr, *ptr, (unsigned char)*ptr);
	return (0);
}
