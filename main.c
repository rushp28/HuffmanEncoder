#include <stdio.h>

#include "char_freq.h"

int main()
{
    CharFreq* pCharFreqs = createCharFreqs("Hello, World!");

    if (!pCharFreqs)
    {
        printf("Error: Memory Allocation for Character Frequencies Failed!\n");
        return 1;
    }
    else
    {
        sortCharFreqs(pCharFreqs);
    }

    destroyCharFreqs(pCharFreqs);

    return 0;
}