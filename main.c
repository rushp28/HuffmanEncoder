#include <stdio.h>

#include "char_info_node.h"
#include "hctn_queue.h"
#include "hc_tree.h"

#define MAX_TEXT_INPUT_SIZE 5000

int main()
{
    char pText[MAX_TEXT_INPUT_SIZE + 1] = {0};

    printf("Enter the Text (Upto %d Characters) you want to Encode: \n", MAX_TEXT_INPUT_SIZE);
    fgets(pText, MAX_TEXT_INPUT_SIZE + 1, stdin);
    if (pText[0] == '\n')
    {
        fprintf(stderr, "ERROR: Failed to Proceed!\nCAUSE: There was no Text Entered!\n");
        return 1;
    }

    CharInfoNode* pCharInfoNodeDictionary = createCharInfoNodeDictionary();
    if (!pCharInfoNodeDictionary)
    {
        return 1;
    }

    calculateCharFreqs(pText, pCharInfoNodeDictionary);
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
    if (pCharacterQueue->pFront->pNextNode == NULL)
    {
        fprintf(stderr, "ERROR: Failed to Proceed!\nCAUSE: There is only One Character in the Text!\n");
        freeCharInfoDictionary(pCharInfoNodeDictionary);
        freeHCTNQueue(pCharacterQueue);
        freeHCTNQueue(pInternalQueue);

        return 1;
    }

    HCTree* pHCTree = createHCTree();
    if (!pHCTree)
    {
        freeCharInfoDictionary(pCharInfoNodeDictionary);
        freeHCTNQueue(pCharacterQueue);
        freeHCTNQueue(pInternalQueue);

        return 1;
    }

    generateHCTree(pHCTree, pCharacterQueue, pInternalQueue);

    char huffmanCodeBuffer[MAX_CHARACTERS] = {0};
    assignHuffmanCodes(pHCTree->pRoot, pCharInfoNodeDictionary, huffmanCodeBuffer, 0);

    printCharInfoDictionary(pCharInfoNodeDictionary);

    encodeText(pText, pCharInfoNodeDictionary);

    freeCharInfoDictionary(pCharInfoNodeDictionary);
    freeHCTNQueue(pCharacterQueue);
    freeHCTNQueue(pInternalQueue);
    freeHCTree(pHCTree);

    return 0;
}