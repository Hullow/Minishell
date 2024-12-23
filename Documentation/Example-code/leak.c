#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
	char *s = malloc(12);
	strcpy(s, "Hello world!");
	printf("string is : %s\n", s);	
	
	return 0;

}
