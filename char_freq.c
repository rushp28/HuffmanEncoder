#include "char_freq.h"

#include <stdio.h>

CharFreq* createCharFreqs(const char text[])
{
    CharFreq* pNewCharFreqs = (CharFreq*)calloc(MAX_CHARACTERS, sizeof(CharFreq));
    if (!pNewCharFreqs)
    {
        return NULL;
    }

    for (int characterValue = 0; characterValue < MAX_CHARACTERS; characterValue++)
    {
        pNewCharFreqs[characterValue].character = (char)characterValue;
    }

    for (int textIndex = 0; text[textIndex]!= '\0'; textIndex++)
    {
        unsigned char castedTextCharacter = (unsigned char)text[textIndex];

        if (isprint(castedTextCharacter))
        {
            pNewCharFreqs[castedTextCharacter].frequency++;
        }
    }

    return pNewCharFreqs;
}

int compareCharFreqs(const void* pVoidFirstCharFreq, const void* pVoidSecondCharFreq)
{
    CharFreq* pFirstCharFreq = (CharFreq*)pVoidFirstCharFreq;
    CharFreq* pSecondCharFreq = (CharFreq*)pVoidSecondCharFreq;

    return (pFirstCharFreq->frequency - pSecondCharFreq->frequency);
}

void sortCharFreqs(CharFreq* pCharFreqs)
{
    qsort(pCharFreqs, MAX_CHARACTERS, sizeof(CharFreq), compareCharFreqs);
}

void destroyCharFreqs(CharFreq* pCharFreqs)
{
    free(pCharFreqs);
}
