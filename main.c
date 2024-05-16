#include <stdio.h>

#include "char_freq.h"
#include "hctn_queue.h"
#include "hc_tree.h"

int main()
{
    CharFreq* pCharFreqs = createCharFreqs("HHHIIIOOO!!!");
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

    HCTree* pHCTree = createHCTree();
    if (!pHCTree)
    {
        destroyCharFreqs(pCharFreqs);
        destroyHCTNQueue(pCharacterQueue);
        destroyHCTNQueue(pInternalQueue);

        return 1;
    }

    generateHCTree(pHCTree, pCharacterQueue, pInternalQueue);

    destroyCharFreqs(pCharFreqs);
    destroyHCTNQueue(pCharacterQueue);
    destroyHCTNQueue(pInternalQueue);
    destroyHCTree(pHCTree);

    return 0;
}