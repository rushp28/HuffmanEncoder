#ifndef M2_CHAR_FREQ_H
#define M2_CHAR_FREQ_H

#include <malloc.h>
#include <ctype.h>

#define MAX_CHARACTERS 128

typedef struct CharFreq {
    char character;
    int frequency;
} CharFreq;

CharFreq* createCharFreqs(const char text[]);

int compareCharFreqs(const void* pVoidFirstCharFreq, const void* pVoidSecondCharFreq);

void sortCharFreqs(CharFreq* pCharFreqs);

void destroyCharFreqs(CharFreq* pCharFreqs);

#endif //M2_CHAR_FREQ_H
