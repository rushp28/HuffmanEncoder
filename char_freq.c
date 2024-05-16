#include "char_freq.h"

CharFreq* createCharFreqs(const char text[])
{
    CharFreq* pNewCharFreqs = (CharFreq*)calloc(MAX_CHARACTERS, sizeof(CharFreq));
    if (pNewCharFreqs == NULL)
    {
        fprintf(stderr, "ERROR: Creating of Character Frequencies Failed!\nCAUSE: Memory Allocation for Character Frequencies Failed!\n");
        return NULL;
    }

    for (int decimalCharValue = 0; decimalCharValue < MAX_CHARACTERS; decimalCharValue++)
    {
        pNewCharFreqs[decimalCharValue].character = (char)decimalCharValue;
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
    if (pCharFreqs == NULL)
    {
        fprintf(stderr, "ERROR: Sorting of Character Frequencies Failed!\nCAUSE: Pointer to Character Frequencies Array is NULL!\n");
        return;
    }

    qsort(pCharFreqs, MAX_CHARACTERS, sizeof(CharFreq), compareCharFreqs);
}

void destroyCharFreqs(CharFreq* pCharFreqs)
{
    if (pCharFreqs == NULL)
    {
        fprintf(stderr, "ERROR: Destroying of Character Frequencies Failed!\nCAUSE: Pointer to Character Frequencies Array is NULL!\n");
        return;
    }

    free(pCharFreqs);
}
