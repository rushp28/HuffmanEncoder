#include <stdio.h>

#include "char_info_node.h"
#include "hctn_queue.h"
#include "hc_tree.h"

int main()
{
    char* pText = "Hello, World! This is a test text. I am testing the Huffman coding algorithm.";

    CharInfoNode* pCharInfoNodeDictionary = createCharInfoNodeDictionary();
    if (!pCharInfoNodeDictionary)
    {
        return 1;
    }

    calculateCharFreqs(pCharInfoNodeDictionary, pText);
    sortCharFreqs(pCharInfoNodeDictionary);

    HCTNQueue* pCharacterQueue = createHCTNQueue();
    HCTNQueue* pInternalQueue = createHCTNQueue();
    if (!pCharacterQueue || !pInternalQueue)
    {
        freeCharInfoDictionary(pCharInfoNodeDictionary);
        freeHCTNQueue(pCharacterQueue);
        freeHCTNQueue(pInternalQueue);

        return 1;
    }

    fillUpHCTNQueue(pCharacterQueue, pCharInfoNodeDictionary);

    HCTree* pHCTree = createHCTree();
    if (!pHCTree)
    {
        freeCharInfoDictionary(pCharInfoNodeDictionary);
        freeHCTNQueue(pCharacterQueue);
        freeHCTNQueue(pInternalQueue);

        return 1;
    }

    generateHCTree(pHCTree, pCharacterQueue, pInternalQueue);

    assignHuffmanCodes(pHCTree->pRoot, pCharInfoNodeDictionary, "", 0);

    printCharInfoDictionary(pCharInfoNodeDictionary);

    encodeText(pText, pCharInfoNodeDictionary);

    freeCharInfoDictionary(pCharInfoNodeDictionary);
    freeHCTNQueue(pCharacterQueue);
    freeHCTNQueue(pInternalQueue);
    freeHCTree(pHCTree);

    return 0;
}