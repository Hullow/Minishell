#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
// compile with gcc -g -fsanitize=address leaks.c and run simply

int main()
{
    char *s = malloc(12);
    strcpy(s, "Hello world!");
    printf("string is: %s\n", s);
    return 0;
}
