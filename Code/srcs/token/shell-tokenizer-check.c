#include <stdio.h>

// credits to @nbelouar
// shows how the default shell of our system tokenizes
// e.g. ./a.out echo '"hello"'
int main(int argc, char *argv[])
{
    int i;
    i = 0;
    printf("#");
    while(i < argc)
    {
        printf("%s#",argv[i]);
        i++;
    }
    printf("\n");
    return 0;
}