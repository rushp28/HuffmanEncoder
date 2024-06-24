#include <stdio.h>
#include <string.h>

#include "char_info_node.h"
#include "hctn_queue.h"
#include "hc_tree.h"

#define MAX_TEXT_INPUT_SIZE 5000
#define MAX_CHARACTERS 128

void clearInputBuffer()
{
    int character;
    while ((character = getchar()) != '\n' && character != EOF);
}

int main()
{
    char pText[MAX_TEXT_INPUT_SIZE + 1] = {0};
    CharInfoNode* pCharInfoNodeDictionary = createCharInfoNodeDictionary();
    HCTNQueue* pCharacterQueue = createHCTNQueue();
    HCTNQueue* pInternalQueue = createHCTNQueue();
    HCTree* pHCTree = createHCTree();
    char huffmanCodeBuffer[MAX_CHARACTERS] = {0};

    if (!pCharInfoNodeDictionary || !pCharacterQueue || !pInternalQueue || !pHCTree)
    {
        destroyCharInfoDictionary(pCharInfoNodeDictionary);
        destroyHCTNQueue(pCharacterQueue);
        destroyHCTNQueue(pInternalQueue);
        return 1;
    }

    fprintf(stdout, "-------------------------------------\nWELCOME TO RUSHP28'S HUFFMAN ENCODER\n-------------------------------------\n\n");
    fflush(stdout);

    fprintf(stdout, "Enter the Text (Up to %d Characters) you want to Encode: \n", MAX_TEXT_INPUT_SIZE);
    fflush(stdout);

    if (fgets(pText, MAX_TEXT_INPUT_SIZE + 1, stdin) == NULL || pText[0] == '\n')
    {
        fprintf(stderr, "ERROR: Failed to Proceed!\nCAUSE: There was no Text Entered or Input Error! Please rerun the app!\n");

        destroyCharInfoDictionary(pCharInfoNodeDictionary);
        destroyHCTNQueue(pCharacterQueue);
        destroyHCTNQueue(pInternalQueue);

        return 1;
    }

    // Check if the input length exceeds the limit
    size_t inputLength = strlen(pText);
    if (inputLength == MAX_TEXT_INPUT_SIZE && pText[inputLength - 1] != '\n')
    {
        fprintf(stderr, "ERROR: Input exceeds %d characters!\n",  strlen(pText));
        clearInputBuffer();

        destroyCharInfoDictionary(pCharInfoNodeDictionary);
        destroyHCTNQueue(pCharacterQueue);
        destroyHCTNQueue(pInternalQueue);

        return 1;
    }

    // Remove the newline character if present
    if (pText[inputLength - 1] == '\n')
    {
        pText[inputLength - 1] = '\0';
    }

    calculateCharFreqs(pText, pCharInfoNodeDictionary);
    sortCharFreqs(pCharInfoNodeDictionary);

    fillUpHCTNQueue(pCharacterQueue, pCharInfoNodeDictionary);
    if (pCharacterQueue->pFront->pNextNode == NULL)
    {
        fprintf(stderr, "ERROR: Failed to Proceed!\nCAUSE: There is only One Character in the Text! Please rerun the app!\n");
        destroyCharInfoDictionary(pCharInfoNodeDictionary);
        destroyHCTNQueue(pCharacterQueue);
        destroyHCTNQueue(pInternalQueue);

        return 1;
    }

    generateHCTree(pHCTree, pCharacterQueue, pInternalQueue);

    assignHuffmanCodes(pHCTree->pRoot, pCharInfoNodeDictionary, huffmanCodeBuffer, 0);

    fprintf(stdout, "\nHuffman Codes Generated!\n\n");
    fflush(stdout);

    printCharInfoDictionary(pCharInfoNodeDictionary);

    encodeText(pText, pCharInfoNodeDictionary);

    destroyCharInfoDictionary(pCharInfoNodeDictionary);
    destroyHCTNQueue(pCharacterQueue);
    destroyHCTNQueue(pInternalQueue);
    destroyHCTree(pHCTree);

    printf("\nPress Enter to Continue...");
    getchar();

    return 0;
}
