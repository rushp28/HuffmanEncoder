#include "char_info_node.h"

CharInfoNode* createCharInfoNodeDictionary()
{
    CharInfoNode* pCharInfoNodeDictionary = (CharInfoNode*)calloc(MAX_CHARACTERS, sizeof(CharInfoNode));
    if (pCharInfoNodeDictionary == NULL)
    {
        fprintf(stderr, "ERROR: Failed to Create Character Information Dictionary!\nCAUSE: Memory Allocation for pCharInfoNodeDictionary Failed!\n");
        return NULL;
    }

    for (int decimalCharValue = 0; decimalCharValue < MAX_CHARACTERS; decimalCharValue++)
    {
        pCharInfoNodeDictionary[decimalCharValue].character = (char)decimalCharValue;
    }

    return pCharInfoNodeDictionary;
}

void calculateCharFreqs(CharInfoNode* pCharInfoNodeDictionary, const char text[])
{
    if (pCharInfoNodeDictionary == NULL)
    {
        fprintf(stderr, "ERROR: Failed to Calculate Character Frequencies!\nCAUSE: Pointer to pCharInfoNodeDictionary is NULL!\n");
        return;
    }

    for (int textIndex = 0; text[textIndex] != '\0'; textIndex++)
    {
        unsigned char castedTextCharacter = (unsigned char)text[textIndex];

        if (isprint(castedTextCharacter))
        {
            pCharInfoNodeDictionary[castedTextCharacter].frequency++;
        }
    }
}

int compareCharFreqs(const void* pVoidFirstCharInfoNode, const void* pVoidSecondCharInfoNode)
{
    CharInfoNode* pFirstCharInfoNode = (CharInfoNode*)pVoidFirstCharInfoNode;
    CharInfoNode* pSecondCharInfoNode = (CharInfoNode*)pVoidSecondCharInfoNode;

    return (pFirstCharInfoNode->frequency - pSecondCharInfoNode->frequency);
}

void sortCharFreqs(CharInfoNode* pCharInfoNodeDictionary)
{
    if (pCharInfoNodeDictionary == NULL)
    {
        fprintf(stderr, "ERROR: Failed to Sort Character Frequencies!\nCAUSE: Pointer to pCharInfoNodeDictionary is NULL!\n");
        return;
    }

    qsort(pCharInfoNodeDictionary, MAX_CHARACTERS, sizeof(CharInfoNode), compareCharFreqs);
}

void assignHuffmanCodes(HCTNode* pHCTNode, CharInfoNode* pCharInfoNodeDictionary, const char* huffmanCode, int huffmanCodeLength)
{
    if (pHCTNode == NULL) return;

    // Allocate memory for the new huffmanCode string
    char* newHuffmanCode = calloc(1, huffmanCodeLength + 2); // +2 for the new bit and null terminator
    strncpy(newHuffmanCode, huffmanCode, huffmanCodeLength);
    newHuffmanCode[huffmanCodeLength] = '\0';

    // Recursive calls for left and right children
    if (pHCTNode->pLeftNode!= NULL)
    {
        newHuffmanCode[huffmanCodeLength] = '0';
        assignHuffmanCodes(pHCTNode->pLeftNode, pCharInfoNodeDictionary, newHuffmanCode, huffmanCodeLength + 1);
    }
    if (pHCTNode->pRightNode!= NULL)
    {
        newHuffmanCode[huffmanCodeLength] = '1';
        assignHuffmanCodes(pHCTNode->pRightNode, pCharInfoNodeDictionary, newHuffmanCode, huffmanCodeLength + 1);
    }

    // Check if leaf node and assign Huffman code
    if (pHCTNode->pLeftNode == NULL && pHCTNode->pRightNode == NULL) {
        unsigned char charIndex = (unsigned char)pHCTNode->character;
        for (int decimalCharIndex = 0; decimalCharIndex < MAX_CHARACTERS; ++decimalCharIndex)
        {
            if (pCharInfoNodeDictionary[decimalCharIndex].character == charIndex)
            {
                pCharInfoNodeDictionary[decimalCharIndex].huffmanCode = calloc(1, huffmanCodeLength + 1);

                strncpy(pCharInfoNodeDictionary[decimalCharIndex].huffmanCode, newHuffmanCode, huffmanCodeLength);
                pCharInfoNodeDictionary[decimalCharIndex].huffmanCode[huffmanCodeLength] = '\0';

                free(newHuffmanCode);
                break;
            }
        }
    }
    else
    {
        free(newHuffmanCode); // Free the temporary huffmanCode string if not assigned
    }
}

void freeCharInfoDictionary(CharInfoNode* pCharInfoNodeDictionary)
{
    if (pCharInfoNodeDictionary == NULL)
    {
        fprintf(stderr, "ERROR: Failed to Destroy Character Information Dictionary!\nCAUSE: Pointer to pCharInfoNodeDictionary is NULL!\n");
        return;
    }

    for (int decimalCharIndex = 0; decimalCharIndex < MAX_CHARACTERS; decimalCharIndex++)
    {
        if (pCharInfoNodeDictionary[decimalCharIndex].huffmanCode != NULL)
        {
            free(pCharInfoNodeDictionary[decimalCharIndex].huffmanCode);
        }
    }

    free(pCharInfoNodeDictionary);
}

void printCharInfoDictionary(CharInfoNode* pCharInfoNodeDictionary)
{
    if (pCharInfoNodeDictionary == NULL)
    {
        fprintf(stderr, "ERROR: Failed to Print Character Information Dictionary!\nCAUSE: Pointer to pCharInfoNodeDictionary is NULL!\n");
        return;
    }

    for (int decimalCharIndex = 0; decimalCharIndex < MAX_CHARACTERS; decimalCharIndex++)
    {
        if (pCharInfoNodeDictionary[decimalCharIndex].frequency > 0)
        {
            printf("Character: %c %d, Frequency: %d, Huffman Code: %s\n", pCharInfoNodeDictionary[decimalCharIndex].character, pCharInfoNodeDictionary[decimalCharIndex].character, pCharInfoNodeDictionary[decimalCharIndex].frequency, pCharInfoNodeDictionary[decimalCharIndex].huffmanCode);
        }
    }
}