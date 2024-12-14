#include <stdio.h>

// Shows how the default shell of our system (bash, zsh, ...) tokenizes prompts
// e.g. ./a.out echo '"hello"'
// credits to @nbelouar
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