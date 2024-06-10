#include <stdio.h>

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
    char option = '1';

    if (!pCharInfoNodeDictionary || !pCharacterQueue || !pInternalQueue || !pHCTree)
    {
        destroyCharInfoDictionary(pCharInfoNodeDictionary);
        destroyHCTNQueue(pCharacterQueue);
        destroyHCTNQueue(pInternalQueue);
        return 1;
    }

    while (option != '4')
    {
        fprintf(stdout, "WELCOME TO RUSHP28'S HUFFMAN ENCODER\nPlease enter the required character to proceed with an operation!\n\n| 1 | -> Enter a New Text to Generate Huffman Codes\n| 2 | -> View Huffman Code Dictionary\n| 3 | -> Display Encoded Text\n| 4 | -> Exit\nOption: ");
        fgets(&option, 2, stdin);
        clearInputBuffer();
        fprintf(stdout, "\n");
        fflush(stdout);

        switch (option)
        {
            case '1':

                fprintf(stdout, "Enter the Text (Upto %d Characters) you want to Encode: \n", MAX_TEXT_INPUT_SIZE);
                fflush(stdout);
                fgets(pText, MAX_TEXT_INPUT_SIZE + 1, stdin);
                fprintf(stdout, "\nHuffman Codes Generated!\n\n");
                fflush(stdout);
                if (pText[0] == '\n')
                {
                    fprintf(stderr, "ERROR: Failed to Proceed!\nCAUSE: There was no Text Entered!\n");

                    break;
                }

                calculateCharFreqs(pText, pCharInfoNodeDictionary);
                sortCharFreqs(pCharInfoNodeDictionary);

                fillUpHCTNQueue(pCharacterQueue, pCharInfoNodeDictionary);
                if (pCharacterQueue->pFront->pNextNode == NULL)
                {
                    fprintf(stderr, "ERROR: Failed to Proceed!\nCAUSE: There is only One Character in the Text!\n");
                    destroyCharInfoDictionary(pCharInfoNodeDictionary);
                    destroyHCTNQueue(pCharacterQueue);
                    destroyHCTNQueue(pInternalQueue);

                    break;
                }

                generateHCTree(pHCTree, pCharacterQueue, pInternalQueue);

                assignHuffmanCodes(pHCTree->pRoot, pCharInfoNodeDictionary, huffmanCodeBuffer, 0);

                break;

            case '2':
                printCharInfoDictionary(pCharInfoNodeDictionary);

                break;

            case '3':
                encodeText(pText, pCharInfoNodeDictionary);

                break;
            default:
                break;
        }
    }

    destroyCharInfoDictionary(pCharInfoNodeDictionary);
    destroyHCTNQueue(pCharacterQueue);
    destroyHCTNQueue(pInternalQueue);
    destroyHCTree(pHCTree);

    return 0;
}