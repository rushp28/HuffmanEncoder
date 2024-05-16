#include <stdio.h>

#include "char_freq.h"
#include "hctn_queue.h"

int main()
{
    CharFreq* pCharFreqs = createCharFreqs("Hello, World!");
    if (!pCharFreqs)
    {
        return 1;
    }

    sortCharFreqs(pCharFreqs);

    HCTNQueue* pCharacterQueue = createHCTNQueue();
    HCTNQueue* pInternalQueue = createHCTNQueue();
    if (!pCharacterQueue || !pInternalQueue)
    {
        destroyCharFreqs(pCharFreqs);
        destroyHCTNQueue(pCharacterQueue);
        destroyHCTNQueue(pInternalQueue);

        return 1;
    }

    fillUpHCTNQueue(pCharacterQueue, pCharFreqs);

    destroyHCTNQueue(pCharacterQueue);
    destroyHCTNQueue(pInternalQueue);
    destroyCharFreqs(pCharFreqs);

    return 0;
}